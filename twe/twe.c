#include <string.h>
#include <stdint.h>

#include "../sha3/sph_fugue.h"
#include "../sha3/sph_hamsi.h"
#include "../sha3/sph_panama.h"
#include "../sha3/sph_shavite.h"

void twe_hash(char* output, const char *input, uint32_t length)
{
    unsigned char hash[128];
    
    memset(hash, 0, 128);

    sph_fugue256_context ctx_fugue;
    sph_shavite256_context ctx_shavite;
    sph_hamsi256_context ctx_hamsi;
    sph_panama_context ctx_panama;
	  
    sph_fugue256_init(&ctx_fugue);
    sph_fugue256(&ctx_fugue, input, length);
    sph_fugue256_close(&ctx_fugue, hash);
    
    sph_shavite256_init(&ctx_shavite);
    sph_shavite256(&ctx_shavite, hash, 64);
    sph_shavite256_close(&ctx_shavite, hash + 64);
    
    sph_hamsi256_init(&ctx_hamsi);
    sph_hamsi256(&ctx_hamsi, hash + 64, 64);
    sph_hamsi256_close(&ctx_hamsi, hash);
    
    sph_panama_init(&ctx_panama);
    sph_panama(&ctx_panama, hash, 64);
    sph_panama_close(&ctx_panama, hash + 64);
    
    memcpy(output, hash + 64, 32);
}
