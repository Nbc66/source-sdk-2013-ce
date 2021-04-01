/**
 *
 * math_proxy.cpp - Implements certain unresolved symbols and points them to their proper endpoints
 *
 */ 
#include <math.h>

#if __GNUC__ > 5

extern "C" float __powf_finite(float x, float y)
{
	return powf(x, y);
}

extern "C" double __atan2_finite(double y, double x)
{
	return atan2(y, x);
}

extern "C" float __logf_finite(float f)
{
	return logf(f);
}

extern "C" float __acosf_finite(float f)
{
	return acosf(f);
}

extern "C" double __exp_finite(double f)
{
	return exp(f);
}

extern "C" float __expf_finite(float f)
{
	return expf(f);
}

extern "C" double __pow_finite(double x, double y)
{
	return pow(x, y);
}

extern "C" double __log_finite(double f)
{
	return log(f);
}

#endif