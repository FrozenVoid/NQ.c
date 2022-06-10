//not really great distribution but faster
static inline uint64_t rndbias(){
static uint64_t a=17;
a+=rotl(~a,7)^rotl(a,11);
a-=rotl(a,6)^rotl(~a,19);
return (uint32_t)a;}

static inline uint32_t mswsrange32(uint32_t maxval){
uint32_t a=(uint32_t)rndbias();
return (((uint64_t)a)*((uint64_t)maxval))>>32;
}
