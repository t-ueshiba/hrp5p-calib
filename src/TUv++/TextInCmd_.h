/*
 *  $Id: TextInCmd_.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __VTEXTINCMD_H
#define __VTEXTINCMD_H

#include "TU/v/TUv++.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class TextInCmd							*
************************************************************************/
class TextInCmd : public Cmd
{
  public:
    TextInCmd(Object& parentObject, const CmdDef& cmd)		;
    virtual ~TextInCmd()					;

    virtual const Widget&	widget()		const	;
  
    virtual const char*	getString()			const	;
    virtual void	setString(const char* str)		;
    
  private:
    const Widget	_widget;			// asciiTextWidget
};

}
}
#endif	// !__VTEXTINCMD_H
