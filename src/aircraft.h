#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "wireprotocol.h"
#include "vector.h"
#define COPY(a,b) memcpy(a,b,sizeof(a))

struct TimeInterval_t
{
  char from;
  char to;
  TimeInterval_t(char _from, char _to):
  from(_from),to(_to){
  }
  TimeInterval_t reverse()
  {
    return TimeInterval_t(to,from);
  }
  TimeInterval_t intersect(TimeInterval_t t2)
  {
    return TimeInterval_t(max(from,t2.from),min(to,t2.to));
  }
  bool invalid(){
    return to<from;
  }
};
struct Results_t
{
  char time;
  int distance;
  Results_t(char _time,int _distance):
  time(_time),distance(_distance){
  };
};

struct aircraft_t
{
  char callsign[5];
  char type[4];
  Dim3::Point position;
  Dim3::Vector speed;
  float arate;

  float fractional(float a){
    return a-(int)a;
  }
  word fr_to_word(float a){
    return (word)(a*65536);
  }
  float fr_from_word(word a){
    return (float)(a)/65536;
  }
  void to_wire(wireprotocol_t &wire);
  bool from_wire(const wireprotocol_t &wire);
    Dim3::Point* calcfutures();
};

struct alertaircraft_t:
aircraft_t
{
  int distanceinmetres;
  short bearingindegrees;
  char remtime;
  unsigned long atime;
  enum category_t {
    NONE,FORMATION,NOTICE,WARNING,ALERT    };
  enum category_t category;

};

struct myaircraft_t:
public aircraft_t
{
  void calcalert(alertaircraft_t &otheraircraft);
  Results_t MinDistanceXY(Dim3::Point* p1, Dim3::Point* p2,TimeInterval_t &ti);
  Results_t MinDistanceZ(Dim3::Point* p1, Dim3::Point* p2,TimeInterval_t &ti);
  TimeInterval_t RAZTimeInterval(float s1, float v1, TimeInterval_t t);

};
#endif


