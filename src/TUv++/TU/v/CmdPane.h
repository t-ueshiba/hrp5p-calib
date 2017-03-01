/*
 *  $Id: CmdPane.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __TU_V_CMDPANE_H
#define __TU_V_CMDPANE_H

#include "TU/v/CmdWindow.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class CmdPane							*
************************************************************************/
class CmdPane : public Pane, public CmdParent
{
  public:
    CmdPane(Window& parentWindow, const CmdDef cmd[])		;
    virtual ~CmdPane()						;

    virtual const Widget&	widget()		const	;

  private:
    const Widget	_widget;		// boxWidget
};

}
}
#endif	// !__TU_V_CMDPANE_H
