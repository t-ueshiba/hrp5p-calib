/*
 *  $Id: Timer.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __TU_V_TIMER_H
#define __TU_V_TIMER_H

#include "TU/v/TUv++.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class Timer								*
************************************************************************/
class Timer
{
  public:
    Timer(Object& vObject, u_long interval=0)				;
    ~Timer()								;
    
    void		start(u_long interval)				;
    void		stop()						;

  private:
    void		start()						;
    void		tick()						;

    friend void		CBtimer(XtPointer vTimer, XtIntervalId*)	;

    Object&		_vObject;
    u_long		_interval;
    XtIntervalId	_id;
};

}
}
#endif	// !__TU_V_TIMER_H
