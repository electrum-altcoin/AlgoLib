#ifndef SCRYPT_H
#define SCRYPT_H

#ifdef __cplusplus
extern "C" {
#endif

extern void scrypt_1024_1_1_256(const char* input, char* output);
extern void scrypt_1024_1_1_256_sp(const char* input, char* output, char* scratchpad);
#define  scrypt_scratchpad_size 131583;

#ifdef __cplusplus
}
#endif

#endif
