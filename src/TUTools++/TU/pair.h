/*
 *  $Id$
 */
/*!
  \file		tuple.h
  \brief	boost::tupleの用途拡張のためのユティリティ
*/
#ifndef __TU_PAIR_H
#define __TU_PAIR_H

#include <utility>
#include <iostream>
#include "TU/functional.h"	// is_convertible<T, C<ARGS...> >

namespace TU
{
/************************************************************************
*  struct is_pair<T>							*
************************************************************************/
template <class T>
using is_pair = is_convertible<T, std::pair>;

/************************************************************************
*  struct pair_traits<PAIR>						*
************************************************************************/
template <class T>
struct pair_traits
{
    static constexpr size_t	size = 1;
    typedef T						leftmost_type;
    typedef T						rightmost_type;
};
template <class S, class T>
struct pair_traits<std::pair<S, T> >
{
    static constexpr size_t	size = pair_traits<S>::size
				     + pair_traits<T>::size;
    typedef typename pair_traits<S>::leftmost_type	leftmost_type;
    typedef typename pair_traits<T>::rightmost_type	rightmost_type;
};

/************************************************************************
*  struct pair_tree<T, N>						*
************************************************************************/
namespace detail
{
  template <class T, size_t N>
  struct pair_tree
  {
      typedef std::pair<typename pair_tree<T, (N>>1)>::type,
			typename pair_tree<T, (N>>1)>::type>	type;
  };
  template <class T>
  struct pair_tree<T, 1>
  {
      typedef T							type;
  };
  template <class T>
  struct pair_tree<T, 0>
  {
      typedef T							type;
  };
}	// namespace detail

//! 2のべき乗個の同一要素から成る多層pairを表すクラス
/*!
  \param T	要素の型
  \param N	要素の個数(2のべき乗)
*/
template <class T, size_t N=1>
using pair_tree = typename detail::pair_tree<T, N>::type;
    
}	// namespace TU

namespace std
{
template <class S, class T> inline ostream&
operator <<(ostream& out, const std::pair<S, T>& x)
{
    return out << '[' << x.first << ' ' << x.second << ']';
}
    
}	// namespace std

#endif	// !__TU_PAIR_H
