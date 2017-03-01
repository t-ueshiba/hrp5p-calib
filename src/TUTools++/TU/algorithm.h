/*
 *  $Id: algorithm.h 2048 2016-11-21 11:01:56Z ueshiba $
 */
/*!
  \file		algorithm.h
  \brief	各種アルゴリズムの定義と実装
*/
#ifndef __TU_ALGORITHM_H
#define __TU_ALGORITHM_H

#include <algorithm>

/*!
  \namespace	std
  \brief	いくつかの基本的な関数を名前空間stdに追加
*/
namespace std
{
/************************************************************************
*  generic algorithms							*
************************************************************************/
//! 3つの引数のうち最小のものを返す．
template <class T> inline const T&
min(const T& a, const T& b, const T& c)
{
    return min(min(a, b), c);
}

//! 3つの引数のうち最大のものを返す．
template <class T> inline const T&
max(const T& a, const T& b, const T& c)
{
    return max(max(a, b), c);
}
    
//! 4つの引数のうち最小のものを返す．
template <class T> inline const T&
min(const T& a, const T& b, const T& c, const T& d)
{
    return min(min(a, b, c), d);
}

//! 4つの引数のうち最大のものを返す．
template <class T> inline const T&
max(const T& a, const T& b, const T& c, const T& d)
{
    return max(max(a, b, c), d);
}

#if __cplusplus < 201700L
template <class ITER, class SIZE, class FUNC> ITER
for_each_n(ITER iter, SIZE n, FUNC func)
{
    for (SIZE i = 0; i < n; ++i, ++iter)
	func(*iter);
    return iter;
}
#endif
}

/*!
  \namespace	TU
  \brief	本ライブラリで定義されたクラスおよび関数を納める名前空間
*/
namespace TU
{
/************************************************************************
*  generic algorithms							*
************************************************************************/
//! 条件を満たす要素が前半に，そうでないものが後半になるように並べ替える．
/*!
  \param begin	データ列の先頭を示す反復子
  \param end	データ列の末尾を示す反復子
  \param pred	条件を指定する単項演算子
  \return	条件を満たさない要素の先頭を示す反復子
*/
template <class Iter, class Pred> Iter
pull_if(Iter begin, Iter end, Pred pred)
{
    for (Iter iter = begin; iter != end; ++iter)
	if (pred(*iter))
	    std::iter_swap(begin++, iter);
    return begin;
}

//! 2つの引数の差の絶対値を返す．
template <class T> inline T
diff(const T& a, const T& b)
{
    return (a > b ? a - b : b - a);
}

//! 2次元データに対して3x3ウィンドウを走査してin-place近傍演算を行う．
/*!
  \param begin	最初の行を示す反復子
  \param end	最後の行の次を示す反復子
  \param op	3x3ウィンドウを定義域とする演算子
*/
template <class Iterator, class OP> void
op3x3(Iterator begin, Iterator end, OP op)
{
    typedef typename std::iterator_traits<Iterator>::value_type	row_type;
    typedef typename row_type::iterator				col_iterator;
    typedef typename std::iterator_traits<col_iterator>::value_type
								value_type;
    
    row_type	buf = *begin;		// 一つ前の行
    --end;
    for (Iterator iter = ++begin; iter != end; )
    {
	col_iterator	p    = buf.begin();	// 左上画素
	col_iterator	q    = iter->begin();	// 左画素	
	value_type	val  = *q;		// 左画素における結果
	col_iterator	cend = (++iter)->end();
	--cend;
	--cend;				// 左下画素の右端
	for (col_iterator c = iter->begin(); c != cend; )   // 左下画素について
	{						    // ループ
	    value_type	tmp = op(p, q, c);	// 注目画素における結果
	    *p  = *q;			// 次行の左上画素 = 左画素
	    *q  = val;			// 左画素における結果を書き込む
	    val	= tmp;			// 次ウィンドウの左画素における結果を保存
	    ++c;
	    ++p;
	    ++q;
	}
	*p = *q;			// 次行の左上画素 = 左画素
	*q = val;			// 左画素における結果を書き込む
	++p;
	++q;
	*p = *q;			// 次行の上画素 = 注目画素
    }
}

//! 2つのシーケンスの個々の要素に2変数関数を適用する.
/*!
  \param begin1	第1のシーケンスの先頭要素を指す反復子
  \param end1	第1のシーケンスの末尾要素の次を指す反復子
  \param begin2	第2のシーケンスの先頭要素を指す反復子
  \param func	適用する2変数関数
*/
template <class Iterator1, class Iterator2, class FUNC> FUNC
for_each(Iterator1 begin1, Iterator1 end1, Iterator2 begin2, FUNC func)
{
    for (; begin1 != end1; ++begin1, ++begin2)
	func(*begin1, *begin2);
    return func;
}
    
/************************************************************************
*  morphological operations						*
************************************************************************/
//! 3x3ウィンドウ内の最大値を返す．
/*!
  \param p	注目点の左上点を指す反復子
  \param q	注目点の左の点を指す反復子
  \param r	注目点の左下点を指す反復子
  \return	3x3ウィンドウ内の最大値
*/
template <class P> inline typename std::iterator_traits<P>::value_type
max3x3(P p, P q, P r)
{
    using namespace	std;
	    
    return max(max(*p, *(p + 1), *(p + 2)),
	       max(*q, *(q + 1), *(q + 2)),
	       max(*r, *(r + 1), *(r + 2)));
}
    
//! 3x3ウィンドウ内の最小値を返す．
/*!
  \param p	注目点の左上点を指す反復子
  \param q	注目点の左の点を指す反復子
  \param r	注目点の左下点を指す反復子
  \return	3x3ウィンドウ内の最小値
*/
template <class P> inline typename std::iterator_traits<P>::value_type
min3x3(P p, P q, P r)
{
    using namespace	std;
	    
    return min(min(*p, *(p + 1), *(p + 2)),
	       min(*q, *(q + 1), *(q + 2)),
	       min(*r, *(r + 1), *(r + 2)));
}

//! morphological open演算をin-placeで行う．
/*
  指定された回数だけ収縮(erosion)を行った後，同じ回数だけ膨張(dilation)を行う．
  \param begin	最初の行を示す反復子
  \param end	最後の行の次を示す反復子
  \param niter	収縮と膨張の回数
*/
template <class Iterator> void
mopOpen(Iterator begin, Iterator end, size_t niter=1)
{
    typedef typename std::iterator_traits<Iterator>::value_type::iterator
								col_iterator;

    for (size_t n = 0; n < niter; ++n)
	op3x3(begin, end, min3x3<col_iterator>);	// 収縮(erosion)
    for (size_t n = 0; n < niter; ++n)
	op3x3(begin, end, max3x3<col_iterator>);	// 膨張(dilation)
}

//! morphological close演算をin-placeで行う．
/*
  指定された回数だけ膨張(dilation)を行った後，同じ回数だけ収縮(erosion)を行う．
  \param begin	最初の行を示す反復子
  \param end	最後の行の次を示す反復子
  \param niter	収縮と膨張の回数
*/
template <class Iterator> void
mopClose(Iterator begin, Iterator end, size_t niter=1)
{
    typedef typename std::iterator_traits<Iterator>::value_type::iterator
								col_iterator;
    
    for (size_t n = 0; n < niter; ++n)
	op3x3(begin, end, max3x3<col_iterator>);	// 膨張(dilation)
    for (size_t n = 0; n < niter; ++n)
	op3x3(begin, end, min3x3<col_iterator>);	// 収縮(erosion)
}
    
}
#endif	// !__TU_ALGORITHM_H
