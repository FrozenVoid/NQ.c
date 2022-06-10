#pragma once
/*
https://github.com/FrozenVoid/random.h
rnd(seed) return randomized seed->rndnum
rnd1() get random 64bit num
range(max) ^below max(0-max)
range32(max) same but for 32-bit(faster)

*/
#include <stdint.h>
static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

static inline uint64_t rnd(uint64_t a1){
static uint64_t a,b;
a+=a1;b+=~a+17;
a+=rotl(b,17)^rotl(a,3);
b+=rotl(a,13)^rotl(b,8);
return b;}

static inline uint64_t rnd1(){
static uint64_t a=17,b=~1;
a+=rotl(b,17)^rotl(a,3);
b+=rotl(a,13)^rotl(b,8);
return b;}


static inline uint64_t range(uint64_t maxval){
uint64_t a=rnd1();
return (((unsigned __int128)a)*((unsigned __int128)maxval))>>64;
}
static inline uint32_t range32(uint32_t maxval){
uint32_t a=(uint32_t)rnd1();
return (((uint64_t)a)*((uint64_t)maxval))>>32;
}
