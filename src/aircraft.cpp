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
	wire.speedz=(char)(speed.z);
	wire.arate=(char)(arate*500);
	//	wire.cksum=wire.calcchecksum();
}
//convert aircraft state from wire representation
bool aircraft_t::from_wire(const wireprotocol_t &wire)
{
	if (wire.version!=0)
		return false;
	COPY(callsign,wire.callsign);
	COPY(type,wire.type);
	position=Dim3::Point(wire.longitude,wire.latitude,short(wire.height)*100);
	speed=Dim3::Vector(wire.speedwe*2,wire.speedns*2,wire.speedz);
	arate=(float(wire.arate))/500;
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

Results_t myaircraft_t::calcresults(alertaircraft_t &otheraircraft,const TimeInterval_t &ti)
{
	Results_t r(SECONDS+1,32767,32767);
	bool first=true;
	Dim3::Point c_position(position),o_position(otheraircraft.position);
	Dim3::VectorAC c_speed(speed),o_speed(otheraircraft.speed);
	for (char i=0;i<=SECONDS;i++)
	{
		if (i>ti.to)
			break;
		c_position=c_position+c_speed;
		if (arate!=0)
		{
			c_speed.xy.bearing+=arate;
			c_speed.xy.updatecartesian();
		}
		o_position=o_position+o_speed;
		if (otheraircraft.arate!=0)
		{
			o_speed.xy.bearing+=otheraircraft.arate;
			o_speed.xy.updatecartesian();
		}
		

		if (i>=ti.from)
		{
			Dim3::VectorAC v=(c_position-o_position);
			int distanceXY=int(v.xy.mod)%65536;
			int distanceZ=abs(v.z);
			if (first || distanceXY<r.distanceXY)
			{
				first=false;
				r.time=i;
				r.distanceXY=distanceXY;
				r.distanceZ=distanceZ;
			}
		}
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
	Dim2::VectorAC v=position.xy-otheraircraft.position.xy;
	a.distanceinmetres=int(v.mod)%65536;
	a.bearingindegrees=int((v.bearing-Dim2::VectorAC(speed.xy).bearing)*180/pi);

	if (t.invalid())
	{
		a.category=alertaircraft_t::NOTICE;
		return;
	}
	Results_t distres=calcresults(otheraircraft,t);


	if (distres.distanceZ>1000)
	{
		a.category=alertaircraft_t::NOTICE;
		return;
	}

	a.remtime=distres.time;
	if (distres.distanceXY>1000)
	{
		a.category=alertaircraft_t::NOTICE;
		return;
	}
	Dim2::VectorAC deltav=speed.xy-
		otheraircraft.speed.xy;
	if (int(deltav.mod/0.07)<distres.distanceXY)
	{
		a.category=alertaircraft_t::FORMATION;
		return;
	}
	if (distres.time>20)
	{
		a.category=alertaircraft_t::NOTICE;
		return;
	}
	if (distres.time>15)
	{
		a.category=alertaircraft_t::WARNING;
		return;
	}
	if (distres.distanceXY>500)
	{
		a.category=alertaircraft_t::WARNING;
		return;
	}
	a.category=alertaircraft_t::ALERT;
	return;
}

