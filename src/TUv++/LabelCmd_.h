/*
 *  $Id: LabelCmd_.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __VLABELCMD_H
#define __VLABELCMD_H

#include "TU/v/TUv++.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class LabelCmd							*
************************************************************************/
class LabelCmd : public Cmd
{
  public:
    LabelCmd(Object& parentObject, const CmdDef& cmd)		;
    virtual ~LabelCmd()						;

    virtual const Widget&	widget()		const	;
    
  private:
    const Widget	_widget;	// labelWidget
};

}
}
#endif	// !__VLABELCMD_H
