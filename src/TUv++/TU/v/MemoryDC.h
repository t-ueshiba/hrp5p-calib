/*
 *  $Id: MemoryDC.h 2060 2016-11-23 01:24:46Z ueshiba $  
 */
#ifndef __TU_V_MEMORYDC_H
#define __TU_V_MEMORYDC_H

#include "TU/v/XDC.h"
#include "TU/v/CanvasPane.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class MemoryDC							*
************************************************************************/
class MemoryDC : public XDC
{
  public:
    MemoryDC(Colormap& colormap, size_t width, size_t height, float zoom=1)	;
    virtual		~MemoryDC()						;

    DC&			setSize(size_t width, size_t height, float zoom)	;

  protected:
    virtual Drawable	drawable()					const	;
    virtual void	initializeGraphics()					;
    virtual DC&		repaintUnderlay()					;
    virtual DC&		repaintOverlay()					;

  private:
    Pixmap	_pixmap;
};

}
}
#endif	// !__TU_V_MEMORYDC_H
