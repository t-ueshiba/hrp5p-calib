/*
 *  $Id: Heap.h 1595 2014-07-28 21:51:36Z ueshiba $
 */
/*!
  \file		Heap.h
  \brief	クラス TU::Heap の定義と実装
*/
#ifndef __TU_HEAP_H
#define __TU_HEAP_H

#include "TU/Array++.h"
#include <functional>

namespace TU
{
/************************************************************************
*  class Heap<T, Cmp>							*
************************************************************************/
//! 最大ヒープ(親ノードは子ノードより大きいか等しい)を表すクラス
/*!
  テンプレートパラメータTは要素の型を指定する．テンプレートパラメータCmp
  は2つのT型要素が昇順に並んでいる時にtrueを返す関数オブジェクト型である．
  たとえば，2つのint型を比較する場合は
  \verbatim
  struct ordered
  {
    bool	operator ()(const int& elm0, const int& elm1) const
		{
		    return elm0 < elm1;
		}
  };
  \endverbatim
  と定義する．
*/
template <class T, class Cmp=std::less<T> >
class Heap
{
  public:
    typedef T					value_type;
    typedef value_type&				reference;
    typedef const value_type&			const_reference;
    typedef value_type*				pointer;
    typedef const value_type*			const_pointer;
    typedef typename Array<T>::iterator		iterator;
    typedef typename Array<T>::const_iterator	const_iterator;
    typedef Cmp					value_compare;
    typedef value_type				key_type;
    typedef value_compare			key_compare;
    
  public:
    explicit Heap(size_t d=0, const Cmp& cmp=Cmp())	;
    Heap(Array<T>& a, const Cmp& cmp=Cmp())		;

  //! ヒープの先頭要素(最大要素)を指す反復子を返す．
  /*!
    begin() から end() までは降順に並んでいるとは限らないことに注意．
    \return	ヒープの先頭要素を指す反復子
  */
    iterator		begin()			{return _array.begin();}

  //! ヒープの先頭要素(最大要素)を指す定数反復子を返す．
  /*!
    begin() から end() までは降順に並んでいるとは限らないことに注意．
    \return	ヒープの先頭要素を指す定数反復子
  */
    const_iterator	begin()		const	{return _array.begin();}

  //! ヒープの先頭要素(最大要素)を指す定数反復子を返す．
  /*!
    cbegin() から cend() までは降順に並んでいるとは限らないことに注意．
    \return	ヒープの先頭要素を指す定数反復子
  */
    const_iterator	cbegin()	const	{return begin();}

  //! ヒープの末尾を指す反復子を返す．
  /*!
    begin() から end() までは降順に並んでいるとは限らないことに注意．
    \return	ヒープの末尾を指す反復子
  */
    iterator		end()			{return _array.begin() + _n;}

  //! ヒープの末尾を指す定数反復子を返す．
  /*!
    begin() から end() までは降順に並んでいるとは限らないことに注意．
    \return	ヒープの末尾を指す定数反復子
  */
    const_iterator	end()		const	{return _array.begin() + _n;}

  //! ヒープの末尾を指す定数反復子を返す．
  /*!
    cbegin() から cend() までは降順に並んでいるとは限らないことに注意．
    \return	ヒープの末尾を指す定数反復子
  */
    const_iterator	cend()		const	{return end();}

  //! 現在の要素数を返す．
  /*!
    \return	要素数
  */
    size_t	size()			const	{return _n;}

  //! ヒープに格納できる最大要素数を返す．
  /*!
    \return	最大要素数
  */
    size_t	max_size()		const	{return _array.size();}

  //! ヒープが空であるか調べる．
  /*!
    \return	空であればtrue, そうでなければfalse
  */
    bool	empty()			const	{return _n == 0;}
    
  //! ヒープが満杯であるか調べる．
  /*!
    \return	満杯であればtrue, そうでなければfalse
  */
    bool	full()			const	{return _n == max_size();}
    
    const T&	top()			const	;
    void	push(const T& elm)		;
    bool	push_or_replace(const T& elm)	;
    T		pop()				;
    void	clear()				;
    void	resize(size_t d)		;
    
  private:
    void	upheap(size_t current)		;
    void	downheap(size_t current)	;
    
    Array<T>	_array;
    size_t	_n;		// # of elements in the heap.
    Cmp		_cmp;
};

//! 空のヒープを作る．
/*!
  \param d	ヒープの容量
  \param cmp	比較関数オブジェクト
*/
template <class T, class Cmp>
Heap<T, Cmp>::Heap(size_t d, const Cmp& cmp)
    :_array(d), _n(0), _cmp(cmp)
{
}

//! 1次元配列からヒープを作る．
/*!
  \param a	1次元配列
  \param cmp	比較関数オブジェクト
*/
template <class T, class Cmp>
Heap<T, Cmp>::Heap(Array<T>& a, const Cmp& cmp)
    :_array(a.data(), a.size()), _n(a.size()), _cmp(cmp)
{
    for (size_t i = _n / 2; i > 0; )
	downheap(--i);
}

//! ヒープの先頭要素を返す．
/*!
  ヒープの先頭はヒープ中の最大要素となる．
  \return	先頭要素
*/
template <class T, class Cmp> inline const T&
Heap<T, Cmp>::top() const
{
    if (_n == 0)
	throw std::out_of_range("TU::Heap<T, Cmp::top: Heap is empty!!");
    return _array[0];
}

//! ヒープに要素を追加する．
/*!
  \param elm	追加する要素
*/
template <class T, class Cmp> inline void
Heap<T, Cmp>::push(const T& elm)
{
    if (_n >= _array.size())
	throw std::length_error("TU::Heap<T, Cmp>::push: Heap is full!!");

    _array[_n] = elm;
    upheap(_n++);
}

//! 指定された要素を追加または先頭要素と入れ替える．
/*!
  ヒープが満杯でないときは無条件に追加し，満杯のときは指定された要素が
  先頭要素よりも小さいときに先頭要素を取り除いてから追加する．
  \param elm	追加する要素
  \return	elmが実際に追加されたらtrue, そうでなければfalse
*/
template <class T, class Cmp> inline bool
Heap<T, Cmp>::push_or_replace(const T& elm)
{
    if (!full())		// 満杯でなかったら...
    {
	push(elm);		// elmを追加する．
	return true;
     }
    else if (_cmp(elm, top()))	// 満杯かつelmがヒープの最大要素よりも
    {				// 小さければ...
	pop();			// その最大要素を取り除き，
	push(elm);		// elmを追加する．
	return true;
    }
    return false;
}
    
//! ヒープの先頭要素を取り除く．
/*!
  ヒープの先頭はヒープ中の最大要素であり，これを取り除く．
  \return	取り除かれた要素
*/
template <class T, class Cmp> inline T
Heap<T, Cmp>::pop()
{
    if (_n == 0)
	throw
	    std::out_of_range("TU::Heap<T, Cmp>::pop: Heap is empty!!");

    T	val = _array[0];			// Store the root value.
    _array[0] = _array[--_n];			// Move the last to the root.
    downheap(0);
    return val;
}

//! ヒープを空にする．
template <class T, class Cmp> inline void
Heap<T, Cmp>::clear()
{
    _n = 0;
}
    
//! ヒープに格納できる最大要素数を変更する．
/*!
  これまでのヒープの内容はすべて破棄される．
  \param d	最大要素数
*/
template <class T, class Cmp> inline void
Heap<T, Cmp>::resize(size_t d)
{
    _array.resize(d);
    _n = 0;
}
    
template <class T, class Cmp> void
Heap<T, Cmp>::upheap(size_t current)
{
    T	val = _array[current];
    while (current > 0)				// While having a parent...
    {
	size_t	parent = (current - 1) / 2;	// Index of the parent node.
	if (!_cmp(_array[parent], val))
	    break;
	
	_array[current] = _array[parent];	// Pull-down the parent.
	current = parent;			// Go upward.
    }
    _array[current] = val;
}

template <class T, class Cmp> void
Heap<T, Cmp>::downheap(size_t current)
{
    T	val = _array[current];
    for (size_t child; (child = 2 * current + 1) < _n; )
    {
	if (child + 1 < _n && _cmp(_array[child], _array[child + 1]))
	    ++child;				// Choose larger child.

	if (!_cmp(val, _array[child]))
	    break;

	_array[current] = _array[child];	// Pull-up the child.
	current = child;			// Go downward.
    }
    _array[current] = val;
}

/************************************************************************
*  Global functions							*
************************************************************************/
//! 1次元配列をヒープソートによって昇順にソートする．
/*!
  \param a	ソートする配列
  \param cmp	比較関数オブジェクト
*/
template <class T, class Cmp> void
sort(Array<T>& a, const Cmp& cmp)
{
    Heap<T, Cmp>	heap(a, cmp);

  // 後ろから a[] に代入しないと a[] の領域を内部で共有している
  // ヒープを壊してしまうことに注意．
    for (size_t i = a.size(); i > 0; )
	a[--i] = heap.pop();
}
 
}
#endif	// !__TU_HEAP_H
