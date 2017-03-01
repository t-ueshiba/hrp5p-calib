/*
 *  $Id: ChoiceFrameCmd_.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __VCHOICEFRAMECMD_H
#define __VCHOICEFRAMECMD_H

#include "FrameCmd_.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class ChoiceFrameCmd							*
************************************************************************/
class ChoiceFrameCmd : public FrameCmd
{
  public:
    ChoiceFrameCmd(Object& parentObject, const CmdDef& cmd)		;
    virtual		 ~ChoiceFrameCmd()				;

    virtual void	callback(CmdId id, CmdVal val)			;
    virtual CmdVal	getValue()				const	;
    virtual void	setValue(CmdVal val)				;
};

}
}
#endif	// !__VCHOICEFRAMECMD_H
