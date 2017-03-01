/*
 *  $Id: ButtonCmd_.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __VBUTTONCMD_H
#define __VBUTTONCMD_H

#include "TU/v/TUv++.h"
#include "TU/v/Bitmap.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class ButtonCmd							*
************************************************************************/
class ButtonCmd : public Cmd
{
  public:
    ButtonCmd(Object& parentObject, const CmdDef& cmd)		;
    virtual ~ButtonCmd()					;
    
    virtual const Widget&	widget()		const	;

    
  private:
    const Widget	_widget;			// commandWidget
    Bitmap* const	_bitmap;
};

}
}
#endif	// !__VBUTTONCMD_H
