/*
 *  $Id: Minimize.h 1777 2015-02-06 10:54:01Z ueshiba $
 */
/*!
  \file		Minimize.h
  \brief	汎用最小自乗法に関連する関数の定義と実装
*/
#ifndef __TU_MINIMIZE_H
#define __TU_MINIMIZE_H

#include "TU/Vector++.h"
#include <algorithm>
#include <stdexcept>

namespace TU
{
/************************************************************************
*  class NullConstraint							*
************************************************************************/
//! 何の拘束も与えないというダミーの拘束条件を表すクラス
/*!
  実体は任意の引数に対して0次元のベクトルを出力するベクトル値関数であり，
  #minimizeSquare() や #minimizeSquareSparse() のテンプレートパラメータG
  として利用することを想定している．
  \param ET 出力ベクトルの要素の型
*/
template <class ET>
class NullConstraint
{
  public:
    typedef ET					element_type;
    typedef Vector<element_type>		vector_type;
    typedef Matrix<element_type>		matrix_type;

  public:
  //! 任意の引数に対して0次元ベクトルを出力する．
    template <class AT>
    vector_type	operator ()(const AT&)	const	{return vector_type(0);}
  //! 任意の引数に対して0x0行列を出力する．
    template <class AT>
    matrix_type	jacobian(const AT&)	const	{return matrix_type(0, 0);}
};

/************************************************************************
*  class ConstNormConstraint						*
************************************************************************/
//! 引数の2乗ノルム値が一定という拘束条件を表すクラス
/*!
  実体は与えられた引数の2乗ノルム値と目標値との差を1次元ベクトルとして返す
  ベクトル値関数であり， #minimizeSquare() や #minimizeSquareSparse() の
  テンプレートパラメータGとして利用することを想定している．
  \param AT	引数の型．以下の条件を満たすこと：
  -# ベクトルや行列である場合，その要素の型を
	AT::element_type
     という名前でtypedefしている．
  -# メンバ関数
	AT::element_type	AT::square() const
     によって，その2乗ノルム値を知ることができる．
  -# Vector<AT::element_type>
     型に変換できる(例：
     Matrix<AT::element_type>
     型はその要素を行優先順に1列に並べたベクトルに変換可能)．
*/
template <class AT>
class ConstNormConstraint
{
  public:
    typedef AT						argument_type;
    typedef typename argument_type::element_type	element_type;
    typedef Vector<element_type>			vector_type;
    typedef Matrix<element_type>			matrix_type;
    
  public:
  //! 新たな拘束条件を生成し，その2乗ノルムの目標値を設定する．
  /*!
    \param x	引数(この2乗ノルム値が目標値となる)
  */
    ConstNormConstraint(const argument_type& x) :_sqr(x.square())	{}

  //! 与えられた引数の2乗ノルム値と目標値の差を出力する．
  /*!
    \param x	引数
    \return	xの2乗ノルム値と目標値の差を収めた1次元ベクトル
  */
    vector_type	operator ()(const argument_type& x) const
		{
		    vector_type	val(1);
		    val[0] = x.square() - _sqr;
		    return val;
		}

  //! 与えられた引数の2乗ノルム値について，この引数自身による1階微分値を出力する．
  /*!
    \param x	引数
    \return	1階微分値を収めた1xd行列(dはベクトル化された引数の次元)
  */
    matrix_type	jacobian(const argument_type& x) const
		{
		    const vector_type&	y = serialize(x);
		    matrix_type		L(1, y.size());
		    (L[0] = y) *= 2.0;
		    return L;
		}

  private:
    const element_type	_sqr;
};

/************************************************************************
*  function minimizeSquare						*
*    -- Compute x st. ||f(x)||^2 -> min under g(x) = 0.			*
************************************************************************/
//! 与えられたベクトル値関数の2乗ノルムを与えられた拘束条件の下で最小化する引数を求める．
/*!
  本関数は，2つのベクトル関数\f$\TUvec{f}{}(\TUvec{x}{})\f$,
  \f$\TUvec{g}{}(\TUvec{x}{})\f$および初期値\f$\TUvec{x}{0}\f$が与えられたとき，
  \f$\TUvec{g}{}(\TUvec{x}{}) = \TUvec{0}{}\f$なる拘束のもとで
  \f$\TUnorm{\TUvec{f}{}(\TUvec{x}{})}^2 \rightarrow \min\f$とする
  \f$\TUvec{x}{}\f$を求める．
  
  テンプレートパラメータATは，ベクトル値関数および拘束条件関数の引数を表す型であり，
  以下の条件を満たすこと：
  -# 引数がベクトルや行列である場合，その要素の型を
	AT::element_type
     という名前でtypedefしている．

  テンプレートパラメータFは，AT型の引数を入力してベクトル値を出力する関数を表す型であり，
  以下の条件を満たすこと：
  -# 出力ベクトルの要素の型を
	F::element_type
     という名前でtypedefしている．
  -# 引数xを与えたときの関数値は，メンバ関数
	Vector<F:element_type>	F::operator ()(const AT& x) const
     によって与えられる．
  -# 引数xを与えたときのヤコビアンは，メンバ関数
	Matrix<F:element_type>	F::jacobian(const AT& x) const
     によって与えられる．
  -# メンバ関数
	void	F::update(const AT& x, const Vector<F::element_type>& dx) const
     によって引数xを微少量dxだけ更新することができる．

  テンプレートパラメータGは，AT型の引数を入力してベクトル値を出力する関数を表す型であり，
  以下の条件を満たすこと：
  -# 出力ベクトルの要素の型を
	G::element_type
     という名前でtypedefしている．
  -# 引数xを与えたときの関数値は，メンバ関数
	Vector<G:element_type>	G::operator ()(const AT& x) const
     によって与えられる．
  -# 引数xを与えたときのヤコビアンは，メンバ関数
	Matrix<G::element_type>	G::jacobian(const AT& x) const
     によって与えられる．

  \param f		その2乗ノルムを最小化すべきベクトル値関数
  \param g		拘束条件を表すベクトル値関数
  \param x		初期値を与えると，gが零ベクトルとなるという拘束条件の下で
			fの2乗ノルムを最小化する引数の値が返される．
  \param niter_max	最大繰り返し回数
  \param tol		収束判定条件を表す閾値(更新量がこの値以下になれば収束と見なす)
  \return		xの推定値の共分散行列
*/
template <class F, class G, class AT> Matrix<typename F::element_type>
minimizeSquare(const F& f, const G& g, AT& x,
	       size_t niter_max=100, double tol=1.5e-8)
{
    using namespace			std;
    typedef typename F::element_type	element_type;	// element type.
    typedef Vector<element_type>	vector_type;
    typedef Matrix<element_type>	matrix_type;
    
    vector_type		fval   = f(x);			// function value.
    element_type	sqr    = fval * fval;		// square value.
    element_type	lambda = 1.0e-4;		// L-M parameter.

    for (size_t n = 0; n++ < niter_max; )
    {
	const matrix_type&	J    = f.jacobian(x);	// Jacobian.
	const vector_type&	Jtf  = fval * J;
	const vector_type&	gval = g(x);		// constraint residual.
	const size_t		xdim = J.ncol(), gdim = gval.size();
	matrix_type		A(xdim + gdim, xdim + gdim);

	A(0, 0, xdim, xdim) = J.trns() * J;
	A(xdim, 0, gdim, xdim) = g.jacobian(x);
	A(0, xdim, xdim, gdim) = A(xdim, 0, gdim, xdim).trns();

	vector_type		diagA(xdim);
	for (size_t i = 0; i < xdim; ++i)
	    diagA[i] = A[i][i];			// Keep diagonal elements.

	for (;;)
	{
	  // Compute dx: update for parameters x to be estimated.
	    for (size_t i = 0; i < xdim; ++i)
		A[i][i] = (1.0 + lambda) * diagA[i];	// Augument diagonals.
	    vector_type	dx(xdim + gdim);
	    dx(0, xdim) = Jtf;
	    dx(xdim, gdim) = gval;
	    dx.solve(A);

	  // Compute updated parameters and function value to it.
	    AT			x_new(x);
	    f.update(x_new, dx(0, xdim));
	    const vector_type&	fval_new = f(x_new);
	    const element_type	sqr_new  = fval_new * fval_new;
#ifdef TU_MINIMIZE_DEBUG
	    cerr << "val^2 = " << sqr << ", gval = " << gval
		 << "  (update: val^2 = " << sqr_new
		 << ", lambda = " << lambda << ")" << endl;
#endif
	    if (fabs(sqr_new - sqr) <=
		tol * (fabs(sqr_new) + fabs(sqr) + 1.0e-10))
	    {
		for (size_t i = 0; i < xdim; ++i)
		    A[i][i] = diagA[i];
		return A(0, 0, xdim, xdim).pinv(1.0e8);
	    }

	    if (sqr_new < sqr)
	    {
		x	= x_new;		// Update parameters.
		fval	= fval_new;		// Update function value.
		sqr	= sqr_new;		// Update square value.
		lambda *= 0.1;			// Decrease L-M parameter.
		break;
	    }
	    else
		lambda *= 10.0;			// Increase L-M parameter.
	}
    }
    throw std::runtime_error("minimizeSquare: maximum iteration limit exceeded!");
    return matrix_type(0, 0);
}

/************************************************************************
*  function minimizeSquareSparse					*
*    -- Compute a and b st. sum||f(a, b[j])||^2 -> min under g(a) = 0.	*
************************************************************************/
//! 与えられたベクトル値関数の2乗ノルムを与えられた拘束条件の下で最小化する引数を求める．
/*!
  本関数は，\f$\TUvec{x}{} = [\TUtvec{a}{}, \TUtvec{b}{1},
  \TUtvec{b}{2}, \ldots, \TUtvec{b}{J}]^\top\f$を入力とする2つのベクト
  ル関数\f$\TUvec{f}{}(\TUvec{x}{}) = [\TUtvec{f}{1}(\TUvec{a}{},
  \TUvec{b}{1}), \TUtvec{f}{2}(\TUvec{a}{}, \TUvec{b}{2}),\ldots,
  \TUtvec{f}{J}(\TUvec{a}{}, \TUvec{b}{J})]^\top\f$,
  \f$\TUvec{g}{}(\TUvec{x}{})\f$および初期値\f$\TUvec{x}{0}\f$が与えら
  れたとき，\f$\TUvec{g}{}(\TUvec{x}{}) = \TUvec{0}{}\f$なる拘束のもと
  で\f$\TUnorm{\TUvec{f}{}(\TUvec{x}{})}^2 \rightarrow \min\f$とする
  \f$\TUvec{x}{}\f$を求める．個々の\f$\TUvec{f}{j}(\cdot)\f$は
  \f$\TUvec{a}{}\f$と\f$\TUvec{b}{j}\f$のみに依存し，
  \f$\TUvec{g}{}(\cdot)\f$は\f$\TUvec{a}{}\f$のみに依存する(すなわち
  \f$\TUvec{g}{}(\TUvec{x}{}) = \TUvec{g}{}(\TUvec{a}{})\f$)ものとする．
  
  テンプレートパラメータATAは，ベクトル値関数fの第1引数および拘束条件関数gの
  引数aを表す型であり，以下の条件を満たすこと：
  -# 引数がベクトルや行列である場合，その要素の型を
	ATA::element_type
     という名前でtypedefしている．

  テンプレートパラメータIBは，個々のベクトル値関数f_jの第2引数b_jを指す
  反復子を表す型であり，以下の条件を満たすこと：
  -# iterator_traits<IB>::element_type
     でこの反復子が指す引数の型(以下，ATBとする)を知ることができる．

  テンプレートパラメータFは，ATA型の引数aとATB型の引数b_jを入力して
  ベクトル値を出力する関数を表す型であり，以下の条件を満たすこと：
  -# 出力ベクトルの要素の型を
	F::element_type
     という名前でtypedefしている．
  -# ヤコビアンの型を
	F::jacobian_type
     という名前でtypedefしている．
  -# ATA型の引数aが持つ自由度を
	size_t	F::adim() const
     によって知ることができる．
  -# 引数aをa_1, a_2,..., a_Iに分割した場合の各a_iが持つ自由度を
	const Array<size_t>&	F::adims() const;
     によって知ることができる．この配列の要素の総和は
	F::adim()
     に等しい．aが分割できない場合長さ1の配列が返され，その唯一の要素の値は
	F::adim()
     に等しい．
  -# 引数a, b_jを与えたときのf_jの関数値は，メンバ関数
	Vector<F:element_type>	F::operator ()(const ATA& a, const ATB& b, int j) const
     によって与えられる．
  -# 引数a, b_jを与えたときのaで微分したヤコビアンは，メンバ関数
	F::jacobian_type	F::jacobianA(const ATA& a, const ATB& b, int j) const
     によって与えられる．
  -# メンバ関数
	void	F::updateA(const ATA& a, const Vector<F::element_type>& da) const
     によって引数aを微少量daだけ更新することができる．
  -# メンバ関数
	void	F::updateB(const ATB& b_j, const Vector<F::element_type>& db_j) const
     によって引数bを微少量db_jだけ更新することができる．

  テンプレートパラメータGは，ATA型の引数を入力してベクトル値を出力する関数を
  表す型であり，以下の条件を満たすこと：
  -# 出力ベクトルの要素の型を
	G::element_type
     という名前でtypedefしている．
  -# 引数aを与えたときの関数値は，メンバ関数
	Vector<G:element_type>	G::operator ()(const ATA& a) const
     によって与えられる．
  -# 引数aを与えたときのヤコビアンは，メンバ関数
	Matrix<G::element_type>	G::jacobian(const ATA& a) const
     によって与えられる．

  \param f		その2乗ノルムを最小化すべきベクトル値関数
  \param g		拘束条件を表すベクトル値関数
  \param a		各f_jの第1引数であり，かつgの引数．初期値を与えると
			最適解が返される．
  \param bbegin		各f_jに与える第2引数の並びの先頭を指す反復子
  \param bend		各f_jに与える第2引数の並びの末尾の次を指す反復子
  \param niter_max	最大繰り返し回数
  \param tol		収束判定条件を表す閾値(更新量がこの値以下になれば
			収束と見なす)
  \return		a, b_1, b_2,..., b_Jの推定値の共分散行列
*/
template <class F, class G, class ATA, class IB>
Matrix<typename F::element_type>
minimizeSquareSparse(const F& f, const G& g, ATA& a, IB bbegin, IB bend,
		     size_t niter_max=100, double tol=1.5e-8)
{
    using namespace					std;
    typedef typename F::element_type			element_type;
    typedef typename F::jacobian_type			jacobian_type;
    typedef Vector<element_type>			vector_type;
    typedef Matrix<element_type>			matrix_type;
    typedef typename iterator_traits<IB>::value_type	ATB; // arg. b type.
    
    const size_t	nb = distance(bbegin, bend);
    Array<vector_type>	fval(nb);	// function values.
    element_type	sqr = 0;	// sum of squares.
    int			j = 0;
    for (IB b = bbegin; b != bend; ++b, ++j)
    {
	fval[j] = f(a, *b, j);
	sqr    += fval[j] * fval[j];
    }
    element_type	lambda = 1.0e-7;		// L-M parameter.

    for (size_t n = 0; n++ < niter_max; )
    {
	const size_t		adim = f.adim();
	jacobian_type		U(f.adims(), f.adims());
	vector_type		Jtf(adim);
	Array<matrix_type>	V(nb);
	Array<matrix_type>	W(nb);
	Array<vector_type>	Ktf(nb);
	j = 0;
	for (IB b = bbegin; b != bend; ++b, ++j)
	{
	    const jacobian_type&	J  = f.jacobianA(a, *b, j);
	    const jacobian_type&	Jt = J.trns();
	    const matrix_type&		K  = f.jacobianB(a, *b, j);

	    U     += Jt * J;
	    Jtf   += fval[j] * J;
	    V[j]   = K.trns() * K;
	    W[j]   = Jt * K;
	    Ktf[j] = fval[j] * K;
	}

      	const vector_type&	gval = g(a);
	const size_t		gdim = gval.size();
	matrix_type		A(adim + gdim, adim + gdim);
	
	A(adim, 0, gdim, adim) = g.jacobian(a);
	A(0, adim, adim, gdim) = A(adim, 0, gdim, adim).trns();

	for (;;)
	{
	  // Compute da: update for parameters a to be estimated.
	    A(0, 0, adim, adim) = U;
	    for (size_t i = 0; i < adim; ++i)
		A[i][i] *= (1.0 + lambda);		// Augument diagonals.

	    vector_type		da(adim + gdim);
	    da(0, adim) = Jtf;
	    da(adim, gdim) = gval;
	    Array<matrix_type>	VinvWt(nb);
	    Array<vector_type>	VinvKtf(nb);
	    for (size_t j = 0; j < nb; ++j)
	    {
		matrix_type	Vinv = V[j];
		for (size_t k = 0; k < Vinv.size(); ++k)
		    Vinv[k][k] *= (1.0 + lambda);	// Augument diagonals.
		Vinv = Vinv.inv();
		VinvWt[j]  = Vinv * W[j].trns();
		VinvKtf[j] = Vinv * Ktf[j];
		A(0, 0, adim, adim) -= W[j] * VinvWt[j];
		da(0, adim) -= W[j] * VinvKtf[j];
	    }
	    da.solve(A);

	  // Compute updated parameters and function value to it.
	    ATA			a_new(a);
	    f.updateA(a_new, da(0, adim));
	    Array<ATB>		b_new(nb);
	    copy(bbegin, bend, b_new.begin());
	    Array<vector_type>	fval_new(nb);
	    element_type	sqr_new = 0;
	    for (size_t j = 0; j < nb; ++j)
	    {
		const vector_type& db = VinvKtf[j] - VinvWt[j] * da(0, adim);
		f.updateB(b_new[j], db);
		fval_new[j] = f(a_new, b_new[j], j);
		sqr_new	   += fval_new[j] * fval_new[j];
	    }
#ifdef TU_MINIMIZE_DEBUG
	    cerr << "val^2 = " << sqr << ", gval = " << gval
		 << "  (update: val^2 = " << sqr_new
		 << ", lambda = " << lambda << ")" << endl;
#endif
	    if (fabs(sqr_new - sqr) <=
		tol * (fabs(sqr_new) + fabs(sqr) + 1.0e-10))
	    {
		size_t		bdim = 0;
		for (size_t j = 0; j < nb; ++j)
		    bdim += V[j].size();
		matrix_type	S(adim + bdim, adim + bdim);
		matrix_type	Sa(S, 0, 0, adim, adim);
		Sa = U;
		for (size_t j = 0; j < nb; ++j)
		{
		    VinvWt[j] = V[j].inv() * W[j].trns();
		    Sa -= W[j] * VinvWt[j];
		}
		for (size_t jj = adim, j = 0; j < nb; ++j)
		{
		    const matrix_type&	VinvWtSa = VinvWt[j] * Sa;
		    for (size_t kk = adim, k = 0; k <= j; ++k)
		    {
			S(jj, kk, VinvWtSa.nrow(), VinvWt[k].nrow())
			     = VinvWtSa * VinvWt[k].trns();
			kk += VinvWt[k].nrow();
		    }
		    S(jj, jj, V[j].nrow(), V[j].nrow()) += V[j].inv();
		    jj += VinvWt[j].nrow();
		}
		Sa = Sa.pinv(1.0e8);
		for (size_t jj = adim, j = 0; j < nb; ++j)
		{
		    S(jj, 0, VinvWt[j].nrow(), adim) = -VinvWt[j] * Sa;
		    jj += VinvWt[j].nrow();
		}
		    
		return S.symmetrize() *= sqr;
	    }
	    
	    if (sqr_new < sqr)
	    {
		a = a_new;			// Update parameters.
		copy(b_new.begin(), b_new.end(), bbegin);
		fval = fval_new;		// Update function values.
		sqr = sqr_new;			// Update residual.
		lambda *= 0.1;			// Decrease L-M parameter.
		break;
	    }
	    else
		lambda *= 10.0;			// Increase L-M parameter.
	}
    }
    throw std::runtime_error("minimizeSquareSparse: maximum iteration limit exceeded!");

    return matrix_type(0, 0);
}

/************************************************************************
*  function minimizeSquareSparseDebug					*
*    -- Compute a and b st. sum||f(a, b[j])||^2 -> min under g(a) = 0.	*
************************************************************************/
template <class F, class G, class ATA, class IB>  Matrix<typename F::ET>
minimizeSquareSparseDebug(const F& f, const G& g, ATA& a, IB bbegin, IB bend,
			  size_t niter_max=100, double tol=1.5e-8)
{
    using namespace					std;
    typedef typename F::element_type			element_type;
    typedef Vector<element_type>			vector_type;
    typedef Matrix<element_type>			matrix_type;
    typedef typename iterator_traits<IB>::value_type	ATB; // arg. b type.

    const size_t	nb = distance(bbegin, bend);
    Array<vector_type>	fval(nb);	// function values.
    element_type	sqr = 0;	// sum of squares.
    int			j = 0;
    for (IB b = bbegin; b != bend; ++b, ++j)
    {
	fval[j] = f(a, *b, j);
	sqr    += fval[j] * fval[j];
    }
    element_type	lambda = 1.0e-7;		// L-M parameter.

    for (size_t n = 0; n++ < niter_max; )
    {
	const size_t		adim = f.adim();
	const size_t		bdim = f.bdim() * nb;
      	const vector_type&	gval = g(a);
	const size_t		gdim = gval.size();
	matrix_type		U(adim, adim);
	vector_type		Jtf(adim);
	Array<matrix_type>	V(nb);
	Array<matrix_type>	W(nb);
	Array<vector_type>	Ktf(nb);
	matrix_type		A(adim + bdim + gdim, adim + bdim + gdim);
	j = 0;
	for (IB b = bbegin; b != bend; ++b, ++j)
	{
	    const matrix_type&	J  = f.jacobianA(a, *b, j);
	    const matrix_type&	Jt = J.trns();
	    const matrix_type&	K  = f.jacobianB(a, *b, j);

	    U     += Jt * J;
	    Jtf   += fval[j] * J;
	    V[j]   = K.trns() * K;
	    W[j]   = Jt * K;
	    Ktf[j] = fval[j] * K;

	    A(0, adim + j*f.bdim(), adim, f.bdim()) = W[j];
	    A(adim + j*f.bdim(), 0, f.bdim(), adim) = W[j].trns();
	}
	A(adim + bdim, 0, gdim, adim) = g.jacobian(a);
	A(0, adim + bdim, adim, gdim) = A(adim + bdim, 0, gdim, adim).trns();

	for (;;)
	{
	  // Compute da: update for parameters a to be estimated.
	    A(0, 0, adim, adim) = U;
	    for (size_t i = 0; i < adim; ++i)
		A[i][i] *= (1.0 + lambda);
	    for (size_t j = 0; j < nb; ++j)
	    {
		A(adim + j*f.bdim(), adim + j*f.bdim(), f.bdim(), f.bdim())
		    = V[j];
		for (size_t k = 0; k < f.bdim(); ++k)
		    A[adim + j*f.bdim() + k][adim + j*f.bdim() + k]
			*= (1.0 + lambda);
	    }

	    vector_type	dx(adim + bdim + gdim);
	    dx(0, adim) = Jtf;
	    for (size_t j = 0; j < nb; ++j)
		dx(adim + j*f.bdim(), f.bdim()) = Ktf[j];
	    dx(adim + bdim, gdim) = gval;
	    dx.solve(A);
	    
	  // Compute updated parameters and function value to it.
	    ATA			a_new(a);
	    f.updateA(a_new, dx(0, adim));
	    Array<ATB>		b_new(nb);
	    copy(bbegin, bend, b_new.begin());
	    Array<vector_type>	fval_new(nb);
	    element_type	sqr_new = 0;
	    for (size_t j = 0; j < nb; ++j)
	    {
		const vector_type& db = dx(adim + j*f.bdim(), f.bdim());
	      //		cerr << "*** check:  "
	      // << (dx(0, adim) * W[j] + V[j] * db - Ktf[j]);
		f.updateB(b_new[j], db);
		fval_new[j] = f(a_new, b_new[j], j);
		sqr_new	   += fval_new[j] * fval_new[j];
	    }
#ifdef TU_MINIMIZE_DEBUG
	    cerr << "val^2 = " << sqr << ", gval = " << gval
		 << "  (update: val^2 = " << sqr_new
		 << ", lambda = " << lambda << ")" << endl;
#endif
	    if (fabs(sqr_new - sqr) <=
		tol * (fabs(sqr_new) + fabs(sqr) + 1.0e-10))
	    {
		A(0, 0, adim, adim) = U;
		for (size_t j = 0; j < nb; ++j)
		    A(adim + j*f.bdim(), adim + j*f.bdim(), f.bdim(), f.bdim())
			= V[j];
		vector_type	evalue;
		A(0, 0, adim + bdim, adim + bdim).eigen(evalue);
		cerr << evalue;
		return A(0, 0, adim + bdim, adim + bdim).pinv(1.0e8) *= sqr;
	    }

	    if (sqr_new < sqr)
	    {
		a = a_new;			// Update parameters.
		copy(b_new.begin(), b_new.end(), bbegin);
		fval = fval_new;		// Update function values.
		sqr = sqr_new;			// Update residual.
		lambda *= 0.1;			// Decrease L-M parameter.
		break;
	    }
	    else
		lambda *= 10.0;			// Increase L-M parameter.
	}
    }
    throw std::runtime_error("minimizeSquareSparseDebug: maximum iteration limit exceeded!");

    return matrix_type(0, 0);
}

}
#endif	// !__TU_MINIMIZE_H
