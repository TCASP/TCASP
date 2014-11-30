#include "stdafx.h"
#include "aircraft.h"
#include <math.h>
#include "tcasalg.h"

#define COPY(a,b) memcpy(a,b,sizeof(a))
//convert aircraft state to wire representation
void aircraft_t::to_wire(wireprotocol_t &wire)
{
  COPY(wire.callsign,callsign);
  COPY(wire.type,type);
  wire.version=0;
  wire.longitude=(short)position.xy.x;
  wire.latitude=(short)position.xy.y;
  wire.height=(byte)(position.z/100);
  wire.speedns=(char)(speed.xy.y/2);
  wire.speedwe=(char)(speed.xy.x/2);
  wire.speedz=(char)(speed.z*10*.3048);
  wire.arate=(char)(arate*10);
  //	wire.cksum=wire.calcchecksum();
}
//convert aircraft state from wire representation
bool aircraft_t::from_wire(const wireprotocol_t &wire)
{
  if (wire.version!=0)
    return false;
  COPY(callsign,wire.callsign);
  COPY(type,wire.type);
  position=Dim3::Point(wire.longitude,wire.latitude,wire.height*100);
  speed=Dim3::Vector(wire.speedwe*2,wire.speedns*2,float(wire.speedz)/10/.3048);
  arate=(float(wire.arate))/10;
  return true;
}
//at 14 degrees latitude
//TODO calcilate at appropriate degrees
const float longitudemetres=108033.96/65536;
const float latitudemetres=110639.29/65536;

//modular arithmetic
inline short minminus(short a,short b)
{
  return a-b;
}
#define SECONDS 20

Dim3::Point* aircraft_t::calcfutures()
{
  Dim3::Point* f=new Dim3::Point[SECONDS+1];
  Dim3::Point* curf=f;
  Dim3::Point c_position(position);
  Dim3::VectorAC c_speed(speed);
  *curf++=c_position;
  for (int t=1;t<=SECONDS;t++)
  {
    c_position=c_position+c_speed;
    if (arate!=0)
    {
      c_speed.xy.bearing+=arate;
      c_speed.xy.updatecartesian();
    }
    *curf++=c_position;
  }
  return f;
}
Results_t myaircraft_t::MinDistanceXY(Dim3::Point* p1, Dim3::Point* p2,TimeInterval_t &ti)
{
  Results_t r(SECONDS+1,32767);
  bool first=true;
  for (char i=0;i<=SECONDS;i++)
  {
    if (i>=ti.from)
    {
      //error do modular math !!!
      Dim2::VectorAC v=(p1->xy-p2->xy);
      int distance=int(v.mod)%65536;
      if (first || distance<r.distance)
      {
        first=false;
        r.time=i;
        r.distance=distance;
      }
    }
    p1++;
    p2++;
  }
  return r;

}
Results_t myaircraft_t::MinDistanceZ(Dim3::Point* p1, Dim3::Point* p2,TimeInterval_t &ti)
{
  Results_t r(SECONDS+1,32767);
  bool first=true;
  for (char i=0;i<=SECONDS;i++)
  {
    if (i>=ti.from)
    {
      int distance=abs(p1->z-p2->z);
      if (first || distance<r.distance)
      {
        first=false;
        r.time=i;
        r.distance=distance;
      }
    }
    p1++;
    p2++;
  }
  return r;
}
TimeInterval_t myaircraft_t::RAZTimeInterval(float s1, float v1, TimeInterval_t t)
{
  if (v1==0)
    return t;
  float H=min(500,SECONDS*abs(v1));
  if (v1>0)
  {
    return TimeInterval_t((int)((- H - s1) / v1), (int)((500 - s1) / v1));
  }
  else
  {
    return TimeInterval_t((int)(( H - s1) / v1), (int)((-500 - s1) / v1));
  }
}
void myaircraft_t::calcalert(alertaircraft_t &otheraircraft)
{
  alertaircraft_t &a=otheraircraft;
  a.atime=millis();
  TimeInterval_t t(0, SECONDS);
  t = RAZTimeInterval(position.z - otheraircraft.position.z, speed.z - otheraircraft.speed.z, t);
  a.remtime=t.from;
  Dim2::VectorAC v=otheraircraft.position.xy-position.xy;
  a.distanceinmetres=int(v.mod)%65536;
  a.bearingindegrees=int((v.bearing-Dim2::VectorAC(speed.xy).bearing)*180/pi);

  if (t.invalid())
  {
    a.category=alertaircraft_t::NOTICE;
    return;
  }
  Dim3::Point* myfutures=calcfutures();
  Dim3::Point* oafutures=otheraircraft.calcfutures();
  Results_t distres=MinDistanceZ(myfutures,oafutures,t);
  if (distres.distance>1000)
  {
    a.category=alertaircraft_t::NOTICE;
    delete myfutures;
    delete oafutures;
    return;
  }

  distres=MinDistanceXY(myfutures,oafutures,t);
  a.remtime=distres.time;
  if (distres.distance>1000)
  {
    a.category=alertaircraft_t::NOTICE;
    delete myfutures;
    delete oafutures;
    return;
  }
  Dim2::VectorAC deltav=speed.xy-
    otheraircraft.speed.xy;
  if (int(deltav.mod/0.07)<distres.distance)
  {
    a.category=alertaircraft_t::FORMATION;
    delete myfutures;
    delete oafutures;
    return;
  }
  if (distres.time>20)
  {
    a.category=alertaircraft_t::NOTICE;
    delete myfutures;
    delete oafutures;
    return;
  }
  if (distres.time>15)
  {
    a.category=alertaircraft_t::WARNING;
    delete myfutures;
    delete oafutures;
    return;
  }
  if (distres.distance>500)
  {
    a.category=alertaircraft_t::WARNING;
    delete myfutures;
    delete oafutures;
    return;
  }
  a.category=alertaircraft_t::ALERT;
  delete myfutures;
  delete oafutures;
  return;
}

