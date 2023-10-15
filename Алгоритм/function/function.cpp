#include "pch.h"
#include "function.h"
#include <cmath>

double y(double x)
{
    double res = 0;
    for (int i = 1; i <= 5; i++)
    {
        res -= i * sin((i + 1) * x + i);
    }
    return res;
}

double characteristic(double m, double x1, double x2, double y1, double y2)
{
    return (m * (x2 - x1) + pow((y2 - y1), 2) / (m * (x2 - x1)) - 2 * (y2 + y1));
}

double shag(double m, double x1, double x2, double y1, double y2)
{
    return ((x1 + x2) / 2) - ((y2 - y1) / (2 * m));
}