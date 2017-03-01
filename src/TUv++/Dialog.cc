/*
 *  $Id: Dialog.cc 2058 2016-11-22 09:52:56Z ueshiba $  
 */
#include "TU/v/Dialog.h"
#include "TU/v/Colormap.h"
#include <X11/Shell.h>

namespace TU
{
namespace v
{
/************************************************************************
*  class Dialog								*
************************************************************************/
Dialog::Dialog(Window& parentWindow, const char* myName, const CmdDef cmd[])
    :Window(parentWindow),
     _widget(XtVaCreatePopupShell("TUvDialog",
				//overrideShellWidgetClass,
				  transientShellWidgetClass,
				  parent().widget(),
				  XtNtitle,		myName,
				  XtNallowShellResize,	TRUE,
				  XtNvisual,	colormap().vinfo().visual,
				  XtNdepth,	colormap().vinfo().depth,
				  XtNcolormap,	(::Colormap)colormap(),
				  nullptr)),
     _pane(*this, cmd)
{
}

Dialog::~Dialog()
{
}

const Object::Widget&
Dialog::widget() const
{
    return _widget;
}

}
}
