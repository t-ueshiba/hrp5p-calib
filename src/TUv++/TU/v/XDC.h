/*
 *  $Id: XDC.h 2060 2016-11-23 01:24:46Z ueshiba $  
 */
#ifndef __TU_V_XDC_H
#define __TU_V_XDC_H

#include "TU/v/DC.h"
#include "TU/v/Colormap.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class XDC								*
************************************************************************/
class XDC : public DC
{
  public:
    struct BPixel16
    {
	BPixel16&	operator =(u_long pixel)	{_p[0] = pixel >> 8;
							 _p[1] = pixel;
							 return *this;}
	
	u_char		_p[2];
    };
    struct LPixel16
    {
	LPixel16&	operator =(u_long pixel)	{_p[0] = pixel;
							 _p[1] = pixel >> 8;
							 return *this;}
	
	u_char		_p[2];
    };
    struct BPixel24
    {
	BPixel24&	operator =(u_long pixel)	{_p[0] = pixel >> 16;
							 _p[1] = pixel >>  8;
							 _p[2] = pixel;
							 return *this;}
	
	u_char		_p[3];
    };
    struct LPixel24
    {
	LPixel24&	operator =(u_long pixel)	{_p[0] = pixel;
							 _p[1] = pixel >>  8;
							 _p[2] = pixel >> 16;
							 return *this;}
	
	u_char		_p[3];
    };
    struct BPixel32
    {
	BPixel32&	operator =(u_long pixel)	{_p[1] = pixel >> 16;
							 _p[2] = pixel >>  8;
							 _p[3] = pixel;
							 return *this;}
	
	u_char		_p[4];
    };
    struct LPixel32
    {
	LPixel32&	operator =(u_long pixel)	{_p[0] = pixel;
							 _p[1] = pixel >>  8;
							 _p[2] = pixel >> 16;
							 return *this;}
	
	u_char		_p[4];
    };
    
  public:
    virtual DC&		setLayer(Layer layer)				;
    virtual DC&		setThickness(size_t thickness)			;
    virtual DC&		setForeground(const BGR& fg)			;
    virtual DC&		setBackground(const BGR& bg)			;
    virtual DC&		setForeground(size_t fg)			;
    virtual DC&		setBackground(size_t bg)			;
    virtual DC&		setSaturation(size_t saturation)		;
    virtual DC&		setSaturationF(float saturation)		;
    
    virtual DC&		clear()						;
    virtual DC&		sync()						;

    using		DC::operator <<;
    virtual DC&		operator <<(const Point2<int>& p)		;
    virtual DC&		operator <<(const LineP2f& l)			;
    virtual DC&		operator <<(const LineP2d& l)			;
    virtual DC&		operator <<(const Image<u_char>& image)		;
    virtual DC&		operator <<(const Image<s_char>& image)		;
    virtual DC&		operator <<(const Image<short>&  image)		;
    virtual DC&		operator <<(const Image<float>&  image)		;
    virtual DC&		operator <<(const Image<BGR>&    image)		;
    virtual DC&		operator <<(const Image<ABGR>&   image)		;
    virtual DC&		operator <<(const Image<BGRA>&   image)		;
    virtual DC&		operator <<(const Image<RGB>&    image)		;
    virtual DC&		operator <<(const Image<RGBA>&   image)		;
    virtual DC&		operator <<(const Image<ARGB>&   image)		;
    virtual DC&		operator <<(const Image<YUV444>& image)		;
    virtual DC&		operator <<(const Image<YUV422>& image)		;
    virtual DC&		operator <<(const Image<YUYV422>& image)	;
    virtual DC&		operator <<(const Image<YUV411>& image)		;
    virtual DC&		drawLine(const Point2<int>& p,
				 const Point2<int>& q)			;
    virtual DC&		draw(const char* s, int u, int v)		;

    void		dump(std::ostream& out)			const	;

  protected:
    XDC(size_t width, size_t height, float zoom,
	Colormap& colormap, GC gc)					;
    virtual		~XDC()						;

    virtual Drawable	drawable()				const	= 0;
    const Colormap&	colormap()				const	;
    GC			gc()					const	;
    
    virtual XDC&	setGraymap()					;
    virtual XDC&	setSignedmap()					;
    virtual XDC&	setColorcube()					;
    virtual void	allocateXImage(int buffWidth, int buffHeight)	;
    virtual void	putXImage()				const	;
    
    virtual size_t	getThickness()				const	;

  private:
    virtual size_t	realWidth()				const	;
    virtual size_t	realHeight()				const	;
    template <class S>
    void		createXImage(const Image<S>& image)		;
    template <class S, class T>
    void		fillBuff(const Image<S>& image)			;
    
    Colormap&		_colormap;
    GC			_gc;
    Array<char>		_buff;

  protected:
    XImage*		_ximage;
};

inline const Colormap&	XDC::colormap()		const	{return _colormap;}
inline GC		XDC::gc()		const	{return _gc;}

}
}
#endif	// !__TU_V_XDC_H
