#pragma once

#ifdef FUNCTION_LIB_EXPORTS
#define FUNCTION_LIB_API _declspec(dllexport)
#else
#define FUNCTION_LIB_API _declspec(dllimport)
#endif

extern "C" FUNCTION_LIB_API double y(double x);
extern "C" FUNCTION_LIB_API double characteristic(double m, double x1, double x2, double y1, double y2);
extern "C" FUNCTION_LIB_API double shag(double m, double x1, double x2, double y1, double y2);