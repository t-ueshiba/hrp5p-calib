/*
 *  $Id: ListCmd_.h 2060 2016-11-23 01:24:46Z ueshiba $  
 */
#ifndef __VLISTCMD_H
#define __VLISTCMD_H

#include "TU/v/TUv++.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class ListCmd							*
************************************************************************/
class ListCmd : public Cmd
{
  public:
    ListCmd(Object& parentObject, const CmdDef& cmd)		;
    virtual ~ListCmd()						;

    virtual const Widget&	widget()		const	;

    virtual CmdVal		getValue()		const	;
    virtual void		setValue(CmdVal val)		;
    virtual void		setProp(const void* prop)	;
    void			setPercent(float percent)	;
    void			scroll(int n)			;
    
  private:
    const Widget	_widget;			// viewportWidget
    const Widget	_list;				// listWidget
    int			_top;
    size_t		_nitems;
    const size_t	_nitemsShown;
};

}
}
#endif	// !__VLISTCMD_H
