/*
 *  $Id: ChoiceMenuButtonCmd_.h 1219 2012-11-09 05:45:49Z ueshiba $  
 */
#ifndef __TUvChoiceMenuButtonCmd_h
#define __TUvChoiceMenuButtonCmd_h

#include "TU/v/Menu.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class ChoiceMenuButtonCmd						*
************************************************************************/
class ChoiceMenuButtonCmd : public Cmd
{
  public:
    ChoiceMenuButtonCmd(Object& parentObject, const CmdDef& cmd)	;
    virtual ~ChoiceMenuButtonCmd()					;
    
    virtual const Widget&	widget()			const	;
    
    virtual void	callback(CmdId id, CmdVal val)			;
    virtual CmdVal	getValue()				const	;
    virtual void	setValue(CmdVal val)				;

  private:
    const Widget	_widget;			// menuButtonWidget
    ChoiceMenu		_menu;
};

}
}
#endif	// !__TUvChoiceMenuButtonCmd_h
