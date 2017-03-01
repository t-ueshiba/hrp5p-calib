/*
 *  $Id: vCanvasP_.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __VCANVASP_H
#define __VCANVASP_H

#include "vCanvas_.h"

/************************************************************************
*  Private definitions for vCanvas widget				*
************************************************************************/
/* New fields for the vCanvas widget class record */
typedef struct _VCanvasClass
{
    int			empty;		/* need something */
} VCanvasClassPart;

/* Full class record declaration */
typedef struct _VCanvasClassRec
{
    CoreClassPart	core_class;
    VCanvasClassPart	vcanvas_class;
} VCanvasClassRec;

extern VCanvasClassRec vCanvasClassRec;

/* New fields for the vCanvas widget record */
typedef struct
{
    int			backing_store;	 /* Whether we allow backing store */
    XtCallbackList	ginit_callbacks; /* called once when realized	   */
} VCanvasPart;

/************************************************************************
*  Full instance record declaration					*
************************************************************************/
typedef struct _VCanvasRec
{
    CorePart		core;
    VCanvasPart		vcanvas;
} VCanvasRec;

#endif	/* !__VCANVASP_H	*/
