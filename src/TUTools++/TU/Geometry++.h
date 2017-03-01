/*
 *  $Id: Geometry++.h 1943 2016-02-21 01:47:13Z ueshiba $
 */
/*!
  \file		Geometry++.h
  \brief	点，直線，超平面および各種の幾何変換に関するクラスの定義と実装
*/
#ifndef __TU_GEOMETRYPP_H
#define __TU_GEOMETRYPP_H

#include "TU/Vector++.h"
#include "TU/Minimize.h"
#include <limits>

namespace TU
{
/************************************************************************
*  class Point1<T>							*
************************************************************************/
//! T型の座標成分を持つ1次元点を表すクラス
/*!
  \param T	座標の型
 */
template <class T>
class Point1 : public Vector<T, 1>
{
  private:
    typedef Vector<T, 1>	super;
    
  public:
  //! 指定された座標成分を持つ1次元点を作る．
  /*!
    \param u	u座標
  */
    explicit Point1(T u=0)	:super()		{(*this)[0] = u;}

  //! 他の1次元ベクトルと同一要素を持つ1次元点を作る．
  /*!
    \param v	コピー元1次元ベクトル
  */
    template <class T2, size_t D2>
    Point1(const Vector<T2, D2>& v) :super(v)		{}

  //! 他の1次元ベクトルを自分に代入する．
  /*!
    \param v	コピー元1次元ベクトル
    \return	この1次元点
  */
    template <class T2, size_t D2>
    Point1&	operator =(const Vector<T2, D2>& v)
		{
		    super::operator =(v);
		    return *this;
		}
};

typedef Point1<short>	Point1s;		//!< short型座標を持つ1次元点
typedef Point1<int>	Point1i;		//!< int型座標を持つ1次元点
typedef Point1<float>	Point1f;		//!< float型座標を持つ1次元点
typedef Point1<double>	Point1d;		//!< double型座標を持つ1次元点

/************************************************************************
*  class Point2<T>							*
************************************************************************/
//! T型の座標成分を持つ2次元点を表すクラス
/*!
  \param T	座標の型
 */
template <class T>
class Point2 : public Vector<T, 2>
{
  private:
    typedef Vector<T, 2>	super;
    
  public:
  //! 指定された座標成分を持つ2次元点を作る．
  /*!
    \param u	u座標
    \param v	v座標
  */
    explicit	Point2(T u=0, T v=0) :super()
		{
		    (*this)[0] = u; (*this)[1] = v;
		}

#if !defined(__NVCC__)
  //! 他の2次元ベクトルと同一要素を持つ2次元点を作る．
  /*!
    \param v	コピー元2次元ベクトル
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
		Point2(const E& v) :super(v)	{}

  //! 他の2次元ベクトルを自分に代入する．
  /*!
    \param v	コピー元2次元ベクトル
    \return	この2次元点
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
    Point2&	operator =(const E& v)	{ super::operator =(v); return *this; }
#endif	// !__NVCC__

  //! 指定された方向の8近傍点を返す．
  /*!
    \param dir	8近傍点の方向(mod 8で解釈．右隣を0とし，時計回りに1づつ増加)
    \return	8近傍点
  */
    Point2	neighbor(int dir) const	{ return Point2(*this).move(dir); }

    Point2&	move(int dir)					;
    int		adj(const Point2& p)			const	;
    int		dir(const Point2& p)			const	;
    int		angle(const Point2& p, const Point2& q)	const	;
};

//! 指定された方向の8近傍点に自身を移動する．
/*!
  \param dir	8近傍点の方向(mod 8で解釈．右隣を0とし，時計回りに1づつ増加)
  \return	移動後のこの点
*/
template <class T> Point2<T>&
Point2<T>::move(int dir)
{
    switch (dir % 8)
    {
      case 0:
	++(*this)[0];
	break;
      case 1:
      case -7:
	++(*this)[0];
	++(*this)[1];
	break;
      case 2:
      case -6:
	++(*this)[1];
	break;
      case 3:
      case -5:
	--(*this)[0];
	++(*this)[1];
	break;
      case 4:
      case -4:
	--(*this)[0];
	break;
      case 5:
      case -3:
	--(*this)[0];
	--(*this)[1];
	break;
      case 6:
      case -2:
	--(*this)[1];
	break;
      case 7:
      case -1:
	++(*this)[0];
	--(*this)[1];
	break;
    }
    return *this;
}

//! この2次元点と指定された2次元点が8隣接しているか調べる．
/*!
  \param p	2次元点
  \return	pと一致していれば-1，8隣接していれば1，いずれでもなければ0
*/
template <class T> int
Point2<T>::adj(const Point2<T>& p) const
{
    const int	du = int(p[0] - (*this)[0]), dv = int(p[1] - (*this)[1]);

    if (du == 0 && dv == 0)
        return -1;
    switch (du)
    {
      case -1:
      case 0:
      case 1:
        switch (dv)
        {
          case -1:
          case 0:
          case 1:
            return 1;
        }
        break;
    }
    return 0;
}

//! この2次元点から指定された2次元点への向きを返す．
/*!
  \param p	2次元点
  \return	-180degから180degまでを8等分した区間を表す-4から3までの整数値．
		特に，pがこの点に一致するならば4
*/
template <class T> int
Point2<T>::dir(const Point2<T>& p) const
{
    const int	du = int(p[0] - (*this)[0]), dv = int(p[1] - (*this)[1]);

    if (du == 0 && dv == 0)
        return 4;
    if (dv >= 0)
        if (du > dv)
            return 0;
        else if (du > 0)
            return 1;
        else if (du > -dv)
            return 2;
        else if (dv > 0)
            return 3;
        else
            return -4;
    else
        if (du >= -dv)
            return -1;
        else if (du >= 0)
            return -2;
        else if (du >= dv)
            return -3;
        else
            return -4;
}

//! この2次元点と指定された2つの2次元点がなす角度を返す．
/*!
  \param p	2次元点
  \param q	2次元点
  \return	p->*this->qがなす角度を-180degから180degまでを8等分した
		区間で表した-4から3までの整数値．特に，p, qの少なくとも
		一方がこの点に一致するならば4
*/
template <class T> int
Point2<T>::angle(const Point2<T>& p, const Point2<T>& q) const
{
    int dp = p.dir(*this), ang = dir(q);
    
    if (dp == 4 || ang == 4)
        return 4;
    else if ((ang -= dp) > 3)
        return ang - 8;
    else if (ang < -4)
        return ang + 8;
    else
        return ang;
}

typedef Point2<short>	Point2s;		//!< short型座標を持つ2次元点
typedef Point2<int>	Point2i;		//!< int型座標を持つ2次元点
typedef Point2<float>	Point2f;		//!< float型座標を持つ2次元点
typedef Point2<double>	Point2d;		//!< double型座標を持つ2次元点

/************************************************************************
*  class Point3<T>							*
************************************************************************/
//! T型の座標成分を持つ3次元点を表すクラス
/*!
  \param T	座標の型
 */
template <class T>
class Point3 : public Vector<T, 3>
{
  private:
    typedef Vector<T, 3>	super;
    
  public:
  //! 指定された座標成分を持つ3次元点を作る．
  /*!
    \param x	x座標
    \param y	y座標
    \param z	z座標
  */
    explicit	Point3(T x=0, T y=0, T z=0) :super()
		{
		    (*this)[0] = x; (*this)[1] = y; (*this)[2] = z;
		}

#if !defined(__NVCC__)
  //! 他の3次元ベクトルと同一要素を持つ3次元点を作る．
  /*!
    \param v	コピー元3次元ベクトル
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
		Point3(const E& v) :super(v)				{}

  //! 他の3次元ベクトルを自分に代入する．
  /*!
    \param v	コピー元3次元ベクトル
    \return	この3次元点
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
    Point3&	operator =(const E& v)	{ super::operator =(v); return *this; }
#endif	// !__NVCC__
};

typedef Point3<short>	Point3s;		//!< short型座標を持つ3次元点
typedef Point3<int>	Point3i;		//!< int型座標を持つ3次元点
typedef Point3<float>	Point3f;		//!< float型座標を持つ3次元点
typedef Point3<double>	Point3d;		//!< double型座標を持つ3次元点

/************************************************************************
*  class Normalize<S>							*
************************************************************************/
//! 点の非同次座標の正規化変換を行うクラス
/*!
  \f$\TUud{x}{}=[\TUtvec{x}{}, 1]^\top~
  (\TUvec{x}{} \in \TUspace{R}{d})\f$に対して，以下のような平行移動と
  スケーリングを行う:
  \f[
	\TUud{y}{} =
	\TUbeginarray{c} s^{-1}(\TUvec{x}{} - \TUvec{c}{}) \\ 1	\TUendarray =
	\TUbeginarray{ccc}
	  s^{-1} \TUvec{I}{d} & -s^{-1}\TUvec{c}{} \\ \TUtvec{0}{d} & 1
	\TUendarray
	\TUbeginarray{c} \TUvec{x}{} \\ 1 \TUendarray =
	\TUvec{T}{}\TUud{x}{}
  \f]
  \f$s\f$と\f$\TUvec{c}{}\f$は，振幅の2乗平均値が空間の次元\f$d\f$に,
  重心が原点になるよう決定される．
*/
template <class S>
class Normalize
{
  public:
    typedef S				element_type;
    typedef Vector<element_type>	vector_type;
    typedef Matrix<element_type>	matrix_type;
    
  public:
  //! 空間の次元を指定して正規化変換オブジェクトを生成する．
  /*!
    恒等変換として初期化される．
    \param d	空間の次元
  */
    Normalize(size_t d=2) :_npoints(0), _scale(1.0), _centroid(d)	{}

    template <class Iterator>
    Normalize(Iterator first, Iterator last)				;
    
    template <class Iterator>
    void		update(Iterator first, Iterator last)		;

    size_t		spaceDim()				const	;
    template <class S2, size_t D2>
    vector_type		operator ()(const Vector<S2, D2>& x)
								const	;
    template <class S2, size_t D2>
    vector_type		normalizeP(const Vector<S2, D2>& x)
								const	;
    
    matrix_type		T()					const	;
    matrix_type		Tt()					const	;
    matrix_type		Tinv()					const	;
    matrix_type		Ttinv()					const	;
    element_type	scale()					const	;
    const vector_type&	centroid()				const	;
    
  private:
    size_t		_npoints;	//!< これまでに与えた点の総数
    element_type	_scale;		//!< これまでに与えた点の振幅のRMS値
    vector_type		_centroid;	//!< これまでに与えた点群の重心
};

//! 与えられた点群の非同次座標から正規化変換オブジェクトを生成する．
/*!
  振幅の2乗平均値が spaceDim(), 重心が原点になるような正規化変換が計算される．
  \param first	点群の先頭を示す反復子
  \param last	点群の末尾を示す反復子
*/
template <class S> template <class Iterator> inline
Normalize<S>::Normalize(Iterator first, Iterator last)
    :_npoints(0), _scale(1.0), _centroid()
{
    update(first, last);
}
    
//! 新たに点群を追加してその非同次座標から現在の正規化変換を更新する．
/*!
  振幅の2乗平均値が spaceDim(), 重心が原点になるような正規化変換が計算される．
  \param first			点群の先頭を示す反復子
  \param last			点群の末尾を示す反復子
  \throw std::invalid_argument	これまでに与えられた点の総数が0の場合に送出
*/
template <class S> template <class Iterator> void
Normalize<S>::update(Iterator first, Iterator last)
{
    if (_npoints == 0)
    {
	if (first == last)
	    throw std::invalid_argument("Normalize::update(): 0-length input data!!");
	_centroid.resize(first->size());
    }
    _scale = _npoints * (spaceDim() * _scale * _scale + _centroid * _centroid);
    _centroid *= _npoints;
    while (first != last)
    {
	_scale += first->square();
	_centroid += *first++;
	++_npoints;
    }
    if (_npoints == 0)
	throw std::invalid_argument("Normalize::update(): no input data accumulated!!");
    _centroid /= _npoints;
    _scale = sqrt((_scale / _npoints - _centroid * _centroid) / spaceDim());
}

//! この正規化変換が適用される空間の次元を返す．
/*! 
  \return	空間の次元(同次座標のベクトルとしての次元は spaceDim()+1)
*/
template <class S> inline size_t
Normalize<S>::spaceDim() const
{
    return _centroid.size();
}
    
//! 与えられた点に正規化変換を適用してその非同次座標を返す．
/*!
  \param x	点の非同次座標(spaceDim() 次元)
  \return	正規化された点の非同次座標(spaceDim() 次元)
*/
template <class S> template <class S2, size_t D2>
inline typename Normalize<S>::vector_type
Normalize<S>::operator ()(const Vector<S2, D2>& x) const
{
    return (vector_type(x) -= _centroid) /= _scale;
}

//! 与えられた点に正規化変換を適用してその同次座標を返す．
/*!
  \param x	点の非同次座標(spaceDim() 次元)
  \return	正規化された点の同次座標(spaceDim()+1次元)
*/
template <class S> template <class S2, size_t D2>
inline typename Normalize<S>::vector_type
Normalize<S>::normalizeP(const Vector<S2, D2>& x) const
{
    return (*this)(x).homogeneous();
}

//! 正規化変換のスケーリング定数を返す．
/*!
  \return	スケーリング定数(与えられた点列の振幅の2乗平均値)
*/
template <class S> inline typename Normalize<S>::element_type
Normalize<S>::scale() const
{
    return _scale;
}

//! 正規化変換の平行移動成分を返す．
/*!
  \return	平行移動成分(与えられた点列の重心)
*/
template <class S> inline const typename Normalize<S>::vector_type&
Normalize<S>::centroid() const
{
    return _centroid;
}

//! 正規化変換行列を返す．
/*!
  \return	変換行列:
		\f$
		\TUvec{T}{} = 
		\TUbeginarray{ccc}
		 s^{-1} \TUvec{I}{d} & -s^{-1}\TUvec{c}{} \\ \TUtvec{0}{d} & 1
		\TUendarray
		\f$
*/
template <class S> typename Normalize<S>::matrix_type
Normalize<S>::T() const
{
    matrix_type	TT(spaceDim()+1, spaceDim()+1);
    for (size_t i = 0; i < spaceDim(); ++i)
    {
	TT[i][i] = 1.0 / _scale;
	TT[i][spaceDim()] = -_centroid[i] / _scale;
    }
    TT[spaceDim()][spaceDim()] = 1.0;

    return TT;
}

//! 正規化変換の転置行列を返す．
/*!
  \return	変換の転置行列:
		\f$
		\TUtvec{T}{} = 
		\TUbeginarray{ccc}
		 s^{-1} \TUvec{I}{d} & \TUvec{0}{d} \\ -s^{-1}\TUtvec{c}{} & 1
		\TUendarray
		\f$
*/
template <class S> typename Normalize<S>::matrix_type
Normalize<S>::Tt() const
{
    matrix_type	TTt(spaceDim()+1, spaceDim()+1);
    for (size_t i = 0; i < spaceDim(); ++i)
    {
	TTt[i][i] = 1.0 / _scale;
	TTt[spaceDim()][i] = -_centroid[i] / _scale;
    }
    TTt[spaceDim()][spaceDim()] = 1.0;

    return TTt;
}

//! 正規化変換の逆行列を返す．
/*!
  \return	変換の逆行列:
		\f$
		\TUinv{T}{} = 
		\TUbeginarray{ccc}
		 s \TUvec{I}{d} & \TUvec{c}{} \\ \TUtvec{0}{d} & 1
		\TUendarray
		\f$
*/
template <class S> typename Normalize<S>::matrix_type
Normalize<S>::Tinv() const
{
    matrix_type	TTinv(spaceDim()+1, spaceDim()+1);
    for (size_t i = 0; i < spaceDim(); ++i)
    {
	TTinv[i][i] = _scale;
	TTinv[i][spaceDim()] = _centroid[i];
    }
    TTinv[spaceDim()][spaceDim()] = 1.0;

    return TTinv;
}

//! 正規化変換の逆行列の転置を返す．
/*!
  \return	変換の逆行列の転置:
		\f$
		\TUtinv{T}{} = 
		\TUbeginarray{ccc}
		 s \TUvec{I}{d} & \TUvec{0}{d} \\ \TUtvec{c}{} & 1
		\TUendarray
		\f$
*/
template <class S> typename Normalize<S>::matrix_type
Normalize<S>::Ttinv() const
{
    matrix_type	TTtinv(spaceDim()+1, spaceDim()+1);
    for (size_t i = 0; i < spaceDim(); ++i)
    {
	TTtinv[i][i] = _scale;
	TTtinv[spaceDim()][i] = _centroid[i];
    }
    TTtinv[spaceDim()][spaceDim()] = 1.0;

    return TTtinv;
}

/************************************************************************
*  class HyperPlane<V>							*
************************************************************************/
//! d次元射影空間中の超平面を表現するクラス
/*!
  d次元射影空間の点\f$\TUud{x}{} \in \TUspace{R}{d+1}\f$に対して
  \f$\TUtud{p}{}\TUud{x}{} = 0,~\TUud{p}{} \in \TUspace{R}{d+1}\f$
  によって表される．
*/
template <class V>
class HyperPlane : public V
{
  private:
    typedef V					super;

  public:
    typedef V					base_type;
    typedef typename super::element_type	element_type;
    typedef Vector<element_type>		vector_type;
    typedef Matrix<element_type>		matrix_type;
    
  public:
  //! 超平面オブジェクトを生成する．
  /*!
    無限遠超平面([0, 0,..., 0, 1])に初期化される．
  */
		HyperPlane()
		    :super()
		{
		    if (super::size() > 0)
			(*this)[super::size()-1] = 1;
		}

  //! 空間の次元を指定して超平面オブジェクトを生成する．
  /*!
    無限遠超平面([0, 0,..., 0, 1])に初期化される．
    \param d	この超平面が存在する射影空間の次元
  */
    explicit	HyperPlane(size_t d) :super(d + 1)	{ (*this)[d] = 1; }
    
  //! 与えられた点列の非同次座標に当てはめられた超平面オブジェクトを生成する．
  /*!
    \param begin			点列の先頭を示す反復子
    \param end				点列の末尾を示す反復子
    \throw std::invalid_argument	点の数が ndataMin() に満たない場合に送出
  */
    template <class Iterator>
		HyperPlane(Iterator begin, Iterator end)
		{
		    fit(begin, end);
		}

#if !defined(__NVCC__)
  //! 同次座標ベクトルを指定して超平面オブジェクトを生成する．
  /*!
    \param p	(d+1)次元ベクトル(dは超平面が存在する射影空間の次元)
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
		HyperPlane(const E& p)	:super(p)	{}

  //! 超平面オブジェクトの同次座標ベクトルを指定する．
  /*!
    \param v	(d+1)次元ベクトル(dは超平面が存在する射影空間の次元)
    \return	この超平面オブジェクト
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
    HyperPlane&	operator =(const E& v)	{super::operator =(v); return *this;}
#endif	// !__NVCC__
    
    using	super::size;

    template <class Iterator>
    void	fit(Iterator begin, Iterator end)	;

  //! この超平面が存在する射影空間の次元を返す．
  /*! 
    \return	射影空間の次元(同次座標のベクトルとしての次元は spaceDim()+1)
  */
    size_t	spaceDim()			const	{return size()-1;}

  //! 超平面を求めるために必要な点の最小個数を返す．
  /*!
    現在設定されている射影空間の次元をもとに計算される．
    \return	必要な点の最小個数すなわち入力空間の次元 spaceDim()
  */
    size_t	ndataMin()			const	{return spaceDim();}

    template <class T, size_t D>
    element_type	sqdist(const Vector<T, D>& x)	const	;
    template <class T, size_t D>
    element_type	dist(const Vector<T, D>& x)	const	;
};

//! 与えられた点列の非同次座標に超平面を当てはめる．
/*!
  \param begin			点列の先頭を示す反復子
  \param end			点列の末尾を示す反復子
  \throw std::invalid_argument	点の数が ndataMin() に満たない場合に送出
*/
template <class V> template <class Iterator> void
HyperPlane<V>::fit(Iterator begin, Iterator end)
{
  // 点列の正規化
    const Normalize<element_type>	normalize(begin, end);

  // 充分な個数の点があるか？
    const size_t	ndata = std::distance(begin, end),
			d     = normalize.spaceDim();
    if (ndata < d)	// Vのサイズが未定なのでndataMin()は無効
	throw std::invalid_argument("Hyperplane::initialize(): not enough input data!!");

  // データ行列の計算
    Matrix<element_type>	A(d, d);
    while (begin != end)
    {
	const vector_type&	x = normalize(*begin++);
	A += x % x;
    }

  // データ行列の最小固有値に対応する固有ベクトルから法線ベクトルを計算し，
  // さらに点列の重心より原点からの距離を計算する．
    vector_type		eval;
    const matrix_type&	Ut = A.eigen(eval);
    super::resize(d+1);
    (*this)(0, d) = Ut[Ut.nrow()-1];
    (*this)[d] = -((*this)(0, d)*normalize.centroid());
    if ((*this)[d] > 0)
	*this *= -1;
}

//! 与えられた点と超平面の距離の2乗を返す．
/*!
  \param x	点の非同次座標(spaceDim() 次元)または同次座標
		(spaceDim()+1次元)
  \return	点と超平面の距離の2乗
*/
template <class V> template <class T, size_t D>
inline typename HyperPlane<V>::element_type
HyperPlane<V>::sqdist(const Vector<T, D>& x) const
{
    const element_type	d = dist(x);
    return d*d;
}

//! 与えられた点と超平面の距離を返す．
/*!
  \param x			点の非同次座標(spaceDim() 次元)または
				同次座標(spaceDim()+1次元)
  \return			点と超平面の距離(非負)
  \throw std::invalid_argument	点のベクトルとしての次元が spaceDim()，
				spaceDim()+1のいずれでもない場合，もしくは
				この点が無限遠点である場合に送出．
*/
template <class V> template <class T, size_t D>
typename HyperPlane<V>::element_type
HyperPlane<V>::dist(const Vector<T, D>& x) const
{
    const vector_type&	p = (*this)(0, spaceDim());
    if (x.size() == spaceDim())
	return (p * x + (*this)[spaceDim()]) / p.length();
    else if (x.size() == spaceDim() + 1)
    {
	if (x[spaceDim()] == element_type(0))
	    throw std::invalid_argument("HyperPlane::dist(): point at infinitiy!!");
	return (*this * x) / (p.length() * x[spaceDim()]);
    }
    else
	throw std::invalid_argument("HyperPlane::dist(): dimension mismatch!!");

    return 0;
}

typedef HyperPlane<Vector3f>	LineP2f;	//!< 2次元空間中のfloat型直線
typedef HyperPlane<Vector3d>	LineP2d;	//!< 2次元空間中のdouble型直線
typedef HyperPlane<Vector4f>	PlaneP3f;	//!< 3次元空間中のfloat型平面
typedef HyperPlane<Vector4d>	PlaneP3d;	//!< 3次元空間中のdouble型平面

/************************************************************************
*  class Projectivity<M>						*
************************************************************************/
//! 射影変換を行うクラス
/*!
  \f$\TUvec{T}{} \in \TUspace{R}{(n+1)\times(m+1)}\f$を用いてm次元空間の点
  \f$\TUud{x}{} \in \TUspace{R}{m+1}\f$をn次元空間の点
  \f$\TUud{y}{} \simeq \TUvec{T}{}\TUud{x}{} \in \TUspace{R}{n+1}\f$
  に写す(\f$m \neq n\f$でも構わない)．
*/
template <class M>
class Projectivity : public M
{
  private:
    typedef M					super;

  public:
    typedef M					base_type;
    typedef typename super::element_type	element_type;
    typedef Vector<element_type>		vector_type;
    typedef Matrix<element_type>		matrix_type;

    Projectivity()							;
    Projectivity(size_t inDim, size_t outDim)				;
    template <class Iterator>
    Projectivity(Iterator begin, Iterator end, bool refine=false)	;

#if !defined(__NVCC__)
  //! 変換行列を指定して射影変換オブジェクトを生成する．
  /*!
    \param T	(m+1)x(n+1)行列(m, nは入力／出力空間の次元)
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
    Projectivity(const E& T) :super(T)					{}

  //! 変換行列を指定する．
  /*!
    \param T	(m+1)x(n+1)行列(m, nは入力／出力空間の次元)
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
    void	set(const E& T)		{super::operator =(T);}
#endif	// !__NVCC__
    
    using	super::nrow;
    using	super::ncol;
    using	super::operator ();
    
    template <class Iterator>
    void	fit(Iterator begin, Iterator end, bool refine=false)	;

  //! この射影変換の入力空間の次元を返す．
  /*! 
    \return	入力空間の次元(同次座標のベクトルとしての次元は inDim()+1)
  */
    size_t	inDim()				const	{return ncol()-1;}

  //! この射影変換の出力空間の次元を返す．
  /*! 
    \return	出力空間の次元(同次座標のベクトルとしての次元は outDim()+1)
  */
    size_t	outDim()			const	{return nrow()-1;}

    size_t	ndataMin()			const	;

    Projectivity	inv()					const	;
    template <class S, size_t D>
    vector_type		operator ()(const Vector<S, D>& x)
								const	;
    template <class S, size_t D>
    vector_type		mapP(const Vector<S, D>& x)		const	;
    template <class S, size_t D>
    matrix_type		jacobian(const Vector<S, D>& x)		const	;
    template <class S, size_t D>
    matrix_type		Jx(const Vector<S, D>& x)		const	;
    template <class In, class Out>
    element_type	sqdist(const std::pair<In, Out>& pair)	const	;
    template <class In, class Out>
    element_type	dist(const std::pair<In, Out>& pair)	const	;
    size_t		nparams()				const	;
    void		update(const vector_type& dt)			;

    template <class Iterator>
    element_type	rmsError(Iterator begin, Iterator end)	const	;
    
  protected:
  //! 射影変換行列の最尤推定のためのコスト関数
    template <class Map, class Iterator>
    class Cost
    {
      public:
	typedef typename Map::element_type	element_type;
	typedef Vector<element_type>		vector_type;
	typedef Matrix<element_type>		matrix_type;
	
      public:
	Cost(Iterator begin, Iterator end)				;

	vector_type	operator ()(const Map& map)		const	;
	matrix_type	jacobian(const Map& map)		const	;
	static void	update(Map& map, const vector_type& dm)		;

      private:
	const Iterator	_begin, _end;
	const size_t	_npoints;
    };
};

//! 射影変換オブジェクトを生成する．
/*!
  恒等変換として初期化される．
*/
template <class M>
Projectivity<M>::Projectivity()
    :super()
{
    if (nrow() > 0 && ncol() > 0)
    {
	size_t	n = std::min(ncol() - 1, nrow() - 1);
	for (size_t i = 0; i < n; ++i)
	    (*this)[i][i] = 1.0;
	(*this)[nrow() - 1][ncol() - 1] = 1.0;
    }
}
    
//! 入力空間と出力空間の次元を指定して射影変換オブジェクトを生成する．
/*!
  恒等変換として初期化される．
  \param inDim	入力空間の次元
  \param outDim	出力空間の次元
*/
template <class M>
Projectivity<M>::Projectivity(size_t inDim, size_t outDim)
    :super(outDim + 1, inDim + 1)
{
    size_t	n = std::min(inDim, outDim);
    for (size_t i = 0; i < n; ++i)
	(*this)[i][i] = 1.0;
    (*this)[outDim][inDim] = 1.0;
}
    
//! 与えられた点対列の非同次座標から射影変換オブジェクトを生成する．
/*!
  \param begin			点対列の先頭を示す反復子
  \param end			点対列の末尾を示す反復子
  \param refine			非線型最適化の有(true)／無(false)を指定
  \throw std::invalid_argument	点対の数が ndataMin() に満たない場合に送出
*/
template <class M> template <class Iterator> inline
Projectivity<M>::Projectivity(Iterator begin, Iterator end, bool refine)
{
    fit(begin, end, refine);
}

//! 与えられた点対列の非同次座標から射影変換を計算する．
/*!
  \param begin			点対列の先頭を示す反復子
  \param end			点対列の末尾を示す反復子
  \param refine			非線型最適化の有(true)／無(false)を指定
  \throw std::invalid_argument	点対の数が ndataMin() に満たない場合に送出
*/
template <class M> template <class Iterator> void
Projectivity<M>::fit(Iterator begin, Iterator end, bool refine)
{
  // 点列の正規化
    const Normalize<element_type>
			xNormalize(make_first_iterator(begin),
				   make_first_iterator(end)),
			yNormalize(make_second_iterator(begin),
				   make_second_iterator(end));

  // 充分な個数の点対があるか？
    const size_t	ndata = std::distance(begin, end);
    const size_t	xdim1 = xNormalize.spaceDim() + 1,
		ydim  = yNormalize.spaceDim();
    if (ndata*ydim < xdim1*(ydim + 1) - 1)	// 行列のサイズが未定なので
						// ndataMin()は使えない
	throw std::invalid_argument("Projectivity::fit(): not enough input data!!");

  // データ行列の計算
    matrix_type	A(xdim1*(ydim + 1), xdim1*(ydim + 1));
    for (Iterator iter = begin; iter != end; ++iter)
    {
	const vector_type&	x  = xNormalize.normalizeP(iter->first);
	const vector_type&	y  = yNormalize(iter->second);
	const matrix_type&	xx = x % x;
	A(0, 0, xdim1, xdim1) += xx;
	for (size_t j = 0; j < ydim; ++j)
	    A(ydim*xdim1, j*xdim1, xdim1, xdim1) -= y[j] * xx;
	A(ydim*xdim1, ydim*xdim1, xdim1, xdim1) += (y*y) * xx;
    }
    for (size_t j = 1; j < ydim; ++j)
	A(j*xdim1, j*xdim1, xdim1, xdim1) = A(0, 0, xdim1, xdim1);
    A.symmetrize();

  // データ行列の最小固有値に対応する固有ベクトルから変換行列を計算し，
  // 正規化をキャンセルする．
    vector_type	eval;
    matrix_type	Ut = A.eigen(eval);
    *this = yNormalize.Tinv()
	  * matrix_type(Ut[Ut.nrow()-1].data(), ydim + 1, xdim1)
	  * xNormalize.T();

  // 変換行列が正方ならば，その行列式が１になるように正規化する．
    if (nrow() == ncol())
    {
	element_type	d = super::det();
	if (d > 0)
	    *this /=  pow( d, element_type(1)/nrow());
	else
	    *this /= -pow(-d, element_type(1)/nrow());
    }

  // 非線型最適化を行う．
    if (refine)
    {
	Cost<Projectivity<M>, Iterator>		cost(begin, end);
	ConstNormConstraint<Projectivity<M> >	constraint(*this);
	minimizeSquare(cost, constraint, *this);
    }
}

//! この射影変換の逆変換を返す．
/*!
  \return	逆変換
*/
template <class M> inline Projectivity<M>
Projectivity<M>::inv() const
{
    return Projectivity(super::inv());
}
    
//! 射影変換を求めるために必要な点対の最小個数を返す．
/*!
  現在設定されている入出力空間の次元をもとに計算される．
  \return	必要な点対の最小個数すなわち入力空間の次元m，出力空間の次元n
		に対して m + 1 + m/n
*/
template <class M> inline size_t
Projectivity<M>::ndataMin() const
{
    return inDim() + 1
	 + size_t(std::ceil(element_type(inDim()) / element_type(outDim())));
}
    
//! 与えられた点に射影変換を適用してその非同次座標を返す．
/*!
  \param x	点の非同次座標(inDim()次元)または同次座標(inDim()+1 次元)
  \return	射影変換された点の非同次座標(outDim() 次元)
*/
template <class M> template <class S, size_t D>
inline typename Projectivity<M>::vector_type
Projectivity<M>::operator ()(const Vector<S, D>& x) const
{
    if (x.size() == inDim())
    {
	vector_type	y(outDim());
	size_t		j;
	for (j = 0; j < y.size(); ++j)
	{
	    y[j] = (*this)[j][x.size()];
	    for (size_t i = 0; i < x.size(); ++i)
		y[j] += (*this)[j][i] * x[i];
	}
	element_type	w = (*this)[j][x.size()];
	for (size_t i = 0; i < x.size(); ++i)
	    w += (*this)[j][i] * x[i];
	return y /= w;
    }
    else
	return vector_type(*this * x).inhomogeneous();
}

//! 与えられた点に射影変換を適用してその同次座標を返す．
/*!
  \param x	点の非同次座標(inDim() 次元)または同次座標(inDim()+1 次元)
  \return	射影変換された点の同次座標(outDim()+1 次元)
*/
template <class M> template <class S, size_t D>
inline typename Projectivity<M>::vector_type
Projectivity<M>::mapP(const Vector<S, D>& x) const
{
    if (x.size() == inDim())
    {
	vector_type	y(nrow());
	for (size_t j = 0; j < y.size(); ++j)
	{
	    y[j] = (*this)[j][x.size()];
	    for (size_t i = 0; i < x.size(); ++i)
		y[j] += (*this)[j][i] * x[i];
	}
	return y;
    }
    else
	return *this * x;
}

//! 与えられた点におけるヤコビ行列を返す．
/*!
  ヤコビ行列とは射影変換行列成分に関する1階微分のことである．
  \param x	点の非同次座標(inDim() 次元)または同次座標(inDim()+1 次元)
  \return	outDim() x ((outDim()+1)x(inDim()+1)) ヤコビ行列
*/
template <class M> template <class S, size_t D>
typename Projectivity<M>::matrix_type
Projectivity<M>::jacobian(const Vector<S, D>& x) const
{
    vector_type	xP;
    if (x.size() == inDim())
	xP = x.homogeneous();
    else
	xP = x;
    const vector_type&	y = mapP(xP);
    matrix_type		J(outDim(), (outDim() + 1)*xP.size());
    for (size_t i = 0; i < J.nrow(); ++i)
    {
	J[i](i*xP.size(), xP.size()) = xP;
	(J[i](outDim()*xP.size(), xP.size()) = xP) *= (-y[i]/y[outDim()]);
    }
    J /= y[outDim()];

    return J;
}
    
//! 与えられた点においてその点の座標に関するヤコビ行列を返す．
/*!
  \param x	点の非同次座標(inDim() 次元)または同次座標(inDim()+1 次元)
  \return	outDim() x inDim() ヤコビ行列
*/
template <class M> template <class S, size_t D>
typename Projectivity<M>::matrix_type
Projectivity<M>::Jx(const Vector<S, D>& x) const
{
    const vector_type&	y = mapP(x);
    matrix_type		J(outDim(), inDim());
    for (size_t i = 0; i < J.nrow(); ++i)
	J[i] = (*this)[i](0, J.ncol())
	     - (y[i]/y[outDim()]) * (*this)[outDim()](0, J.ncol());
    J /= y[outDim()];

    return J;
}
    
//! 入力点に射影変換を適用した点と出力点の距離の2乗を返す．
/*!
  \param pair	入力点の非同次座標(inDim() 次元)と出力点の非同次座標
		(outDim() 次元)の対
  \return	変換された入力点と出力点の距離の2乗
*/
template <class M> template <class In, class Out>
inline typename Projectivity<M>::element_type
Projectivity<M>::sqdist(const std::pair<In, Out>& pair) const
{
    return (*this)(pair.first).sqdist(pair.second);
}
    
//! 入力点に射影変換を適用した点と出力点の距離を返す．
/*!
  \param pair	入力点の非同次座標(inDim() 次元)と出力点の非同次座標
		(outDim() 次元)の対
  \return	変換された入力点と出力点の距離
*/
template <class M> template <class In, class Out>
inline typename Projectivity<M>::element_type
Projectivity<M>::dist(const std::pair<In, Out>& pair) const
{
    return sqrt(sqdist(pair));
}

//! この射影変換のパラメータ数を返す．
/*!
  射影変換行列の要素数であり，変換の自由度数とは異なる．
  \return	射影変換のパラメータ数((outDim()+1) x (inDim()+1))
*/
template <class M> inline size_t
Projectivity<M>::nparams() const
{
    return (outDim() + 1)*(inDim() + 1);
}

//! 射影変換行列を与えられた量だけ修正する．
/*!
  \param dt	修正量を表すベクトル((outDim()+1) x (inDim()+1) 次元)
*/
template <class M> inline void
Projectivity<M>::update(const vector_type& dt)
{
    vector_type		t(super::data(), nparams());
    element_type	l = t.length();
    t -= dt;
    t *= (l / t.length());	// 修正の前後で射影変換行列のノルムは不変
}

//! 与えられた点対列の平均変換誤差を返す．
/*!
  \param begin	点対列の先頭を示す反復子
  \param end	点対列の末尾を示す反復子
  \return	平均変換誤差
*/
template <class M> template <class Iterator>
typename Projectivity<M>::element_type
Projectivity<M>::rmsError(Iterator begin, Iterator end) const
{
    element_type	sqrerr_sum = 0;
    size_t		npoints = 0;
    for (Iterator iter = begin; iter != end; ++iter)
    {
	const vector_type&	err = (*this)(iter->first) - iter->second;
	sqrerr_sum += err.square();
	++npoints;
    }

    return (npoints > 0 ? sqrt(sqrerr_sum / npoints) : 0);
}

template <class M> template <class Map, class Iterator>
Projectivity<M>::Cost<Map, Iterator>::Cost(Iterator begin, Iterator end)
    :_begin(begin), _end(end), _npoints(std::distance(_begin, _end))
{
}
    
template <class M> template <class Map, class Iterator>
typename Projectivity<M>::template Cost<Map, Iterator>::vector_type
Projectivity<M>::Cost<Map, Iterator>::operator ()(const Map& map) const
{
    const size_t	outDim = map.outDim();
    vector_type	val(_npoints*outDim);
    size_t	n = 0;
    for (Iterator iter = _begin; iter != _end; ++iter)
    {
	val(n, outDim) = map(iter->first) - iter->second;
	n += outDim;
    }
    
    return val;
}
    
template <class M> template <class Map, class Iterator>
typename Projectivity<M>::template Cost<Map, Iterator>::matrix_type
Projectivity<M>::Cost<Map, Iterator>::jacobian(const Map& map) const
{
    const size_t	outDim = map.outDim();
    matrix_type	J(_npoints*outDim, map.nparams());
    size_t	n = 0;
    for (Iterator iter = _begin; iter != _end; ++iter)
    {
	J(n, 0, outDim, J.ncol()) = map.jacobian(iter->first);
	n += outDim;
    }

    return J;
}

template <class M> template <class Map, class Iterator> inline void
Projectivity<M>::Cost<Map, Iterator>::update(Map& map, const vector_type& dm)
{
    map.update(dm);
}

typedef Projectivity<Matrix22f>	Projectivity11f;
typedef Projectivity<Matrix22d>	Projectivity11d;
typedef Projectivity<Matrix33f>	Projectivity22f;
typedef Projectivity<Matrix33d>	Projectivity22d;
typedef Projectivity<Matrix44f>	Projectivity33f;
typedef Projectivity<Matrix44d>	Projectivity33d;
typedef Projectivity<Matrix34f>	Projectivity23f;
typedef Projectivity<Matrix34d>	Projectivity23d;

/************************************************************************
*  class Affinity<M>							*
************************************************************************/
//! アフィン変換を行うクラス
/*!
  \f$\TUvec{A}{} \in \TUspace{R}{n\times m}\f$と
  \f$\TUvec{b}{} \in \TUspace{R}{n}\f$を用いてm次元空間の点
  \f$\TUvec{x}{} \in \TUspace{R}{m}\f$をn次元空間の点
  \f$\TUvec{y}{} \simeq \TUvec{A}{}\TUvec{x}{} + \TUvec{b}{}
  \in \TUspace{R}{n}\f$に写す(\f$m \neq n\f$でも構わない)．
*/
template <class M>
class Affinity : public Projectivity<M>
{
  private:
    typedef Projectivity<M>			super;

  public:
    typedef typename super::base_type		base_type;
    typedef typename super::element_type	element_type;
    typedef typename super::vector_type		vector_type;
    typedef typename super::matrix_type		matrix_type;

  //! アフィン変換オブジェクトを生成する．
		Affinity()	:super()				{}
    
  //! 入力空間と出力空間の次元を指定してアフィン変換オブジェクトを生成する．
  /*!
    恒等変換として初期化される．
    \param inDim	入力空間の次元
    \param outDim	出力空間の次元
  */
		Affinity(size_t inDim, size_t outDim)
		    :super(inDim, outDim)				{}

  //! 与えられた点対列の非同次座標からアフィン変換オブジェクトを生成する．
  /*!
    \param begin			点対列の先頭を示す反復子
    \param end				点対列の末尾を示す反復子
    \throw std::invalid_argument	点対の数が ndataMin() に満たない場合に送出
  */
    template <class Iterator>
		Affinity(Iterator begin, Iterator end)
		{
		    fit(begin, end);
		}

#if !defined(__NVCC__)
  //! 変換行列を指定してアフィン変換オブジェクトを生成する．
  /*!
    変換行列の下端行は強制的に 0,0,...,0,1 に設定される．
    \param T	(m+1) x (n+1) 行列(m, nは入力／出力空間の次元)
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
		Affinity(const E& T)
		    :super(T)
		{
		    (*this)[outDim()] = 0;
		    (*this)[outDim()][inDim()] = 1;
		}
    
  //! 変換行列を指定する．
  /*!
    変換行列の下端行は強制的に 0,0,...,0,1 に設定される．
    \param T	(m+1) x (n+1) 行列(m, nは入力／出力空間の次元)
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
    void	set(const E& T)
		{
		    super::set(T);
		    (*this)[outDim()] = 0;
		    (*this)[outDim()][inDim()] = 1;
		}
#endif	// !__NVCC__
    
    using	super::inDim;
    using	super::outDim;
    using	super::mapP;
    using	super::Jx;
    
    template <class Iterator>
    void	fit(Iterator begin, Iterator end)			;
    Affinity	inv()						const	;
    size_t	ndataMin()					const	;

    template <class S, size_t D>
    matrix_type	jacobian(const Vector<S, D>& x)			const	;
    size_t	nparams()					const	;
    void	update(const vector_type& dt)				;
    
  //! このアフィン変換の変形部分を表現する行列を返す．
  /*! 
    \return	outDim() x inDim() 行列
  */
    const matrix_type
		A()	const	{return super::operator ()(0, 0,
							   outDim(), inDim());}
    vector_type	b()	const	;
};

//! 与えられた点対列の非同次座標からアフィン変換を計算する．
/*!
  \param begin			点対列の先頭を示す反復子
  \param end			点対列の末尾を示す反復子
  \throw std::invalid_argument	点対の数が ndataMin() に満たない場合に送出
*/
template<class M> template <class Iterator> void
Affinity<M>::fit(Iterator begin, Iterator end)
{
  // 充分な個数の点対があるか？
    const size_t	ndata = std::distance(begin, end);
    if (ndata == 0)		// beginが有効か？
	throw std::invalid_argument("Affinity::fit(): 0-length input data!!");
    const size_t	xdim = begin->first.size();
    if (ndata < xdim + 1)	// 行列のサイズが未定なのでndataMin()は無効
	throw std::invalid_argument("Affinity::fit(): not enough input data!!");

  // データ行列の計算
    const size_t	ydim = begin->second.size(), xydim2 = xdim*ydim;
    matrix_type	N(xdim, xdim);
    vector_type	c(xdim), v(xydim2 + ydim);
    for (Iterator iter = begin; iter != end; ++iter)
    {
	const vector_type&	x = iter->first;
	const vector_type&	y = iter->second;

	N += x % x;
	c += x;
	for (size_t j = 0; j < ydim; ++j)
	    v(j*xdim, xdim) += y[j]*x;
	v(xydim2, ydim) += y;
    }
    matrix_type	W(xydim2 + ydim, xydim2 + ydim);
    for (size_t j = 0; j < ydim; ++j)
    {
	W(j*xdim, j*xdim, xdim, xdim) = N;
	W[xydim2 + j](j*xdim, xdim)   = c;
	W[xydim2 + j][xydim2 + j]     = ndata;
    }
    W.symmetrize();

  // W*u = vを解いて変換パラメータを求める．
    v.solve(W);

  // 変換行列をセットする．
    super::resize(ydim + 1, xdim + 1);
    super::operator ()(0, 0, ydim, xdim) = matrix_type(v.data(), ydim, xdim);
    for (size_t j = 0; j < ydim; ++j)
	(*this)[j][xdim] = v[xydim2 + j];
    (*this)[ydim][xdim] = 1;
}

//! このアフィン変換の並行移動部分を表現するベクトルを返す．
/*! 
  \return	outDim() 次元ベクトル
*/
template <class M> typename Affinity<M>::vector_type
Affinity<M>::b() const
{
    vector_type	bb(outDim());
    for (size_t j = 0; j < bb.size(); ++j)
	bb[j] = (*this)[j][inDim()];

    return bb;
}

//! このアフィン変換の逆変換を返す．
/*!
  \return	逆変換
*/
template <class M> inline Affinity<M>
Affinity<M>::inv() const
{
    return Affinity(super::inv());
}
    
//! アフィン変換を求めるために必要な点対の最小個数を返す．
/*!
  現在設定されている入出力空間の次元をもとに計算される．
  \return	必要な点対の最小個数すなわち入力空間の次元mに対して m + 1
*/
template<class M> inline size_t
Affinity<M>::ndataMin() const
{
    return inDim() + 1;
}

//! 与えられた点におけるヤコビ行列を返す．
/*!
  ヤコビ行列とはアフィン変換行列成分に関する1階微分のことである．
  \param x	点の非同次座標(inDim() 次元)または同次座標(inDim()+1次元)
  \return	outDim() x (outDim()x(inDim()+1)) ヤコビ行列
*/
template <class M> template <class S, size_t D>
typename Affinity<M>::matrix_type
Affinity<M>::jacobian(const Vector<S, D>& x) const
{
    vector_type	xP;
    if (x.size() == inDim())
	xP = x.homogeneous();
    else
	xP = x;
    const vector_type&	y = mapP(xP);
    matrix_type		J(outDim(), outDim()*xP.size());
    for (size_t i = 0; i < J.nrow(); ++i)
	J[i](i*xP.size(), xP.size()) = xP;
    J /= y[outDim()];

    return J;
}

//! このアフィン変換の独立なパラメータ数を返す．
/*!
  アフィン変換行列の最初のoutDim()行の要素数であり，変換の自由度数と一致する．
  \return	アフィン変換のパラメータ数(outDim() x (inDim()+1))
*/
template <class M> inline size_t
Affinity<M>::nparams() const
{
    return outDim()*(inDim() + 1);
}

//! アフィン変換行列を与えられた量だけ修正する．
/*!
  \param dt	修正量を表すベクトル(outDim() x (inDim()+1) 次元)
*/
template <class M> inline void
Affinity<M>::update(const vector_type& dt)
{
    vector_type		t(*this);
    t(0, nparams()) -= dt;
}

typedef Affinity<Matrix22f>	Affinity11f;
typedef Affinity<Matrix22d>	Affinity11d;
typedef Affinity<Matrix33f>	Affinity22f;
typedef Affinity<Matrix33d>	Affinity22d;
typedef Affinity<Matrix44f>	Affinity33f;
typedef Affinity<Matrix44d>	Affinity33d;
typedef Affinity<Matrix34f>	Affinity23f;
typedef Affinity<Matrix34d>	Affinity23d;

/************************************************************************
*  class Rigidity<M>							*
************************************************************************/
//! 剛体変換を行うクラス
/*!
  回転行列\f$\TUvec{R}{} \in \TUspace{SO}{n}\f$と
  \f$\TUvec{t}{} \in \TUspace{R}{n}\f$を用いてm次元空間の点
  \f$\TUvec{x}{} \in \TUspace{R}{n}\f$をn次元空間の点
  \f$\TUvec{y}{} \simeq \TUvec{R}{}\TUvec{x}{} + \TUvec{t}{}
  \in \TUspace{R}{n}\f$に写す．
*/
template <class M>
class Rigidity : public Affinity<M>
{
  private:
    typedef Affinity<M>				super;

  public:
    typedef typename super::base_type		base_type;
    typedef typename super::element_type	element_type;
    typedef typename super::vector_type		vector_type;
    typedef typename super::matrix_type		matrix_type;

  //! 剛体変換オブジェクトを生成する．
  /*!
    恒等変換として初期化される．
  */
			Rigidity() :super()		{}
    
  //! 入力空間と出力空間の次元を指定して剛体変換オブジェクトを生成する．
  /*!
    恒等変換として初期化される．
    \param d	入力/出力空間の次元
  */
    explicit		Rigidity(size_t d) :super(d, d)	{}

  //! 与えられた点対列の非同次座標から剛体変換オブジェクトを生成する．
  /*!
    \param begin			点対列の先頭を示す反復子
    \param end				点対列の末尾を示す反復子
    \throw std::invalid_argument	点対の数が ndataMin() に満たない場合に送出
  */
    template <class Iterator>
			Rigidity(Iterator begin, Iterator end)
			{
			    fit(begin, end);
			}

#if !defined(__NVCC__)
  //! 変換行列を指定して剛体変換オブジェクトを生成する．
  /*!
    \param T	(d+1) x (d+1)行列(dは入力/出力空間の次元)
  */
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
			Rigidity(const E& T)			{ set(T); }

  //! 変換行列を指定する．
  /*!
    \param T	(d+1) x (d+1) 行列(dは入力/出力空間の次元)
  */
    template <class E>
    typename std::enable_if<is_range<E>::value>::type
			set(const E& T)
			{
			    if (T().size() != T().ncol())
				throw std::invalid_argument("Rigidity::set(): non-square matrix!!");
			    super::set(T);
			}
#endif

    using		super::inDim;
    using		super::outDim;

  //! この剛体変換の入力/出力空間の次元を返す．
  /*! 
    \return	入力/出力空間の次元(同次座標のベクトルとしての次元は dim()+1)
  */
    size_t		dim()			const	{ return inDim(); };
    
  //! この剛体変換の回転部分を表現する回転行列を返す．
  /*! 
    \return	dim() x dim() 行列
  */
    const matrix_type	R()			const	{ return super::A(); }

  //! この剛体変換の並行移動部分を表現するベクトルを返す．
  /*! 
    \return	dim() 次元ベクトル
  */
    vector_type		t()			const	{ return super::b(); }

    template <class Iterator>
    void		fit(Iterator begin, Iterator end)	;
    Rigidity		inv()				const	;
    size_t		ndataMin()			const	;
    template <class S, size_t D>
    matrix_type		jacobian(const Vector<S, D>& x)	const	;
    size_t		nparams()			const	;
    void		update(const vector_type& dt)		;
};

//! 与えられた点対列の非同次座標から剛体変換を計算する．
/*!
  \param begin			点対列の先頭を示す反復子
  \param end			点対列の末尾を示す反復子
  \throw std::invalid_argument	点対の数が ndataMin() に満たない場合に送出
*/
template<class M> template <class Iterator> void
Rigidity<M>::fit(Iterator begin, Iterator end)
{
  // 充分な個数の点対があるか？
    const size_t	ndata = std::distance(begin, end);
    if (ndata == 0)		// beginが有効か？
	throw std::invalid_argument("Rigidity::fit(): 0-length input data!!");
    const size_t	d = begin->first.size();
    if (begin->second.size() != d)
	throw std::invalid_argument("Rigidity::fit(): input data contains a pair of different dimensions!!");
    if (ndata < d)		// 行列のサイズが未定なのでndataMin()は無効
	throw std::invalid_argument("Rigidity::fit(): not enough input data!!");

  // 重心の計算
    vector_type	xc(d), yc(d);
    for (Iterator corres = begin; corres != end; ++corres)
    {
	xc += corres->first;
	yc += corres->second;
    }
    xc /= ndata;
    yc /= ndata;
    
  // モーメント行列の計算
    matrix_type	A(d, d);
    for (Iterator corres = begin; corres != end; ++corres)
	A += (corres->first - xc) % (corres->second - yc);

  // 点群間の剛体変換の計算
    SVDecomposition<element_type>	svd(A);
    super::resize(d + 1, d + 1);
    super::operator ()(0, 0, d, d) = svd.Ut().trns() * svd.Vt();
    for (size_t i = 0; i < d; ++i)
	(*this)[i][d] = yc[i] - (*this)[i](0, d) * xc;
    (*this)[d][d] = 1;
}

//! この剛体変換の逆変換を返す．
/*!
  \return	逆変換
*/
template <class M> inline Rigidity<M>
Rigidity<M>::inv() const
{
    Rigidity	Dinv(inDim());

    for (size_t i = 0; i < dim(); ++i)
	for (size_t j = 0; j < dim(); ++j)
	    Dinv[j][i] = (*this)[i][j];

    vector_type	tt = t();
    for (size_t j = 0; j < dim(); ++j)
	Dinv[j][dim()] = -(Dinv[j](0, dim()) * tt);

    return Dinv;
}
    
//! 剛体変換を求めるために必要な点対の最小個数を返す．
/*!
  現在設定されている空間の次元をもとに計算される．
  \return	必要な点対の最小個数すなわち空間の次元mに対してm
*/
template<class M> inline size_t
Rigidity<M>::ndataMin() const
{
    return dim();
}

//! 与えられた点におけるヤコビ行列を返す．
/*!
  ヤコビ行列とは並進/回転パラメータに関する1階微分のことである．
  \param x	点の非同次座標(dim() 次元)または同次座標(dim()+1 次元)
  \return	dim()xdim() x (dim()+1)/2 ヤコビ行列
*/
template <class M> template <class S, size_t D>
typename Rigidity<M>::matrix_type
Rigidity<M>::jacobian(const Vector<S, D>& x) const
{
    vector_type	xx;
    if (x.size() == dim())
	xx = x;
    else
	xx = x.inhomogeneous();
    
    size_t	dof = dim() * (dim() + 1) / 2;
    matrix_type	J(dim(), dof);
    
    switch (dim())
    {
      case 2:
	J[0][0] = J[1][1] = 1;
	J[0][2] = -((*this)[1](0, 2) * xx);
	J[1][2] =   (*this)[0](0, 2) * xx;
	break;
      case 3:
	J[0][0] = J[1][1] = J[2][2] = 1.0;
	J(0, 3, 3, 3) = (R() * xx).skew();
	break;
      default:
	throw std::runtime_error("Rigidity<M>::jacobian(): sorry, not implemented yet...");
    }

    return J;
}
    
//! この剛体変換の独立なパラメータ数を返す．
/*!
  剛体変換の独立なパラメータ数すなわち変換の自由度数に一致する．
  \return	剛体変換のパラメータ数(dim() x (dim()+1))/2
*/
template <class M> inline size_t
Rigidity<M>::nparams() const
{
    return (dim()*(dim() + 1))/2;
}

//! 剛体変換行列を与えられた量だけ修正する．
/*!
  \param dt	修正量を表すベクトル(dim() x (dim()+1)/2 次元)
*/
template <class M> void
Rigidity<M>::update(const vector_type& dt)
{
    for (size_t i = 0; i < dim(); ++i)
	(*this)[i][dim()] -= dt[i];
    
    switch (dim())
    {
      case 2:
	(*this)(0, 0, 2, 2) = matrix_type::Rt(vector_type(-dt[2]))
			    * (*this)(0, 0, 2, 2);
	break;
      case 3:
	(*this)(0, 0, 3, 3) = matrix_type::Rt(vector_type(-dt(3, 3)))
			    * (*this)(0, 0, 3, 3);
	break;
      default:
	throw std::runtime_error("Rigidity<M>::update(): sorry, not implemented yet...");
    }
}

typedef Rigidity<Matrix33f>	Rigidity22f;
typedef Rigidity<Matrix33d>	Rigidity22d;
typedef Rigidity<Matrix44f>	Rigidity33f;
typedef Rigidity<Matrix44d>	Rigidity33d;

/************************************************************************
*  class Homography<T>							*
************************************************************************/
//! 2次元射影変換を行うクラス
/*!
  \f$\TUvec{H}{} = \in \TUspace{R}{3\times 3}\f$を用いて2次元空間の点
  \f$\TUud{x}{} \in \TUspace{R}{3}\f$を2次元空間の点
  \f$\TUud{y}{} \simeq \TUvec{H}{}\TUud{x}{} \in \TUspace{R}{3}\f$
  に写す．
*/
template <class T>
class Homography : public Projectivity<Matrix<T, 3, 3> >
{
  private:
    typedef Projectivity<Matrix<T, 3, 3> >	super;
    
  public:
    enum	{DOF=8};

    typedef typename super::base_type		base_type;
    typedef typename super::vector_type		vector_type;
    typedef typename super::matrix_type		matrix_type;
    typedef typename super::element_type	element_type;
    typedef Point2<element_type>		point_type;
    typedef Vector<element_type, DOF>		param_type;
    typedef Matrix<element_type, 2, DOF>	jacobian_type;

  public:
    Homography()			:super()		{}
    template <class Iterator>
    Homography(Iterator begin, Iterator end, bool refine=false)	;
#if !defined(__NVCC__)
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
    Homography(const E& H)	:super(H)			{}
#endif	// !__NVCC__

    using	super::operator ();
    using	super::inDim;
    using	super::outDim;
    using	super::ndataMin;
    using	super::nparams;
    
    Homography	inv()					const	;
    point_type	operator ()(int u, int v)		const	;
    static jacobian_type
		jacobian0(int u, int v)				;
    
    void	compose(const param_type& dt)			;
};


//! 与えられた点対列の非同次座標から2次元射影変換オブジェクトを生成する．
/*!
  \param begin			点対列の先頭を示す反復子
  \param end			点対列の末尾を示す反復子
  \param refine			非線型最適化の有(true)／無(false)を指定
  \throw std::invalid_argument	点対の数が ndataMin() に満たない場合に送出
*/
template<class T> template <class Iterator> inline
Homography<T>::Homography(Iterator begin, Iterator end, bool refine)
    :super()
{
    fit(begin, end, refine);
}

//! この2次元射影変換の逆変換を返す．
/*!
  \return	逆変換
*/
template <class T> Homography<T>
Homography<T>::inv() const
{
    return Homography(base_type::inv());
}

template <class T> inline typename Homography<T>::point_type
Homography<T>::operator ()(int u, int v) const
{
    const element_type	w = element_type(1) /
			  ((*this)[2][0]*u + (*this)[2][1]*v + (*this)[2][2]);
    return point_type(w * ((*this)[0][0]*u + (*this)[0][1]*v + (*this)[0][2]),
		      w * ((*this)[1][0]*u + (*this)[1][1]*v + (*this)[1][2]));
}

template <class T> inline typename Homography<T>::jacobian_type
Homography<T>::jacobian0(int u, int v)
{
    jacobian_type	J(2, 8);
    J[0][0] = J[1][3] = u;
    J[0][1] = J[1][4] = v;
    J[0][2] = J[1][5] = 1.0;
    J[0][3] = J[0][4] = J[0][5] = J[1][0] = J[1][1] = J[1][2] = 0.0;
    J[0][6]	      = -u * u;
    J[0][7] = J[1][6] = -u * v;
    J[1][7]	      = -v * v;

    return J;
}

template <class T> inline void
Homography<T>::compose(const param_type& dt)
{
    element_type	t0 = (*this)[0][0],
			t1 = (*this)[0][1],
			t2 = (*this)[0][2];
    (*this)[0][0] -= (t0*dt[0] + t1*dt[3] + t2*dt[6]);
    (*this)[0][1] -= (t0*dt[1] + t1*dt[4] + t2*dt[7]);
    (*this)[0][2] -= (t0*dt[2] + t1*dt[5]);
    
    t0 = (*this)[1][0];
    t1 = (*this)[1][1];
    t2 = (*this)[1][2];
    (*this)[1][0] -= (t0*dt[0] + t1*dt[3] + t2*dt[6]);
    (*this)[1][1] -= (t0*dt[1] + t1*dt[4] + t2*dt[7]);
    (*this)[1][2] -= (t0*dt[2] + t1*dt[5]);

    t0 = (*this)[2][0];
    t1 = (*this)[2][1];
    t2 = (*this)[2][2];
    (*this)[2][0] -= (t0*dt[0] + t1*dt[3] + t2*dt[6]);
    (*this)[2][1] -= (t0*dt[1] + t1*dt[4] + t2*dt[7]);
    (*this)[2][2] -= (t0*dt[2] + t1*dt[5]);
}

/************************************************************************
*  class Affinity2<T>							*
************************************************************************/
//! 2次元アフィン変換を行うクラス
/*!
  \f$\TUvec{A}{} = \in \TUspace{R}{3\times 3}\f$を用いて2次元空間の点
  \f$\TUud{x}{} \in \TUspace{R}{3}\f$を2次元空間の点
  \f$\TUud{y}{} \simeq \TUvec{A}{}\TUud{x}{} \in \TUspace{R}{3}\f$
  に写す．
*/
template <class T>
class Affinity2 : public Affinity<Matrix<T, 3, 3> >
{
  private:
    typedef Affinity<Matrix<T, 3, 3> >		super;
    
  public:
    enum	{DOF=6};

    typedef typename super::base_type		base_type;
    typedef typename super::vector_type		vector_type;
    typedef typename super::matrix_type		matrix_type;
    typedef typename super::element_type	element_type;
    typedef Vector<element_type, DOF>		param_type;
    typedef Point2<element_type>		point_type;
    typedef Matrix<element_type, 2, DOF>	jacobian_type;

  public:
		Affinity2()	:super()			{}

  //! 与えられた点対列の非同次座標から2次元アフィン変換オブジェクトを生成する．
  /*!
    \param begin			点対列の先頭を示す反復子
    \param end				点対列の末尾を示す反復子
    \throw std::invalid_argument	点対の数が ndataMin() に満たない場合に送出
  */
    template <class Iterator>
		Affinity2(Iterator begin, Iterator end)
		{
		    fit(begin, end);
		}

#if !defined(__NVCC__)
    template <class E,
	      typename std::enable_if<is_range<E>::value>::type* = nullptr>
		Affinity2(const E& A)
		    :super(A)
		{
		    (*this)[2][0] = (*this)[2][1] = 0; (*this)[2][2] = 1;
		}
#endif	// !__NVCC__

    using	super::operator ();
    using	super::inDim;
    using	super::outDim;
    using	super::ndataMin;
    using	super::nparams;

    Affinity2	inv()					const	;
    point_type	operator ()(int u, int v)		const	;
    static jacobian_type
		jacobian0(int u, int v)				;
    
    void	compose(const param_type& dt)			;
};

//! この2次元アフィン変換の逆変換を返す．
/*!
  \return	逆変換
*/
template <class T> inline Affinity2<T>
Affinity2<T>::inv() const
{
    return Affinity2(base_type::inv());
}
    
template <class T> inline typename Affinity2<T>::point_type
Affinity2<T>::operator ()(int u, int v) const
{
    return point_type((*this)[0][0]*u + (*this)[0][1]*v + (*this)[0][2],
		      (*this)[1][0]*u + (*this)[1][1]*v + (*this)[1][2]);
}

template <class T> inline typename Affinity2<T>::jacobian_type
Affinity2<T>::jacobian0(int u, int v)
{
    jacobian_type	J;
    J[0][0] = J[1][3] = u;
    J[0][1] = J[1][4] = v;
    J[0][2] = J[1][5] = 1;
    J[0][3] = J[0][4] = J[0][5] = J[1][0] = J[1][1] = J[1][2] = 0;

    return J;
}
    
template <class T> inline void
Affinity2<T>::compose(const param_type& dt)
{
    element_type	t0 = (*this)[0][0], t1 = (*this)[0][1];
    (*this)[0][0] -= (t0*dt[0] + t1*dt[3]);
    (*this)[0][1] -= (t0*dt[1] + t1*dt[4]);
    (*this)[0][2] -= (t0*dt[2] + t1*dt[5]);
    
    t0 = (*this)[1][0];
    t1 = (*this)[1][1];
    (*this)[1][0] -= (t0*dt[0] + t1*dt[3]);
    (*this)[1][1] -= (t0*dt[1] + t1*dt[4]);
    (*this)[1][2] -= (t0*dt[2] + t1*dt[5]);
}
    
/************************************************************************
*   class BoundingBox<P>						*
************************************************************************/
//! P型の点に対するbounding boxを表すクラス
/*!
  \param P	点の型(次元は自由)
*/
template <class P>
class BoundingBox
{
  public:
  //! 点の要素の型
    typedef typename P::element_type		element_type;

  public:
    BoundingBox()				;
    explicit BoundingBox(size_t d)		;

    bool		operator !()	const	;
  //! このbounding boxが属する空間の次元を返す．
  /*!
    \return	空間の次元
  */
    size_t		dim()		const	{return _min.size();}

  //! このbounding boxの最小点を返す．
  /*!
    \return	最小点
  */
    const P&		min()		const	{return _min;}

  //! このbounding boxの最大点を返す．
  /*!
    \return	最大点
  */
    const P&		max()		const	{return _max;}

  //! このbounding boxの最小点の指定された軸の座標値を返す．
  /*!
    \param i	軸を指定するindex
    \return	軸の座標値
  */
    element_type	min(int i)	const	{return _min[i];}

  //! このbounding boxの最大点の指定された軸の座標値を返す．
  /*!
    \param i	軸を指定するindex
    \return	軸の座標値
  */
    element_type	max(int i)	const	{return _max[i];}

  //! このbounding boxの指定された軸に沿った長さを返す．
  /*!
    \param i	軸を指定するindex
    \return	軸に沿った長さ
  */
    element_type	length(int i)	const	{return _max[i] - _min[i];}

  //! このbounding boxの幅を返す．
  /*!
    \return	幅 (TU::BoundingBox::length (0)に等しい)
  */
    element_type	width()		const	{return length(0);}

  //! このbounding boxの高さを返す．
  /*!
    \return	高さ (TU::BoundingBox::length (1)に等しい)
  */
    element_type	height()	const	{return length(1);}

  //! このbounding boxの奥行きを返す．
  /*!
    \return	奥行き (TU::BoundingBox::length (2)に等しい)
  */
    element_type	depth()		const	{return length(2);}

    template <class S, size_t D>
    bool		include(const Vector<S, D>& p)		;
    BoundingBox&	clear()					;
    template <class S, size_t D>
    BoundingBox&	expand(const Vector<S, D>& p)		;
    template <class S, size_t D>
    BoundingBox&	operator +=(const Vector<S, D>& dt)	;
    template <class S, size_t D>
    BoundingBox&	operator -=(const Vector<S, D>& dt)	;
    template <class S>
    BoundingBox&	operator *=(S c)			;
    BoundingBox&	operator |=(const BoundingBox& bbox)	;
    BoundingBox&	operator &=(const BoundingBox& bbox)	;
    
  private:
  //! 入力ストリームからbounding boxを成す2つの点の座標を入力する(ASCII)．
  /*!
    \param in	入力ストリーム
    \param bbox	bounding box
    \return	inで指定した入力ストリーム
  */
    friend std::istream&
    operator >>(std::istream& in, BoundingBox<P>& bbox)
    {
	return in >> bbox._min >> bbox._max;
    }
    
    P	_min;
    P	_max;
};

//! 空のbounding boxを作る．
template <class P> inline
BoundingBox<P>::BoundingBox()
    :_min(), _max()
{
    clear();
}

//! 指定した次元の空間において空のbounding boxを作る．
/*!
  \param d	空間の次元
*/
template <class P> inline
BoundingBox<P>::BoundingBox(size_t d)
    :_min(d), _max(d)
{
    clear();
}

//! bounding boxが空であるか調べる．
/*!
  \return	空であればtrue, そうでなければfalse
*/
template <class P> bool
BoundingBox<P>::operator !() const
{
    for (size_t i = 0; i < dim(); ++i)
	if (_min[i] > _max[i])
	    return true;
    return false;
}

//! bounding boxが与えられた点を含むか調べる．
/*!
  \param p	点の座標
  \return	含めばtrue, そうでなければfalse
*/
template <class P> template <class S, size_t D> bool
BoundingBox<P>::include(const Vector<S, D>& p)
{
    for (size_t i = 0; i < dim(); ++i)
	if (p[i] < _min[i] || p[i] > _max[i])
	    return false;
    return true;
}

//! bounding boxを空にする．
/*!
  \return	空にされたこのbounding box
*/
template <class P> BoundingBox<P>&
BoundingBox<P>::clear()
{
    typedef std::numeric_limits<element_type>	Limits;
    
    for (size_t i = 0; i < dim(); ++i)
    {
	_min[i] = Limits::max();
	_max[i] = (Limits::is_integer ? Limits::min() : -Limits::max());
    }
    return *this;
}

//! bounding boxを与えられた点を含むように拡張する．
/*!
  \param p	点の座標
  \return	拡張されたこのbounding box
*/
template <class P> template <class S, size_t D> BoundingBox<P>&
BoundingBox<P>::expand(const Vector<S, D>& p)
{
    for (int i = 0; i < dim(); ++i)
    {
	_min[i] = std::min(_min[i], p[i]);
	_max[i] = std::max(_max[i], p[i]);
    }
    return *this;
}

//! bounding boxを与えられた変位だけ正方向に平行移動する．
/*!
  \param dt	変位
  \return	平行移動されたこのbounding box
*/
template <class P> template <class S, size_t D>
inline BoundingBox<P>&
BoundingBox<P>::operator +=(const Vector<S, D>& dt)
{
    _min += dt;
    _max += dt;
    return *this;
}
    
//! bounding boxを与えられた変位だけ負方向に平行移動する．
/*!
  \param dt	変位
  \return	平行移動されたこのbounding box
*/
template <class P> template <class S, size_t D>
inline BoundingBox<P>&
BoundingBox<P>::operator -=(const Vector<S, D>& dt)
{
    _min -= dt;
    _max -= dt;
    return *this;
}
    
//! bounding boxを与えられたスケールだけ拡大／縮小する．
/*!
  負のスケールを与えるとbounding boxが反転する．
  \param c	スケール
  \return	平行移動されたこのbounding box
*/
template <class P> template <class S> inline BoundingBox<P>&
BoundingBox<P>::operator *=(S c)
{
    if (c < S(0))
	std::swap(_min, _max);
    _min *= c;
    _max *= c;
    return *this;
}

//! このbounding boxと指定されたbounding boxとの結びをとる．
/*!
  \param bbox	bounding box
  \return	結びをとった後のこのbounding box
*/
template <class P> inline BoundingBox<P>&
BoundingBox<P>::operator |=(const BoundingBox<P>& bbox)
{
    return expand(bbox.min()).expand(bbox.max());
}
    
//! このbounding boxと指定されたbounding boxとの交わりをとる．
/*!
  与えられたbounding boxとの間に共通部分がなければ空のbounding boxとなる．
  \param bbox	bounding box
  \return	交わりをとった後のこのbounding box
*/
template <class P> BoundingBox<P>&
BoundingBox<P>::operator &=(const BoundingBox<P>& bbox)
{
    for (int i = 0; i < dim(); ++i)
    {
	_min[i] = std::max(_min[i], bbox.min(i));
	_max[i] = std::min(_max[i], bbox.max(i));
    }
    return *this;
}
    
//! 2つのbounding boxの結びをとる．
/*!
  \param a	bounding box
  \param b	bounding box
  \return	aとbの結びとなるbounding box
*/
template <class P> inline BoundingBox<P>
operator |(const BoundingBox<P>& a, const BoundingBox<P>& b)
{
    BoundingBox<P>	c(a);
    return c |= b;
}
    
//! 2つのbounding boxの交わりをとる．
/*!
  与えられたbounding boxに共通部分がなければ空のbounding boxを返す．
  \param a	bounding box
  \param b	bounding box
  \return	aとbの交わりとなるbounding box
*/
template <class P> inline BoundingBox<P>
operator &(const BoundingBox<P>& a, const BoundingBox<P>& b)
{
    BoundingBox<P>	c(a);
    return c &= b;
}

//! 出力ストリームにbounding boxを成す2つの点の座標を出力する(ASCII)．
/*!
  \param out	出力ストリーム
  \param bbox	bounding box
  \return	outで指定した出力ストリーム
*/
template <class P> std::ostream&
operator <<(std::ostream& out, const BoundingBox<P>& bbox)
{
#ifdef TU_DEBUG
    for (size_t i = 0; i < bbox.dim(); ++i)
    {
	if (i != 0)
	    out << 'x';
	out << '[' << bbox.min(i) << ", " << bbox.max(i) << ']';
    }
    return out << std::endl;
#else
    return out << bbox.min() << bbox.max() << std::endl;
#endif
}
    
}
#endif	// !__TU_GEOMETRYPP_H
