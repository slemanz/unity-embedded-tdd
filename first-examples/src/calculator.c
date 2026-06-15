#include "calculator.h"
#include <limits.h>

int Calculator_Multiply(int a, int b)
{
    long long result = (long long)a * (long long)b;

    if (result > INT_MAX)
        return INT_MAX;

    return (int)result;
}
