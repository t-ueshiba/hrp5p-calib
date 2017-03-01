/*
 *  $Id: MenuButtonCmd_.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __VMENUBUTTONCMD_H
#define __VMENUBUTTONCMD_H

#include "TU/v/Menu.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class MenuButtonCmd							*
************************************************************************/
class MenuButtonCmd : public Cmd
{
  public:
    MenuButtonCmd(Object& parentObject, const CmdDef& cmd)	;
    virtual ~MenuButtonCmd()					;
    
    virtual const Widget&	widget()		const	;
    
  private:
    const Widget	_widget;			// menuButtonWidget

  protected:
    Menu		_menu;
};

}
}
#endif	// !__VMENUBUTTONCMD_H
