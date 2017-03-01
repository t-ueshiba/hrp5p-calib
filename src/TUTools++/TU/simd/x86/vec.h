/*
 *  $Id$
 */
#if !defined(__TU_SIMD_X86_VEC_H)
#define __TU_SIMD_X86_VEC_H

#include "TU/simd/x86/arch.h"

#define _mm_set_epi64		_mm_set_epi64x
#define _mm_set1_epi64		_mm_set1_epi64x
#define _mm256_set_epi64	_mm256_set_epi64x
#define _mm256_set1_epi64	_mm256_set1_epi64x

namespace TU
{
namespace simd
{
/************************************************************************
*  SIMD vector types							*
************************************************************************/
#if defined(AVX2)
  typedef __m256i	ivec_t;		//!< 整数ベクトルのSIMD型
#elif defined(SSE2)  
  typedef __m128i	ivec_t;		//!< 整数ベクトルのSIMD型
#else
  typedef __m64		ivec_t;		//!< 整数ベクトルのSIMD型
#endif
    
#if defined(AVX)
  typedef __m256	fvec_t;		//!< floatベクトルのSIMD型
#elif defined(SSE)
  typedef __m128	fvec_t;		//!< floatベクトルのSIMD型
#else
  typedef char		fvec_t;		//!< ダミー
#endif

#if defined(AVX)
  typedef __m256d	dvec_t;		//!< doubleベクトルのSIMD型
#elif defined(SSE2)
  typedef __m128d	dvec_t;		//!< doubleベクトルのSIMD型
#else
  typedef char		dvec_t;		//!< ダミー
#endif

#if defined(SSE)
typedef vec<float>	F32vec;		//!< 32bit浮動小数点数ベクトル
#  if defined(SSE2)
typedef vec<double>	F64vec;		//!< 64bit浮動小数点数ベクトル
#  endif
#endif
    
/************************************************************************
*  Constructors of vec<T>						*
************************************************************************/
#define SIMD_CONSTRUCTOR_1(type)					\
    template <> inline							\
    vec<type>::vec(element_type a)					\
	:_base(SIMD_MNEMONIC(set1, SIMD_PREFIX(type), ,			\
			     SIMD_SIGNED(type))(a))			\
    {									\
    }									\
    template <> inline vec<type>&					\
    vec<type>::operator =(element_type a)				\
    {									\
	_base = SIMD_MNEMONIC(set1, SIMD_PREFIX(type), ,		\
			      SIMD_SIGNED(type))(a);			\
	return *this;							\
    }
#define SIMD_CONSTRUCTOR_2(type)					\
    template <> inline							\
    vec<type>::vec(element_type a0, element_type a1)			\
	:_base(SIMD_MNEMONIC(set, SIMD_PREFIX(type), ,			\
			     SIMD_SIGNED(type))(a1, a0))		\
    {									\
    }
#define SIMD_CONSTRUCTOR_4(type)					\
    template <> inline							\
    vec<type>::vec(element_type a0, element_type a1,			\
		   element_type a2, element_type a3)			\
	:_base(SIMD_MNEMONIC(set, SIMD_PREFIX(type), ,			\
			     SIMD_SIGNED(type))(a3, a2, a1, a0))	\
    {									\
    }
#define SIMD_CONSTRUCTOR_8(type)					\
    template <> inline							\
    vec<type>::vec(element_type a0, element_type a1,			\
		   element_type a2, element_type a3,			\
		   element_type a4, element_type a5,			\
		   element_type a6, element_type a7)			\
	:_base(SIMD_MNEMONIC(set,					\
			     SIMD_PREFIX(type), , SIMD_SIGNED(type))	\
	       (a7, a6, a5, a4,	a3, a2, a1, a0))			\
    {									\
    }
#define SIMD_CONSTRUCTOR_16(type)					\
    template <> inline							\
    vec<type>::vec(element_type a0,  element_type a1,			\
		   element_type a2,  element_type a3,			\
		   element_type a4,  element_type a5,			\
		   element_type a6,  element_type a7,			\
		   element_type a8,  element_type a9,			\
		   element_type a10, element_type a11,			\
		   element_type a12, element_type a13,			\
		   element_type a14, element_type a15)			\
	:_base(SIMD_MNEMONIC(set,					\
			     SIMD_PREFIX(type), , SIMD_SIGNED(type))	\
	       (a15, a14, a13, a12, a11, a10, a9, a8,			\
		 a7,  a6,  a5,  a4,  a3,  a2, a1, a0))			\
    {									\
    }
#define SIMD_CONSTRUCTOR_32(type)					\
    template <> inline							\
    vec<type>::vec(element_type a0,  element_type a1,			\
		   element_type a2,  element_type a3,			\
		   element_type a4,  element_type a5,			\
		   element_type a6,  element_type a7,			\
		   element_type a8,  element_type a9,			\
		   element_type a10, element_type a11,			\
		   element_type a12, element_type a13,			\
		   element_type a14, element_type a15,			\
		   element_type a16, element_type a17,			\
		   element_type a18, element_type a19,			\
		   element_type a20, element_type a21,			\
		   element_type a22, element_type a23,			\
		   element_type a24, element_type a25,			\
		   element_type a26, element_type a27,			\
		   element_type a28, element_type a29,			\
		   element_type a30, element_type a31)			\
	:_base(SIMD_MNEMONIC(set,					\
			     SIMD_PREFIX(type), , SIMD_SIGNED(type))	\
	       (a31, a30, a29, a28, a27, a26, a25, a24,			\
		a23, a22, a21, a20, a19, a18, a17, a16,			\
		a15, a14, a13, a12, a11, a10,  a9,  a8,			\
		 a7,  a6,  a5,  a4,  a3,  a2,  a1,  a0))		\
    {									\
    }

SIMD_CONSTRUCTOR_1(int8_t)
SIMD_CONSTRUCTOR_1(int16_t)
SIMD_CONSTRUCTOR_1(int32_t)
SIMD_CONSTRUCTOR_1(uint8_t)
SIMD_CONSTRUCTOR_1(uint16_t)
SIMD_CONSTRUCTOR_1(uint32_t)
#if defined(SSE2)
  SIMD_CONSTRUCTOR_1(int64_t)
  SIMD_CONSTRUCTOR_1(uint64_t)
#endif

#if defined(AVX2)
  SIMD_CONSTRUCTOR_32(int8_t)	
  SIMD_CONSTRUCTOR_16(int16_t)	
  SIMD_CONSTRUCTOR_8(int32_t)
  SIMD_CONSTRUCTOR_4(int64_t)
  SIMD_CONSTRUCTOR_32(uint8_t)	
  SIMD_CONSTRUCTOR_16(uint16_t)	
  SIMD_CONSTRUCTOR_8(uint32_t)
  SIMD_CONSTRUCTOR_4(uint64_t)
#elif defined(SSE2)
  SIMD_CONSTRUCTOR_16(int8_t)
  SIMD_CONSTRUCTOR_8(int16_t)
  SIMD_CONSTRUCTOR_4(int32_t)
  SIMD_CONSTRUCTOR_2(int64_t)
  SIMD_CONSTRUCTOR_16(uint8_t)
  SIMD_CONSTRUCTOR_8(uint16_t)
  SIMD_CONSTRUCTOR_4(uint32_t)
  SIMD_CONSTRUCTOR_2(uint64_t)
#else
  SIMD_CONSTRUCTOR_8(int8_t)
  SIMD_CONSTRUCTOR_4(int16_t)
  SIMD_CONSTRUCTOR_2(int32_t)
  SIMD_CONSTRUCTOR_8(uint8_t)
  SIMD_CONSTRUCTOR_4(uint16_t)
  SIMD_CONSTRUCTOR_2(uint32_t)
#endif

#if defined(SSE)
  SIMD_CONSTRUCTOR_1(float)
#  if defined(AVX)
  SIMD_CONSTRUCTOR_8(float)
#  else
  SIMD_CONSTRUCTOR_4(float)
#  endif
#endif

#if defined(SSE2)
  SIMD_CONSTRUCTOR_1(double)
#  if defined(AVX) 
  SIMD_CONSTRUCTOR_4(double)
#  else
  SIMD_CONSTRUCTOR_2(double)
#  endif
#endif

#undef SIMD_CONSTRUCTOR_1
#undef SIMD_CONSTRUCTOR_2
#undef SIMD_CONSTRUCTOR_4
#undef SIMD_CONSTRUCTOR_8
#undef SIMD_CONSTRUCTOR_16
#undef SIMD_CONSTRUCTOR_32

/************************************************************************
*  Control functions							*
************************************************************************/
inline void	empty()	{ _mm_empty(); }

}	// namespace simd
}	// namespace TU
#endif	// !__TU_SIMD_X86_VEC_H
