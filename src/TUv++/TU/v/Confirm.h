/*
 *  $Id: Confirm.h 1589 2014-07-11 04:00:54Z ueshiba $  
 */
#ifndef __TU_V_CONFIRM_H
#define __TU_V_CONFIRM_H

#include <sstream>
#include "TU/v/ModalDialog.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class Confirm							*
************************************************************************/
class Confirm : public ModalDialog, public std::ostringstream
{
  public:
    Confirm(Window& parentWindow)					;
    virtual		~Confirm()					;

    bool		ok()						;
    
    virtual void	callback(CmdId id, CmdVal val)			;

  private:
    bool		_ok;
};

}
}
#endif	// !__TU_V_CONFIRM_H
