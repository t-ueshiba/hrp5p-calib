/*
 *  $Id: ChoiceMenuButtonCmd.cc 1219 2012-11-09 05:45:49Z ueshiba $  
 */
#include "ChoiceMenuButtonCmd_.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class ChoiceMenuButtonCmd						*
************************************************************************/
ChoiceMenuButtonCmd::ChoiceMenuButtonCmd(Object& parentObject,
					 const CmdDef& cmd)
    :Cmd(parentObject, cmd.id),
     _widget(parent().widget(), "TUvChoiceMenuButtonCmd", cmd),
     _menu(*this, (MenuDef*)cmd.prop)
{
    addCmd(&_menu);
    setValue(getValue());
}

ChoiceMenuButtonCmd::~ChoiceMenuButtonCmd()
{
    detachCmd();
}

const Object::Widget&
ChoiceMenuButtonCmd::widget() const
{
    return _widget;
}

void
ChoiceMenuButtonCmd::callback(CmdId nid, CmdVal nval)
{
    if (nid == _menu.id())
    {
	setValue(nval);
	parent().callback(id(), getValue());
    }
    else
	parent().callback(nid, nval);
}

CmdVal
ChoiceMenuButtonCmd::getValue() const
{
    return _menu.getValue();
}

void
ChoiceMenuButtonCmd::setValue(CmdVal val)
{
    _menu.setValue(val);
}

}
}
