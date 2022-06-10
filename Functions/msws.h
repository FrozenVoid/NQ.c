static inline uint32_t msws() {
static uint64_t x = 0, w = 0, s = 0xb5ad4eceda1ce2a9;
   x *= x; x += (w += s); return x = (x>>32) | (x<<32);}

static inline uint32_t mswsrange32(uint32_t maxval){
uint32_t a=(uint32_t)msws();
return (((uint64_t)a)*((uint64_t)maxval))>>32;
}
