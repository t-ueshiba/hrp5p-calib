/*
 *  $Id: CanvasPane.h 2060 2016-11-23 01:24:46Z ueshiba $  
 */
#ifndef __TU_V_CANVASPANE_H
#define __TU_V_CANVASPANE_H

#include "TU/v/TUv++.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class CanvasPane							*
************************************************************************/
class CanvasPane : public Pane
{
  public:
    CanvasPane(Window& parentWin, size_t devWidth=0, size_t devHeight=0);
    virtual			~CanvasPane()				;

    virtual const Widget&	widget()			const	;

    virtual void		repaintUnderlay()			;
    virtual void		repaintOverlay()			;
    void			moveDC(int u, int v)			;
    
  protected:
    virtual CanvasPane&		canvasPane()				;
    virtual void		initializeGraphics()			;
    
  private:
  // allow access to initializeGraphics
    friend void		CBcanvasPaneDC(::Widget, XtPointer client_data,
				       XtPointer)			;

    const Widget	_widget;		// viewportWidget
};

}
}
#endif	// !__TU_V_CANVASPANE_H
