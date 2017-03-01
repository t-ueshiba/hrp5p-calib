/*
 *  $Id: FrameCmd_.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __VFRAMECMD_H
#define __VFRAMECMD_H

#include "TU/v/TUv++.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class FrameCmd							*
************************************************************************/
class FrameCmd : public Cmd
{
  public:
    FrameCmd(Object& parentObject, const CmdDef& cmd)	;
    virtual ~FrameCmd()					;
    
    virtual const Widget&	widget()	const	;

  private:
    const Widget		_widget;		// frameWidget
};

}
}
#endif	// !__VFRAMECMD_H
