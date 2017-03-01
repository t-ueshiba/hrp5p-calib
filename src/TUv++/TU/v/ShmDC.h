/*
 *  $Id: ShmDC.h 2060 2016-11-23 01:24:46Z ueshiba $  
 */
#ifndef __TU_V_SHMDC_H
#define __TU_V_SHMDC_H

#include "TU/v/CanvasPaneDC.h"
#include <X11/extensions/XShm.h>

namespace TU
{
namespace v
{
/************************************************************************
*  class ShmDC								*
************************************************************************/
class ShmDC : public CanvasPaneDC
{
  public:
    ShmDC(CanvasPane& parentCanvasPane, size_t width=0, size_t height=0,
	  float zoom=1)							;
    virtual		~ShmDC()					;

  protected:
    virtual void	allocateXImage(int buffWidth, int buffHeight)	;
    virtual void	putXImage()				const	;
    char*		attachShm(size_t size)				;
    virtual void	destroyShmImage()				;
    XShmSegmentInfo*	xShmInfo()					;
    
  private:
    XShmSegmentInfo	_xShmInfo;
    size_t		_xShmSize;	// Size of shm currently allocated.
    bool		_xShmAvailable;
};

inline XShmSegmentInfo*
ShmDC::xShmInfo()
{
    return &_xShmInfo;
}

}
}
#endif	// !__TU_V_SHMDC_H
