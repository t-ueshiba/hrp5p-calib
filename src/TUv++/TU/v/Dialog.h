/*
 *  $Id: Dialog.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __TU_V_DIALOG_H
#define __TU_V_DIALOG_H

#include "TU/v/CmdPane.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class Dialog								*
************************************************************************/
class Dialog : public Window
{
  public:
    Dialog(Window& parentWindow, const char* myName,
	   const CmdDef cmd[])					;
    virtual ~Dialog()						;

    virtual const Widget&	widget()		const	;

  protected:
    CmdPane&			pane()				{return _pane;}
    
  private:
    const Widget	_widget;		// transientShellWidget
    CmdPane		_pane;
};

}
}
#endif	// !__TU_V_DIALOG_H
