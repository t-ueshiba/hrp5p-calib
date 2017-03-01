/*
 *  $Id: ToggleButtonCmd_.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __VTOGGLEBUTTONCMD_H
#define __VTOGGLEBUTTONCMD_H

#include "TU/v/TUv++.h"
#include "TU/v/Bitmap.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class ToggleButtonCmd						*
************************************************************************/
class ToggleButtonCmd : public Cmd
{
  public:
    ToggleButtonCmd(Object& parentObject, const CmdDef& cmd)		;
    virtual ~ToggleButtonCmd()						;
    
    virtual const Widget&	widget()			const	;

    virtual CmdVal		getValue()			const	;
    virtual void		setValue(CmdVal val)			;
    
  private:
    const Widget	_widget;			// toggleWidget
    Bitmap* const	_bitmap;
};

}
}
#endif	// !__VTOGGLEBUTTONCMD_H
