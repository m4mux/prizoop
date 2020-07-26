#pragma once

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#include "fxcg\display.h"
#include "fxcg\keyboard.h"
#include "fxcg\file.h"
#include "fxcg\registers.h"
#include "fxcg\rtc.h"
#include "fxcg\system.h"
#include "fxcg\serial.h"
#include "fxcg\tmu.h"

#if TARGET_WINSIM
#define ALIGN(x) alignas(x)
#define LITTLE_E
#define FORCE_INLINE __forceinline
#define RESTRICT __restrict
#include <time.h>
#else
#define ALIGN(x) __attribute__((aligned(x)))
#define BIG_E
#define FORCE_INLINE __attribute__((always_inline)) inline
#define RESTRICT __restrict__
#include "fxcg_registers.h"
#include "fxcg\heap.h"
#define malloc sys_malloc
#define calloc sys_calloc
#define realloc sys_realloc
#define free sys_free

#endif

#ifdef LITTLE_E
static inline void EndianSwap(unsigned short& s) {
	s = ((s & 0xFF00) >> 8) | ((s & 0x00FF) << 8);
}
static inline void ShortSwap(unsigned int& s) {
	s = ((s & 0xFF00) >> 8) | ((s & 0x00FF) << 8);
}
static inline void EndianSwap(unsigned int& i) {
	i = ((i & 0xFF000000) >> 24) | ((i & 0x00FF0000) >> 8) | ((i & 0x0000FF00) << 8) | ((i & 0x000000FF) << 24);
}
#else
#define EndianSwap(...) 
#define ShortSwap(...) 
#endif

// compile time assert, will throw negative subscript error
#ifdef __GNUC__
#define CT_ASSERT(cond) static_assert(cond);
#else
#define CT_ASSERT(cond) typedef char check##__LINE__ [(cond) ? 1 : -1];
#endif

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#include "ScopeTimer.h"

extern void ScreenPrint(char* buffer);
extern void reset_printf();
#define printf(...) { char buffer[256]; memset(buffer, 0, 256); sprintf(buffer, __VA_ARGS__); ScreenPrint(buffer); }
