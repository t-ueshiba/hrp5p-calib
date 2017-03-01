/*
 *  $Id: RadioButtonCmd_.h 2060 2016-11-23 01:24:46Z ueshiba $  
 */
#ifndef __VRADIOBUTTONCMD_H
#define __VRADIOBUTTONCMD_H

#include "TU/v/TUv++.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class RadioButtonCmd							*
************************************************************************/
class RadioButtonCmd : public Cmd
{
  public:
    RadioButtonCmd(Object& parentObject, const CmdDef& cmd)	;
    virtual ~RadioButtonCmd()					;
    
    virtual const Widget&	widget()		const	;

    virtual CmdVal		getValue()		const	;
    virtual void		setValue(CmdVal val)		;
    
  private:
    const Widget	_widget;			// gridboxWidget
    const Widget	_button;			// commandWidget
    const Widget	_label;				// labelWidget

    static size_t	_nitems;
};

}
}
#endif	// !__VRADIOBUTTONCMD_H
