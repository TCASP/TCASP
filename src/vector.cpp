#include "stdafx.h"
#include <math.h>
#include "vector.h"

namespace Dim2
{
  bool VectorAC::iszero()const  
  {
    return mod<SMALL_NUM;
  }
  Point operator + (const Point &p1,const Vector &p2)
  {
    Point v(p1.x+p2.x,p1.y+p2.y);
    return v;
  }
  Point operator - (const Point &p1,const Vector &p2)
  {
    Point v(p1.x-p2.x,p1.y-p2.y);
    return v;
  }

  Vector operator - (const Point &p1,const Point &p2)
  {
    Vector v(p1.x-p2.x,p1.y-p2.y);
    return v;
  }
  Vector operator - (const Vector &p1,const Vector &p2)
  {
    Vector v(p1.x-p2.x,p1.y-p2.y);
    return v;
  }
  Vector operator + (const Vector &p1,const Vector &p2)
  {
    Vector v(p1.x+p2.x,p1.y+p2.y);
    return v;
  }
  Vector operator * (const float &f,const Vector &vi)
  {
    Vector v(f*vi.x,f*vi.y);
    return v;
  }
  float dot(const Vector &p1, const Vector &p2)
  {
    return p1.x * p2.x + p1.y * p2.y;
  }
  Vector Vector::Perpendicular()const
  {
    Vector v(y,-x);
    return v;
  }
  Line::Line(const Point &_P0,const Point &_P1):
  P0(_P0),P1(_P1){
  }
  Segment::Segment(const Point &_P0,const Point &_P1):
  P0(_P0),P1(_P1){
  }
  Track::Track(const Point &_P0,const Vector &_v):
  P0(_P0),v(_v){
  }
};

namespace Dim3
{
  Point operator + (const Point &p1,const Vector &p2)
  {
    Point v(p1.xy+p2.xy,p1.z+p2.z);
    return v;
  }
  Point operator + (const Point &p1,const VectorAC &p2)
  {
    return p1+Vector(p2.xy.x,p2.xy.y,p2.z);
  }
  Vector operator - (const Point &p1,const Point &p2)
  {
    Vector v(p1.xy-p2.xy,p1.z-p2.z);
    return v;
  }
  Vector operator - (const Vector &p1,const Vector &p2)
  {
    Vector v(p1.xy-p2.xy,p1.z-p2.z);
    return v;
  }
  Line::Line(const Point &_P0,const Point &_P1):
  P0(_P0),P1(_P1){
  }
  Segment::Segment(const Point &_P0,const Point &_P1):
  P0(_P0),P1(_P1){
  }
  Track::Track(const Point &_P0,const Vector &_v):
  P0(_P0),v(_v){
  }
}

