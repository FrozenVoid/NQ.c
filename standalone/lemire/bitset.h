//amalgamation of https://github.com/lemire/cbitset/tree/master/src
#ifndef BITSET_H
#define BITSET_H
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#ifndef CBITSET_PORTABILITY_H
#define CBITSET_PORTABILITY_H
#include <stdint.h>

// For compatibility with MSVC with the use of `restrict`
#if (__STDC_VERSION__ >= 199901L) || (defined(__GNUC__) && defined(__STDC_VERSION__ ))
#define CBITSET_RESTRICT restrict
#else
#define CBITSET_RESTRICT
#endif // (__STDC_VERSION__ >= 199901L) || (defined(__GNUC__) && defined(__STDC_VERSION__ ))

#ifdef _MSC_VER
/* Microsoft C/C++-compatible compiler */
#include <intrin.h>

#ifndef __clang__ // if one compiles with MSVC *with* clang, then these intrinsics are defined!!!
// sadly there is no way to check whether we are missing these intrinsics specifically.

/* wrappers for Visual Studio built-ins that look like gcc built-ins */
/* result might be undefined when input_num is zero */
static inline int __builtin_ctzll(unsigned long long input_num) {
    unsigned long index;
#ifdef _WIN64 // highly recommended!!!
    _BitScanForward64(&index, input_num);
#else // if we must support 32-bit Windows
    if ((uint32_t)input_num != 0) {
        _BitScanForward(&index, (uint32_t)input_num);
    }
    else {
        _BitScanForward(&index, (uint32_t)(input_num >> 32));
        index += 32;
    }
#endif
    return index;
}

/* result might be undefined when input_num is zero */
static inline int __builtin_clzll(unsigned long long input_num) {
    unsigned long index;
#ifdef _WIN64 // highly recommended!!!
    _BitScanReverse64(&index, input_num);
#else // if we must support 32-bit Windows
    if (input_num > 0xFFFFFFF) {
        _BitScanReverse(&index, (uint32_t)(input_num >> 32));
    }
    else {
        _BitScanReverse(&index, (uint32_t)(input_num));
        index += 32;
    }
#endif
    return 63 - index;
}

/* result might be undefined when input_num is zero */
static inline int __builtin_clz(int input_num) {
    unsigned long index;
    _BitScanReverse(&index, input_num);
    return 31 - index;
}

/* result might be undefined when input_num is zero */
static inline int __builtin_popcountll(unsigned long long input_num) {
#if defined(_M_ARM64) || defined(_M_ARM)
  input_num = input_num - ((input_num >> 1) & 0x5555555555555555);
  input_num = (input_num & 0x3333333333333333) + ((input_num >> 2) & 0x3333333333333333);
  input_num = ((input_num + (input_num >> 4)) & 0x0F0F0F0F0F0F0F0F);
  return (uint32_t)((input_num * (0x0101010101010101)) >> 56);
#elif defined(_WIN64) // highly recommended!!!
    return (int)__popcnt64(input_num);
#else // if we must support 32-bit Windows
    return (int)(__popcnt((uint32_t)input_num) + __popcnt((uint32_t)(input_num >> 32)));
#endif
}

static inline void __builtin_unreachable() {
    __assume(0);
}
#endif
#endif
#endif


struct bitset_s {
    uint64_t * CBITSET_RESTRICT array;
    size_t arraysize;
    size_t capacity;

};

typedef struct bitset_s bitset_t;

/* Create a new bitset. Return NULL in case of failure. */
bitset_t *bitset_create( void );

/* Create a new bitset able to contain size bits. Return NULL in case of failure. */
bitset_t *bitset_create_with_capacity( size_t size );

/* Free memory. */
void bitset_free(bitset_t *bitset);

/* Set all bits to zero. */
void bitset_clear(bitset_t *bitset);

/* Create a copy */
bitset_t * bitset_copy(const bitset_t *bitset);

/* Resize the bitset. Return true in case of success, false for failure. Pad with zeroes new buffer areas if requested. */
bool bitset_resize( bitset_t *bitset,  size_t newarraysize, bool padwithzeroes );

/* returns how many bytes of memory the backend buffer uses */
static inline size_t bitset_size_in_bytes(const bitset_t *bitset) {
  return bitset->arraysize*sizeof(uint64_t);
}

/* returns how many bits can be accessed */
static inline size_t bitset_size_in_bits(const bitset_t *bitset) {
  return bitset->arraysize * 64;
}

/* returns how many words (64-bit) of memory the backend buffer uses */
static inline size_t bitset_size_in_words(const bitset_t *bitset) {
  return bitset->arraysize;
}


/* Grow the bitset so that it can support newarraysize * 64 bits with padding. Return true in case of success, false for failure. */
static inline bool bitset_grow( bitset_t *bitset,  size_t newarraysize ) {
  if (bitset->capacity < newarraysize) {
    uint64_t *newarray;
    bitset->capacity = newarraysize * 2;
    if ((newarray = (uint64_t *) realloc(bitset->array, sizeof(uint64_t) * bitset->capacity)) == NULL) {
      free(bitset->array);
      return false;
    }
    bitset->array = newarray;
  }
  memset(bitset->array + bitset->arraysize ,0,sizeof(uint64_t) * (newarraysize - bitset->arraysize));
  bitset->arraysize = newarraysize;
  return true; // success!
}

/* attempts to recover unused memory, return false in case of reallocation failure */
bool bitset_trim(bitset_t *bitset);

/* shifts all bits by 's' positions so that the bitset representing values 1,2,10 would represent values 1+s, 2+s, 10+s */
void bitset_shift_left(bitset_t *bitset, size_t s);

/* shifts all bits by 's' positions so that the bitset representing values 1,2,10 would represent values 1-s, 2-s, 10-s, negative values are deleted */
void bitset_shift_right(bitset_t *bitset, size_t s);

/* Set the ith bit. Attempts to resize the bitset if needed (may silently fail) */
static inline void bitset_set(bitset_t *bitset,  size_t i ) {
  size_t shiftedi = i >> 6;
  if (shiftedi >= bitset->arraysize) {
    if( ! bitset_grow(bitset,  shiftedi + 1) ) {
        return;
    }
  }
  bitset->array[shiftedi] |= ((uint64_t)1) << (i % 64);
}

/* Set the ith bit to the specified value. Attempts to resize the bitset if needed (may silently fail) */
static inline void bitset_set_to_value(bitset_t *bitset,  size_t i, bool flag) {

  size_t shiftedi = i >> 6;
  uint64_t mask = ((uint64_t)1) << (i % 64);
  uint64_t dynmask = ((uint64_t)flag) << (i % 64);
   if ((shiftedi >= bitset->arraysize)) {
   hit("Overflowin in bitset");
    if( ! bitset_grow(bitset,  shiftedi + 1) ) {
        return;
    }
  }
  uint64_t w = bitset->array[shiftedi];
  w &= ~mask;
  w |= dynmask;
  //hit(bitset->array[shiftedi]!=w);
  bitset->array[shiftedi] = w;
}




/* Get the value of the ith bit.  */
static inline bool bitset_get(const bitset_t *bitset,  size_t i ) {
  size_t shiftedi = i >> 6;
  if (shiftedi >= bitset->arraysize) {
    return false;
  }
  return ( bitset->array[shiftedi] & ( ((uint64_t)1) << (i % 64))) != 0 ;
}

/* Count number of bits set.  */
size_t bitset_count(const bitset_t *bitset);

/* Find the index of the first bit set.  */
size_t bitset_minimum(const bitset_t *bitset);

/* Find the index of the last bit set.  */
size_t bitset_maximum(const bitset_t *bitset);


/* compute the union in-place (to b1), returns true if successful, to generate a new bitset first call bitset_copy */
bool bitset_inplace_union(bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2);

/* report the size of the union (without materializing it) */
size_t bitset_union_count(const bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2);

/* compute the intersection in-place (to b1), to generate a new bitset first call bitset_copy */
void bitset_inplace_intersection(bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2);

/* report the size of the intersection (without materializing it) */
size_t bitset_intersection_count(const bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2);


/* returns true if the bitsets contain no common elements */
bool bitsets_disjoint(const bitset_t * b1, const bitset_t * b2);

/* returns true if the bitsets contain any common elements */
bool bitsets_intersect(const bitset_t * b1, const bitset_t * b2);

/* returns true if b1 contains all of the set bits of b2 */
bool bitset_contains_all(const bitset_t * b1, const bitset_t * b2);


/* compute the difference in-place (to b1), to generate a new bitset first call bitset_copy */
void bitset_inplace_difference(bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2);

/* compute the size of the difference */
size_t  bitset_difference_count(const bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2) ;

/* compute the symmetric difference in-place (to b1), return true if successful, to generate a new bitset first call bitset_copy */
bool bitset_inplace_symmetric_difference(bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2);

/* compute the size of the symmetric difference  */
size_t  bitset_symmetric_difference_count(const bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2);

/* iterate over the set bits
 like so :
  for(size_t i = 0; nextSetBit(b,&i) ; i++) {
    //.....
  }
  */
static inline bool nextSetBit(const bitset_t *bitset, size_t *i) {
      size_t x = *i >> 6;
      if (x >= bitset->arraysize) {
        return false;
      }
      uint64_t w = bitset->array[x];
      w >>= (*i & 63);
      if (w != 0) {
        *i += __builtin_ctzll(w);
        return true;
      }
      x ++;
      while (x < bitset->arraysize) {
        w = bitset->array[x];
        if (w != 0) {
          *i = x * 64 + __builtin_ctzll(w);
          return true;
        }
        x ++;
      }
      return false;
}

/* iterate over the set bits
 like so :
   size_t buffer[256];
   size_t howmany = 0;
  for(size_t startfrom = 0; (howmany = nextSetBits(b,buffer,256, &startfrom)) > 0 ; startfrom++) {
    //.....
  }
  */
static inline size_t nextSetBits(const bitset_t *bitset, size_t *buffer, size_t capacity, size_t * startfrom) {
      if(capacity == 0) return 0;// sanity check
      size_t x = *startfrom >> 6;
      if (x >= bitset->arraysize) {
          return 0;// nothing more to iterate over
      }
      uint64_t w = bitset->array[x];
      w >>= (*startfrom & 63);
      size_t howmany = 0;
      size_t base = x << 6;
      while(howmany < capacity) {
            while (w != 0) {
              uint64_t t = w & (~w + 1);
              int r = __builtin_ctzll(w);
              buffer[howmany++] = r + base;
              if(howmany == capacity) goto end;
              w ^= t;
            }
            x += 1;
            if(x == bitset->arraysize) {
              break;
            }
            base += 64;
            w = bitset->array[x];
      }
      end:
      if(howmany > 0) {
        *startfrom = buffer[howmany - 1];
      }
      return howmany;
}

typedef bool (*bitset_iterator)(size_t value, void *param);

// return true if uninterrupted
static inline bool bitset_for_each(const bitset_t *b, bitset_iterator iterator, void *ptr) {
  size_t base = 0;
  for (size_t i = 0; i < b->arraysize; ++i ) {
    uint64_t w = b->array[i];
    while (w != 0) {
      uint64_t t = w & (~w + 1);
      int r = __builtin_ctzll(w);
      if(!iterator(r + base, ptr)) return false;
      w ^= t;
    }
    base += 64;
  }
  return true;
}

static inline void bitset_print(const bitset_t *b) {
  printf("{");
  for(size_t i = 0; nextSetBit(b,&i) ; i++) {
    printf("%zu, ",i);
  }
  printf("}");
}



#endif


/* Create a new bitset. Return NULL in case of failure. */
bitset_t *bitset_create() {
  bitset_t *bitset = NULL;
  /* Allocate the bitset itself. */
  if( ( bitset = (bitset_t*) malloc( sizeof( bitset_t ) ) ) == NULL ) {
      return NULL;
  }
  bitset->array = NULL;
  bitset->arraysize = 0;
  bitset->capacity = 0;
  return bitset;
}

/* Create a new bitset able to contain size bits. Return NULL in case of failure. */
bitset_t *bitset_create_with_capacity( size_t size ) {
  bitset_t *bitset = NULL;
  /* Allocate the bitset itself. */
  if( ( bitset = (bitset_t*) malloc( sizeof( bitset_t ) ) ) == NULL ) {
      return NULL;
  }
  bitset->arraysize = (size + sizeof(uint64_t) * 8 - 1) / (sizeof(uint64_t) * 8);
  bitset->capacity = bitset->arraysize;
  if ((bitset->array = (uint64_t *) calloc(bitset->arraysize, sizeof(uint64_t))) == NULL) {
    free( bitset);
    return NULL;
  }
  return bitset;
}

/* Create a copy */
bitset_t *bitset_copy( const bitset_t * bitset ) {
  bitset_t *copy = NULL;
  /* Allocate the bitset itself. */
  if( ( copy = (bitset_t*) malloc( sizeof( bitset_t ) ) ) == NULL ) {
      return NULL;
  }
  memcpy(copy,bitset,sizeof(bitset_t));
  copy->capacity = copy->arraysize;
  if ((copy->array = (uint64_t *) malloc(sizeof(uint64_t) * bitset->arraysize)) == NULL) {
    free(copy);
    return NULL;
  }
  memcpy(copy->array,bitset->array,sizeof(uint64_t) * bitset->arraysize);
  return copy;
}

void bitset_clear(bitset_t *bitset) {
  memset(bitset->array,0,sizeof(uint64_t) * bitset->arraysize);
}

void bitset_fill(bitset_t *bitset) {
  memset(bitset->array,0xff,sizeof(uint64_t) * bitset->arraysize);
}

void bitset_shift_left(bitset_t *bitset, size_t s) {
  size_t extra_words = s / 64;
  int inword_shift = s % 64;
  size_t as = bitset->arraysize;
  if(inword_shift == 0) {
    bitset_resize(bitset,as + extra_words, false);
    // could be done with a memmove
    for(size_t i = as + extra_words ; i > extra_words; i--) {
      bitset->array[i - 1] = bitset->array[i - 1 - extra_words];
    }
  } else {
    bitset_resize(bitset,as + extra_words + 1, true);
    bitset->array[as + extra_words] =
     bitset->array[as - 1] >> (64 - inword_shift);
    for(size_t i = as + extra_words ; i >= extra_words + 2; i--) {
      bitset->array[i - 1] = (bitset->array[i - 1 - extra_words] << inword_shift)
      | (bitset->array[i - 2 - extra_words]>>(64 - inword_shift));
    }
    bitset->array[extra_words] = bitset->array[0] <<  inword_shift;
  }
  for(size_t i = 0; i < extra_words; i++) {
    bitset->array[i] = 0;
  }
}


void bitset_shift_right(bitset_t *bitset, size_t s) {
  size_t extra_words = s / 64;
  int inword_shift = s % 64;
  size_t as = bitset->arraysize;
  if(inword_shift == 0) {
    // could be done with a memmove
    for(size_t i = 0 ; i < as - extra_words; i++) {
      bitset->array[i] = bitset->array[i + extra_words];
    }
    bitset_resize(bitset,as - extra_words, false);

  } else {
    for(size_t i = 0 ; i + extra_words + 1 < as ; i++) {
      bitset->array[i] = (bitset->array[i + extra_words] >> inword_shift)
      | (bitset->array[i + extra_words + 1] << (64 - inword_shift));
    }
    bitset->array[as - extra_words - 1] = (bitset->array[as - 1] >> inword_shift);
    bitset_resize(bitset,as - extra_words , false);
  }
}

/* Free memory. */
void bitset_free(bitset_t *bitset) {
  free(bitset->array);
  free(bitset);
}
/* Resize the bitset so that it can support newarraysize * 64 bits. Return true in case of success, false for failure. */
bool bitset_resize( bitset_t *bitset,  size_t newarraysize, bool padwithzeroes ) {
  size_t smallest = newarraysize < bitset->arraysize ? newarraysize : bitset->arraysize;
  if (bitset->capacity < newarraysize) {
    uint64_t *newarray;
    bitset->capacity = newarraysize * 2;
    if ((newarray = (uint64_t *) realloc(bitset->array, sizeof(uint64_t) * bitset->capacity)) == NULL) {
      free(bitset->array);
      return false;
    }
    bitset->array = newarray;
  }
  if (padwithzeroes && (newarraysize > smallest))
    memset(bitset->array + smallest,0,sizeof(uint64_t) * (newarraysize - smallest));
  bitset->arraysize = newarraysize;
  return true; // success!
}



size_t bitset_count(const bitset_t *bitset) {
    size_t card = 0;
    size_t k = 0;
    // assumes that long long is 8 bytes
    for(; k + 7 < bitset->arraysize; k+=8) {
        card += __builtin_popcountll(bitset->array[k]);
        card += __builtin_popcountll(bitset->array[k+1]);
        card += __builtin_popcountll(bitset->array[k+2]);
        card += __builtin_popcountll(bitset->array[k+3]);
        card += __builtin_popcountll(bitset->array[k+4]);
        card += __builtin_popcountll(bitset->array[k+5]);
        card += __builtin_popcountll(bitset->array[k+6]);
        card += __builtin_popcountll(bitset->array[k+7]);
    }
    for(; k + 3 < bitset->arraysize; k+=4) {
        card += __builtin_popcountll(bitset->array[k]);
        card += __builtin_popcountll(bitset->array[k+1]);
        card += __builtin_popcountll(bitset->array[k+2]);
        card += __builtin_popcountll(bitset->array[k+3]);
    }
    for(; k < bitset->arraysize; k++) {
        card += __builtin_popcountll(bitset->array[k]);
    }
    return card;
}


bool bitset_inplace_union(bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2) {
  size_t minlength = b1->arraysize < b2->arraysize ? b1->arraysize : b2->arraysize;
  for(size_t k = 0 ; k < minlength; ++k) {
    b1->array[k] |= b2->array[k];
  }
  if(b2->arraysize > b1->arraysize) {
     size_t oldsize = b1->arraysize;
     if(!bitset_resize( b1, b2->arraysize, false)) return false;
     memcpy(b1->array + oldsize, b2->array + oldsize, (b2->arraysize - oldsize) * sizeof(uint64_t));
  }
  return true;
}



size_t bitset_minimum(const bitset_t *bitset) {
  for(size_t k = 0; k < bitset->arraysize; k++) {
    uint64_t w = bitset->array[k];
    if ( w != 0 ) {
      return __builtin_ctzll(w) + k * 64;
    }
  }
  return 0;
}

size_t bitset_maximum(const bitset_t *bitset) {
  for(size_t k = bitset->arraysize ; k > 0 ; k--) {
    uint64_t w = bitset->array[k - 1];
    if ( w != 0 ) {
      return  63 - __builtin_clzll(w) + (k - 1) * 64;
    }
  }
  return 0;
}

/* Returns true if bitsets share no common elements, false otherwise.
 *
 * Performs early-out if common element found. */
bool bitsets_disjoint(const bitset_t * b1, const bitset_t * b2) {
  size_t minlength = b1->arraysize < b2->arraysize ? b1->arraysize : b2->arraysize;

  for(size_t k = 0; k < minlength; k++) {
    if((b1->array[k] & b2->array[k]) != 0)
      return false;
  }
  return true;
}


/* Returns true if bitsets contain at least 1 common element, false if they are
 * disjoint.
 *
 * Performs early-out if common element found. */
bool bitsets_intersect(const bitset_t * b1, const bitset_t * b2) {
  size_t minlength = b1->arraysize < b2->arraysize ? b1->arraysize : b2->arraysize;

  for(size_t k = 0; k < minlength; k++) {
    if((b1->array[k] & b2->array[k]) != 0)
      return true;
  }
  return false;
}

/* Returns true if b has any bits set in or after b->array[starting_loc]. */
static bool any_bits_set(const bitset_t * b, size_t starting_loc) {
  if(starting_loc >= b->arraysize) {
    return false;
  }
  for(size_t k = starting_loc; k < b->arraysize; k++) {
    if(b->array[k] != 0)
      return true;
  }
  return false;
}

/* Returns true if b1 has all of b2's bits set.
 *
 * Performs early out if a bit is found in b2 that is not found in b1. */
bool bitset_contains_all(const bitset_t * b1, const bitset_t * b2) {
 for(size_t k = 0; k < b1->arraysize; k++) {
    if((b1->array[k] & b2->array[k]) != b2->array[k]) {
      return false;
    }
  }
  if(b2->arraysize > b1->arraysize) {
    /* Need to check if b2 has any bits set beyond b1's array */
    return !any_bits_set(b2, b1->arraysize);
  }
  return true;
}

size_t bitset_union_count(const bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2) {
  size_t answer = 0;
  size_t minlength = b1->arraysize < b2->arraysize ? b1->arraysize : b2->arraysize;
  size_t k = 0;
  for( ; k + 3 < minlength; k += 4) {
    answer += __builtin_popcountll ( b1->array[k] | b2->array[k]);
    answer += __builtin_popcountll ( b1->array[k+1] | b2->array[k+1]);
    answer += __builtin_popcountll ( b1->array[k+2] | b2->array[k+2]);
    answer += __builtin_popcountll ( b1->array[k+3] | b2->array[k+3]);
  }
  for( ; k < minlength; ++k) {
    answer += __builtin_popcountll ( b1->array[k] | b2->array[k]);
  }
  if(b2->arraysize > b1->arraysize) {
    //k = b1->arraysize;
    for(; k + 3 < b2->arraysize; k+=4) {
      answer += __builtin_popcountll (b2->array[k]);
      answer += __builtin_popcountll (b2->array[k+1]);
      answer += __builtin_popcountll (b2->array[k+2]);
      answer += __builtin_popcountll (b2->array[k+3]);
    }
    for(; k < b2->arraysize; ++k) {
      answer += __builtin_popcountll (b2->array[k]);
    }
  } else {
    //k = b2->arraysize;
    for(; k  + 3 < b1->arraysize; k+=4) {
      answer += __builtin_popcountll (b1->array[k]);
      answer += __builtin_popcountll (b1->array[k+1]);
      answer += __builtin_popcountll (b1->array[k+2]);
      answer += __builtin_popcountll (b1->array[k+3]);
    }
    for(; k < b1->arraysize; ++k) {
      answer += __builtin_popcountll (b1->array[k]);
    }
  }
  return answer;
}

void bitset_inplace_intersection(bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2) {
  size_t minlength = b1->arraysize < b2->arraysize ? b1->arraysize : b2->arraysize;
  size_t k = 0;
  for( ; k < minlength; ++k) {
    b1->array[k] &= b2->array[k];
  }
  for(; k < b1->arraysize; ++k) {
    b1->array[k] = 0; // memset could, maybe, be a tiny bit faster
  }
}

size_t bitset_intersection_count(const bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2) {
  size_t answer = 0;
  size_t minlength = b1->arraysize < b2->arraysize ? b1->arraysize : b2->arraysize;
  for(size_t k = 0 ; k < minlength; ++k) {
    answer += __builtin_popcountll ( b1->array[k] & b2->array[k]);
  }
  return answer;
}

void bitset_inplace_difference(bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2) {
  size_t minlength = b1->arraysize < b2->arraysize ? b1->arraysize : b2->arraysize;
  size_t k = 0;
  for( ; k < minlength; ++k) {
    b1->array[k] &= ~ (b2->array[k]);
  }
}


size_t  bitset_difference_count(const bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2) {
  size_t minlength = b1->arraysize < b2->arraysize ? b1->arraysize : b2->arraysize;
  size_t k = 0;
  size_t answer = 0;
  for( ; k < minlength; ++k) {
    answer += __builtin_popcountll (b1->array[k] & ~ (b2->array[k]));
  }
  for( ; k < b1->arraysize ; ++k) {
    answer += __builtin_popcountll (b1->array[k]);
  }
  return answer;
}

bool bitset_inplace_symmetric_difference(bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2) {
  size_t minlength = b1->arraysize < b2->arraysize ? b1->arraysize : b2->arraysize;
  size_t k = 0;
  for( ; k < minlength; ++k) {
    b1->array[k] ^= b2->array[k];
  }
  if(b2->arraysize > b1->arraysize) {
     size_t oldsize = b1->arraysize;
     if(!bitset_resize( b1, b2->arraysize, false)) return false;
     memcpy(b1->array + oldsize, b2->array + oldsize, (b2->arraysize - oldsize) * sizeof(uint64_t));
  }
  return true;
}

size_t  bitset_symmetric_difference_count(const bitset_t * CBITSET_RESTRICT b1, const bitset_t * CBITSET_RESTRICT b2) {
  size_t minlength = b1->arraysize < b2->arraysize ? b1->arraysize : b2->arraysize;
  size_t k = 0;
  size_t answer = 0;
  for( ; k < minlength; ++k) {
    answer += __builtin_popcountll(b1->array[k] ^ b2->array[k]);
  }
  if(b2->arraysize > b1->arraysize) {
    for( ; k < b2->arraysize; ++k) {
      answer += __builtin_popcountll(b2->array[k]);
    }
  } else {
    for( ; k < b1->arraysize; ++k) {
      answer += __builtin_popcountll(b1->array[k]);
    }
  }
  return answer;
}



bool bitset_trim(bitset_t * bitset) {
  size_t newsize = bitset->arraysize;
  while(newsize > 0) {
    if(bitset->array[newsize - 1] == 0)
        newsize -= 1;
    else
        break;
  }
  if(bitset->capacity == newsize) return true; // nothing to do
  bitset->capacity = newsize;
  bitset->arraysize = newsize;
  uint64_t *newarray;
  if ((newarray = (uint64_t *) realloc(bitset->array, sizeof(uint64_t) * bitset->capacity)) == NULL) {
      free(bitset->array);
      return false;
  }
  bitset->array = newarray;
  return true;
}
