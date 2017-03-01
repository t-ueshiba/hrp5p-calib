/*
 *  $Id: Icon.cc 1219 2012-11-09 05:45:49Z ueshiba $  
 */
#include "TU/v/Icon.h"
#include <stdexcept>

namespace TU
{
namespace v
{
/************************************************************************
*  class Icon								*
************************************************************************/
Icon::Icon(const Colormap& colormap, const u_char data[])
    :_display(colormap.display()),
     _pixmap(XCreatePixmap(_display, DefaultRootWindow(_display),
			   data[0], data[1], colormap.vinfo().depth))
{
    u_long	pixel[5];

    GC		gc = DefaultGC(_display, colormap.vinfo().screen);
    XGCValues	values;
    XGetGCValues(_display, gc, GCForeground, &values);	// keep foreground
    
    int		i = 2;
    for (int v = 0; v < data[1]; ++v)
	for (int u = 0; u < data[0]; ++u)
	{
	    if (data[i] >= sizeof(pixel) / sizeof(pixel[0]))
	    {
		throw std::runtime_error("TU::v::Icon::Icon(): invalid input icon data!");
	    }
	    XSetForeground(_display, gc, pixel[data[i++]]);
	    XDrawPoint(_display, _pixmap, gc, u, v);
	}
    XChangeGC(_display, gc, GCForeground, &values);	// restore foreground
}

Icon::~Icon()
{
    XFreePixmap(_display, _pixmap);
}

}
}
