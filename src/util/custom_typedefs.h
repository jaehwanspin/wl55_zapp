#ifndef __UTIL_CUSTOM_TYPEDEFS_H__
#define __UTIL_CUSTOM_TYPEDEFS_H__

#ifdef __cplusplus
extern "C"
{
#endif

#define APP_VERSION_MAJOR 0
#define APP_VERSION_MINOR 1
#define APP_VERSION_PATCH 0

typedef struct { char val[64]; } str8_64_t;
typedef struct { char val[32]; } str8_32_t;
typedef struct { char val[16]; } str8_16_t;
typedef struct { char val[8]; }  str8_8_t;

#ifdef __cplusplus
}

#else

#define nullptr 0

#endif

#endif