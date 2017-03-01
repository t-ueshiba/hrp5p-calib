/*
 *  $Id: Array++.h 2039 2016-11-15 22:03:33Z ueshiba $
 */
/*!
  \file		Array++.h
  \brief	配列クラスの定義と実装
*/
#ifndef __TU_ARRAYPP_H
#define __TU_ARRAYPP_H

#include <initializer_list>
#include <memory>			// std::allocator<T>
#include <algorithm>			// std::copy()
#include <numeric>			// std::inner_product()
#include <stdexcept>
#include <cmath>			// floor()
#include <cassert>
#include <iostream>
#include <iomanip>
#include "TU/iterator.h"

namespace TU
{
/************************************************************************
*  class BufTraits<T>							*
************************************************************************/
template <class T, class ALLOC>
struct BufTraits
{
    typedef ALLOC					allocator_type;
    typedef typename allocator_type::pointer		pointer;
    typedef typename allocator_type::const_pointer	const_pointer;
    typedef pointer					iterator;
    typedef const_pointer				const_iterator;

  protected:
    static pointer	null()
			{
			    return nullptr;
			}
    
    template <class IN_, class OUT_>
    static OUT_		copy(IN_ ib, IN_ ie, OUT_ out)
			{
			    return std::copy(ib, ie, out);
			}

    template <class T_>
    static void		fill(iterator ib, iterator ie, const T_& c)
			{
			    std::fill(ib, ie, c);
			}

    static void		init(iterator ib, iterator ie)
			{
			    std::fill(ib, ie, 0);
			}
};

/************************************************************************
*  class Buf<T, D, ALLOC>						*
************************************************************************/
//! 固定長バッファクラス
/*!
  単独で使用することはなく，#TU::Array の基底クラスまたは #TU::Array2 の
  内部バッファクラスとして使う．
  \param T	要素の型
  \param D	バッファ中の要素数
*/
template <class T, size_t D, class ALLOC>
class Buf : public BufTraits<T, ALLOC>
{
  private:
    typedef BufTraits<T, ALLOC>			super;

  public:
    typedef void				allocator_type;
    typedef T					value_type;
    typedef typename super::pointer		pointer;
    typedef typename super::const_pointer	const_pointer;
    typedef typename super::iterator		iterator;
    typedef typename super::const_iterator	const_iterator;
    
  public:
    explicit		Buf(size_t siz=D)
			{
			    resize(siz);
			}

			Buf(const Buf& b)
			{
			    for_each(b.begin(), assign());
			}
    Buf&		operator =(const Buf& b)
			{
			    if (this != &b)
				for_each(b.begin(), assign());
			    return *this;
			}
    
  //! 外部の領域と要素数を指定してバッファを生成する（ダミー関数）．
  /*!
    実際はバッファが使用する記憶領域は固定されていて変更できないので，
    この関数は常に例外を送出する．
    \throw std::logic_error	この関数が呼ばれたら必ず送出
  */
			Buf(pointer, size_t)
			{
			    throw std::logic_error("Buf<T, D>::Buf(pointer, size_t): cannot specify a pointer to external storage!!");
			}

    pointer		data()			{ return _p; }
    const_pointer	data()		const	{ return _p; }
    iterator		begin()			{ return _p; }
    const_iterator	begin()		const	{ return _p; }
    const_iterator	cbegin()	const	{ return _p; }
    iterator		end()			{ return _p + D; }
    const_iterator	end()		const	{ return _p + D; }
    const_iterator	cend()		const	{ return _p + D; }
    constexpr static size_t
			size()			{ return D; }

  //! バッファの要素数を変更する．
  /*!
    実際にはバッファの要素数を変更することはできないので，与えられた要素数が
    このバッファの要素数に等しい場合のみ，通常どおりにこの関数から制御が返る．
    \param siz	新しい要素数
    \return	常にfalse
  */
    static bool		resize(size_t siz)
			{
			    assert(siz == D);
			    return false;
			}
	
  //! バッファが内部で使用する記憶領域を指定したものに変更する．
  /*!
    実際にはバッファの記憶領域を変更することはできないので，与えられたポインタ
    と要素数がこのバッファのそれらに等しい場合のみ，通常どおりにこの関数から制御
    が返る．
    \param p	新しい記憶領域へのポインタ
    \param siz	新しい要素数
  */
    void		resize(pointer p, size_t siz) const
			{
			    assert(p == _p && siz == D);
			}

  //! 入力ストリームから配列を読み込む(ASCII)．
  /*!
    \param in	入力ストリーム
    \return	inで指定した入力ストリーム
  */
    std::istream&	get(std::istream& in)
			{
			    for (auto& x : *this)
				in >> x;
			    return in;
			}

    static bool		shared()
			{
			  // この型の引数に対して移動コンストラクタ/移動代入を
			  // 呼んでもshallow copyはできないので，trueを返す．
			    return true;
			}
    
  protected:
    template <class OP, class ITER>
    void		for_each(ITER src, const OP& op)
			{
			    for_each_impl<0, OP>::exec(src, begin(), op);
			}
    
  private:
    template <size_t N, class OP>
    struct for_each_impl
    {
	template <class ITER_>
	static void	exec(ITER_ src, iterator dst, const OP& op)
			{
			    op(*dst, *src);
			    for_each_impl<N+1, OP>::exec(++src, ++dst, op);
			}
    };
    template <class OP>
    struct for_each_impl<D, OP>
    {
	template <class ITER_>
	static void	exec(ITER_, iterator, const OP&)		{}
    };
    
  private:
    alignas(sizeof(value_type)) value_type	_p[D];	// D-sized buffer
};

//! 可変長バッファクラス
/*!
  単独で使用することはなく，#TU::Array の基底クラスまたは #TU::Array2 の
  内部バッファクラスとして使う．
  \param T	要素の型
  \param ALLOC	アロケータの型
*/
template <class T, class ALLOC>
class Buf<T, 0, ALLOC> : public BufTraits<T, ALLOC>
{
  private:
    typedef BufTraits<T, ALLOC>			super;
    
  public:
    typedef typename super::allocator_type	allocator_type;
    typedef T					value_type;
    typedef typename super::pointer		pointer;
    typedef typename super::const_pointer	const_pointer;
    typedef typename super::iterator		iterator;
    typedef typename super::const_iterator	const_iterator;
    
  public:
    explicit		Buf(size_t siz=0)
			    :_size(siz), _p(alloc(_size)),
			     _shared(0), _capacity(_size)	{}

			Buf(const Buf& b)
			    :_size(b._size), _p(alloc(_size)),
			     _shared(0), _capacity(_size)
			{
			    super::copy(b.begin(), b.end(), begin());
			}
    Buf&		operator =(const Buf& b)
			{
			    if (this != &b)
			    {
				resize(b._size);
				super::copy(b.begin(), b.end(), begin());
			    }
			    return *this;
			}
  /*
   *  [注意1] 移動コンストラクタ/移動代入演算子を定義するなら
   *  コピーコンストラクタ/標準代入演算子も陽に定義する必要あり
   *  
   *  [注意2] Buf型オブジェクト x が x._shared == 1 である場合，
   *  x はそのデータの寿命を管理していない．したがって，xを右辺値として
   *  他のBuf型オブジェクト y に移動させる場合，shallow copy すると
   *  x の寿命と無関係に y のデータが無効になる可能性があるので，deep copy
   *  しなければならない．
   *
   *  [注意3] このことは，Array2<Array<T> >型オブジェクト a を
   *  Array<Array<T> >型オブジェクト b に移動させる時に重要である．
   *  a の各行 row について row._shared == 1 であるが，これをそのまま
   *  b の各行に shallow copy してしまうと，b の各要素が使用する記憶領域は
   *  a._buf のままである．よって，a が破壊されるときに一緒に a._buf も
   *  破壊されると b に dangling pointer が生じる．
   */
			Buf(Buf&& b)
			    :_size(b._size),
			     _p(b._shared ? alloc(_size) : b._p),
			     _shared(0),
			     _capacity(b._shared ? _size : b._capacity)
			{
			    if (b._shared)
				super::copy(b.begin(), b.end(), begin());
			    else
			    {
			      // b の 破壊時に this->_p がdeleteされることを防ぐ．
				b._size	    = 0;
				b._p	    = super::null();
				b._capacity = 0;
			    }
			}

    Buf&		operator =(Buf&& b)
			{
			    if (_shared || b._shared)
			    {
				resize(b._size);
				super::copy(b.begin(), b.end(), begin());
			    }
			    else
			    {
				free(_p, _size);
				_size     = b._size;
				_p	  = b._p;
				_capacity = b._capacity;

			      // b の 破壊時に this->_p がdeleteされることを防ぐ．
				b._size	    = 0;
				b._p	    = super::null();
				b._capacity = 0;
			    }

			    return *this;
			}

			~Buf()
			{
			    if (!_shared)
				free(_p, _size);
			}

			Buf(pointer p, size_t siz)
			    :_size(siz), _p(p),
			     _shared(1), _capacity(_size)	{}

    pointer		data()			{ return _p; }
    const_pointer	data()		const	{ return _p; }
    iterator		begin()			{ return _p; }
    const_iterator	begin()		const	{ return _p; }
    const_iterator	cbegin()	const	{ return _p; }
    iterator		end()			{ return _p + _size; }
    const_iterator	end()		const	{ return _p + _size; }
    const_iterator	cend()		const	{ return _p + _size; }
    size_t		size()		const	{ return _size; }
    
  //! バッファの要素数を変更する．
  /*!
    ただし，他のオブジェクトと記憶領域を共有しているバッファの要素数を
    変更することはできない．
    \param siz			新しい要素数
    \return			sizが元の要素数よりも大きければtrue，そう
				でなければfalse
    \throw std::logic_error	記憶領域を他のオブジェクトと共有している場合
				に送出
  */
    bool		resize(size_t siz)
			{
			    if (_size == siz)
				return false;
    
			    if (_shared)
				throw std::logic_error("Buf<T, ALLOC>::resize: cannot change size of shared buffer!");

			    const size_t	old_size = _size;
			    _size = siz;
			    if (_capacity < _size)
			    {
				free(_p, old_size);
				_p = alloc(_size);
				_capacity = _size;
			    }
			    return _size > old_size;
			}
	
  //! バッファが内部で使用する記憶領域を指定したものに変更する．
  /*!
    \param p	新しい記憶領域へのポインタ
    \param siz	新しい要素数
  */
    void		resize(pointer p, size_t siz)
			{
			    if (!_shared)
				free(_p, _size);
			    _size     = siz;
			    _p	      = p;
			    _shared   = 1;
			    _capacity = _size;
			}

    std::istream&	get(std::istream& in, size_t m=0)	;

    bool		shared() const
			{
			    return _shared;
			}
    
  protected:
    template <class OP, class ITER>
    void		for_each(ITER src, const OP& op)
			{
			    for (iterator dst = begin(), e = end();
				 dst != e; ++dst, ++src)
				op(*dst, *src);
			}
    
  private:
    pointer		alloc(size_t siz)
			{
			    pointer	p = _allocator.allocate(siz);
			    for (pointer q = p, qe = q + siz; q != qe; ++q)
				_allocator.construct(q, value_type());
			    return p;
			}
    void		free(pointer p, size_t siz)
			{
			    for (pointer q = p, qe = q + siz; q != qe; ++q)
				_allocator.destroy(q);
			    _allocator.deallocate(p, siz);
			}
    
  private:
    allocator_type	_allocator;		//!< アロケータ
    size_t		_size;			//!< 要素数
    pointer		_p;			//!< 記憶領域の先頭ポインタ
    size_t		_shared	  : 1;		//!< 記憶領域の共有を示すフラグ
    size_t		_capacity : 8*sizeof(size_t)-1;	//!< 要素数単位の容量
};

//! 入力ストリームから指定した箇所に配列を読み込む(ASCII)．
/*!
  \param in	入力ストリーム
  \param m	読み込み先の先頭を指定するindex
  \return	inで指定した入力ストリーム
*/
template <class T, class ALLOC> std::istream&
Buf<T, 0, ALLOC>::get(std::istream& in, size_t m)
{
    const size_t	BufSiz = (sizeof(value_type) < 2048 ?
				  2048 / sizeof(value_type) : 1);
    const pointer	tmp = new value_type[BufSiz];
    size_t		n = 0;
    
    while (n < BufSiz)
    {
	char	c;
	while (in.get(c))		// skip white spaces other than '\n'
	    if (!isspace(c) || c == '\n')
		break;

	if (!in || c == '\n')
	{
	    resize(m + n);
	    break;
	}

	in.putback(c);
	in >> tmp[n++];
    }
    if (n == BufSiz)
	get(in, m + n);

    for (size_t i = 0; i < n; ++i)
	_p[m + i] = std::move(tmp[i]);

    delete [] tmp;
    
    return in;
}
    
/************************************************************************
*  class Array<T, D, ALLOC>						*
************************************************************************/
//! T型オブジェクトの1次元配列クラス
/*!
  \param T	要素の型
  \param D	次元(0ならば可変)
  \param ALLOC	アロケータの型
*/
template <class T, size_t D=0, class ALLOC=std::allocator<T> >
class Array : public Buf<T, D, ALLOC>
{
  private:
    typedef typename std::is_arithmetic<T>::type	value_is_arithmetic;
    typedef Buf<T, D, ALLOC>				super;

  public:
  //! アロケータの型
    typedef typename super::allocator_type		allocator_type;
  //! 成分の型
    typedef element_t<T>				element_type;
  //! 要素の型    
    typedef typename super::value_type			value_type;
  //! 要素へのポインタ
    typedef typename super::pointer			pointer;
  //! 定数要素へのポインタ
    typedef typename super::const_pointer		const_pointer;
  //! 反復子
    typedef typename super::iterator			iterator;
  //! 定数反復子
    typedef typename super::const_iterator		const_iterator;
  //! 逆反復子    
    typedef std::reverse_iterator<iterator>		reverse_iterator;
  //! 定数逆反復子    
    typedef std::reverse_iterator<const_iterator>	const_reverse_iterator;
  //! 要素への参照
    typedef typename std::iterator_traits<iterator>::reference
							reference;
  //! 定数要素への参照
    typedef typename std::iterator_traits<const_iterator>::reference
							const_reference;
  //! ポインタ間の差
    typedef std::ptrdiff_t				difference_type;

  public:
  //! 配列を生成する．
		Array() :super()				{ init(); }
    
		Array(std::initializer_list<value_type> args)
		    :super(args.size())
		{
		    super::copy(args.begin(), args.end(), begin());
		}

    Array&	operator =(std::initializer_list<value_type> args)
		{
		    super::resize(args.size());
		    super::copy(args.begin(), args.end(), begin());
		    return *this;
		}

  //! 指定した要素数の配列を生成する．
  /*!
    \param d	配列の要素数
  */
    explicit	Array(size_t d)	:super(d)			{ init(); }

  //! 外部の領域と要素数を指定して配列を生成する．
  /*!
    \param p	外部領域へのポインタ
    \param d	配列の要素数
  */
		Array(pointer p, size_t d) :super(p, d)		{}

  //! 記憶領域を元の配列と共有した部分配列を作る．
  /*!
    \param a	配列
    \param i	部分配列の第0要素を指定するindex
    \param d	部分配列の次元(要素数)
  */
    template <size_t D2, class ALLOC2>
		Array(Array<T, D2, ALLOC2>& a, size_t i, size_t d)
		    :super((i < a.size() ? &a[i] : super::null()),
			   partial_size(i, d, a.size()))	{}
#if defined(__NVCC__)
    template <size_t D_, class ALLOC_>
		Array(const Array<T, D_, ALLOC_>& a)
		    :super(a.size())
		{
		    super::copy(a.begin(), a.end(), begin());
		}

    template <size_t D_, class ALLOC_>
    Array&	operator =(const Array<T, D_, ALLOC_>& a)
		{
		    super::resize(a.size());
		    super::copy(a.begin(), a.end(), begin());
		    return *this;
		}
#else
  //! 他の配列と同一要素を持つ配列を作る（コピーコンストラクタの拡張）．
  /*!
    コピーコンストラクタは別個自動的に生成される．
    \param expr	コピー元の配列
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
		Array(const E& expr)
		    :super(expr.size())
		{
		    super::for_each(expr.begin(), assign());
		}
    
  //! 他の配列を自分に代入する（標準代入演算子の拡張）．
  /*!
    標準代入演算子は別個自動的に生成される．
    \param expr	コピー元の配列
    \return	この配列
  */
    template <class E>
    typename std::enable_if<is_range<E>::value, Array&>::type
		operator =(const E& expr)
		{
		    super::resize(expr.size());
		    super::for_each(expr.begin(), assign());
		    return *this;
		}
#endif	// __NVCC__
  //! この配列と記憶領域を共有した部分配列を生成する．
  /*!
    \param i	部分配列の第0成分を指定するindex
    \param d	部分配列の次元(要素数)
    \return	生成された部分配列
  */
    Array<T>	operator ()(size_t i, size_t d)
		{
		    return Array<T>(*this, i, d);
		}

  //! この配列と記憶領域を共有した部分配列を生成する．
  /*!
    \param i	部分配列の第0成分を指定するindex
    \param d	部分配列の次元(要素数)
    \return	生成された部分配列
  */
    const Array<T>
		operator ()(size_t i, size_t d) const
		{
		    return Array<T>(const_cast<Array&>(*this), i, d);
		}
    
  //! 他の配列に自分を代入する．
  /*!
    \param expr	コピー先の配列
    \return	この配列
  */
    template <size_t D_, class ALLOC_>
    void	write(Array<T, D_, ALLOC_>& a) const
		{
		    a.resize(size());
		    super::copy(begin(), end(), a.begin());
		}

  //! 全ての要素に同一の値を代入する．
  /*!
    \param c	代入する値
  */
    Array&	operator =(const element_type& c)
		{
		    super::fill(begin(), end(), c);
		    return *this;
		}
    
    using	super::data;
    using	super::begin;
    using	super::cbegin;
    using	super::end;
    using	super::cend;
    using	super::size;
    
    size_t			dim() const
				{
				    return size();
				}
    reverse_iterator		rbegin()
				{
				    return reverse_iterator(end());
				}
    const_reverse_iterator	rbegin() const
				{
				    return const_reverse_iterator(end());
				}
    const_reverse_iterator	crbegin() const
				{
				    return rbegin();
				}
    reverse_iterator		rend()
				{
				    return reverse_iterator(begin());
				}
    const_reverse_iterator	rend() const
				{
				    return const_reverse_iterator(begin());
				}
    const_reverse_iterator	crend() const
				{
				    return rend();
				}
    reference			operator [](size_t i)
				{
				    assert(i < size());
				    return *(begin() + i);
				}
    const_reference		operator [](size_t i) const
				{
				    assert(i < size());
				    return *(begin() + i);
				}
    template <class S>
    value_type			at(S uf) const
				{
				    const auto	u  = floor(uf);
				    const auto	p  = data()
						   + difference_type(u);
				    const auto	du = uf - u;
				    return (du ?
					    (1.0 - du)*p[0] + du*p[1] : p[0]);
				}

#if !defined(__NVCC__)
  //! 2つの配列を要素毎に比較し，同じであるか調べる．
  /*!
    \param expr	比較対象となる配列
    \return	全ての要素が同じならばtrue，そうでなければfalse
  */
    template <class E>
    typename std::enable_if<is_range<E>::value, bool>::type
			operator ==(const E& expr) const
			{
			    if (size() != expr.size())
				return false;
			    auto	p = expr.begin();
			    for (const auto& x : *this)
			    {
				if (x != *p)
				    return false;
				++p;
			    }
			    return true;
			}

  //! 2つの配列を要素毎に比較し，異なるものが存在するか調べる．
  /*!
    \param expr	比較対象となる配列
    \return	異なる要素が存在すればtrue，そうでなければfalse
  */
    template <class E>
    typename std::enable_if<is_range<E>::value, bool>::type
			operator !=(const E& expr) const
			{
			    return !(*this == expr);
			}
#endif	// !__NVCC__
    bool		resize(size_t siz)
			{
			    bool enlarged = super::resize(siz);
			    init();
			    return enlarged;
			}

    void		resize(pointer p, size_t siz)
			{
			    super::resize(p, siz);
			}
    
  //! 出力ストリームに配列を書き出す(ASCII)．
  /*!
    \param out	出力ストリーム
    \return	outで指定した出力ストリーム
  */
    std::ostream&	put(std::ostream& out) const
			{
			    for (const auto& x : *this)
				out << ' ' << x;
			    return out;
			}

  //! 入力ストリームから配列を読み込む(binary)．
  /*!
    \param in	入力ストリーム
    \return	inで指定した入力ストリーム
  */
    std::istream&	restore(std::istream& in)
			{
			    in.read(reinterpret_cast<char*>(data()),
				    sizeof(value_type) * size());
			    return in;
			}

  //! 出力ストリームに配列を書き出す(binary)．
  /*!
    \param out	出力ストリーム
    \return	outで指定した出力ストリーム
  */
    std::ostream&	save(std::ostream& out) const
			{
			    out.write(reinterpret_cast<const char*>(data()),
				      sizeof(value_type) * size());
			    return out;
			}

  //! 指定した値がこの配列の要素数に一致するか調べる．
  /*!
    \param d			調べたい値
    \throw std::logic_error	d != size()の場合に送出
  */
    void		check_size(size_t d) const
			{
#if !defined(NO_CHECK_SIZE)
			    if (d != size())
				throw std::logic_error("Array<T, B>::check_size: mismatched size!");
#endif
			}

    void		init()
			{
			    init(value_is_arithmetic());
			}

  protected:
    static size_t	partial_size(size_t i, size_t d, size_t a)
			{
			    return (i+d <= a ? d : i < a ? a-i : 0);
			}

  private:
    void		init(std::true_type)
			{
			    super::init(begin(), end());
			}
    void		init(std::false_type)
			{
			}
};

/************************************************************************
*  class Array2<T, R, C>						*
************************************************************************/
//! 1次元配列Tの1次元配列として定義された2次元配列クラス
/*!
  \param T	1次元配列の型
  \param R	行数(0ならば可変)
  \param C	列数(0ならば可変)
*/
template <class T, size_t R=0, size_t C=0>
class Array2 : public Array<T, R>
{
  private:
    typedef Array<T, R>					super;
    typedef Buf<typename T::value_type, R*C,
		typename T::allocator_type>	 	buf_type;
    
  public:
  //! 成分の型    
    typedef typename super::element_type		element_type;
  //! 行の型    
    typedef typename super::value_type			value_type;
  //! 行の反復子    
    typedef typename super::iterator			iterator;
  //! 行の定数反復子    
    typedef typename super::const_iterator		const_iterator;
  //! 行の逆反復子    
    typedef typename super::reverse_iterator		reverse_iterator;
  //! 行の定数逆反復子    
    typedef typename super::const_reverse_iterator	const_reverse_iterator;
  //! 行への参照    
    typedef typename super::reference			reference;
  //! 定数行への参照    
    typedef typename super::const_reference		const_reference;
  //! 要素へのポインタ    
    typedef typename buf_type::pointer			pointer;
  //! 定数要素へのポインタ    
    typedef typename buf_type::const_pointer		const_pointer;
  //! ポインタ間の差    
    typedef std::ptrdiff_t				difference_type;
    
  public:
		Array2()			//!< デフォルトコンストラクタ
		    :super(), _ncol(0), _buf()
		{
		    if (size() > 0)
			_ncol = _buf.size() / size();
		    set_rows();
		    for (auto& x : *this)
			x.init();
		}

		Array2(const Array2& a)		//!< コピーコンストラクタ
		    :super(a.size()), _ncol(a.ncol()), _buf(size()*a.stride())
		{
		    set_rows();
		    super::operator =(static_cast<const super&>(a));
		}    

    Array2&	operator =(const Array2& a)	//!< 標準代入演算子
		{
		    if (this != &a)
		    {
			if (super::resize(a.size()) || _ncol != a.ncol())
			{
			    _ncol = a.ncol();
			    _buf.resize(size()*a.stride());
			    set_rows();
			}
			super::operator =(static_cast<const super&>(a));
		    }
		    return *this;
		}

		Array2(Array2&& a)		//!< 移動コンストラクタ
		    :super(), _ncol(0), _buf()
		{
		    operator =(std::move(a));
		}

    Array2&	operator =(Array2&& a)		//!< 移動代入演算子
		{
		  // 代入元と代入先のいずれかが shared buffer なら deep copy
		    if (_buf.shared() || a._buf.shared())
			operator =(static_cast<const Array2&>(a));
		    else
		    {
		      // a をmoveする前にa._ncolとa._bufをコピーしておく
			_ncol = a.ncol();
			_buf  = std::move(a._buf);
			super::operator =(static_cast<super&&>(a));
		    }
		    return *this;
		}

		Array2(std::initializer_list<value_type> args)
		    :super(args.size()),
		     _ncol(args.size() ? args.begin()->size() : 0),
		     _buf(size()*stride(1))
		{
		    set_rows();
		    super::copy(args.begin(), args.end(), begin());
		}
		
    Array2&	operator =(std::initializer_list<value_type> args)
		{
		    resize(args.size(),
			   (args.size() ? args.begin()->size() : 0), 1);
		    super::copy(args.begin(), args.end(), begin());
		    return *this;
		}
    
  //! 行数と列数を指定して2次元配列を生成する．
  /*!
    \param r	行数
    \param c	列数
    \param unit	1行あたりのバイト数がこの値の倍数になる
  */
		Array2(size_t r, size_t c, size_t unit=1)
		    :super(r), _ncol(c), _buf(size()*stride(unit))
		{
		    set_rows();
		    for (auto& x : *this)
			x.init();
		}

  //! 外部の領域と行数および列数を指定して2次元配列を生成する．
  /*!
    \param p	外部領域へのポインタ
    \param r	行数
    \param c	列数
  */
		Array2(pointer p, size_t r, size_t c)
		    :super(r), _ncol(c), _buf(p, size()*stride(1))
		{
		    set_rows();
		}

  //! 記憶領域を元の配列と共有した部分配列を作る.
  /*!
    \param a	配列
    \param i	部分配列の左上隅要素の行を指定するindex
    \param j	部分配列の左上隅要素の列を指定するindex
    \param r	部分配列の行数
    \param c	部分配列の列数
  */
    template <size_t R2, size_t C2>
		Array2(Array2<T, R2, C2>& a,
		       size_t i, size_t j, size_t r, size_t c)
		    :super(super::partial_size(i, r, a.size())),
		     _ncol(super::partial_size(j, c, a.ncol())),
		     _buf((size() > 0 && ncol() > 0 ? a[i].data() + j
						    : nullptr),
			  (size() > 0 ? (size() - 1)*a.stride() + _ncol : 0))
		{
		    set_rows();
		}    

#if defined(__NVCC__)
    template <class T_, size_t R_, size_t C_>
		Array2(const Array2<T_, R_, C_>& a)
		    :super(a.size()), _ncol(a.ncol()), _buf(size()*stride(1))
		{
		    set_rows();

		    auto	iter = a.begin();
		    for (auto& row : *this)
		    {
			row = *iter;
			++iter;
		    }
		}

    template <class T_, size_t R_, size_t C_>
    Array2&	operator =(const Array2<T_, R_, C_>& a)
		{
		    if (super::resize(a.size()) || _ncol != a.ncol())
		    {
			_ncol = a.ncol();
			_buf.resize(size()*stride(1));
			set_rows();
		    }

		    auto	iter = a.begin();
		    for (auto& row : *this)
		    {
			row = *iter;
			++iter;
		    }
		    return *this;
		}
#else
  //! 他の配列と同一要素を持つ配列を作る（コピーコンストラクタの拡張）．
  /*!
    コピーコンストラクタを定義しないと自動的に作られてしまうので，
    このコンストラクタがあってもコピーコンストラクタを別個に定義
    しなければならない．
    \param expr	コピー元の配列
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
		Array2(const E& expr)
		    :super(expr.size()), _ncol(TU::ncol(expr)),
		     _buf(size()*stride(1))
		{
		    set_rows();
		    super::operator =(expr);
		}

  //! 他の配列を自分に代入する（標準代入演算子の拡張）．
  /*!
    標準代入演算子を定義しないと自動的に作られてしまうので，この代入演算子が
    あっても標準代入演算子を別個に定義しなければならない．
    \param expr		コピー元の配列
    \return		この配列
  */
    template <class E>
    typename std::enable_if<is_range<E>::value, Array2&>::type
		operator =(const E& expr)
		{
		    resize(expr.size(), TU::ncol(expr), 1);
		    super::operator =(expr);
		    return *this;
		}
#endif	// __NVCC__
  //! この配列と記憶領域を共有した部分配列を生成する．
  /*!
    \param i	部分配列の左上隅成分となる行を指定するindex
    \param j	部分配列の左上隅成分となる列を指定するindex
    \param r	部分配列の行数
    \param c	部分配列の列数
    \return	生成された部分配列
  */
    Array2<T>	operator ()(size_t i, size_t j, size_t r, size_t c)
		{
		    return Array2<T>(*this, i, j, r, c);
		}

  /*!
    \param i	部分配列の左上隅成分となる行を指定するindex
    \param j	部分配列の左上隅成分となる列を指定するindex
    \param r	部分配列の行数
    \param c	部分配列の列数
    \return	生成された部分配列
  */
    const Array2<T>
		operator ()(size_t i, size_t j, size_t r, size_t c) const
		{
		    return Array2<T>(const_cast<Array2&>(*this), i, j, r, c);
		}
    
  //! 他の配列に自分を代入する．
  /*!
    \param a	コピー先の配列
    \return	この配列
  */
    template <class T_, size_t R_, size_t C_>
    void	write(Array2<T_, R_, C_>& a) const
		{
		    a.resize(size(), _ncol);

		    auto	iter = a.begin();
		    for (const auto& row : *this)
		    {
			row.write(*iter);
			++iter;
		    }
		}

    Array2&	operator =(const element_type& c)
		{
		    super::operator =(c);
		    return *this;
		}
    
    using		super::begin;
    using		super::cbegin;
    using		super::end;
    using		super::cend;
    using		super::rbegin;
    using		super::crbegin;
    using		super::rend;
    using		super::crend;
    using		super::size;
    using		super::dim;

    pointer		data()		{ return _buf.data(); }
    const_pointer	data()	 const	{ return _buf.data(); }
    size_t		nrow()	 const	{ return size(); }
    size_t		ncol()	 const	{ return _ncol; }
    size_t		stride() const
			{
			    return (size() == 0 ? 0 :
				    size() == 1 ? _ncol : 
				    (_buf.size() - _ncol)/(size() - 1));
			}
    template <class S> typename T::value_type
			at(const Array<S, 2>& p) const
			{
			    const auto	v  = difference_type(floor(p[1]));
			    const auto	a0 = (*this)[v].at(p[0]);
			    const auto	dv = p[1] - v;
			    return (dv ?
				    (1.0 - dv)*a0 + dv*(*this)[v+1].at(p[0]) :
				    a0);
			}

  //! 配列のサイズを変更する．
  /*!
    \param r	新しい行数
    \param c	新しい列数
    \param unit	1行あたりのバイト数がこの値の倍数になる
    \return	rが元の行数より大きい又はcが元の列数と異なればtrue，
		そうでなければfalse
  */
    bool		resize(size_t r, size_t c, size_t unit=1)
			{
			    bool	enlarged = false;
			    if (super::resize(r) || _ncol != c)
			    {
				enlarged = true;
				_ncol = c;
				_buf.resize(size()*stride(unit));
				set_rows();
			    }
			    for (auto& x : *this)
				x.init();
			    return enlarged;
			}
	
  //! 配列が内部で使用する記憶領域を指定したものに変更する．
  /*!
    \param p	新しい記憶領域へのポインタ
    \param r	新しい行数
    \param c	新しい列数
  */
    void		resize(pointer p, size_t r, size_t c)
			{
			    super::resize(r);
			    _ncol = c;
			    _buf.resize(p, size()*stride(1));
			    set_rows();
			}

  //! 入力ストリームから配列を読み込む(binary)．
  /*!
    \param in	入力ストリーム
    \return	inで指定した入力ストリーム
  */
    std::istream&	restore(std::istream& in)
			{
			    for (auto& row : *this)
				row.restore(in);
			    return in;
			}

  //! 出力ストリームに配列を書き出す(binary)．
  /*!
    \param out	出力ストリーム
    \return	outで指定した出力ストリーム
  */
    std::ostream&	save(std::ostream& out) const
			{
			    for (const auto& row : *this)
				row.save(out);
			    return out;
			}

    std::istream&	get(std::istream& in,
			    size_t i=0, size_t j=0, size_t jmax=0)	;
    
  private:
    void		set_rows()
			{
			    auto	p    = _buf.data();
			    const auto	strd = stride();
			    for (auto& row : *this)
			    {
				row.resize(p, _ncol);
				p += strd;
			    }
			}

    size_t		stride(size_t unit) const
			{
			    constexpr size_t
				siz = sizeof(typename buf_type::value_type);

			    if (unit == 0)
				unit = 1;
			    const auto	n = lcm(siz, unit)/siz;

			    return n*((_ncol + n - 1)/n);
			}

  private:
    size_t		_ncol;		//!< 列数
    buf_type		_buf;		//!< データを格納するバッファ
};

//! 入力ストリームから指定した箇所に2次元配列を読み込む(ASCII)．
/*!
  \param in	入力ストリーム
  \param i	読み込み先の先頭行を指定するindex
  \param j	読み込み先の先頭列を指定するindex
  \param jmax	これまでに読んできた要素の列番号の最大値
  \return	inで指定した入力ストリーム
*/
template <class T, size_t R, size_t C> std::istream&
Array2<T, R, C>::get(std::istream& in, size_t i, size_t j, size_t jmax)
{
    char	c;

    while (in.get(c))			// Skip white spaces other than '\n'.
	if (!isspace(c) || c == '\n')
	    break;

    if (!in || c == '\n')
    {
	++i;				// Proceed to the next row.
	if (j > jmax)
	    jmax = j;
	j = 0;				// Return to the first column.

	while (in.get(c))		// Skip white spaces other than '\n'.
	    if (!isspace(c) || c == '\n')
		break;

	if (!in || c == '\n')
	{
	    if (jmax > 0)
		resize(i, jmax);
	    return in;
	}
    }
    in.putback(c);
    typename buf_type::value_type	val;
    in >> val;
    get(in, i, j + 1, jmax);
    (*this)[i][j] = std::move(val);
    return in;
}    

/************************************************************************
*  I/O functions							*
************************************************************************/
//! 出力ストリームへ式の演算結果を書き出し(ASCII)，さらに改行コードを出力する．
/*!
  \param out	出力ストリーム
  \param expr	その結果を書き出す式
  \return	outで指定した出力ストリーム
*/
template <class E>
typename std::enable_if<detail::is_opnode<E>::value, std::ostream&>::type
operator <<(std::ostream& out, const E& expr)
{
    for (const auto& x : expr)
	out << ' ' << x;
    return out << std::endl;
}

//! 出力ストリームへ配列を書き出し(ASCII)，さらに改行コードを出力する．
/*!
  \param out	出力ストリーム
  \param a	書き出す配列
  \return	outで指定した出力ストリーム
*/
template <class T, size_t D, class ALLOC> inline std::ostream&
operator <<(std::ostream& out, const Array<T, D, ALLOC>& a)
{
    return a.put(out) << std::endl;
}

//! 入力ストリームから配列を読み込む(ASCII)．
/*!
  \param in	入力ストリーム
  \param a	配列の読み込み先
  \return	inで指定した入力ストリーム
*/
template <class T, size_t D, class ALLOC> inline std::istream&
operator >>(std::istream& in, Array<T, D, ALLOC>& a)
{
    return a.get(in >> std::ws);
}

//! 入力ストリームから2次元配列を読み込む(ASCII)．
/*!
  \param in	入力ストリーム
  \param a	配列の読み込み先
  \return	inで指定した入力ストリーム
*/
template <class T, size_t R, size_t C> inline std::istream&
operator >>(std::istream& in, Array2<T, R, C>& a)
{
    return a.get(in >> std::ws);
}

#if !defined(__NVCC__)
namespace detail
{
  /**********************************************************************
  *  class Product<L, R>						*
  **********************************************************************/
  //! 2つの配列式の積演算を表すクラス
  template <class L, class R>
  class Product : public opnode
  {
    private:
      typedef is_range<value_t<L> >			lvalue_is_range;
      typedef is_range<value_t<R> >			rvalue_is_range;
      typedef element_t<R>				element_type;
      
    // 左辺が多次元配列ならあらかじめ右辺を評価する: A*b, A*B
      typedef argument_t<R, lvalue_is_range::value>	rargument_type;
      typedef typename std::decay<rargument_type>::type	right_type;
    
    // 右辺のみが多次元配列ならあらかじめ左辺を評価する: a*B
    // (両辺とも多次元配列ならあらかじめ右辺のみを評価する: A*B)
      typedef argument_t<L, (!lvalue_is_range::value &&
			      rvalue_is_range::value)>	largument_type;
      typedef typename std::decay<largument_type>::type	left_type;

      template <class L_>
      struct RowIterator
      {
	  typedef typename L_::const_iterator			type;
      };

      template <class R_>
      struct ColumnIterator
      {
	  typedef column_iterator<void,
				  typename R_::const_iterator>	type;
      };

    // 左辺が多次元配列なら左辺の各行を反復: A*b, A*B
    // そうでないなら右辺の各列を反復: a*B
      typedef typename std::conditional<
	  lvalue_is_range::value, RowIterator<left_type>,
	  ColumnIterator<right_type> >::type::type	base_iterator;

      template <class R_>
      struct ColumnType
      {
	  typedef typename std::iterator_traits<
	      typename ColumnIterator<R_>::type>::value_type	type;
      };
      
    // 右辺の反復単位は，右辺が多次元配列なら列: b，そうでないなら右辺自体: B
      typedef typename std::conditional<
	  rvalue_is_range::value, ColumnType<right_type>,
	  impl::identity<right_type> >::type::type	rcolumn_type;

    // 反復子が返すProduct演算子は，
    // 左辺が多次元配列なら"左辺の行x右辺": a*B，a*b
    // そうでないなら"左辺x右辺の列": a*b
      typedef typename std::conditional<
	  lvalue_is_range::value,
	  Product<value_t<left_type>, right_type>,
	  Product<left_type, rcolumn_type> >::type	product_type;
    
    public:
    //! value()の戻り値の型
      typedef typename std::conditional<
	  (lvalue_is_range::value || rvalue_is_range::value),
	  Product<L, R>, element_type>::type		type;
    //! 要素の型
      typedef typename product_type::type		value_type;
    //! 評価結果の型
      typedef typename std::conditional<
	  (lvalue_is_range::value || rvalue_is_range::value),
	  Array<result_t<value_type> >,
	  element_type>::type				result_type;

    //! 定数反復子
      class const_iterator
	  : public boost::iterator_adaptor<const_iterator,
					   base_iterator,
					   value_type,
					   boost::use_default,
					   value_type>
      {
	private:
	  typedef boost::iterator_adaptor<const_iterator,
					  base_iterator,
					  value_type,
					  boost::use_default,
					  value_type>	super;
	  typedef typename std::conditional<
		      lvalue_is_range::value,
		      right_type, left_type>::type	other_type;
	
	public:
	  typedef typename super::reference		reference;

	  friend class	boost::iterator_core_access;
	
	public:
	  const_iterator(base_iterator iter, const other_type& other)
	      :super(iter), _other(other)				{}
	
	private:
	  reference	dereference(std::true_type) const	// A*b, A*B
			{
			    return product_type::value(*super::base(), _other);
			}
	  reference	dereference(std::false_type) const	// a*B
			{
			    return product_type::value(_other, *super::base());
			}
	  reference	dereference() const
			{
			    return dereference(lvalue_is_range());
			}
	
	private:
	  const other_type&	_other;
      };

      typedef const_iterator	iterator;	//!< 定数反復子の別名
    
    private:
      static type	value(const L& l, const R& r, std::true_type)
			{
			    return Product(l, r);	// A*b, a*B, A*B
			}
      static type	value(const L& l, const R& r, std::false_type)	// a*b
			{
			    return std::inner_product(l.begin(), l.end(),
						      r.begin(),
						      element_type(0));
			}
      const_iterator	begin(std::true_type) const
			{
			    return const_iterator(_l.begin(), _r);
			}
      const_iterator	begin(std::false_type) const
			{
			    return const_iterator(
				       column_begin(_r.begin(), _r.end()), _l);
			}
      const_iterator	end(std::true_type) const
			{
			    return const_iterator(_l.end(), _r);
			}
      const_iterator	end(std::false_type) const
			{
			    return const_iterator(
				       column_end(_r.begin(), _r.end()), _l);
			}
      size_t		size(std::true_type) const	// A*b, A*B
			{
			    return _l.size();
			}
      size_t		size(std::false_type) const	// a*B
			{
			    return ncol(_r);
			}
      void		check_size(size_t size, std::true_type) const
			{
			    if (ncol(_l) != size)
				throw std::logic_error("Product<L, R>::check_size: mismatched size!");
			}
      void		check_size(size_t size, std::false_type) const
			{
			    if (_l.size() != size)
				throw std::logic_error("Product<L, R>::check_size: mismatched size!");
			}
    
    public:
			Product(const L& l, const R& r)
			    :_l(l), _r(r)
			{
			    check_size(_r.size(), lvalue_is_range());
			}

      static type	value(const L& l, const R& r)
			{
			    return value(l, r,
					 std::integral_constant<
					     bool,
					     (lvalue_is_range::value ||
					      rvalue_is_range::value)>());
			}
    
    //! 演算結果の先頭要素を指す定数反復子を返す.
      const_iterator	begin() const
			{
			    return begin(lvalue_is_range());
			}
    //! 演算結果の末尾を指す定数反復子を返す.
      const_iterator	end() const
			{
			    return end(lvalue_is_range());
			}
    //! 演算結果の要素数を返す.
      size_t		size() const
			{
			    return size(lvalue_is_range());
			}
    
    private:
      largument_type	_l;
      rargument_type	_r;
  };

  /**********************************************************************
  *  class ExteriorProduct<L, R>					*
  **********************************************************************/
  //! 2つの配列型の式の外積演算を表すクラス
  template <class L, class R>
  class ExteriorProduct : public opnode
  {
    private:
    // 左右両辺をあらかじめ評価する
      typedef argument_t<L, true>			largument_type;
      typedef argument_t<R, true>			rargument_type;
      typedef typename std::decay<rargument_type>::type	right_type;
      typedef typename std::decay<largument_type>::type
			  ::const_iterator		base_iterator;
    
    public:
    //! 評価結果の型
      typedef Array<right_type>				result_type;
    //! 要素の型
      typedef decltype(std::declval<element_t<L> >() *
		       std::declval<right_type>())	value_type;
      
    //! 定数反復子
      class const_iterator
	  : public boost::iterator_adaptor<const_iterator,
					   base_iterator,
					   value_type,
					   boost::use_default,
					   value_type>
      {
	private:
	  typedef boost::iterator_adaptor<const_iterator,
					  base_iterator,
					  value_type,
					  boost::use_default,
					  value_type>	super;
	
	public:
	  typedef typename super::reference		reference;

	friend class	boost::iterator_core_access;
	
	public:
	  const_iterator(base_iterator iter, const right_type& r)
	      :super(iter), _r(r)				{}
	
	private:
	  reference	dereference() const
			{
			    return *super::base() * _r;
			}
	
	private:
	  const right_type&	_r;
      };

      typedef const_iterator	iterator;	//!< 定数反復子の別名
    
    public:
			ExteriorProduct(const L& l, const R& r)
			    :_l(l), _r(r)			{}

    //! 演算結果の先頭要素を指す定数反復子を返す.
      const_iterator	begin() const
			{
			    return const_iterator(_l.begin(), _r);
			}
    //! 演算結果の末尾を指す定数反復子を返す.
      const_iterator	end() const
			{
			    return const_iterator(_l.end(), _r);
			}
    //! 演算結果の要素数を返す.
      size_t		size() const
			{
			    return _l.size();
			}
    
    private:
      largument_type	_l;
      rargument_type	_r;
  };

  /**********************************************************************
  *  class CrossProduct<L, R>						*
  **********************************************************************/
  //! 2つの配列型の式のベクトル積演算を表すクラス
  template <class L, class R>
  class CrossProduct : public detail::opnode
  {
    private:
    // 左辺が1次元配列ならあらかじめ評価する
      typedef value_t<L>				lvalue_type;
      typedef is_range<lvalue_type>			lvalue_is_range;
      typedef argument_t<L, !lvalue_is_range::value>	largument_type;

    // あらかじめ右辺を評価する
      typedef argument_t<R, true>			rargument_type;
      typedef typename std::decay<rargument_type>::type	right_type;

    // 3次元ベクトル型
      typedef value_t<right_type>			rvalue_type;
      typedef Array<rvalue_type, 3>			array3_type;

    // 左辺が多次元配列ならその行と右辺のベクトル積を返す反復子を定義
      typedef const_iterator_t<L>			base_iterator;
      typedef CrossProduct<lvalue_type, right_type>	product_type;

    public:
    //! value()の戻り値の型
      typedef typename std::conditional<
	  lvalue_is_range::value,
	  CrossProduct<L, R>, array3_type>::type	type;
    //! 要素の型(左辺が1次元配列なら product_type は評価できないことに注意)
      typedef typename std::conditional<
	  lvalue_is_range::value,
	  product_type,
	  impl::identity<array3_type> >::type::type	value_type;
    //! 評価結果の型
      typedef typename std::conditional<
	  lvalue_is_range::value,
	  Array<result_t<value_type> >,
	  array3_type>::type				result_type;
    
    //! 定数反復子
      class const_iterator
	  : public boost::iterator_adaptor<const_iterator,
					   base_iterator,
					   value_type,
					   boost::use_default,
					   value_type>
      {
	private:
	  typedef boost::iterator_adaptor<const_iterator,
					  base_iterator,
					  value_type,
					  boost::use_default,
					  value_type>	super;

	public:
	  typedef typename super::difference_type	difference_type;
	  typedef typename super::reference		reference;
	  typedef typename super::iterator_category	iterator_category;

	  friend class	boost::iterator_core_access;

	public:
	  const_iterator(base_iterator iter, const right_type& r)
	      :super(iter), _r(r)					{}

	private:
	  reference	dereference() const
			{
			    return product_type(*super::base(), _r).value();
			}

	private:
	  const right_type&	_r;
      };

      typedef const_iterator	iterator;	//!< 定数反復子の別名

    private:
      void		check_size(size_t size, std::true_type) const
			{
			    if (ncol(_l) != size)
				throw std::logic_error("CrossProduct<L, R>::check_size: mismatched size!");
			}
      void		check_size(size_t size, std::false_type) const
			{
			    if (_l.size() != size)
				throw std::logic_error("CrossProduct<L, R>::check_size: mismatched size!");
			}
      type		value(std::true_type) const
			{
			    return *this;
			}
      type		value(std::false_type) const
			{
			    type	val;
			    val[0] = _l[1] * _r[2] - _l[2] * _r[1];
			    val[1] = _l[2] * _r[0] - _l[0] * _r[2];
			    val[2] = _l[0] * _r[1] - _l[1] * _r[0];

			    return val;
			}
    
    public:
			CrossProduct(const L& l, const R& r)
			    :_l(l), _r(r)
			{
			    check_size(3, lvalue_is_range());
			    check_size(_r.size(), lvalue_is_range());
			}

      type		value()
			{
			    return value(lvalue_is_range());
			}

    //! 演算結果の先頭要素を指す定数反復子を返す.
      const_iterator	begin() const
			{
			    return const_iterator(_l.begin(), _r);
			}
    //! 演算結果の末尾を指す定数反復子を返す.
      const_iterator	end() const
			{
			    return const_iterator(_l.end(), _r);
			}
    //! 演算結果の要素数を返す.
      size_t		size() const
			{
			    return _l.size();
			}
    
    private:
      largument_type	_l;
      rargument_type	_r;
  };
}

/************************************************************************
*  numerical operators							*
************************************************************************/
//! 2つの配列式の積をとる.
/*!
  aliasingを防ぐため，積演算子ノードではなく評価結果そのものを返す.
  \param l	左辺の配列式
  \param r	右辺の配列式
  \return	積の評価結果
*/
template <class L, class R,
	  typename std::enable_if<(is_range<L>::value &&
				   is_range<R>::value)>::type* = nullptr>
inline typename detail::Product<L, R>::result_type
operator *(const L& l, const R& r)
{
    return detail::Product<L, R>::value(l, r);
}

//! 2つの配列タイプの式の外積をとる.
/*!
  \param l	左辺の配列式
  \param r	右辺の配列式
  \return	外積演算子ノード
*/
template <class L, class R,
	  typename std::enable_if<(is_range<L>::value &&
				   is_range<R>::value)>::type* = nullptr>
inline auto
operator %(const L& l, const R& r)
    -> decltype(detail::ExteriorProduct<L, R>(l, r))
{
    return detail::ExteriorProduct<L, R>(l, r);
}

//! 2つの配列タイプの式のベクトル積をとる.
/*!
  aliasingを防ぐため，積演算子ノードではなく評価結果そのものを返す.
  \param l	左辺の配列式
  \param r	右辺の配列式
  \return	ベクトル積
*/
template <class L, class R,
	  typename std::enable_if<(is_range<L>::value &&
				   is_range<R>::value)>::type* = nullptr>
inline typename detail::CrossProduct<L, R>::result_type
operator ^(const L& l, const R& r)
{
    return detail::CrossProduct<L, R>(l, r).value();
}
#endif	// !__NVCC__
}
#endif	// !__TU_ARRAYPP_H
