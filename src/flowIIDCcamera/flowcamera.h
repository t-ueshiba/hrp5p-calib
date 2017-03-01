/*
 *  $Id: flowcamera.h 1246 2012-11-30 06:23:09Z ueshiba $
 */
#include <sys/time.h>
#include <iostream>
#include "TU/v/TUv++.h"

namespace TU
{
/************************************************************************
*  global variables and definitions					*
************************************************************************/
extern bool	active;
    
namespace v
{
enum
{
  // Camera control.
    c_ContinuousShot,
};

/************************************************************************
*  global functions							*
************************************************************************/
template <class CAMERA> inline const CmdDef*
createMenuCmds(const CAMERA& camera)
{
    static MenuDef fileMenu[] =
    {
	{"Restore camera config. from memory",	M_Open,		false, noSub},
	{"Save camera config. to memory",	M_Save,		false, noSub},
	{"Save camera config. to file",		M_SaveAs,	false, noSub},
	{"-",					M_Line,		false, noSub},
	{"Quit",				M_Exit,		false, noSub},
	EndOfMenu
    };

    static CmdDef menuCmds[] =
    {
	{C_MenuButton,   M_File,	   0, "File",		 fileMenu,
	 CA_None, 0, 0, 1, 1, 0},
	{C_MenuButton,   M_Format,	   0, "Format",		 noProp,
	 CA_None, 1, 0, 1, 1, 0},
	{C_ToggleButton, c_ContinuousShot, 0, "Continuous shot", noProp,
	 CA_None, 2, 0, 1, 1, 0},
	EndOfCmds
    };

    menuCmds[1].prop = createFormatMenu(camera);
    
    return menuCmds;
}

}	// namespace v
 
/************************************************************************
*  global functions							*
************************************************************************/
template <class CAMERA> inline void
saveCameraConfig(const CAMERA& camera)
{
}
    
template <class CAMERA> inline void
restoreCameraConfig(CAMERA& camera)
{
}
    
#ifdef __TU_IIDCPP_H
inline void
saveCameraConfig(IIDCCamera& camera)
{
    camera.saveConfig(1);
}
	
inline void
restoreCameraConfig(IIDCCamera& camera)
{
    camera.restoreConfig(1);
}
#endif
    
inline void
countTime()
{
    static int		nframes = 0;
    static timeval	start;
    
    if (nframes == 10)
    {
	timeval	end;
	gettimeofday(&end, NULL);
	double	interval = (end.tv_sec  - start.tv_sec) +
	    (end.tv_usec - start.tv_usec) / 1.0e6;
	std::cerr << nframes / interval << " frames/sec" << std::endl;
	nframes = 0;
    }
    if (nframes++ == 0)
	gettimeofday(&start, NULL);
}

template <class CAMERA> void
run(Array<CAMERA>& cameras)
{
    CaptureAndSave<CAMERA>	captureAndSave(cameras);
    captureAndSave.saveHeaders(std::cout);		// 画像数とヘッダを出力
    for (auto& camera : cameras)
	camera.continuousShot(true);			// カメラ出力開始

    while (active)
    {
	countTime();

	if (!captureAndSave(std::cout))
	    active = false;
    }

    for (auto& camera : cameras)
	camera.continuousShot(false);			// カメラ出力停止
}

}	// namespace TU
