/*
 *  $Id: vCanvas_.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __VCANVAS_H
#define __VCANVAS_H

/************************************************************************
*  canvas Widget (subclass of Core)					*
************************************************************************/

/* Parameters:

 Name		     Class		RepType		Default Value
 ----		     -----		-------		-------------
 background	     Background		Pixel		XtDefaultBackground
 border		     BorderColor	Pixel		XtDefaultForeground
 borderWidth	     BorderWidth	Dimension	1
 destroyCallback     Callback		Pointer		NULL
 hSpace 	     HSpace		Dimension	4
 height		     Height		Dimension	0
 mappedWhenManaged   MappedWhenManaged	Boolean		True
 vSpace 	     VSpace		Dimension	4
 width		     Width		Dimension	0
 x		     Position		Position	0
 y		     Position		Position	0

*/

#define XtNginitCallback	"ginitCallback"
#define XtCGinitCallback	"GinitCallback"

/* Class record constants */

typedef struct _VCanvasClassRec		*VCanvasWidgetClass;
typedef struct _VCanvasRec		*VCanvasWidget;

extern WidgetClass			vCanvasWidgetClass;

#endif	/* __VCANVAS_H	*/
