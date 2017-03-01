/*
 *  $Id: App.h 1705 2014-11-05 01:01:14Z ueshiba $  
 */
#ifndef __TU_VAPP_H
#define __TU_VAPP_H

#include "TU/v/TUv++.h"
#include "TU/v/Colormap.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class App								*
************************************************************************/
class App : public Window
{
  public:
    App(int& argc, char* argv[])					;
    virtual ~App()							;

    virtual const Widget&	widget()			const	;
    virtual Colormap&		colormap()				;
    virtual void		callback(CmdId id, CmdVal val)		;

	    void	step()						;
	    void	run()						;
    virtual void	exit()						;

	    void	addColormapWindow(const Window& vWindow)const;
    
  protected:
    virtual App&	app()						;

  private:
    XtAppContext	_appContext;
    const Widget	_widget;		// applicationShellWidget
    Colormap		_colormap;
    bool		_active;
};

}
}
#endif	// !__TU_VAPP_H
