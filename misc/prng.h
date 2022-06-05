static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}


static uint64_t prng_seed[2]={11,-11};

uint64_t xoroshiro128(void) {
	const uint64_t s0 = prng_seed[0];
	uint64_t s1 = prng_seed[1];
	const uint64_t result = s0 + s1;

	s1 ^= s0;
	prng_seed[0] = rotl(s0, 24) ^ s1 ^ (s1 << 16); // a, b
	prng_seed[1] = rotl(s1, 37); // c

	return result;
}
