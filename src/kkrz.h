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

typedef union v2
{
    struct
    {
        f32 x;
        f32 y;
    };

    struct
    {
        f32 width;
        f32 height;
    };
} v2;
