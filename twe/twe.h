#ifndef TWE_H
#define TWE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void twe_hash(const char* input, char* output, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif


