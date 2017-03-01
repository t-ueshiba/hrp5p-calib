/*
 *  $Id: LabelCmd.cc 1219 2012-11-09 05:45:49Z ueshiba $  
 */
#include "LabelCmd_.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class LabelCmd							*
************************************************************************/
LabelCmd::LabelCmd(Object& parentObject, const CmdDef& cmd)
    :Cmd(parentObject, cmd.id),
     _widget(parent().widget(), "TUvLabelCmd", cmd)
{
}

LabelCmd::~LabelCmd()
{
}

const Object::Widget&
LabelCmd::widget() const
{
    return _widget;
}

}
}
