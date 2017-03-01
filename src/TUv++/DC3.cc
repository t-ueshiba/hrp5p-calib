/*
 *  $Id: DC3.cc 1219 2012-11-09 05:45:49Z ueshiba $  
 */
#include "TU/v/DC3.h"

namespace TU
{
namespace v
{
/************************************************************************
*  class DC3								*
************************************************************************/
DC3::~DC3()
{
}

DC3&
DC3::translate(double d)
{
    if (_axis == Z)
	_distance -= d;
    return *this;
}

/************************************************************************
*  Manipulators								*
************************************************************************/
OManip1<DC3, DC3::Axis>
axis(DC3::Axis axis)
{
    return OManip1<DC3, DC3::Axis>(&DC3::setAxis, axis);
}

OManip1<DC3, double>
distance(double dist)
{
    return OManip1<DC3, double>(&DC3::setDistance, dist);
}

OManip1<DC3, double>
translate(double dist)
{
    return OManip1<DC3, double>(&DC3::translate, dist);
}

OManip1<DC3, double>
rotate(double angle)
{
    return OManip1<DC3, double>(&DC3::rotate, angle);
}

}
}
