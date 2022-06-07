#pragma once
#include <limits.h>//CHAR_BIT
#define totypeof(t,x) ((typeof(t))x)
#define nthbit(num,nth) (totypeof(num,1)<<(nth))
#define togbit(num,nth) ((num)^=(nthbit(num,nth)))
#define setbit(num,nth) ((num)|=(nthbit(num,nth)))
#define clrbit(num,nth) ((num)&=(~(nthbit(num,nth))))
#define isbitset(num,nth) ((num)&(nthbit(num,nth)))
//masked operations
//merge maskbits from b to a
#define mergebits(a,b,mask) ((a)|=((b)& totypeof(b,mask)))
//toggle set maskbits from b in a
#define togbits(a,b,mask) ((a)^=((b)& totypeof(b,mask)))
//clear set maskbits from b in a
#define clrbits(a,b,mask) ((a)&=(~((b)& totypeof(b,mask))))
//get all set maskbits from b in a
#define getbits(a,b,mask)  ((a)&(((b)& totypeof(b,mask))))

//every array is a bitset
#define bitelemloc(arr,nth) ((nth)/(sizeof(arr[0])*CHAR_BIT))
#define bitpelemloc(arr,nth) ((nth)%((sizeof(arr[0])*CHAR_BIT)))
#define asetbit(arr, nth) setbit(arr[bitelemloc(arr,nth)],bitpelemloc(arr,nth))
#define atogbit(arr, nth) togbit(arr[bitelemloc(arr,nth)],bitpelemloc(arr,nth))
#define aclrbit(arr, nth) clrbit(arr[bitelemloc(arr,nth)],bitpelemloc(arr,nth))
#define isabitset(arr, nth) isbitset(arr[bitelemloc(arr,nth)],bitpelemloc(arr,nth))
