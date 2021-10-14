#ifndef MYAPPLICATION_PLATFORM_H
#define MYAPPLICATION_PLATFORM_H

#if defined(_WIN32) || defined(_WIN64)
#define OS_WIN
#elif defined(__linux__)
#define OS_LINUX
#endif

#endif //MYAPPLICATION_PLATFORM_H