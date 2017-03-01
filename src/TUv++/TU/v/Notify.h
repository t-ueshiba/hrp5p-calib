/*
 *  $Id: Notify.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __TU_V_NOTIFY_H
#define __TU_V_NOTIFY_H

#include <sstream>
#include "TU/v/ModalDialog.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class Notify								*
************************************************************************/
class Notify : public ModalDialog, public std::ostringstream
{
  public:
    Notify(Window& parentWindow)					;
    virtual		~Notify()					;

    virtual void	show()						;
    
    virtual void	callback(CmdId id, CmdVal val)			;
};

}
}
#endif // !__TU_V_NOTIFY_H
