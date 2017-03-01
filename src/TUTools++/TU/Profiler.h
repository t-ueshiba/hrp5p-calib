/*
 *  $Id: Profiler.h 1966 2016-04-17 07:04:48Z ueshiba $
 */
/*!
  \file		Profiler.h
  \brief	クラス TU::Profiler の定義と実装
*/
#ifndef __TU_PROFILER_H
#define __TU_PROFILER_H

#include <chrono>
#include <string>
#include "TU/types.h"
#include "TU/Array++.h"

namespace TU
{
/************************************************************************
*  class Profiler<bool>							*
************************************************************************/
//! プログラムの各ステップ毎に実行時間を測定するためのクラス．
template <class CLOCK=std::chrono::system_clock>
class Profiler;
    
template <class CLOCK>
class Profiler
{
  public:
    typedef CLOCK			clock;
    typedef typename clock::duration	duration;
    typedef typename clock::time_point	time_point;
    
  public:
  //! 指定された個数のタイマを持つプロファイラを作成する．
  /*!
    \param ntimers	タイマの個数
  */
		Profiler(size_t ntimers)
		    :_active(-1), _accums(ntimers), _t0(), _nframes(0)
		{
		    reset();
		}

  //! これまでに処理されたフレーム数を返す．
  /*!
    \return	フレーム数
  */
    size_t	nframes()		const	{ return _nframes; }

  //! 全てのタイマをリセットする（蓄積時間を空にし，フレーム番号を0に戻す）．
    void	reset() const
		{
		    _active = -1;
		    for (size_t n = 0; n < _accums.size(); ++n)
			_accums[n] = duration::zero();
		    _t0 = time_point(duration::zero());
		    _nframes = 0;
		}
    
  //! 現在動いているタイマがあればそれを停止し，指定されたタイマを起動する．
  /*!
    \param n	タイマの番号
  */
    void	start(int n) const
		{
		    if (n != _active)
		    {
			if (_active >= 0)	// 稼働中のタイマがあれば...
			{	// 起動時刻から現在までの時間を稼働中のタイマに加算
			    auto	t1 = clock::now();
			    _accums[_active] += (t1 - _t0);
			    _active = -1;		// タイマを停止
			}
			if (0 <= n && n < _accums.size())
			{
			    _t0 = clock::now();	// 起動時刻を記録
			    _active = n;	// タイマを起動
			}
		    }
		}
    
  //! 現在動いているタイマがあれば，それを停止する．
    void	stop()			const	{ start(-1); }

  //! 現在動いているタイマがあればそれを停止し，フレーム番号を一つ進める．
    void	nextFrame()		const	{ stop(); ++_nframes; }

  //! 1フレームあたりの実行時間と1秒あたりの処理フレーム数を表示する．
  /*!
    処理速度は，各タイマ毎の蓄積時間から計算されたものと，全タイマの蓄積時間の
    総計から計算されたものの両方が表示される．
    \param out	出力ストリーム
  */
    template <class PERIOD=std::milli>
    void	print(std::ostream& out) const
		{
		    auto	total = duration::zero();

		    for (const auto& accum : _accums)
		    {
			print<PERIOD>(out, accum);
			total += accum;
		    }
		    out << '|';
		    print<PERIOD>(out, total);
		    out << std::endl;
		}

    template <class PERIOD=std::milli>
    void	printTabSeparated(std::ostream& out) const
		{
		    typedef std::chrono::duration<float, PERIOD>	 dr;

		    auto	total = duration::zero();

		    for (const auto& accum : _accums)
		    {
			if (_nframes > 0)
			    out << dr(accum).count()/_nframes;
			out << '\t';
			total += accum;
		    }
		    out << "| " << dr(total).count()/_nframes << std::endl;
		}

  private:
    template <class PERIOD>
    void	print(std::ostream& out, const duration& d) const
		{
		    using	std::setw;

		    typedef std::chrono::duration<float, PERIOD>	 dr;
		    typedef std::chrono::duration<float, std::ratio<1> > ds;
	
		    if (_nframes > 0)
		    {
			out << setw(9)
			    << dr(d).count()/_nframes << cap(PERIOD())
			    << '(' << setw(7)
			    << _nframes/ds(d).count() << "fps)";
		    }
		    else
			out << setw(9) << '*' << cap(PERIOD()) << '('
			    << setw(7) << '*' << "fps)";
		}

    static std::string	cap(std::pico)		{ return std::string("ps"); }
    static std::string	cap(std::nano)		{ return std::string("ns"); }
    static std::string	cap(std::micro)		{ return std::string("us"); }
    static std::string	cap(std::milli)		{ return std::string("ms"); }
    static std::string	cap(std::ratio<1>)	{ return std::string("s");  }
    
  private:
    mutable int			_active;
    mutable Array<duration>	_accums;
    mutable time_point		_t0;
    mutable size_t		_nframes;
};

template <>
struct Profiler<void>
{
    Profiler(size_t)				{}

    void	reset()			const	{}
    void	print(std::ostream&)	const	{}
    void	start(int)		const	{}
    void	nextFrame()		const	{}
};

}
#endif	// !__TU_PROFILER_H
