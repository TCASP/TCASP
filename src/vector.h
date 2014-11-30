#ifndef VECTOR_H
#define VECTOR_H

#include "stdafx.h"
#include <math.h>

const float SMALL_NUM=0.00000001; // anything that avoids division overflow

namespace Dim2
{
  struct Point
  {
    short x,y;
    Point(const short &_x,const short &_y):
    x(_x),y(_y){
    };
    //		Point(short _x,short _y):x(_x),y(_y){};
  };
struct Vector:
  Point
  {
    Vector(const short &_x,const short &_y):
    Point(_x,_y){
    };
    bool iszero() const;
    Vector Perpendicular()const;
  };
struct VectorAC:
  Point
  {
    VectorAC(const Vector &v):
    Point(v.x,v.y){
      updateangular();
    }
    VectorAC(const short &_x,const short &_y):
    Point(_x,_y){
      updateangular();
    };
    float mod;
    float modsquared;
    float bearing;
    void updateangular(){
      modsquared=(x*x)+(y*y);
      mod=sqrt(modsquared);
      bearing=atan2(y,x);
    }
    void updatecartesian(){
      x=mod*cos(bearing);
      y=-mod*sin(bearing);
    }
    bool iszero() const;
    Vector Perpendicular()const;
    //float bearing()const;
  };
  struct Line
  {
    Point P0,P1;
    Line(const Point &_P0,const Point &_P1);
  };
  struct Segment
  {
    Point P0,P1;
    Segment(const Point &_P0,const Point &_P1);
  };
  struct Track
  {
    Point P0;
    Vector v;
    Track(const Point &_P0,const Vector &_v);
  };
  Point operator + (const Point &p1,const Vector &p2);
  Point operator - (const Point &p1,const Vector &p2);
  Vector operator - (const Point &p1,const Point &p2);
  Vector operator - (const Vector &p1,const Vector &p2);
  Vector operator + (const Vector &p1,const Vector &p2);
  Vector operator * (const float &f,const Vector &vi);

  float dot(const Vector &p1, const Vector &p2);
  // dot product (3D) which allows vector operations in arguments

}
namespace Dim3
{
  struct Point
  {
    Dim2::Point xy;
    short z;
    //Point(const short &_x,const short &_y, const short &_z):xy(_x,_y),z(_z){}
    Point(short _x,short _y, short _z):
    xy(_x,_y),z(_z){
    }
    Point(const Dim2::Point &_xy,const short &_z):
    xy(_xy),z(_z){
    }
    Point():
    xy(0,0),z(0){
    }
  };
  struct Vector
  {
    Dim2::Vector xy;
    short z;
    Vector(short _x,short _y, short _z):
    xy(_x,_y),z(_z){
    }
    //Vector(const short &_x,const short &_y, const short &_z):xy(_x,_y),z(_z){}
    Vector(const Dim2::Vector &_xy,const short &_z):
    xy(_xy),z(_z){
    }
    Vector():
    xy(0,0),z(0){
    }
  };
  struct VectorAC
  {
    Dim2::VectorAC xy;
    short z;
    VectorAC(short _x,short _y, short _z):
    xy(_x,_y),z(_z){
    }
    //Vector(const short &_x,const short &_y, const short &_z):xy(_x,_y),z(_z){}
    VectorAC(const Dim2::Vector &_xy,const short &_z):
    xy(_xy),z(_z){
    }
    VectorAC(Dim3::Vector &v):
    xy(v.xy.x,v.xy.y),z(v.z){
    }
    VectorAC():
    xy(0,0),z(0){
    }
  };
  struct Line
  {
    Point P0,P1;
    Line(const Point &_P0,const Point &_P1);
  };
  struct Segment
  {
    Point P0,P1;
    Segment(const Point &_P0,const Point &_P1);
  };
  struct Track
  {
    Point P0;
    Vector v;
    Track(const Point &_P0,const Vector &_v);
    Track(){
    };
  };
  Point operator + (const Point &p1,const VectorAC &p2);
  Point operator + (const Point &p1,const Vector &p2);
  Point operator - (const Point &p1,const Vector &p2);
  Vector operator - (const Point &p1,const Point &p2);
  Vector operator - (const Vector &p1,const Vector &p2);
  Vector operator + (const Vector &p1,const Vector &p2);
  Vector operator * (const float &f,const Vector &vi);

}
#if OLDCODE

namespace Dim2
{
  struct Point
  {
    float x,y;
    Point(const float &_x,const float &_y):
    x(_x),y(_y){
    };
    //		Point(float _x,float _y):x(_x),y(_y){};
  };
struct Vector:
  Point
  {
    Vector(const float &_x,const float &_y):
    Point(_x,_y){
    };
    bool iszero() const;
    Vector Perpendicular()const;
  };
struct VectorAC:
  Point
  {
    VectorAC(const Vector &v):
    Point(v.x,v.y){
      updateangular();
    }
    VectorAC(const float &_x,const float &_y):
    Point(_x,_y){
      updateangular();
    };
    float mod;
    float modsquared;
    float bearing;
    void updateangular(){
      modsquared=(x*x)+(y*y);
      mod=sqrt(modsquared);
      bearing=atan2(y,x);
    }
    void updatecartesian(){
      x=mod*cos(bearing);
      y=-mod*sin(bearing);
    }
    bool iszero() const;
    Vector Perpendicular()const;
    //float bearing()const;
  };
  struct Line
  {
    Point P0,P1;
    Line(const Point &_P0,const Point &_P1);
  };
  struct Segment
  {
    Point P0,P1;
    Segment(const Point &_P0,const Point &_P1);
  };
  struct Track
  {
    Point P0;
    Vector v;
    Track(const Point &_P0,const Vector &_v);
  };
  Point operator + (const Point &p1,const Vector &p2);
  Point operator - (const Point &p1,const Vector &p2);
  Vector operator - (const Point &p1,const Point &p2);
  Vector operator - (const Vector &p1,const Vector &p2);
  Vector operator + (const Vector &p1,const Vector &p2);
  Vector operator * (const float &f,const Vector &vi);

  float dot(const Vector &p1, const Vector &p2);
  // dot product (3D) which allows vector operations in arguments

}
namespace Dim3
{
  struct Point
  {
    Dim2::Point xy;
    float z;
    //Point(const float &_x,const float &_y, const float &_z):xy(_x,_y),z(_z){}
    Point(float _x,float _y, float _z):
    xy(_x,_y),z(_z){
    }
    Point(const Dim2::Point &_xy,const float &_z):
    xy(_xy),z(_z){
    }
    Point():
    xy(0,0),z(0){
    }
  };
  struct Vector
  {
    Dim2::Vector xy;
    float z;
    Vector(float _x,float _y, float _z):
    xy(_x,_y),z(_z){
    }
    //Vector(const float &_x,const float &_y, const float &_z):xy(_x,_y),z(_z){}
    Vector(const Dim2::Vector &_xy,const float &_z):
    xy(_xy),z(_z){
    }
    Vector():
    xy(0,0),z(0){
    }
  };
  struct VectorAC
  {
    Dim2::VectorAC xy;
    float z;
    VectorAC(float _x,float _y, float _z):
    xy(_x,_y),z(_z){
    }
    //Vector(const float &_x,const float &_y, const float &_z):xy(_x,_y),z(_z){}
    VectorAC(const Dim2::Vector &_xy,const float &_z):
    xy(_xy),z(_z){
    }
    VectorAC(Dim3::Vector &v):
    xy(v.xy.x,v.xy.y),z(v.z){
    }
    VectorAC():
    xy(0,0),z(0){
    }
  };
  struct Line
  {
    Point P0,P1;
    Line(const Point &_P0,const Point &_P1);
  };
  struct Segment
  {
    Point P0,P1;
    Segment(const Point &_P0,const Point &_P1);
  };
  struct Track
  {
    Point P0;
    Vector v;
    Track(const Point &_P0,const Vector &_v);
    Track(){
    };
  };
  Point operator + (const Point &p1,const VectorAC &p2);
  Point operator + (const Point &p1,const Vector &p2);
  Point operator - (const Point &p1,const Vector &p2);
  Vector operator - (const Point &p1,const Point &p2);
  Vector operator - (const Vector &p1,const Vector &p2);
  Vector operator + (const Vector &p1,const Vector &p2);
  Vector operator * (const float &f,const Vector &vi);

}


#if OLDCODE
namespace Dim2
{
  struct Point
  {
    float x,y;
    Point(const float &_x,const float &_y):
    x(_x),y(_y){
    };
    //		Point(float _x,float _y):x(_x),y(_y){};
  };
struct Vector:
  Point
  {
    Vector(const float &_x,const float &_y):
    Point(_x,_y){
    };
    bool iszero() const;
    Vector Perpendicular()const;
  };
struct VectorAC:
  Point
  {
    VectorAC(const Vector &v):
    Point(v.x,v.y){
      updateangular();
    }
    VectorAC(const float &_x,const float &_y):
    Point(_x,_y){
      updateangular();
    };
    float mod;
    float modsquared;
    float bearing;
    void updateangular(){
      modsquared=(x*x)+(y*y);
      mod=sqrt(modsquared);
      bearing=atan2(y,x);
    }
    void updatecartesian(){
      x=mod*cos(bearing);
      y=-mod*sin(bearing);
    }
    bool iszero() const;
    Vector Perpendicular()const;
    //float bearing()const;
  };
  struct Line
  {
    Point P0,P1;
    Line(const Point &_P0,const Point &_P1);
  };
  struct Segment
  {
    Point P0,P1;
    Segment(const Point &_P0,const Point &_P1);
  };
  struct Track
  {
    Point P0;
    Vector v;
    Track(const Point &_P0,const Vector &_v);
  };
  Point operator + (const Point &p1,const Vector &p2);
  Point operator - (const Point &p1,const Vector &p2);
  Vector operator - (const Point &p1,const Point &p2);
  Vector operator - (const Vector &p1,const Vector &p2);
  Vector operator + (const Vector &p1,const Vector &p2);
  Vector operator * (const float &f,const Vector &vi);

  float dot(const Vector &p1, const Vector &p2);
  // dot product (3D) which allows vector operations in arguments

}
namespace Dim3
{
  struct Point
  {
    Dim2::Point xy;
    float z;
    //Point(const float &_x,const float &_y, const float &_z):xy(_x,_y),z(_z){}
    Point(float _x,float _y, float _z):
    xy(_x,_y),z(_z){
    }
    Point(const Dim2::Point &_xy,const float &_z):
    xy(_xy),z(_z){
    }
    Point():
    xy(0,0),z(0){
    }
  };
  struct Vector
  {
    Dim2::Vector xy;
    float z;
    Vector(float _x,float _y, float _z):
    xy(_x,_y),z(_z){
    }
    //Vector(const float &_x,const float &_y, const float &_z):xy(_x,_y),z(_z){}
    Vector(const Dim2::Vector &_xy,const float &_z):
    xy(_xy),z(_z){
    }
    Vector():
    xy(0,0),z(0){
    }
  };
  struct VectorAC
  {
    Dim2::VectorAC xy;
    float z;
    VectorAC(float _x,float _y, float _z):
    xy(_x,_y),z(_z){
    }
    //Vector(const float &_x,const float &_y, const float &_z):xy(_x,_y),z(_z){}
    VectorAC(const Dim2::Vector &_xy,const float &_z):
    xy(_xy),z(_z){
    }
    VectorAC(Dim3::Vector &v):
    xy(v.xy.x,v.xy.y),z(v.z){
    }
    VectorAC():
    xy(0,0),z(0){
    }
  };
  struct Line
  {
    Point P0,P1;
    Line(const Point &_P0,const Point &_P1);
  };
  struct Segment
  {
    Point P0,P1;
    Segment(const Point &_P0,const Point &_P1);
  };
  struct Track
  {
    Point P0;
    Vector v;
    Track(const Point &_P0,const Vector &_v);
    Track(){
    };
  };
  Point operator + (const Point &p1,const VectorAC &p2);
  Point operator + (const Point &p1,const Vector &p2);
  Point operator - (const Point &p1,const Vector &p2);
  Vector operator - (const Point &p1,const Point &p2);
  Vector operator - (const Vector &p1,const Vector &p2);
  Vector operator + (const Vector &p1,const Vector &p2);
  Vector operator * (const float &f,const Vector &vi);

}
#endif
namespace Dim2
{
  struct Point
  {
    float x,y;
    Point(const float &_x,const float &_y):
    x(_x),y(_y){
    };
    //		Point(float _x,float _y):x(_x),y(_y){};
  };
struct Vector:
  Point
  {
    Vector(const float &_x,const float &_y):
    Point(_x,_y){
    };
    bool iszero() const;
    Vector Perpendicular()const;
  };
struct VectorAC:
  Point
  {
    VectorAC(const Vector &v):
    Point(v.x,v.y){
      updateangular();
    }
    VectorAC(const float &_x,const float &_y):
    Point(_x,_y){
      updateangular();
    };
    float mod;
    float modsquared;
    float bearing;
    void updateangular(){
      modsquared=(x*x)+(y*y);
      mod=sqrt(modsquared);
      bearing=atan2(y,x);
    }
    void updatecartesian(){
      x=mod*cos(bearing);
      y=-mod*sin(bearing);
    }
    bool iszero() const;
    Vector Perpendicular()const;
    //float bearing()const;
  };
  struct Line
  {
    Point P0,P1;
    Line(const Point &_P0,const Point &_P1);
  };
  struct Segment
  {
    Point P0,P1;
    Segment(const Point &_P0,const Point &_P1);
  };
  struct Track
  {
    Point P0;
    Vector v;
    Track(const Point &_P0,const Vector &_v);
  };
  Point operator + (const Point &p1,const Vector &p2);
  Point operator - (const Point &p1,const Vector &p2);
  Vector operator - (const Point &p1,const Point &p2);
  Vector operator - (const Vector &p1,const Vector &p2);
  Vector operator + (const Vector &p1,const Vector &p2);
  Vector operator * (const float &f,const Vector &vi);

  float dot(const Vector &p1, const Vector &p2);
  // dot product (3D) which allows vector operations in arguments

}
namespace Dim3
{
  struct Point
  {
    Dim2::Point xy;
    float z;
    //Point(const float &_x,const float &_y, const float &_z):xy(_x,_y),z(_z){}
    Point(float _x,float _y, float _z):
    xy(_x,_y),z(_z){
    }
    Point(const Dim2::Point &_xy,const float &_z):
    xy(_xy),z(_z){
    }
    Point():
    xy(0,0),z(0){
    }
  };
  struct Vector
  {
    Dim2::Vector xy;
    float z;
    Vector(float _x,float _y, float _z):
    xy(_x,_y),z(_z){
    }
    //Vector(const float &_x,const float &_y, const float &_z):xy(_x,_y),z(_z){}
    Vector(const Dim2::Vector &_xy,const float &_z):
    xy(_xy),z(_z){
    }
    Vector():
    xy(0,0),z(0){
    }
  };
  struct VectorAC
  {
    Dim2::VectorAC xy;
    float z;
    VectorAC(float _x,float _y, float _z):
    xy(_x,_y),z(_z){
    }
    //Vector(const float &_x,const float &_y, const float &_z):xy(_x,_y),z(_z){}
    VectorAC(const Dim2::Vector &_xy,const float &_z):
    xy(_xy),z(_z){
    }
    VectorAC(Dim3::Vector &v):
    xy(v.xy.x,v.xy.y),z(v.z){
    }
    VectorAC():
    xy(0,0),z(0){
    }
  };
  struct Line
  {
    Point P0,P1;
    Line(const Point &_P0,const Point &_P1);
  };
  struct Segment
  {
    Point P0,P1;
    Segment(const Point &_P0,const Point &_P1);
  };
  struct Track
  {
    Point P0;
    Vector v;
    Track(const Point &_P0,const Vector &_v);
    Track(){
    };
  };
  Point operator + (const Point &p1,const VectorAC &p2);
  Point operator + (const Point &p1,const Vector &p2);
  Point operator - (const Point &p1,const Vector &p2);
  Vector operator - (const Point &p1,const Point &p2);
  Vector operator - (const Vector &p1,const Vector &p2);
  Vector operator + (const Vector &p1,const Vector &p2);
  Vector operator * (const float &f,const Vector &vi);

}
#endif


#endif


