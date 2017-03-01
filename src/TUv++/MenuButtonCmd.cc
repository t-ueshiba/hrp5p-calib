/*
 *  $Id: MenuButtonCmd.cc 1219 2012-11-09 05:45:49Z ueshiba $  
 */
#include "MenuButtonCmd_.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class MenuButtonCmd							*
************************************************************************/
MenuButtonCmd::MenuButtonCmd(Object& parentObject, const CmdDef& cmd)
    :Cmd(parentObject, cmd.id),
     _widget(parent().widget(), "TUvMenuButtonCmd", cmd),
     _menu(*this, (MenuDef*)cmd.prop)
{
    addCmd(&_menu);
}

MenuButtonCmd::~MenuButtonCmd()
{
    detachCmd();
}

const Object::Widget&
MenuButtonCmd::widget() const
{
    return _widget;
}

}
}
