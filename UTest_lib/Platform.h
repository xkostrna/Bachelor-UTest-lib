#ifndef UTEST_PLATFORM_H
#define UTEST_PLATFORM_H

#if defined(DOCKER)
#define PLATFORM_CONTAINER
#else
#define PLATFORM_USER
#endif

#endif
