/*
 *  $Id: ModalDialog.cc 2058 2016-11-22 09:52:56Z ueshiba $  
 */
#include "TU/v/ModalDialog.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class ModalDialog							*
************************************************************************/
ModalDialog::ModalDialog(Window& parentWindow, const char* myName,
			 const CmdDef cmd[])
    :Dialog(parentWindow, myName, cmd), _active(false)
{
}

ModalDialog::~ModalDialog()
{
}

void
ModalDialog::show()
{
    Point2<int>	p = parent().widget().position();
    p[0] += 10;
    p[1] += 10;
    XtVaSetValues(widget(), XtNx, p[0], XtNy, p[1], nullptr);
    XtPopup(widget(), XtGrabExclusive);

    XtAppContext	appContext = XtWidgetToApplicationContext(widget());
    _active = true;
    while (_active)
    {
	XEvent  event;
	
	XtAppNextEvent(appContext, &event);
	XtDispatchEvent(&event);
    }

    XtPopdown(widget());
}

void
ModalDialog::hide()
{
    _active = false;
}

}
}
