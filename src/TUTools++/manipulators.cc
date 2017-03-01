/*
 *  $Id: manipulators.cc 1202 2012-09-25 00:03:13Z ueshiba $
 */
#include <iostream>
#include "TU/Manip.h"

namespace TU
{
/************************************************************************
*  Manipulators for std::istream					*
************************************************************************/
//! 行の終わりまで読み飛ばす．
/*!
  NLが読み込まれるまでストリームからの入力を続ける．NLはストリームに残されない．
  \param in	入力ストリーム
  \return	inで指定した入力ストリーム
*/
__PORT std::istream&
skipl(std::istream& in)	// manipulator for skipping the rest of a line
{
    for (char c; in.get(c); )
	if (c == '\n')
	    break;
    return in;
}
 
}
