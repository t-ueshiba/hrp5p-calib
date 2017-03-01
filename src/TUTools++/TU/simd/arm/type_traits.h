/*
 *  $id$
 */
#if !defined(__TU_SIMD_ARM_TYPE_TRAITS_H)
#define __TU_SIMD_ARM_TYPE_TRAITS_H

#include <arm_neon.h>

namespace TU
{
namespace simd
{
/************************************************************************
*  type traits								*
************************************************************************/
template <class T>	struct type_traits;

template <>
struct type_traits<int8_t> : type_traits_base<int8_t>
{
    typedef float		complementary_type;
    typedef complementary_type	complementary_mask_type;
    typedef int8x8_t		half_type;
    typedef int8x16_t		base_type;
};
    
template <>
struct type_traits<int16_t> : type_traits_base<int16_t>
{
    typedef float		complementary_type;
    typedef complementary_type	complementary_mask_type;
    typedef int16x4_t		half_type;
    typedef int16x8_t		base_type;
};
    
template <>
struct type_traits<int32_t> : type_traits_base<int32_t>
{
    typedef float		complementary_type;
    typedef complementary_type	complementary_mask_type;
    typedef int32x2_t		half_type;
    typedef int32x4_t		base_type;
};
    
template <>
struct type_traits<int64_t> : type_traits_base<int64_t>
{
    typedef float		complementary_type;
    typedef complementary_type	complementary_mask_type;
    typedef int64x1_t		half_type;
    typedef int64x2_t		base_type;
};
    
template <>
struct type_traits<uint8_t> : type_traits_base<uint8_t>
{
    typedef float		complementary_type;
    typedef complementary_type	complementary_mask_type;
    typedef uint8x8_t		half_type;
    typedef uint8x16_t		base_type;
};
    
template <>
struct type_traits<uint16_t> : type_traits_base<uint16_t>
{
    typedef float		complementary_type;
    typedef complementary_type	complementary_mask_type;
    typedef uint16x4_t		half_type;
    typedef uint16x8_t		base_type;
};
    
template <>
struct type_traits<uint32_t> : type_traits_base<uint32_t>
{
    typedef float		complementary_type;
    typedef complementary_type	complementary_mask_type;
    typedef uint32x2_t		half_type;
    typedef uint32x4_t		base_type;
};
    
template <>
struct type_traits<uint64_t> : type_traits_base<uint64_t>
{
    typedef float		complementary_type;
    typedef complementary_type	complementary_mask_type;
    typedef uint64x1_t		half_type;
    typedef uint64x2_t		base_type;
};

template <>
struct type_traits<float> : type_traits_base<float>
{
    typedef uint32_t		mask_type;
    typedef int32_t		complementary_type;
    typedef mask_type		complementary_mask_type;
    typedef float32x2_t		half_type;
    typedef float32x4_t		base_type;
};

template <class T> using half_type = typename type_traits<T>::half_type;
    
}	// namespace simd
}	// namespace TU
#endif	// !__TU_SIMD_ARM_TYPE_TRAITS_H
