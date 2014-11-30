#ifndef TCASALG_H
#define TCASALG_H
#include "vector.h"

struct Plane
{
  Dim3::Vector s;
  Dim3::Vector v;
};
static const int TAU=20;
static const double DMOD=0.3*1852;
static const int ZTHR=850;
//int ALIM=xxx;
static const int HMD=0;
struct RA
{
  //int FROM, TO;
  //int SL;

  //int FROM, TO;
  //int SL;
  //int TAU;
  //double DMOD;
  //int ZTHR;
  //int ALIM;
  //int HMD;
  //RA(int from, int to, int sl, int tau, double dmod, int zthr, int alim, int hmd);
  //	RA(int from, int to, int sl, int tau, double dmod, int zthr);
  static const RA& find(int alt,const RA*l);
  static  RA const RAlist[];
  static const RA& findRA(int alt);
  static  RA const TAlist[];
  static const RA& findTA(int alt);
  static bool Horizontal_RA(const Dim2::Vector &s2, const Dim2::Vector &v2);
  static bool Vertical_RA(const double &s1, const double &v1);
  static double root(const double &a, const double &b, const double &c, int epsilon);
  static double Delta(const Dim2::Vector &s2, const Dim2::Vector &v2, double D);
  static double Phi(const Dim2::Vector &s2, const Dim2::Vector &v2, int D, int epsilon);
  static bool CD2D(const Dim2::Vector &s2, const Dim2::Vector &v2, int D, int B);
  static bool TCASII_RA(const Dim3::Vector &s3, const Dim3::Vector &v3);
  static bool TCASII_RA_at(const Dim3::Vector &s3, const Dim3::Vector &v3, int t);
};
#endif

