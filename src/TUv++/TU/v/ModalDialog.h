/*
 *  $Id: ModalDialog.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __TU_V_MODALDIALOG_H
#define __TU_V_MODALDIALOG_H

#include "TU/v/Dialog.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class ModalDialog							*
************************************************************************/
class ModalDialog : public Dialog
{
  public:
    ModalDialog(Window& parentWindow, const char* myName, 
		const CmdDef cmd[])				;
    virtual ~ModalDialog()					;

    virtual void	show()					;
    virtual void	hide()					;
    
  private:
    bool		_active;
};

}
}
#endif	// !__TU_V_MODALDIALOG_H
