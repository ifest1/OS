#ifndef STDINT_H__
#define STDINT_H__

// signed integers
typedef signed char             int8_t;
typedef short int               int16_t;
typedef long                    int32_t;
typedef long long               int64_t;

// unsigned integers
typedef unsigned char           uint8_t;
typedef unsigned short int      uint16_t;
typedef unsigned long           uint32_t;
typedef unsigned long long      uint64_t;

typedef int                     bool;

// limit macros
#define INT8_MIN                (-0x7f - 1)
#define INT16_MIN               (-0x7fff - 1)
#define INT32_MIN               (-0x7fffffff - 1)

#define true                    1
#define false                   0
#endif