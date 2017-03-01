/*
 *  $Id: Movie.h 1777 2015-02-06 10:54:01Z ueshiba $
 */
/*!
  \file		Movie.h
  \brief	クラス TU::Movie の定義と実装
*/
#ifndef __TU_MOVIE_H
#define __TU_MOVIE_H

#include <utility>
#include <list>
#include "TU/Image++.h"
#include "TU/Manip.h"

namespace TU
{
/************************************************************************
*  class Movie<T>							*
************************************************************************/
//! ムービーを表すクラス
/*!
  複数のビューを持つことができ，そのサイズは各ビュー毎に個別に指定できる．
  \param T	画素の型
*/
template <class T> class Movie
{
  public:
  //! 各ビューの幅と高さのペア
    typedef std::pair<size_t, size_t>			Size;

  private:
  //! ビュー
    struct View : public Image<T>
    {
	View()	:Image<T>(), offset(0)			{}
	
	size_t	offset;		//!< フレームの先頭からの画像データ領域のオフセット
    };

  //! フレーム
    class Frame : public Array<T>
    {
      private:
	typedef Array<T>				super;

      public:
	explicit Frame(size_t n=0)	:super(n)	{}
    };

    typedef std::list<Frame>				Frames;
    typedef typename Frames::iterator			iterator;

  public:
    Movie(size_t nviews=0)						;

  // Set sizes for each view.
    Movie<T>&		setSizes(const Array<Size>& sizes)		;

  // General information.
    bool		isCircularMode()			const	;
    Movie<T>&		setCircularMode(bool circular)			;
    size_t		nviews()				const	;
    size_t		width(size_t view)			const	;
    size_t		height(size_t view)			const	;
    const Image<T>&	image(size_t view)			const	;
    Image<T>&		image(size_t view)				;

  // Handling frames.
			operator bool()				const	;
    size_t		nframes()				const	;
    size_t		currentFrame()				const	;
    Movie<T>&		setFrame(size_t frame)				;
    Movie<T>&		rewind()					;
    Movie<T>&		operator ++()					;
    Movie<T>&		operator --()					;
    
  // Edit movie.
    Movie<T>&		insert(size_t n)				;
    const Movie<T>&	copy(size_t n)				const	;
    Movie<T>&		cut(size_t n)					;
    size_t		paste()						;
    Movie<T>&		swap()						;
    
  // Restore/Save movie.
    std::istream&	restore(std::istream& in)			;
    std::ostream&	save(std::ostream& out,
			     ImageBase::Type type=ImageBase::DEFAULT)	;
    ImageBase::Type	saveHeader(std::ostream& out,
				   ImageBase::Type
				       type=ImageBase::DEFAULT)	const	;
    std::ostream&	saveFrame(std::ostream& out,
				  ImageBase::Type
				      type=ImageBase::DEFAULT)	const	;

  private:
    Movie<T>&		setFrameToViews()				;
    ImageBase::TypeInfo	restoreHeader(std::istream& in)			;
    std::istream&	restoreFrames(std::istream& in,
				      ImageBase::TypeInfo typeInfo,
				      size_t m)				;
    static size_t	npixels(size_t n)				;
    
  private:
    bool		_circular;	//!< 循環モード/非循環モード
    Array<View>		_views;		//!< ビューの並び
    Frames		_frames;	//!< フレームの並び
    iterator		_dummy;		//!< フレームの末尾を表すダミーフレーム
    iterator		_current;	//!< 現フレーム
    size_t		_cFrame;	//!< 現フレームの番号
    mutable Frames	_buf;		//!< 編集用バッファ
};

//! ビュー数を指定してムービーを生成する．
/*!
  \param nviews		ビュー数
*/
template <class T> inline
Movie<T>::Movie(size_t nviews)
    :_circular(false), _views(nviews), _frames(1),
     _dummy(_frames.begin()), _current(_dummy), _cFrame(0), _buf()
{
}

//! 各ビューのサイズを指定する．
/*!
  指定後は，現在のビューとフレームを共に0に設定する．
  \param sizes	各ビューの幅と高さのペアを収めた配列．配列のサイズがビュー数となる．
  \return	このムービー
*/
template <class T> Movie<T>&
Movie<T>::setSizes(const Array<Size>& sizes)
{
  // ビュー数と各ビューのオフセットを設定．
    _views.resize(sizes.size());
    size_t	n = 0;
    for (size_t i = 0; i < nviews(); ++i)
    {
	_views[i].offset = n;
	n += npixels(sizes[i].first * sizes[i].second);
    }
    
  // 大きさが1フレームあたりの画素数に等しいダミーフレームを確保．
    _frames.clear();			// 全フレームを廃棄
    _frames.push_front(Frame(n));	// ダミーフレームを確保
    _dummy  = _frames.begin();

  // 各ビューにダミーフレームを設定．
    for (size_t i = 0; i < nviews(); ++i)
	_views[i].resize(_dummy->data() + _views[i].offset,
			 sizes[i].second, sizes[i].first);

  // 現フレームをダミーフレームに設定．
    _current = _dummy;
    _cFrame  = 0;
    
    return *this;
}

//! 循環モードであるか調べる．
/*!
  \return	循環モードであればtrue, そうでなければfalse
*/
template <class T> inline bool
Movie<T>::isCircularMode() const
{
    return _circular;
}
    
//! 循環/非循環モードを設定する．
/*!
  循環モードに設定する場合は，現フレームがムービーの末尾であれば先頭に設定する．
  \param circular	循環モードであればtrue, そうでなければfalse
  \return		このムービー
*/
template <class T> Movie<T>&
Movie<T>::setCircularMode(bool circular)
{
    _circular = circular;

    if (_circular && _current == _dummy)
	return rewind();
    else
	return *this;
}
    
//! ビュー数を返す．
/*!
  \return	view数
*/
template <class T> inline size_t
Movie<T>::nviews() const
{
    return _views.size();
}

//! 指定されたビューに対応する画像の幅を返す．
/*!
  \param view	ビュー番号
  \return	画像の幅
*/
template <class T> inline size_t
Movie<T>::width(size_t view) const
{
    return _views[view].width();
}
    
//! 指定されたビューに対応する画像の高さを返す．
/*!
  \param view	ビュー番号
  \return	画像の高さ
*/
template <class T> inline size_t
Movie<T>::height(size_t view) const
{
    return _views[view].height();
}

//! 現在のフレームの指定されたビューに対応する画像を返す．
/*!
  \param view	ビュー番号
  \return	画像
*/
template <class T> inline const Image<T>&
Movie<T>::image(size_t view) const
{
    return _views[view];
}

//! 現在のフレームの指定されたビューに対応する画像を返す．
/*!
  \param view	ビュー番号
  \return	画像
*/
template <class T> inline Image<T>&
Movie<T>::image(size_t view)
{
    return _views[view];
}

//! 現フレームの状態を調べる．
/*!
  \return	現フレームが最後のフレームの次に達していればfalse,
		そうでなければtrue
*/
template <class T> inline
Movie<T>::operator bool() const
{
    return (_current != _dummy);
}

//! フレーム数を返す．
/*!
  \return	フレーム数
*/
template <class T> inline size_t
Movie<T>::nframes() const
{
    return _frames.size() - 1;		// ダミーフレームはカウントしない．
}

//! 現在のフレーム番号を返す．
/*!
  \return	フレーム番号
*/
template <class T> inline size_t
Movie<T>::currentFrame() const
{
    return _cFrame;
}

//! 現フレームを指定する．
/*!
  frame >= nframes() の場合は現フレームは nframes() が返す値に設定され，
  #operator bool() でfalseが返される状態になる．
  \param frame	フレーム番号
  \return	このムービー
*/
template <class T> inline Movie<T>&
Movie<T>::setFrame(size_t frame)
{
    using namespace	std;

    _cFrame  = min(frame, nframes());
    _current = _frames.begin();
    advance(_current, _cFrame);

    return setFrameToViews();
}
    
//! 現フレームをムービーの先頭に戻す．
/*!
  \return	このムービー
*/
template <class T> inline Movie<T>&
Movie<T>::rewind()
{
    return setFrame(0);
}

//! 現フレームを1つ先に進める．
/*!
  現フレームが既に最後のフレームの次に達していたら( #operator bool() で
  falseが返される状態になっていたら)，何もせずにリターンする．
  現フレームが最後のフレームである場合，循環モードでないならばさらに
  最後のフレームの次に進み， #operator bool() でfalseが返される状態になる．
  循環モードならば先頭フレームに移動する．
  \return	このムービー
*/
template <class T> inline Movie<T>&
Movie<T>::operator ++()
{
    if (_current == _dummy)
	return *this;

    ++_current;
    ++_cFrame;
    if (_current == _dummy && _circular)	// 末尾に達し，
    {						// かつ循環モードならば...
	_current = _frames.begin();		// 先頭に移動する．
	_cFrame  = 0;
    }

    return setFrameToViews();
}

//! 現在のフレームを1つ前に戻す．
/*!
  現フレームがムービーの先頭の場合，循環モードでないならばムービーの
  最後のフレームの次に移動し， #operator bool() でfalseが返される状態になる．
  循環モードならば最後のフレームに移動する．
  \return	このムービー
*/
template <class T> inline Movie<T>&
Movie<T>::operator --()
{
    if (_current == _frames.begin())	// ムービーの先頭ならば...
    {
	_current = _dummy;		// 最後のフレームの次に移動する．
	_cFrame  = nframes();
	
	if (_circular)			// さらに循環モードならば...
	{
	    --_current;			// 最後のフレームに戻る．
	    --_cFrame;
	}
    }
    else
    {
	--_current;
	--_cFrame;
    }

    return setFrameToViews();
}

//! 現フレームの直前に指定した枚数のフレームを挿入する．
/*!
  現フレームは挿入した最初のフレームとなる．
  \param n	挿入する枚数
  \return	このムービー
*/
template <class T> Movie<T>&
Movie<T>::insert(size_t n)
{
    iterator	cur = _current;		// 現フレームを記憶する．

  // 挿入後の _current の再設定に備える．
    if (_current == _frames.begin())	// 先頭に挿入するなら...
	_current = _frames.end();	// 一時的に無効化．
    else				// そうでなければ...
	--_current;			// 挿入位置の1つ前．

  // 現フレームの直前に挿入
    _frames.insert(cur, n, Frame(_dummy->size()));

  // _current に挿入された領域の先頭を再設定する．
  // 先頭からの _current のオフセット _cFrame は変化しない．
    if (_current == _frames.end())	// 先頭に挿入した場合は...
	_current = _frames.begin();	// ムービーの先頭．
    else				// そうでなければ...
	++_current;			// 挿入位置の1つ前の次．

    return setFrameToViews();
}
    
//! 現フレームから指定された枚数のフレームを編集用バッファにコピーする．
/*!
  編集用バッファの内容は上書きされる．現フレームは変化しない．
  \param n	コピーされる枚数
  \return	このムービー
 */
template <class T> const Movie<T>&
Movie<T>::copy(size_t n) const
{
  // コピーされる領域の末尾を検出する．
    iterator	tail = _current;
    std::advance(tail, std::min(n, nframes() - _cFrame));

  // [_current, tail) を _buf にコピーする．
    _buf.assign(_current, tail);

    return *this;
}

//! 現フレームから指定されたフレーム数をカットして編集用バッファに移す．
/*!
  編集用バッファの内容は上書きされる．現フレームはカットされた領域の直後となる．
  \param n	カットされるフレーム数
  \return	このムービー
 */
template <class T> Movie<T>&
Movie<T>::cut(size_t n)
{
  // カットされる領域の末尾を検出する．
    n = std::min(n, nframes() - _cFrame);
    iterator	tail = _current;
    std::advance(tail, n);

  // [_current, tail) を _buf に移す．
    _buf.clear();
    _buf.splice(_buf.begin(), _frames, _current, tail);
    
  // _currentをカットされた領域の直後に再設定する．
  // 先頭からの _current のオフセット _cFrame は変化しない．
    _current = tail;

    if (_current == _dummy && _circular)  // 末尾までカットかつ循環モードならば...
	return rewind();		  // 先頭に戻る．
    else				  // そうでなければ...
	return setFrameToViews();	  // _current を各ビューに設定する．
}

//! 現フレームの直前に編集用バッファの内容を挿入する．
/*!
  編集用バッファは空になる．現フレームは挿入された領域の先頭になる．
  \return	挿入されたフレーム数
 */
template <class T> size_t
Movie<T>::paste()
{
    iterator	cur = _current;		// 現フレームを記憶する．
    size_t	n = _buf.size();	// 編集用バッファ中のフレーム数
    
  // 挿入後の _current の再設定に備える．
    if (_current == _frames.begin())	// 先頭に挿入するなら...
	_current = _frames.end();	// 一時的に無効化．
    else				// そうでなければ...
	--_current;			// 挿入位置の1つ前．

  // _bufの内容を現フレームの直前に挿入する．
    _frames.splice(cur, _buf);

  // _current に挿入された領域の先頭を再設定する．
  // 先頭からの _current のオフセット _cFrame は変化しない．
    if (_current == _frames.end())	// 先頭に挿入した場合は...
	_current = _frames.begin();	// ムービーの先頭．
    else				// そうでなければ...
	++_current;			// 挿入位置の1つ前の次．

    setFrameToViews();

    return n;
}

//! 現フレームの前後を交換する．
/*!
  現フレームは交換前のムービーの先頭になる．
  \return	このムービー
 */
template <class T> inline Movie<T>&
Movie<T>::swap()
{
    iterator	tmp = _frames.begin();	// 交換前の先頭を記憶

    _frames.splice(_frames.begin(), _frames, _current, _dummy);

    _current = tmp;			// 交換前の先頭を現フレームとする
    _cFrame  = nframes() - _cFrame;	// 交換後の前半の長さ = 交換前の後半の長さ
    
    return setFrameToViews();
}
    
//! 入力ストリームからムービーを読み込む．
/*!
  入力ストリームの末尾に達するまでフレームを読み続ける．
  \param in	入力ストリーム
  \return	inで指定した入力ストリーム
*/
template <class T> inline std::istream&
Movie<T>::restore(std::istream& in)
{
    return restoreFrames(in, restoreHeader(in), 0);
}

//! ムービーを指定した画素タイプで出力ストリームに書き出す．
/*!
 \param out	出力ストリーム
 \param type	画素タイプ．ただし， #TU::ImageBase::DEFAULT を指定した場合は，
		このムービーの画素タイプで書き出される．   
 \return	outで指定した出力ストリーム
*/
template <class T> std::ostream&
Movie<T>::save(std::ostream& out, ImageBase::Type type)
{
    saveHeader(out, type);

    bool	circular = isCircularMode();
    setCircularMode(false);

    for (rewind(); *this; ++(*this))
	saveFrame(out, type);
    rewind();

    setCircularMode(circular);
    
    return out;
}

//! ムービーのヘッダを指定した画素タイプで出力ストリームに書き出す．
/*!
 \param out	出力ストリーム
 \param type	画素タイプ．ただし， #TU::ImageBase::DEFAULT を指定した場合は，
		このムービーの画素タイプで書き出される．   
 \return	実際に書き出す場合の画素タイプ
*/
template <class T> ImageBase::Type
Movie<T>::saveHeader(std::ostream& out, ImageBase::Type type) const
{
    using namespace	std;
    
    out << 'M' << nviews() << endl;
    for (size_t i = 0; i < nviews(); ++i)
	type = _views[i].saveHeader(out, type);
    return type;
}

//! 現在のフレームを指定した画素タイプで出力ストリームに書き出す．
/*!
 \param out	出力ストリーム
 \param type	画素タイプ．ただし， #TU::ImageBase::DEFAULT を指定した場合は，
		このムービーの画素タイプで書き出される．   
 \return	outで指定した出力ストリーム
*/
template <class T> std::ostream&
Movie<T>::saveFrame(std::ostream& out, ImageBase::Type type) const
{
    for (size_t i = 0; i < nviews(); ++i)
	_views[i].saveData(out, type);
    return out;
}

/*
 *  private member functions
 */
//! 現フレームを個々のビューにセットする．
/*!
  \return	このムービー
*/ 
template <class T> Movie<T>&
Movie<T>::setFrameToViews()
{
    for (size_t i = 0; i < _views.size(); ++i)
	_views[i].resize(_current->data() + _views[i].offset,
			 _views[i].height(), _views[i].width());
    return *this;
}
    
template <class T> ImageBase::TypeInfo
Movie<T>::restoreHeader(std::istream& in)
{
    using namespace	std;

  // ファイルの先頭文字が'M'であることを確認する．
    char	c;
    if (!in.get(c))
	return ImageBase::TypeInfo(ImageBase::DEFAULT);
    if (c != 'M')
	throw runtime_error("TU::Movie<T>::restoreHeader: not a movie file!!");

  // ビュー数を読み込み，そのための領域を確保する．
    size_t	nv;
    in >> nv >> skipl;
    _views.resize(nv);

  // 各ビューのヘッダを読み込み，その画像サイズをセットする．
    ImageBase::TypeInfo	typeInfo(ImageBase::DEFAULT);
    Array<Size>		sizes(nviews());
    for (size_t i = 0; i < nviews(); ++i)
    {
	typeInfo = _views[i].restoreHeader(in);
	sizes[i] = make_pair(_views[i].width(), _views[i].height());
    }
    setSizes(sizes);
    
    return typeInfo;
}

template <class T> std::istream&
Movie<T>::restoreFrames(std::istream& in,
			ImageBase::TypeInfo typeInfo, size_t m)
{
    for (;;)
    {
      // とりあえずダミーフレームに読み込む．
	for (size_t i = 0; i < nviews(); ++i)
	    if (!_views[i].restoreData(in, typeInfo))
		goto finish;

      // コピーしてダミーフレームの直前に挿入
	_frames.insert(_dummy, *_dummy);
    }

  finish:
    rewind();	// 先頭フレームを現フレームとする．
    
    return in;
}

template <class T> inline size_t
Movie<T>::npixels(size_t n)
{
    return n;
}

template <> inline size_t
Movie<YUV411>::npixels(size_t n)
{
    return n / 2;
}

}
#endif	// !__TU_MOVIE_H
