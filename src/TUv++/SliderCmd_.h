/*
 *  $Id: SliderCmd_.h 2060 2016-11-23 01:24:46Z ueshiba $  
 */
#ifndef __VSLIDERCMD_H
#define __VSLIDERCMD_H

#include "TU/v/TUv++.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class SliderCmd							*
************************************************************************/
class SliderCmd : public Cmd
{
  public:
    SliderCmd(Object& parentObject, const CmdDef& cmd)		;
    virtual ~SliderCmd()					;

    virtual const Widget&	widget()		const	;

    virtual CmdVal		getValue()		const	;
    virtual void		setValue(CmdVal val)		;
    virtual void		setProp(const void* prop)	;
    void			setPercent(float percent)	;
    
  private:
    void			setValueInternal(float val)	;

    const Widget	_widget;			// gridboxWidget
    const Widget	_title;				// labelWidget
    const Widget	_slider;			// slider3dWidget
    const Widget	_text;				// labelWidget
    float		_min;
    float		_max;
    float		_step;
    CmdVal		_val;
};

}
}
#endif	// !__VSLIDERCMD_H
