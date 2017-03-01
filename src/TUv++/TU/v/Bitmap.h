/*
 *  $Id: Bitmap.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __TU_V_BITMAP_H
#define __TU_V_BITMAP_H

#include "TU/v/Colormap.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class TUvBitmap							*
************************************************************************/
class Bitmap
{
  public:
    Bitmap(const Colormap& colormap, const u_char data[])	;
    ~Bitmap()							;

    Pixmap		xpixmap()		const	{return _bitmap;}
    
  private:
    Display* const	_display;
    const Pixmap	_bitmap;
};

}
}
#endif	// !__TU_V_BITMAP_H
