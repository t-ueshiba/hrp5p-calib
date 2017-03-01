/*
 *  $Id: Widget-Xaw.cc 2060 2016-11-23 01:24:46Z ueshiba $  
 */
#include "TU/v/TUv++.h"
#include <X11/Xaw3d/ThreeD.h>
#include <X11/Xaw3d/Command.h>
#include <X11/Xaw3d/Toggle.h>
#include <X11/Xaw3d/MenuButton.h>
#include "vGridbox_.h"
#include "vTextField_.h"
#include "vViewport_.h"
#include <stdexcept>

namespace TU
{
namespace v
{
/************************************************************************
*  static functions							*
************************************************************************/
static WidgetClass
cmdWidgetClass(CmdType type)
{
    switch (type)
    {
      case C_Button:
	return commandWidgetClass;
	
      case C_ToggleButton:
	return toggleWidgetClass;

      case C_Frame:
      case C_ChoiceFrame:
      case C_RadioButton:
      case C_Slider:
	return gridboxWidgetClass;
	
      case C_Icon:
      case C_Label:
	return labelWidgetClass;
	
      case C_TextIn:
	return textfieldWidgetClass;
	
      case C_MenuButton:
      case C_ChoiceMenuButton:
	return menuButtonWidgetClass;
	
      case C_List:
	return vViewportWidgetClass;

      default:
	break;
    }
    
    throw std::domain_error("cmdWidgetClass: Unkown command type!!");
    
    return 0;
}

/************************************************************************
*  class Object::Widget							*
************************************************************************/
Object::Widget::Widget(::Widget widget)
    :_widget(widget)
{
#ifdef DEBUG
    using namespace	std;
    
    cerr << " Widget() --- widget: " << hex << (void*)_widget << dec
	 << " (" << XtName(_widget) << ')'
	 << endl;
#endif
}

Object::Widget::Widget(const Widget& parentWidget,
		       const char* name, const CmdDef& cmd)
    :_widget(XtVaCreateManagedWidget(name,
				     cmdWidgetClass(cmd.type),
				     parentWidget,
	/* for vViewportWidget */    XtNforceBars,	TRUE,
	/* for vViewportWidget */    XtNallowVert,	TRUE,
				     nullptr))
{
#ifdef DEBUG
    using namespace	std;
    
    cerr << " Widget() --- widget: " << hex << (void*)_widget << dec
	 << " (" << XtName(_widget) << ')'
	 << endl;
#endif

    XtVaSetValues(_widget,
		  XtNborderWidth,	(cmd.attrs & CA_NoBorder ? 0 : 1),

		// Constraint resources for gridbox.
		  XtNfill,		FillWidth,
		//		  XtNgravity,		East,
                  XtNgridx,		cmd.gridx,
		  XtNgridy,		cmd.gridy,
                  XtNgridWidth,		cmd.gridWidth,
		  XtNgridHeight,	cmd.gridHeight,
                  nullptr);

    switch (cmd.type)
    {
      case C_Icon:
	XtVaSetValues(_widget,
		      XtNinternalWidth,		0,
		      XtNinternalHeight,	0,
		      XtNbitmap,		cmd.prop,
		      nullptr);
	break;
	
      case C_Label:
      {
	XtVaSetValues(_widget,
		      XtNborderWidth,	0,
		      XtNrelief,	(cmd.attrs & CA_NoBorder ?
					 XtReliefNone : XtReliefSunken),
		      XtNshadowWidth,	2,
		      XtNlabel, (cmd.prop != 0 ? (char*)cmd.prop : cmd.title),
		      nullptr);
      }
	break;
	
      case C_Button:
	if (cmd.attrs & CA_DefaultButton)
	{
	    XtAccelerators	button = XtParseAcceleratorTable
		("<Key>Return: set() notify() unset()\n");
	    XtVaSetValues(_widget, XtNaccelerators, button, nullptr);
	}
      // Fall through to the next case block.
      case C_ToggleButton:
	XtVaSetValues(_widget,
		      XtNborderWidth,	0,
		      XtNrelief,	(cmd.attrs & CA_NoBorder ?
					 XtReliefNone : XtReliefRaised),
		      XtNlabel,		cmd.title,
		      nullptr);
	break;

      case C_Frame:
      case C_ChoiceFrame:
	XtVaSetValues(_widget,
		      XtNdefaultDistance,   (cmd.attrs & CA_NoSpace  ? 0 : 4),
		      XtNbackground,	    parentWidget.background(),
		      nullptr);
	break;

      case C_RadioButton:
	XtVaSetValues(_widget,	
		      XtNbackground,		parentWidget.background(),
		      XtNborderWidth,		0,
		      XtNdefaultDistance,	0,
		      nullptr);
	break;
	
      case C_Slider:
	XtVaSetValues(_widget,
		      XtNdefaultDistance,	2,
		      nullptr);
	break;
	
      case C_TextIn:
	XtVaSetValues(_widget,
		      XtNborderWidth,	0,
		      XtNrelief,	(cmd.attrs & CA_NoBorder ?
					 XtReliefNone : XtReliefRaised),
		      XtNstring,	cmd.title,
		      XtNinsertPosition,0,
		    //XtNecho,		!(cmd.attrs & CA_Password),
		      nullptr);
	break;

      case C_MenuButton:
      case C_ChoiceMenuButton:
	XtVaSetValues(_widget,
		      XtNborderWidth,	0,
		      XtNrelief,	(cmd.attrs & CA_NoBorder ?
					 XtReliefNone : XtReliefRaised),
		      XtNlabel,		cmd.title,
		      XtNmenuName,	"TUvMenu",
		      nullptr);
	break;

      case C_List:
	XtVaSetValues(_widget,
		      XtNwidth,		60,
		      XtNuseBottom,	TRUE,
		      XtNuseRight,	TRUE,
		      nullptr);
	break;

      default:
	break;
    }

    if (cmd.size > 0)
	XtVaSetValues(_widget, XtNwidth, cmd.size, nullptr);
}

Object::Widget::~Widget()
{
#ifdef DEBUG
    using namespace	std;
    
    cerr << "~Widget() --- widget: " << hex << (void*)_widget << dec
	 << " (" << XtName(_widget) << ')'
	 << endl;
#endif
#ifdef DESTROY_WIDGET
    XtDestroyWidget(_widget);
#endif
}

size_t
Object::Widget::width() const
{
    Dimension	w;
    XtVaGetValues(_widget, XtNwidth, &w, nullptr);
    return w;
}

size_t
Object::Widget::height() const
{
    Dimension	h;
    XtVaGetValues(_widget, XtNheight, &h, nullptr);
    return h;
}

Point2<int>
Object::Widget::position() const
{
    Position	x, y;
    XtVaGetValues(_widget, XtNx, &x, XtNy, &y, nullptr);
    return Point2<int>(x, y);
}

u_long
Object::Widget::background() const
{
    Pixel	bg;
    XtVaGetValues(_widget, XtNbackground, &bg, nullptr);
    return bg;
}

Object::Widget&
Object::Widget::setWidth(size_t w)
{
    XtVaSetValues(_widget, XtNwidth, (Dimension)w, nullptr);
    return *this;
}

Object::Widget&
Object::Widget::setHeight(size_t h)
{
    XtVaSetValues(_widget, XtNheight, (Dimension)h, nullptr);
    return *this;
}

Object::Widget&
Object::Widget::setPosition(const Point2<int>& p)
{
    Position	x = p[0], y = p[1];
    XtVaSetValues(_widget, XtNx, x, XtNy, y, nullptr);
    return *this;
}

}
}
