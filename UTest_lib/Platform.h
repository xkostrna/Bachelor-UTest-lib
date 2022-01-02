#ifndef UTEST_PLATFORM_H
#define UTEST_PLATFORM_H

#if defined(DOCKER)
#define PLATFORM_CONTAINER
#else
#define PLATFORM_USER
#endif

#if defined (_WIN32) || (_WIN64)
#define WINDOWS
#elif defined (__unix__)
#define UNIX
#endif

#if !defined(WINDOWS) && !defined(UNIX)
#   error Platform not defined, please use Windows or Unix based OS.
#endif

#endif
