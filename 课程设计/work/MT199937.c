#include <stdio.h>

#define MT19937_N 624
#define MT19937_M 397
#define MT19937_R 31
#define MT19937_A 0x9908B0DFUL
#define MT19937_U 11
#define MT19937_S 7
#define MT19937_B 0x9D2C5680UL
#define MT19937_T 15
#define MT19937_C 0xEFC60000UL
#define MT19937_L 18
#define MT19937_F 1812433253UL

static unsigned int mt[MT19937_N];
static int index = MT19937_N + 1;

void mt19937_init(unsigned int seed) {
    mt[0] = seed;
    for (int i = 1; i < MT19937_N; i++) {
        mt[i] = (MT19937_F * (mt[i - 1] ^ (mt[i - 1] >> 30)) + i);
    }
}

unsigned int mt19937_generate() {
    if (index >= MT19937_N) {
        for (int i = 0; i < MT19937_N - MT19937_M; i++) {
            unsigned int x = (mt[i] & 0x80000000UL) | (mt[i + 1] & 0x7FFFFFFFUL);
            mt[i] = mt[i + MT19937_M] ^ (x >> 1) ^ ((x & 1) * MT19937_A);
        }
        for (int i = MT19937_N - MT19937_M; i < MT19937_N - 1; i++) {
            unsigned int x = (mt[i] & 0x80000000UL) | (mt[i + 1] & 0x7FFFFFFFUL);
            mt[i] = mt[i + (MT19937_M - MT19937_N)] ^ (x >> 1) ^ ((x & 1) * MT19937_A);
        }
        unsigned int x = (mt[MT19937_N - 1] & 0x80000000UL) | (mt[0] & 0x7FFFFFFFUL);
        mt[MT19937_N - 1] = mt[MT19937_M - 1] ^ (x >> 1) ^ ((x & 1) * MT19937_A);
        index = 0;
    }

    unsigned int y = mt[index++];
    y ^= (y >> MT19937_U);
    y ^= (y << MT19937_S) & MT19937_B;
    y ^= (y << MT19937_T) & MT19937_C;
    y ^= (y >> MT19937_L);

    return y;
}