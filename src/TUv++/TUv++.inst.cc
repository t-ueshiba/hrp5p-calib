/*
 *  $Id: TUv++.inst.cc 1219 2012-11-09 05:45:49Z ueshiba $  
 */
#if defined(__GNUG__) || defined(__INTEL_COMPILER)

#include "TU/v/TUv++.h"

namespace TU
{
template class List<v::Cmd>;
template class List<v::Window>;
template class List<v::Pane>;
}

#endif
