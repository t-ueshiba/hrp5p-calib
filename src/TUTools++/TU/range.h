/*
 *  $Id$
 */
/*!
  \file		range.h
  \brief	2つの反復子によって指定されるレンジの定義と実装
*/
#ifndef __TU_RANGE_H
#define __TU_RANGE_H

#include <iostream>
#include <cstddef>	// for size_t
#include <cassert>
#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <boost/iterator/iterator_adaptor.hpp>

namespace std
{
#if __cplusplus < 201700L
/************************************************************************
*  function std::size(T)						*
************************************************************************/
template <class T> inline size_t
size(const T& x)
{
    return x.size();
}
template <class T, size_t N> inline constexpr size_t
size(const T (&array)[N]) noexcept
{
    return N;
}
#endif
}	// namespace std

namespace TU
{
/************************************************************************
*  predicate is_range<E>						*
************************************************************************/
namespace impl
{
  struct is_range
  {
      template <class E> static auto
      check(const E& x) -> decltype(x.begin(), x.end(),
				    std::true_type())			;
      static std::false_type
      check(...)							;
  };
}	// namespace impl

template <class E>
using is_range = decltype(impl::is_range::check(std::declval<E>()));

/************************************************************************
*  class range<ITER, SIZE>						*
************************************************************************/
//! 2つの反復子によって指定される範囲(レンジ)を表すクラス
/*!
  \param ITER	反復子の型
  \param SIZE	レンジに含まれる要素数(0ならば可変長)
*/
template <class ITER, size_t SIZE=0>	class range;

//! 固定長レンジ
/*!
  \param ITER	反復子の型
  \param SIZE	レンジに含まれる要素数
*/
template <class ITER, size_t SIZE>
class range
{
  public:
    using iterator		= ITER;
    using reverse_iterator	= std::reverse_iterator<iterator>;
    using value_type		= typename std::iterator_traits<iterator>
					      ::value_type;
    using reference		= typename std::iterator_traits<iterator>
					      ::reference;
    using const_iterator	= iterator;

  public:
		range(iterator begin)	:_begin(begin)	{}
    
		range()					= delete;
		range(const range&)			= default;
    range&	operator =(const range& r)
		{
		    std::copy_n(r._begin, SIZE, _begin);
		    return *this;
		}
		range(range&&)				= default;
    range&	operator =(range&&)			= default;
    
    template <class ITER_,
	      typename std::enable_if<
		  std::is_convertible<ITER_, iterator>::value>::type* = nullptr>
		range(const range<ITER_, SIZE>& r)
		    :_begin(r.begin())
		{
		}

    template <class E_>
    typename std::enable_if<is_range<E_>::value, range&>::type
		operator =(const E_& expr)
		{
		    assert(std::size(expr) == SIZE);
		    std::copy_n(std::begin(expr), SIZE, _begin);
		    return *this;
		}

		range(std::initializer_list<value_type> args)
		    :_begin(const_cast<iterator>(args.begin()))
    		{
		    assert(args.size() == SIZE);
		}
    range&	operator =(std::initializer_list<value_type> args)
		{
		    assert(args.size() == SIZE);
		    std::copy_n(args.begin(), SIZE, begin());
		    return *this;
		}

    constexpr static
    size_t	size()			{ return SIZE; }
    iterator	begin()		const	{ return _begin; }
    iterator	end()		const	{ return _begin + SIZE; }
    iterator	cbegin()	const	{ return begin(); }
    iterator	cend()		const	{ return end(); }
    reverse_iterator
		rbegin()	const	{ return reverse_iterator(end()); }
    reverse_iterator
		rend()		const	{ return reverse_iterator(begin()); }
    reverse_iterator
		crbegin()	const	{ return rbegin(); }
    reverse_iterator
		crend()		const	{ return rend(); }
    reference	operator [](size_t i) const
		{
		    assert(i < size());
		    return *(_begin + i);
		}
    
  private:
    const iterator	_begin;
};

//! 可変長レンジ
/*!
  \param ITER	反復子の型
*/
template <class ITER>
class range<ITER, 0>
{
  public:
    using iterator		= ITER;
    using const_iterator	= iterator;
    using reverse_iterator	= std::reverse_iterator<iterator>;
    using value_type		= typename std::iterator_traits<iterator>
					      ::value_type;
    using reference		= typename std::iterator_traits<iterator>
					      ::reference;

  public:
		range(iterator begin, iterator end)
		    :_begin(begin), _end(end)		{}
    
		range()					= delete;
		range(const range&)			= default;
    range&	operator =(const range& r)
		{
		    assert(r.size() == size());
		    std::copy(r._begin, r._end, _begin);
		    return *this;
		}
		range(range&&)				= default;
    range&	operator =(range&&)			= default;
    
    template <class ITER_,
	      typename std::enable_if<
		  std::is_convertible<ITER_, iterator>::value>::type* = nullptr>
		range(const range<ITER_, 0>& r)
		    :_begin(r.begin()), _end(r.end())
		{
		}

    template <class E_>
    typename std::enable_if<is_range<E_>::value, range&>::type
		operator =(const E_& expr)
		{
		    assert(std::size(expr) == size());
		    std::copy(std::begin(expr), std::end(expr), _begin);
		    return *this;
		}
		
		range(std::initializer_list<value_type> args)
		    :_begin(const_cast<iterator>(args.begin())),
		     _end(  const_cast<iterator>(args.end()))
    		{
		}
    range&	operator =(std::initializer_list<value_type> args)
		{
		    assert(args.size() == size());
		    std::copy(args.begin(), args.end(), begin());
		    return *this;
		}
		
    size_t	size()		const	{ return std::distance(_begin, _end); }
    iterator	begin()		const	{ return _begin; }
    iterator	end()		const	{ return _end; }
    iterator	cbegin()	const	{ return begin(); }
    iterator	cend()		const	{ return end(); }
    reverse_iterator
		rbegin()	const	{ return reverse_iterator(end()); }
    reverse_iterator
		rend()		const	{ return reverse_iterator(begin()); }
    reverse_iterator
		crbegin()	const	{ return rbegin(); }
    reverse_iterator
		crend()		const	{ return rend(); }
    reference	operator [](size_t i) const
		{
		    assert(i < size());
		    return *(_begin + i);
		}
    
  private:
    const iterator	_begin;
    const iterator	_end;
};

//! 固定長レンジを生成する
/*!
  \param SIZE	レンジ長
  \param iter	レンジの先頭要素を指す反復子
*/
template <size_t SIZE, class ITER> inline range<ITER, SIZE>
make_range(ITER iter)
{
    return {iter};
}
    
//! 可変長レンジを生成する
/*!
  \param begin	レンジの先頭要素を指す反復子
  \param end	レンジの末尾要素の次を指す反復子
*/
template <class ITER> inline range<ITER>
make_range(ITER begin, ITER end)
{
    return {begin, end};
}

//! 可変長レンジを生成する
/*!
  \param iter	レンジの先頭要素を指す反復子
  \param size	レンジの要素数
*/
template <class ITER> inline range<ITER>
make_range(ITER iter, size_t size)
{
    return {iter, iter + size};
}

//! 出力ストリームにレンジの内容を書き出す
/*!
  \param out	出力ストリーム
  \param r	レンジ
  \return	outで指定した出力ストリーム
*/
template <class ITER, size_t SIZE> std::ostream&
operator <<(std::ostream& out, const range<ITER, SIZE>& r)
{
    for (const auto& val : r)
	out << ' ' << val;
    return out << std::endl;
}
    
/************************************************************************
*  class range_iterator<ITER, SIZE, STRIDE>				*
************************************************************************/
namespace detail
{
  template <size_t SIZE, size_t STRIDE>
  struct size_and_stride
  {
      constexpr static size_t	size()		{ return SIZE; }
      constexpr static size_t	stride()	{ return STRIDE; }
  };
  template <size_t SIZE>
  struct size_and_stride<SIZE, 0>
  {
      size_and_stride(size_t stride)
	  :_stride(stride)			{}
      constexpr static size_t	size()		{ return SIZE; }
      size_t			stride() const	{ return _stride; }

    private:
      size_t	_stride;
  };
  template <size_t STRIDE>
  struct size_and_stride<0, STRIDE>
  {
      size_and_stride(size_t size)
	  :_size(size)				{}
      size_t			size()	 const	{ return _size; }
      constexpr static size_t	stride()	{ return STRIDE; }

    private:
      size_t	_size;
  };
  template <>
  struct size_and_stride<0, 0>
  {
      size_and_stride(size_t size, size_t stride)
	  :_size(size), _stride(stride)		{}
      size_t			size()	 const	{ return _size; }
      size_t			stride() const	{ return _stride; }

    private:
      size_t	_size;
      size_t	_stride;
  };
}	// namespace detail
    
//! 配列を一定間隔に切り分けたレンジを指す反復子
/*!
  \param ITER	配列の要素を指す反復子の型
  \param SIZE	レンジ長(0ならば可変長)
  \param STRIDE	インクリメントしたときに進める要素数(0ならば可変)
*/
template <class ITER, size_t SIZE=0, size_t STRIDE=0>
class range_iterator
    : public boost::iterator_adaptor<range_iterator<ITER, SIZE, STRIDE>,
						    ITER,
						    range<ITER, SIZE>,
						    boost::use_default,
						    range<ITER, SIZE> >,
      public detail::size_and_stride<SIZE, STRIDE>
{
  private:
    using super	= boost::iterator_adaptor<range_iterator,
					  ITER,
					  range<ITER, SIZE>,
					  boost::use_default,
					  range<ITER, SIZE> >;
    using ss	= detail::size_and_stride<SIZE, STRIDE>;
    
  public:
    using		typename super::reference;
    using		typename super::difference_type;

    friend class	boost::iterator_core_access;
	  
  public:
    template <size_t SIZE_=SIZE, size_t STRIDE_=STRIDE,
	      typename std::enable_if<
		  (SIZE_ != 0) && (STRIDE_ != 0)>::type* = nullptr>
		range_iterator(ITER iter)
		    :super(iter), ss()					{}
    template <size_t SIZE_=SIZE, size_t STRIDE_=STRIDE,
	      typename std::enable_if<
		  (SIZE_ != 0) && (STRIDE_ == 0)>::type* = nullptr>
		range_iterator(ITER iter, size_t stride)
		    :super(iter), ss(stride)				{}
    template <size_t SIZE_=SIZE, size_t STRIDE_=STRIDE,
	      typename std::enable_if<
		  (SIZE_ == 0) && (STRIDE_ != 0)>::type* = nullptr>
		range_iterator(ITER iter, size_t size)
		    :super(iter), ss(size)				{}
    template <size_t SIZE_=SIZE, size_t STRIDE_=STRIDE,
	      typename std::enable_if<
		  (SIZE_ == 0) && (STRIDE_ == 0)>::type* = nullptr>
		range_iterator(ITER iter, size_t size, size_t stride)
		    :super(iter), ss(size, stride)			{}

    template <class ITER_,
	      typename std::enable_if<
		  std::is_convertible<ITER_, ITER>::value>::type* = nullptr>
		range_iterator(
		    const range_iterator<ITER_, SIZE, STRIDE>& iter)
		    :super(iter), ss(iter)				{}

    using	ss::size;
    using	ss::stride;
    
  private:
    template <size_t SIZE_=SIZE>
    typename std::enable_if<SIZE_ == 0, reference>::type
		dereference() const
		{
		    return {super::base(), super::base() + size()};
		}
    template <size_t SIZE_=SIZE>
    typename std::enable_if<SIZE_ != 0, reference>::type
		dereference() const
		{
		    return {super::base()};
		}
    void	increment()
		{
		    std::advance(super::base_reference(), stride());
		}
    void	decrement()
		{
		    std::advance(super::base_reference(), -stride());
		}
    void	advance(difference_type n)
		{
		    std::advance(super::base_reference(), n*stride());
		}
    difference_type
		distance_to(const range_iterator& iter) const
		{
		    return std::distance(super::base(), iter.base()) / stride();
		}
};

//! 固定長レンジを指し，インクリメント時に固定した要素数だけ進める反復子を生成する
/*!
  \param SIZE	レンジ長
  \param STRIDE	インクリメント時に進める要素数
  \param iter	レンジの先頭要素を指す反復子
*/
template <size_t SIZE, size_t STRIDE, class ITER>
inline range_iterator<ITER, SIZE, STRIDE>
make_range_iterator(ITER iter)
{
    return {iter};
}

//! 固定長レンジを指し，インクリメント時に指定した要素数だけ進める反復子を生成する
/*!
  \param SIZE	レンジ長
  \param iter	レンジの先頭要素を指す反復子
  \param stride	インクリメント時に進める要素数
*/
template <size_t SIZE, class ITER> inline range_iterator<ITER, SIZE>
make_range_iterator(ITER iter, size_t stride)
{
    return {iter, stride};
}
    
//! 指定された長さのレンジを指し，インクリメント時に指定した要素数だけ進める反復子を生成する
/*!
  \param iter	レンジの先頭要素を指す反復子
  \param size	レンジ長
  \param stride	インクリメント時に進める要素数
*/
template <class ITER> inline range_iterator<ITER>
make_range_iterator(ITER iter, size_t size, size_t stride)
{
    return {iter, size, stride};
}
    
/************************************************************************
*  sizes and strides of multidimensional ranges				*
************************************************************************/
namespace detail
{
  template <class E> inline size_t
  size(const E& expr, std::integral_constant<size_t, 0>)
  {
      return std::size(expr);
  }
  template <size_t I, class E> inline size_t
  size(const E& expr, std::integral_constant<size_t, I>)
  {
      return size(*std::begin(expr), std::integral_constant<size_t, I-1>());
  }

  template <class E> inline size_t
  stride(const E& expr, std::integral_constant<size_t, 1>)
  {
      return std::begin(expr).stride();
  }
  template <size_t I, class E> inline size_t
  stride(const E& expr, std::integral_constant<size_t, I>)
  {
      return stride(*std::begin(expr), std::integral_constant<size_t, I-1>());
  }
}	// namespace detail

template <size_t I, class E>
inline typename std::enable_if<is_range<E>::value, size_t>::type
size(const E& expr)
{
    return detail::size(expr, std::integral_constant<size_t, I>());
}

template <size_t I, class E>
inline typename std::enable_if<is_range<E>::value, size_t>::type
stride(const E& expr)
{
    return detail::stride(expr, std::integral_constant<size_t, I>());
}

/************************************************************************
*  fixed size & fixed stride ranges and associated iterators		*
************************************************************************/
//! 多次元固定長レンジを指し，インクリメント時に固定したブロック数だけ進める反復子を生成する
/*!
  \param SIZE	最上位軸のレンジ長
  \param STRIDE	インクリメント時に進める最上位軸のブロック数
  \param SS	2番目以降の軸の(レンジ長，ストライド)の並び
  \param iter	レンジの先頭要素を指す反復子
*/
template <size_t SIZE, size_t STRIDE, size_t... SS, class ITER,
	  typename std::enable_if<sizeof...(SS) != 0>::type* = nullptr>
inline auto
make_range_iterator(ITER iter)
    -> decltype(make_range_iterator<SIZE, STRIDE>(
  		    make_range_iterator<SS...>(iter)))
{
    return make_range_iterator<SIZE, STRIDE>(make_range_iterator<SS...>(iter));
}

template <size_t SIZE, size_t... SS, class ITER,
	  typename std::enable_if<sizeof...(SS) != 0>::type* = nullptr>
inline auto
make_range(ITER iter)
    -> decltype(make_range<SIZE>(make_range_iterator<SS...>(iter)))
{
    return make_range<SIZE>(make_range_iterator<SS...>(iter));
}

#if !defined(__NVCC__)
/************************************************************************
*  fixed size & variable stride ranges and associated iterators		*
************************************************************************/
//! 多次元固定長レンジを指し，インクリメント時に指定したブロック数だけ進める反復子を生成する
/*!
  \param SIZE		最上位軸のレンジ長
  \param SIZES		2番目以降の軸のレンジ長の並び
  \param stride		最上位軸のストライド
  \param strides	2番目以降の軸のストライドの並び
  \param iter		レンジの先頭要素を指す反復子
*/
template <size_t SIZE, size_t... SIZES, class ITER, class... STRIDES,
	  typename std::enable_if<
	      sizeof...(SIZES) == sizeof...(STRIDES)>::type* = nullptr>
inline auto
make_range_iterator(ITER iter, size_t stride, STRIDES... strides)
    -> decltype(make_range_iterator<SIZE>(
  		    make_range_iterator<SIZES...>(iter, strides...), stride))
{
    return make_range_iterator<SIZE>(
	       make_range_iterator<SIZES...>(iter, strides...), stride);
}

template <size_t SIZE, size_t... SIZES, class ITER, class... STRIDES,
	  typename std::enable_if<
	      sizeof...(SIZES) == sizeof...(STRIDES)>::type* = nullptr>
inline auto
make_range(ITER iter, STRIDES... strides)
  // g++-5.4.0 のバグのためコメントアウト
  //-> decltype(make_range<SIZE>(
  //		    make_range_iterator<SIZES...>(iter, strides...)))
{
    return make_range<SIZE>(make_range_iterator<SIZES...>(iter, strides...));
}

/************************************************************************
*  variable size & variable stride ranges and associated iterators	*
************************************************************************/
//! 多次元固定長レンジを指し，インクリメント時に指定したブロック数だけ進める反復子を生成する
/*!
  \param iter		レンジの先頭要素を指す反復子
  \param size		最上位軸のレンジ長
  \param stride		最上位軸のストライド
  \param ss		2番目以降の軸の(レンジ長, ストライド)の並び
*/
template <class ITER, class... SS> inline auto
make_range_iterator(ITER iter, size_t size, size_t stride, SS... ss)
    -> decltype(make_range_iterator(make_range_iterator(iter, ss...),
				    size, stride))
{
    return make_range_iterator(make_range_iterator(iter, ss...),
			       size, stride);
}

template <class ITER, class... SS> inline auto
make_range(ITER iter, size_t size, SS... ss)
    -> decltype(make_range(make_range_iterator(iter, ss...), size))
{
    return make_range(make_range_iterator(iter, ss...), size);
}

/************************************************************************
*  ranges with variable but identical size and stride			*
*  and associated iterators						*
************************************************************************/
template <class ITER> inline ITER
make_dense_range_iterator(ITER iter)
{
    return iter;
}
    
template <class ITER, class... SIZES> inline auto
make_dense_range_iterator(ITER iter, size_t size, SIZES... sizes)
  // g++-5.4.0 のバグのためコメントアウト
  //-> decltype(make_range_iterator(
  //		    make_dense_range_iterator(iter, sizes...), size, size))
{
    return make_range_iterator(make_dense_range_iterator(iter, sizes...),
			       size, size);
}
    
template <class ITER, class... SIZES> inline auto
make_dense_range(ITER iter, size_t size, SIZES... sizes)
    -> decltype(make_range(make_dense_range_iterator(iter, sizes...), size))
{
    return make_range(make_dense_range_iterator(iter, sizes...), size);
}

/************************************************************************
*  subrange extraction							*
************************************************************************/
template <class ITER> inline ITER
make_subrange_iterator(ITER iter)
{
    return iter;
}

template <class ITER, class... IS> inline auto
make_subrange_iterator(const range_iterator<ITER>& iter,
		       size_t idx, size_t size, IS... is)
    -> decltype(make_range_iterator(
		    make_subrange_iterator(iter->begin() + idx, is...),
		    size, iter.stride()))
{
    return make_range_iterator(make_subrange_iterator(
				   iter->begin() + idx, is...),
			       size, iter.stride());
}

template <class RANGE, class... IS,
	  typename std::enable_if<
	      is_range<typename std::decay<RANGE>::type>::value>::type* = nullptr>
inline auto
make_subrange(RANGE&& r, size_t idx, size_t size, IS... is)
    -> decltype(make_range(make_subrange_iterator(
			       r.begin() + idx, is...), size))
{
    return make_range(make_subrange_iterator(r.begin() + idx, is...), size);
}

template <class RANGE, class... IS,
	  typename std::enable_if<is_range<RANGE>::value>::type* = nullptr>
inline auto
make_subrange(const RANGE& r, size_t idx, size_t size, IS... is)
    -> decltype(make_range(
		    make_subrange_iterator(r.begin() + idx, is...), size))
{
    return make_range(make_subrange_iterator(r.begin() + idx, is...), size);
}

template <size_t SIZE, size_t... SIZES, class ITER, class... INDICES,
	  typename std::enable_if<
	      sizeof...(SIZES) == sizeof...(INDICES)>::type* = nullptr>
inline auto
make_subrange_iterator(const ITER& iter, size_t idx, INDICES... indices)
  // g++-5.4.0 のバグのためコメントアウト
  //-> decltype(make_range_iterator<SIZE>(
  //		    make_subrange_iterator<SIZES...>(
  //			iter->begin() + idx, indices...), iter.stride()))
{
    return make_range_iterator<SIZE>(make_subrange_iterator<SIZES...>(
					 iter->begin() + idx, indices...),
				     iter.stride());
}

template <size_t SIZE, size_t... SIZES, class RANGE, class... INDICES,
	  typename std::enable_if<
	      is_range<typename std::decay<RANGE>::type>::value &&
	      (sizeof...(SIZES) == sizeof...(INDICES))>::type* = nullptr>
inline auto
make_subrange(RANGE&& r, size_t idx, INDICES... indices)
    -> decltype(make_range<SIZE>(make_subrange_iterator<SIZES...>(
  				     r.begin() + idx, indices...)))
{
    return make_range<SIZE>(make_subrange_iterator<SIZES...>(
				r.begin() + idx, indices...));
}

template <size_t SIZE, size_t... SIZES, class RANGE, class... INDICES,
	  typename std::enable_if<
	      is_range<RANGE>::value &&
	      (sizeof...(SIZES) == sizeof...(INDICES))>::type* = nullptr>
inline auto
make_subrange(const RANGE& r, size_t idx, INDICES... indices)
    -> decltype(make_range<SIZE>(make_subrange_iterator<SIZES...>(
				     r.begin() + idx, indices...)))
{
    return make_range<SIZE>(make_subrange_iterator<SIZES...>(
				r.begin() + idx, indices...));
}
#endif	// !__NVCC__
    
/************************************************************************
*  generic algorithms for ranges					*
************************************************************************/
template <class E, class T>
typename std::enable_if<!is_range<typename std::decay<E>::type>::value>::type
fill(E&& expr, const T& val)
{
    expr = val;
}
template <class E, class T>
typename std::enable_if<is_range<typename std::decay<E>::type>::value>::type
fill(E&& expr, const T& val)
{
    for (auto iter = std::begin(expr); iter != std::end(expr); ++iter)
	fill(*iter, val);
}
    
}	// namespace TU
#endif	// !__TU_RANGE_H
