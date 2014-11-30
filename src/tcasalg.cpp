#include "stdafx.h"
#include "tcasalg.h"
#if 0
//RA::RA(int from, int to, int sl, int tau, double dmod, int zthr, int alim, int hmd)
//{
//	FROM = from;
//	TO = to;
//	SL = sl;
//	TAU = tau;
//	DMOD = dmod * 1852;//convert to metres
//	ZTHR = zthr;
//	ALIM = alim;
//	HMD = (int)(hmd * .3048);//convert to metres
//}
//RA::RA(int from, int to, int sl, int tau, double dmod, int zthr)
//{
//	FROM = from;
//	TO = to;
//	SL = sl;
//	TAU = tau;
//	DMOD = dmod * 1852;//convert to metres
//	ZTHR = zthr;
//	ALIM = 0;
//	HMD = 0;
//}
//RA const RA::RAlist[] = {
//	RA(1000,2350,3,15,.2,600,300,1215),
//	RA(2350,5000,4,20,.35,600,300,2126),
//	RA(5000,10000,5,25,.55,600,350,3342),
//	RA(10000,20000,6,30,.8,600,400,4861),
//	RA(20000,42000,7,35,1.1,700,600,6683),
//	RA(42000,-1,7,35,1.1,800,700,6683)
//};
//const RA& RA::find(int alt,const RA*l)
//{
//	do
//	{
//		if (l->FROM != -1 && l->FROM > alt)
//			continue;
//		if (l->TO != -1 && l->TO < alt)
//			continue;
//		return *l;
//	}
//	while (l++->TO!=-1);
//#ifdef ARDUINO
//	while(1){}
//#else
//	throw 0;
//#endif
//}
//
//const RA& RA::findRA(int alt)
//{
//	return find(alt,RAlist);
//}
//RA const RA::TAlist[] = {
//	RA(-1,1000,2,20,.3,850),
//	RA(1000,2350,3,25,.33,850),
//	RA(2350,5000,4,30,.48,850),
//	RA(5000,10000,5,40,.75,850),
//	RA(10000,20000,6,45,.75,850),
//	RA(20000,42000,7,48,1.3,750),
//	RA(42000,-1,7,48,1.3,1200)
//};
//const RA& RA::findTA(int alt)
//{
//	return find(alt,TAlist);
//}
bool RA::Horizontal_RA(const Dim2::Vector &s2, const Dim2::Vector &v2)
{
  double TAUmod = 0;
  if (s2.modsquared > 10)
    TAUmod = ((DMOD * DMOD) - s2.modsquared) / Dim2::dot(s2, v2);
  return s2.mod < DMOD || (TAUmod > 0 && TAUmod <= TAU);
}
bool RA::Vertical_RA(const double  &s1, const double &v1)
{
  double cpatime = -s1 / v1;
  return abs(s1) < ZTHR || (cpatime > 0 && cpatime < TAU);
}
double RA::root(const double &a, const double &b, const double &c, int epsilon)
{
  double n = ((b * b) - (4 * a * c));
  if (a == 0 || n < 0)
    return 0;
  return (sqrt(n) * epsilon - b) / (2 * a);
}
double RA::Delta(const Dim2::Vector &s2, const Dim2::Vector &v2, double D)
{
  return (D * D * v2.modsquared) - pow(Dim2::dot(s2, v2.Perpendicular()), 2);
}
double RA::Phi(const Dim2::Vector &s2, const Dim2::Vector &v2, int D, int epsilon)
{
  return root(v2.modsquared, 2 * Dim2::dot(s2, v2), s2.modsquared - (D * D), epsilon);
}
bool RA::CD2D(const Dim2::Vector &s2, const Dim2::Vector &v2, int D, int B)
{
  if (v2.iszero() && s2.mod < D)
    return true;
  double delta = Delta(s2, v2, D);
  double phi = Phi(s2, v2, D, 1);
  if (!v2.iszero() && delta >= 0 && phi >= B)
    return true;
  return false;
}

bool RA::TCASII_RA(const Dim3::Vector &s3, const Dim3::Vector &v3)
{
  return Vertical_RA(s3.z, v3.z) && Horizontal_RA(s3.xy, v3.xy) && (HMD==0 || CD2D(s3.xy, v3.xy, HMD, 0));
}

bool RA::TCASII_RA_at(const Dim3::Vector &s3, const Dim3::Vector &v3, int t)
{
  const Dim2::Vector &s2t = s3.xy + (t * s3.xy);
  double s1t = s3.z + (t * s3.z);

  return Vertical_RA(s1t, s3.z) && Horizontal_RA(s2t, v3.xy) && (HMD==0 || CD2D(s3.xy, v3.xy, HMD, t));
}
/*	int tcpa(const Dim2::Vector &s2, const Dim2::Vector &v2)
 {
 return (int)(-Dim2::dot(s2, v2) / v2.modsquared);
 }
 int tstar(int B, int T, const Dim2::Vector &s2, const Dim2::Vector &v2, int tee)
 {
 return max(B, min(T, tcpa(s2, v2) - (tee / 2)));
 }
 int Time_Min_TAUmod(const Dim2::Vector &s2, const Dim2::Vector &v2, int B, int T)
 {
 if (Dim2::dot(s2 + (B * v2), v2) >= 0)
 return B;
 if (!v2.iszero())
 {
 double delta = Delta(s2, v2, DMOD);
 if (delta <= 0)
 {
 int taumin = (int)(2 * sqrt(-delta) / v2.modsquared);
 return tstar(B, T, s2, v2, taumin);
 }
 }
 if (Dim2::dot(s2 + (T * v2), v2) < 0)
 return T;
 return tstar(B, T, s2, v2, 0);
 }
 bool RA2D(const Dim2::Vector &s2, const Dim2::Vector &v2, int B, int T)
 {
 return (Delta(s2, v2, DMOD) >= 0 && (Dim2::dot(s2 + B * v2, v2) < 0) && (Dim2::dot(s2 + T * v2, v2) >= 0))
 || Horizontal_RA(s2 + Time_Min_TAUmod(s2, v2, B, T) * v2, v2);
 }
 struct TimeInterval
 {
 int t1, t2;
 TimeInterval(int b, int t)
 {
 t1 = b; t2 = t;
 }
 };
 TimeInterval RAD2DTimeInterval(const Dim2::Vector &s2, const Dim2::Vector &v2, int B, int T)
 {
 double a = v2.modsquared;
 double b = 2 * Dim2::dot(s2, v2) + TAU * a;
 double c = s2.modsquared + TAU * Dim2::dot(s2, v2) - (DMOD * DMOD);
 if ((int)a == 0 && s2.mod <= DMOD)
 return TimeInterval(B, T);
 int theta = (int)Phi(s2, v2, (int)DMOD, 1);
 if (s2.mod <= DMOD)
 return TimeInterval(B, theta);
 if (Dim2::dot(s2, v2) >= 0 || (b * b) - (4 * a * c) < 0)
 return TimeInterval(T + 1, 0);
 if (Delta(s2, v2, DMOD) >= 0)
 return  TimeInterval((int)root(a, b, c, -1), theta);
 return  TimeInterval((int)root(a, b, c, -1), (int)root(a, b, c, 1));
 }
 TimeInterval RA3DTimeInterval(Plane plane1, Plane plane2, int B, int T, bool hmdf)
 {
 Dim3::Vector s3 = plane1.s - plane2.s;
 Dim3::Vector v3 = plane1.v - plane2.v;
 
 const Dim2::Vector &s2;s2.x=s3.x;s2.y=s3.y;
 const Dim2::Vector &v2;v2.x=v3.x;v2.y=v3.y;
 double s1;s1.x=s3.z;
 double v1;v1.x=v3.z;
 
 TimeInterval NotPossible = TimeInterval(T, B);
 if (hmdf && !CD2D(s2, v2, HMD, B))
 return NotPossible;
 if (v1.iszero() && Dim1::mod(s1) > ZTHR)
 return NotPossible;
 TimeInterval tiz = RAZTimeInterval(s1, v1, B, T);//RAZTimeInterval
 if (tiz.t2 < B || T < tiz.t1)
 return NotPossible;
 TimeInterval ti = TimeInterval(max(B, tiz.t1), min(T, tiz.t2));
 TimeInterval tixy = RAD2DTimeInterval(s2, v2, B, T);
 TimeInterval ti12 = TimeInterval(max(ti.t1, min(ti.t2, tixy.t1)), max(ti.t1, min(ti.t2, tixy.t2)));
 if (tixy.t1 > tixy.t2 || tixy.t2 < ti.t1 || tixy.t1 > ti.t2)
 return NotPossible;
 if (hmdf && HMD < DMOD && Dim2::dot(s2 + tiz.t1 * v2, v2) >= 0 && Dim2::mod(s2 + tiz.t1 * v2) > HMD)
 return NotPossible;
 if (hmdf && HMD < DMOD)
 {
 int phi = (int)Phi(s2, v2, HMD, 1);
 int t3 = v2.iszero() ? T : max(B, min(phi, T));
 int t4 = min(ti12.t2, t3);
 return TimeInterval(ti12.t1, t4);
 }
 return ti12;
 }
 TimeInterval RAZTimeInterval(double s1, double v1, int B, int T)
 {
 if (v1.iszero())
 return new TimeInterval(B, T);
 double H = min(ZTHR, TAU * double.mod(v1));
 return TimeInterval((int)((-v1.sign * H - s1.x) / v1.x), (int)((v1.sign * ZTHR - s1.x) / v1.x));
 }
 bool RA3D(Plane p1, Plane p2, int B, int T)
 {
 var ti = RA3DTimeInterval(p1, p2, B, T, HMD>0);
 return (ti.t1 <= ti.t2);
 }*/

#endif

