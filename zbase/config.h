// Copyright (c) 2012 Junheng Zang. All Rights Reserved.
//
// System-wide configuration
//
#ifndef ZBASE__CONFIG_H
#define ZBASE__CONFIG_H

// Operating system
#if defined(linux) || defined(__linux) || defined(__linux__)
#	define ZBASE_OS "Linux"
#	define ZBASE_LINUX
#	define ZBASE_HAS_EPOLL
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#	define ZBASE_OS "Win32"
#	define ZBASE_WINDOWS
#endif

// Compiler related
#if defined(__GNUC__) || defined(__GLIBC__) 
#	define ZBASE_USE_GLIBC
#endif

// Word size
#if defined __WORDSIZE
#	define ZBASE_WORD_SIZE __WORDSIZE
#elif defined __x86_64__
#	define ZBASE_WORD_SIZE 64
#else
#	define ZBASE_WORD_SIZE 32
#endif

// SMP
#ifndef ZBASE_ARCH_SMP
//#	define ZBASE_ARCH_SMP
#endif

// Thread-safe
#define ZBASE_MULTITHREADS

// Support C99
#define ZBASE_C99
// Support C++11
#define ZBASE_CPP11

#define ZBASE_HAS_OCTETSTREAM_H

#endif // ZBASE__CONFIG_H

