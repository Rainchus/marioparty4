#ifndef _MATH_H
#define _MATH_H

#define M_PI 3.141592653589793

#ifdef MATH_EXPORT_CONST
extern inline float sqrtf(float x)
{
	static const double _half=.5;
	static const double _three=3.0;
	volatile float y;
	if(x > 0.0f)
	{
		double guess = __frsqrte((double)x);   // returns an approximation to
		guess = _half*guess*(_three - guess*guess*x);  // now have 12 sig bits
		guess = _half*guess*(_three - guess*guess*x);  // now have 24 sig bits
		guess = _half*guess*(_three - guess*guess*x);  // now have 32 sig bits
		y=(float)(x*guess);
		return y;
	}
	return x;
}
#else
extern inline float sqrtf(float x)
{
	volatile float y;
	if(x > 0.0f)
	{
		double guess = __frsqrte((double)x);   // returns an approximation to
		guess = 0.5*guess*(3.0 - guess*guess*x);  // now have 12 sig bits
		guess = 0.5*guess*(3.0 - guess*guess*x);  // now have 24 sig bits
		guess = 0.5*guess*(3.0 - guess*guess*x);  // now have 32 sig bits
		y=(float)(x*guess);
		return y;
	}
	return x;
}
#endif
double atan(double x);
double copysign(double x, double y);
double cos(double x);
double floor(double x);
double frexp(double x, int *exp);
double ldexp(double x, int exp);
double modf(double x, double *intpart);
double sin(double x);
double tan(double x);
double acos(double x);
double asin(double x);
double atan2(double y, double x);
double fmod(double x, double y);
double log(double x);
float tanf(float x);
float sinf(float x);
float cosf(float x);
float atan2f(float y, float x);
float acosf(float x);

#define abs(x) __abs(x)

#endif
