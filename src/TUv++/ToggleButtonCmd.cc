/*
 *  $Id: ToggleButtonCmd.cc 2096 2016-11-28 04:49:00Z ueshiba $  
 */
#include "ToggleButtonCmd_.h"
#include <X11/Xaw3d/Toggle.h>

namespace TU
{
namespace v
{
/************************************************************************
*  class ToggleButtonCmd						*
************************************************************************/
ToggleButtonCmd::ToggleButtonCmd(Object& parentObject, const CmdDef& cmd)
    :Cmd(parentObject, cmd.id),
     _widget(parent().widget(), "TUvToggleButtonCmd", cmd),
     _bitmap(cmd.prop == noProp ? 0 :
	     new Bitmap(window().colormap(), (u_char*)cmd.prop))
{
    setValue(cmd.val);
    setDefaultCallback(_widget);
    if (_bitmap != 0)
	XtVaSetValues(_widget, XtNbitmap, _bitmap->xpixmap(), nullptr);
}

ToggleButtonCmd::~ToggleButtonCmd()
{
    removeDefaultCallback(_widget);
    delete _bitmap;
}

const Object::Widget&
ToggleButtonCmd::widget() const
{
    return _widget;
}

CmdVal
ToggleButtonCmd::getValue() const
{
    Boolean	state;
    XtVaGetValues(_widget, XtNstate, &state, nullptr);
    return (state == TRUE ? 1 : 0);
}

void
ToggleButtonCmd::setValue(CmdVal val)
{
    XtVaSetValues(_widget, XtNstate, (val != 0 ? TRUE : FALSE), nullptr);
}

}
}
