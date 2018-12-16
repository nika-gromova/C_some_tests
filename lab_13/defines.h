#ifndef DEFINES_H
#define DEFINES_H

#include <math.h>
#define OK 0
#define INPUT_ERROR -1
#define OPEN_FILE_ERROR -2
#define READ_FILE_ERROR -3
#define MEMORY_ERROR -4
#define USAGE_ERROR -5

#define EPS 1e-10
#define IS_EQUAL(num1, num2) (fabs((num1) - (num2)) <= EPS)

#endif // DEFINES_H
