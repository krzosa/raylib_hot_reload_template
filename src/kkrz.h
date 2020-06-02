/* My personal header file,
    contains typedefines, defines I like, useful functions etc.
*/

#pragma once
#include "stdint.h"

// function internal to the file(obj) its in
#define internal static
#define global_variable static
// persistent variable with local scope, for example global variable declared in main
#define local_persist static

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef float f32;
typedef double f64;
typedef int32_t bool32;
typedef Vector2 v2;

inline v2
operator*(const v2 a, const float scalar)
{
    v2 result;
    result.x = a.x * scalar;
    result.y = a.y * scalar;

    return result;
}

inline v2
operator+(const v2 a, const v2 b)
{
    v2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline v2
operator-(const v2 a, const v2 b)
{
    v2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline v2
operator-(const v2 a)
{
    v2 result;
    result.x = -a.x;
    result.y = -a.y;

    return result;
}

inline f32
Clamp(f32 val, f32 min, f32 max)
{
    if (val > max)
        return max;
    else if (val < min)
        return min;
    return val;
}

inline i32
Clamp(i32 val, i32 min, i32 max)
{
    if (val > max)
        return max;
    else if (val < min)
        return min;
    return val;
}

/* QUICK LOG */
#define LOGU32(number) TraceLog(LOG_INFO, "%u", number)
#define LOGI32(number) TraceLog(LOG_INFO, "%d", number)
#define LOGF32(number) TraceLog(LOG_INFO, "%f", number)

/* TIMER */
global_variable f64 globalTimer = 0;

internal void StartTimer()
{
    globalTimer = GetTime();
}

internal double StopTimer()
{
    return GetTime() - globalTimer;
}
/*  */