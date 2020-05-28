#pragma once
#include <stdint.h>

// function internal to the file(obj) its in
#define internal static
#define global_variable static
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

#if KKRZ_STANDALONE
struct Vector2
{
    f32 x;
    f32 y;
};
#endif
typedef Vector2 v2;

inline static v2 operator*(const v2 a, const float scalar)
{
    v2 result;
    result.x = a.x * scalar;
    result.y = a.y * scalar;

    return result;
}

inline static v2 operator+(const v2 a, const v2 b)
{
    v2 result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;

    return result;
}

inline static v2 operator-(const v2 a, const v2 b)
{
    v2 result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;

    return result;
}

inline static v2 operator-(const v2 a)
{
    v2 result;
    result.x = -a.x;
    result.y = -a.y;

    return result;
}

f32 clampFloat(f32 val, f32 min, f32 max)
{
    if (val > max)
        return max;
    else if (val < min)
        return min;
    return val;
}

i32 clampInt(i32 val, i32 min, i32 max)
{
    if (val > max)
        return max;
    else if (val < min)
        return min;
    return val;
}