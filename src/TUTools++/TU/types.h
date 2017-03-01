/*
 *  $Id: types.h 1953 2016-03-05 09:17:24Z ueshiba $
 */
/*!
  \mainpage	libTUTools++ - 配列，ベクトル，行列，画像等の基本的なデータ型とそれに付随したアルゴリズムを収めたライブラリ
  \anchor	libTUTools

  \section abstract 概要
  libTUTools++は，配列，ベクトル，行列，画像等の基本的なデータ型とそれ
  に付随したアルゴリズムを収めたライブラリである．現在実装されている主
  要なクラスおよび関数はおおまかに以下の分野に分類される．

  <b>1次元および2次元配列</b>
  - #TU::Array
  - #TU::Array2

  <b>ベクトルと行列および線形計算</b>
  - #TU::Vector
  - #TU::Matrix
  - #TU::LUDecomposition
  - #TU::Householder
  - #TU::QRDecomposition
  - #TU::TriDiagonal
  - #TU::BiDiagonal
  - #TU::SVDecomposition
  - #TU::BlockDiagonalMatrix
  - #TU::SparseMatrix
  - #TU::BandMatrix

  <b>非線形最適化</b>
  - #TU::NullConstraint
  - #TU::ConstNormConstraint
  - #TU::minimizeSquare(const F&, const G&, AT&, size_t, double)
  - #TU::minimizeSquareSparse(const F&, const G&, ATA&, IB, IB, size_t, double)

  <b>RANSAC</b>
  - #TU::ransac(const PointSet&, Model&, Conform, double)

  <b>グラフカット</b>
  - #boost::GraphCuts

  <b>動的計画法</b>
  - #TU::DP

  <b>点，直線，平面等の幾何要素とその変換</b>
  - #TU::Point1
  - #TU::Point2
  - #TU::Point3
  - #TU::HyperPlane
  - #TU::Normalize
  - #TU::Projectivity
  - #TU::Affinity
  - #TU::Rigidity
  - #TU::Homography
  - #TU::Affinity2
  - #TU::BoundingBox
  
  <b>投影の幾何</b>
  - #TU::IntrinsicBase
  - #TU::IntrinsicWithFocalLength
  - #TU::IntrinsicWithEuclideanImagePlane
  - #TU::Intrinsic
  - #TU::IntrinsicWithDistortion
  - #TU::CanonicalCamera
  - #TU::Camera
  
  <b>画素と画像</b>
  - #TU::RGB
  - #TU::BGR
  - #TU::RGBA
  - #TU::ABGR
  - #TU::ARGB
  - #TU::BGRA
  - #TU::YUV444
  - #TU::YUV422
  - #TU::YUV411
  - #TU::ImageLine
  - #TU::Image
  - #TU::GenericImage
  - #TU::ComplexImage
  - #TU::CCSImage
  - #TU::Movie

  <b>画像処理</b>
  - #TU::Rectify
  - #TU::EdgeDetector
  - #TU::CorrectIntensity
  - #TU::IntegralImage
  - #TU::DiagonalIntegralImage
  
  <b>画像に限らない信号処理</b>
  - #TU::Warp
  - #TU::Filter2
  - #TU::SeparableFilter2
  - #TU::IIRFilter
  - #TU::BidirectionalIIRFilter
  - #TU::BidirectionalIIRFilter2
  - #TU::DericheConvolver
  - #TU::DericheConvolver2
  - #TU::GaussianConvolver
  - #TU::GaussianConvolver2
  - #TU::BoxFilter
  - #TU::BoxFilter2
  - #TU::GuidedFilter
  - #TU::GuidedFilter2
  - #TU::FIRFilter
  - #TU::FIRGaussianConvolver
  - #TU::WeightedMedianFilter
  - #TU::TreeFilter

  <b>特殊データ構造</b>
  - #TU::List
  - #TU::Heap
  - #TU::PSTree
  - #TU::NDTree
  
  <b>Bezier曲線とBezier曲面</b>
  - #TU::BezierCurve
  - #TU::BezierSurface
  
  <b>B-spline曲線とB-spline曲面</b>
  - #TU::BSplineKnots
  - #TU::BSplineCurve
  - #TU::BSplineSurface
  
  <b>メッシュ</b>
  - #TU::Mesh

  <b>アルゴリズム</b>
  - #std::min(const T&, const T&, const T&)
  - #std::min(const T&, const T&, const T&, const T&)
  - #std::max(const T&, const T&, const T&)
  - #std::max(const T&, const T&, const T&, const T&)
  - #TU::pull_if(Iter, Iter, Pred)
  - #TU::diff(const T&, const T&)
  - #TU::op3x3(Iterator begin, Iterator end, OP op)
  - #TU::max3x3(P p, P q, P r)
  - #TU::min3x3(P p, P q, P r)
  - #TU::mopOpen(Iterator begin, Iterator end, size_t niter)
  - #TU::mopClose(Iterator begin, Iterator end, size_t niter)

  <b>関数オブジェクト</b>
  - #TU::generic_function
  - #TU::generic_binary_function
  - #TU::plus
  - #TU::minus
  - #TU::multiplies
  - #TU::divides
  - #TU::identity
  - #TU::plus_assign
  - #TU::minus_assign
  - #TU::multiplies_assign
  - #TU::divides_assign
  - #TU::modulus_assign
  - #TU::bit_and_assign
  - #TU::bit_or_assign
  - #TU::bit_xor_assign
  - #TU::equal_to
  - #TU::not_equal_to
  - #TU::less
  - #TU::greater
  - #TU::less_equal
  - #TU::greater_equal
  - #TU::square()
  - #TU::length()
  - #TU::sqdist()
  - #TU::dist()
  - #TU::gcd()
  - #TU::lcm()

  <b>反復子</b>
  - #TU::make_mbr_iterator()
  - #TU::make_first_iterator()
  - #TU::make_second_iterator()
  - #TU::fast_zip_iterator
  - #TU::assignment_iterator
  - #TU::assignment2_iterator
  - #TU::row_iterator
  - #TU::row2col
  - #TU::column_iterator
  - #TU::ring_iterator
  - #TU::multiplex_iterator
  - #TU::box_filter_iterator
  - #TU::iir_filter_iterator
  
  <b>マニピュレータ</b>
  - #TU::skipl(std::istream&)
  - #TU::IOManip
  - #TU::IManip1
  - #TU::OManip1
  - #TU::IOManip1
  - #TU::IManip2
  - #TU::OManip2

  <b>ストリーム
  - #TU::fdistream
  - #TU::fdostream
  - #TU::fdstream
  
  <b>シリアルインタフェース</b>
  - #TU::Serial
  - #TU::TriggerGenerator
  - #TU::PM16C_04
  - #TU::SHOT602

  <b>乱数発生器</b>
  - #TU::Random

  <b>SIMD命令</b>
  - #TU::simd::vec
  
  \file		types.h
  \brief	基本的なデータ型をグローバルな名前空間に追加
*/
#ifndef __TU_TYPES_H
#define __TU_TYPES_H

#if defined(WIN32) || defined(X64)
#  ifdef _USRDLL
#    define __PORT	__declspec(dllexport)
#  else
#    define __PORT	__declspec(dllimport)
#  endif
#  define _USE_MATH_DEFINES	    // <math.h>のM_PI等の定義を有効化
#  define _CRT_SECURE_NO_WARNINGS   // C標準関数使用時の警告を抑制
#  define _CRT_NONSTDC_NO_DEPRECATE // POSIX関数使用時の警告を抑制
#  define _SCL_SECURE_NO_WARNINGS   // C++標準関数使用時の警告を抑制

typedef unsigned int		size_t;		//!< 配列等のサイズを表す型
typedef unsigned char		u_char;		//!< 符号なし8bit整数
typedef unsigned short		u_short;	//!< 符号なし16bit整数
typedef unsigned int		u_int;		//!< 符号なし32bit整数
typedef unsigned long		u_long;		//!< 符号なし32/64bit整数
typedef signed char		int8_t;		//!< 符号付き8bit整数
typedef short			int16_t;	//!< 符号付き16bit整数
typedef int			int32_t;	//!< 符号付き32bit整数
typedef long long		int64_t;	//!< 符号付き64bit整数
typedef unsigned char		uint8_t;	//!< 符号なし8bit整数
typedef unsigned short		uint16_t;	//!< 符号なし16bit整数
typedef unsigned int		uint32_t;	//!< 符号なし32bit整数
typedef unsigned long long	uint64_t;	//!< 符号なし64bit整数
#else
#  define __PORT
#  include <sys/types.h>
#endif

typedef signed char		s_char;		//!< 符号付き8bit整数

#endif	//  !__TU_TYPES_H
