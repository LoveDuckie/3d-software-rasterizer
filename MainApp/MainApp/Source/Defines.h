#pragma once
#if defined _UNICODE
#ifndef STR
#define STR(x) L##x
typedef wchar_t tchar;
#define tstrlen wcslen
#endif
#else
#ifndef STR
#define STR(x) x
typedef char tchar;
#define tstrlen strlen
#endif
#endif

#ifndef APP_FORCEINLINE
#define APP_FORCEINLINE __forceinline
#endif

#ifndef APP_INLINE
#define APP_INLINE inline
#endif

#ifndef PLATFORM_NAME
#ifdef WIN32
#define PLATFORM_NAME WINDOWS
#endif
#endif

#ifndef PLATFORM_ARCHITECTURE
#ifdef _WIN32
#define PLATFORM_ARCHITECTURE WIN32
#elif _WIN64
#define PLATFORM_ARCHITECTURE WIN64
#endif
#endif

#if defined(PLATFORM_ARCHITECTURE)
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;
typedef double float64;
typedef float float32;
#else
#error Error: the platform architecture was not defined.
#endif