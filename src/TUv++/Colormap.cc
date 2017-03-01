/*
 *  $Id: Colormap.cc 2060 2016-11-23 01:24:46Z ueshiba $  
 */
#include "TU/v/Colormap.h"
#include <sstream>

namespace TU
{
namespace v
{
/************************************************************************
*  Static functions							*
************************************************************************/
inline float	slant(int b, int a)	{return (a > 0 && b > 0 ?
						 float(b) / float(a) : 0.0);}
static size_t
underlayResolution(size_t resolutionRequired, const XVisualInfo& vinfo)
{
    switch (vinfo.c_class)
    {
      case GrayScale:
      case PseudoColor:
      case DirectColor:
	return resolutionRequired;
    }
    return vinfo.colormap_size;
}

/************************************************************************
*  class Colormap							*
************************************************************************/
/*
 *  public member functions
 */
Colormap::Colormap(Display* display, const XVisualInfo& vinfo)
    :_display(display),
     _vinfo(vinfo),
     _colormap(_vinfo.visual != DefaultVisual(_display, _vinfo.screen) ?
	       XCreateColormap(_display, RootWindow(_display, _vinfo.screen),
			       _vinfo.visual, AllocNone) :
	       DefaultColormap(_display, _vinfo.screen)),
   // underlay stuffs
     _resolution(0),
     _saturation(256),
     _gain(_saturation / 256.0),
   // overlay stuffs
     _overlayPlanes(0),
   // colorcube stuffs
     _colorcubeNPixels(0),
     _gStride(0),
     _bStride(0),
     _rMul(0),
     _gMul(0),
     _bMul(0),
   // general stuffs
     _pixels(0, 0),
     _mode(RGBColor),
     _map(Graymap)
{
    if (_vinfo.c_class != TrueColor && _vinfo.c_class != DirectColor)
	_vinfo.red_mask = _vinfo.green_mask = _vinfo.blue_mask = ~0x0L;
}

Colormap::Colormap(Display* display, const XVisualInfo& vinfo,
		   Mode mode, size_t resolution,
		   size_t underlayCmapDim, size_t overlayDepth,
		   size_t rDim, size_t gDim, size_t bDim)
    :_display(display),
     _vinfo(vinfo),
     _colormap(XCreateColormap(_display, RootWindow(_display, _vinfo.screen),
			       _vinfo.visual, AllocNone)),
   // underlay stuffs
     _resolution(underlayResolution(resolution, _vinfo)),
     _saturation(256),
     _gain(_saturation / 256.0),
   // overlay stuffs
     _overlayPlanes(0),
   // colorcube stuffs
     _colorcubeNPixels(rDim * gDim * bDim),
     _gStride(rDim),
     _bStride(rDim * gDim),
     _rMul((rDim-1) / 255.0),
     _gMul((gDim-1) / 255.0),
     _bMul((bDim-1) / 255.0),
   // general stuffs
     _pixels((_vinfo.c_class == GrayScale   ||
	      _vinfo.c_class == PseudoColor ||
	      _vinfo.c_class == DirectColor ?  1 << overlayDepth : 1),
	     (_vinfo.c_class == GrayScale   ||
	      _vinfo.c_class == DirectColor ?  _resolution + underlayCmapDim : 
	      _vinfo.c_class == PseudoColor ?
	      std::max(_resolution + underlayCmapDim,
		       (_colorcubeNPixels - 1) / (1 << overlayDepth) + 1) :
	      _resolution)),
     _mode(mode),
     _map(Graymap)
{
    using namespace	std;
    
    if (_vinfo.c_class != TrueColor && _vinfo.c_class != DirectColor)
	_vinfo.red_mask = _vinfo.green_mask = _vinfo.blue_mask = ~0x0L;

  // Set dither mask.
    _dithermask[0][0] = 0.0;
    _dithermask[0][1] = 0.5;
    _dithermask[0][2] = 0.125;
    _dithermask[0][3] = 0.625;
    _dithermask[1][0] = 0.75;
    _dithermask[1][1] = 0.25;
    _dithermask[1][2] = 0.875;
    _dithermask[1][3] = 0.375;
    _dithermask[2][0] = 0.1875;
    _dithermask[2][1] = 0.6875;
    _dithermask[2][2] = 0.0625;
    _dithermask[2][3] = 0.5625;
    _dithermask[3][0] = 0.9375;
    _dithermask[3][1] = 0.4375;
    _dithermask[3][2] = 0.8125;
    _dithermask[3][3] = 0.3125;

  // Allocate color cells from X colormap if needed.
    switch (_vinfo.c_class)
    {
      case GrayScale:
      case PseudoColor:
      case DirectColor:
      {
      // Allocate private color cells and planes.
	u_long	planes[8*sizeof(u_long)];
	if (!XAllocColorCells(_display, _colormap, False, planes, overlayDepth,
			      _pixels[0].data(), _pixels.ncol()))
	{
	    throw runtime_error("TU::v::Colormap::Colormap(): failed to allocate private colors.");
	}

      // Set overlay pixel values by ORing planes obtained.
	for (size_t overlay = 1; overlay < _pixels.nrow(); ++overlay)
	{
	    u_long	mask = 0;
	    for (size_t i = 0; i < overlayDepth; ++i)
		if ((overlay >> i) & 0x01)
		    mask |= planes[i];
	    for (size_t underlay = 0; underlay < _pixels.ncol(); ++underlay)
		_pixels[overlay][underlay] = _pixels[0][underlay] | mask;
	}

      // Set overlay planes.
	for (size_t i = 0; i < overlayDepth; ++i)
	    _overlayPlanes |= planes[i];
      }
      break;
    }

  // Set gray values.
    setGraymapInternal();

  // Setup the underlay lookup table.
    setSaturation(_saturation);

  // Setup the overlay lookup table.
    float	delta = slant(_pixels.nrow() - 1, 255);
    for (size_t i = 0; i < 256; ++i)
	_overlayTable[i] = _pixels[size_t(0.5 + i*delta)][0] & _overlayPlanes;
}

Colormap::~Colormap()
{
    XFreeColors(_display, _colormap, _pixels[0].data(), _pixels.ncol(),
		_overlayPlanes);
    XFreeColormap(_display, _colormap);
}

void
Colormap::setGraymap()
{
    if (_map != Graymap)
    {
	_map = Graymap;
	setSaturation(_saturation);
	if (_vinfo.c_class == PseudoColor)
	    setGraymapInternal();
    }
}

void
Colormap::setSignedmap()
{
    if (_map != Signedmap)
    {
	_map = Signedmap;
	setSaturation(_saturation);
	if (_vinfo.c_class == PseudoColor)
	    setSignedmapInternal();
    }
}

void
Colormap::setColorcube()
{
    if (_map != Colorcube)
    {
	_map = Colorcube;
	setSaturation(_saturation);
	if (_vinfo.c_class == PseudoColor)
	    setColorcubeInternal();
    }
}

void
Colormap::setSaturation(size_t saturation)
{
    using namespace	std;
    
    if (_resolution == 0)
	throw out_of_range("TU::v::Colormap::setSaturation: resolution must be positive!!");
    
    _saturation = min(saturation, size_t(UnderlayTableSize / 2));

    if (_map == Signedmap && _vinfo.c_class == PseudoColor)
    {
	const size_t	range = (_resolution + 1) / 2;
	float		delta = slant(range - 1, _saturation - 1);
	size_t		val = 0;
	for (; val < _saturation; ++val)
	    _underlayTable[val] = _pixels[0][size_t(0.5 + val*delta)];
	for (; val < UnderlayTableSize / 2; ++val)
	    _underlayTable[val] = _pixels[0][range - 1];
	for (; val < UnderlayTableSize - _saturation; ++val)
	    _underlayTable[val] = _pixels[0][range];
	delta = slant(_resolution - 1 - range, _saturation - 1);
	for (; val < UnderlayTableSize; ++val)
	    _underlayTable[val]
		= _pixels[0][_resolution - 1 - 
			     size_t(0.5 + (UnderlayTableSize - 1 - val)*delta)];
    }
    else
    {
	const float	delta = slant(_resolution - 1, _saturation - 1);
	size_t		val = 0;
	for (; val < _saturation; ++val)
	    _underlayTable[val] = _pixels[0][size_t(0.5 + val*delta)];
	for (; val <= UnderlayTableSize - _saturation; ++val)
	    _underlayTable[val] = _pixels[0][_resolution - 1];
	for (; val < UnderlayTableSize; ++val)
	    _underlayTable[val]
		= _pixels[0][size_t(0.5 + (UnderlayTableSize - val)*delta)];
    }
}

/*
 *  underlay stuffs
 */
u_long
Colormap::getUnderlayPixel(size_t index) const
{
    using namespace	std;
    
    if (_mode != IndexedColor)
    {
	throw runtime_error("TU::v::Colormap::getUnderlayPixel: Not in IndexedColor mode!!");
    }
    if (_resolution + index >= _pixels.ncol())
    {
        ostringstream	msg;
	msg << "TU::v::Colormap::getUnderlayPixel: Index (" << index
	    << ") is not within the range [" << 0 << ", "
	    << _pixels.ncol() - _resolution << ")!" << endl;
	throw out_of_range(msg.str());
    }
    return _pixels[0][_resolution + index];
}

BGR
Colormap::getUnderlayValue(size_t index) const
{
    XColor	color;
    color.pixel = getUnderlayPixel(index);
    XQueryColor(_display, _colormap, &color);
    BGR		bgr;
    bgr.r = color.red   >> 8;
    bgr.g = color.green >> 8;
    bgr.b = color.blue  >> 8;
    return bgr;
}

void
Colormap::setUnderlayValue(size_t index, BGR bgr)
{
    using namespace	std;
    
    if (_mode != IndexedColor)
    {
	throw runtime_error("TU::v::Colormap::setUnderlayValue: Not in IndexedColor mode!!");
    }
    if (_resolution + index >= _pixels.ncol())
    {
	ostringstream	msg;
	msg << "TU::v::Colormap::setUnderlayValue: Index (" << index
	    << ") is not within the range [" << 0 << ", "
	    << _pixels.ncol() - _resolution
	    << ")!" << endl;
	throw out_of_range(msg.str());
    }

    XColor	color;
    color.red   = bgr.r << 8;
    color.green = bgr.g << 8;
    color.blue  = bgr.b << 8;
    color.pixel = _pixels[0][_resolution + index];
    color.flags = DoRed | DoGreen | DoBlue;
    XStoreColor(_display, _colormap, &color);
}

Array<u_long>
Colormap::getUnderlayPixels() const
{
    if (_mode == IndexedColor)
    {
	Array<u_long>	pixels(_pixels.ncol() - _resolution);
	for (size_t i = 0; i < pixels.dim(); ++i)
	    pixels[i] = _pixels[0][_resolution + i];	// user-defined pixels.
	return pixels;
    }
    else
    {
	Array<u_long>	pixels(_vinfo.c_class == PseudoColor ?
			       _colorcubeNPixels : _resolution);
	for (size_t i = 0; i < pixels.dim(); ++i)
	    pixels[i] = _pixels[0][i];			// ordinary pixels.
	return pixels;
    }
}

/*
 *  overlay stuffs
 */
u_long
Colormap::getOverlayPixel(size_t index) const
{
    using namespace	std;
    
    if (_mode != IndexedColor)
    {
	throw runtime_error("TU::v::Colormap::getOverlayPixel: Not in IndexedColor mode!!");
    }
    if (index >= _pixels.nrow())
    {
	ostringstream	msg;
	msg << "TU::v::Colormap::getOverlayPixel: Index (" << index
	    << ") is not within the range [" << 0 << ", " << _pixels.nrow()
	    << ")!" << endl;
	throw out_of_range(msg.str());
    }
    return _pixels[index][0];
}

BGR
Colormap::getOverlayValue(size_t index) const
{
    XColor	color;
    color.pixel = getOverlayPixel(index);
    XQueryColor(_display, _colormap, &color);
    BGR	bgr;
    bgr.r = color.red   >> 8;
    bgr.g = color.green >> 8;
    bgr.b = color.blue  >> 8;
    return bgr;
}

void
Colormap::setOverlayValue(size_t index, BGR bgr)
{
    using namespace	std;
    
    if (_mode != IndexedColor)
    {
	throw runtime_error("TU::v::Colormap::setOverlayValue: Not in IndexedColor mode!!");
    }
    if (index < 1 || index >= _pixels.nrow())
    {
	ostringstream	msg;
	msg << "TU::v::Colormap::setOverlayValue: Index (" << index
	    << ") is not within the range [" << 1 << ", " << _pixels.nrow()
	    << ")!" << endl;
	throw out_of_range(msg.str());
    }

    XColor	color;
    color.red	= bgr.r << 8;
    color.green	= bgr.g << 8;
    color.blue	= bgr.b << 8;
    color.flags = DoRed | DoGreen | DoBlue;
    for (size_t i = 0; i < _pixels.ncol(); ++i)
    {
	color.pixel = _pixels[index][i];
	XStoreColor(_display, _colormap, &color);
    }
}

Array<u_long>
Colormap::getOverlayPixels() const
{
    Array<u_long>	pixels(_pixels.nrow());
    for (size_t i = 0; i < pixels.dim(); ++i)
	pixels[i] = _pixels[i][0];	// transparent and user-defined pixels.
    return pixels;
}

/*
 *  Private member functions
 */
void
Colormap::setGraymapInternal()
{
    using namespace	std;

  // Set underlay gray map.
    float	delta = slant(USHRT_MAX, _resolution - 1);
    switch (_vinfo.c_class)
    {
      case GrayScale:
      case PseudoColor:
      case DirectColor:
	for (size_t i = 0; i < _resolution; ++i)
	{
	    XColor	color;
	    color.red = color.green = color.blue = u_short(0.5 + i*delta);
	    color.flags = DoRed | DoGreen | DoBlue;
	    color.pixel = _pixels[0][i];
	    XStoreColor(_display, _colormap, &color);
	}
	break;
	
      default:
	for (size_t i = 0; i < _resolution; ++i)
	{
	    XColor	color;
	    color.red = color.green = color.blue = u_short(0.5 + i*delta);
	    color.flags = DoRed | DoGreen | DoBlue;
	    if (!XAllocColor(_display, _colormap, &color))
	    {
		throw runtime_error("TU::v::Colormap::setGraymapInternal: Failed to allocate shared color!!");
	    }
	    _pixels[0][i] = color.pixel;
	}
	break;
    }

  // Set overlay gray map.    
    delta = slant(USHRT_MAX, _pixels.nrow() - 1);
    for (size_t i = 1; i < _pixels.nrow(); ++i)	// Keep transparency pixel:i=0.
    {
	XColor	color;
	color.red = color.green = color.blue = u_short(0.5 + i*delta);
	color.flags = DoRed | DoGreen | DoBlue;
	for (size_t j = 0; j < _pixels.ncol(); ++j)
	{
	    color.pixel = _pixels[i][j];
	    XStoreColor(_display, _colormap, &color);
	}
    }
}

void
Colormap::setSignedmapInternal()
{
    if (_vinfo.c_class == PseudoColor)
    {
	const size_t	range  = (_resolution + 1) / 2;
	const float	delta  = slant(USHRT_MAX, range - 1),
			delta2 = slant(USHRT_MAX, _resolution - 1 - range);
	for (size_t i = 0; i < _resolution; ++i)
	{
	    XColor	color;
	    color.red = color.green = color.blue = 0;
	    if (i < range)
		color.green = u_short(0.5 + i*delta);
	    else
		color.red = u_short(0.5 + (_resolution - 1 - i)*delta2);
	    color.flags = DoRed | DoGreen | DoBlue;
	    color.pixel = _pixels[0][i];
	    XStoreColor(_display, _colormap, &color);
	}
    }
    else
	setGraymapInternal();
}

void
Colormap::setColorcubeInternal()
{
    const float	rStep = (rDim() > 1 ? float(USHRT_MAX) / (rDim()-1) : 0.0),
		gStep = (gDim() > 1 ? float(USHRT_MAX) / (gDim()-1) : 0.0),
		bStep = (bDim() > 1 ? float(USHRT_MAX) / (bDim()-1) : 0.0);
    for (size_t b = 0; b < bDim(); ++b)
    {
	XColor	color;
	color.flags = DoRed | DoGreen | DoBlue;
	
	color.blue = u_short(0.5 + b * bStep);
	for (size_t g = 0; g < gDim(); ++g)
	{
	    color.green = u_short(0.5 + g * gStep);
	    for (size_t r = 0; r < rDim(); ++r)
	    {
		color.red = u_short(0.5 + r * rStep);
		color.pixel = _pixels[0][r + g*_gStride + b*_bStride];
		XStoreColor(_display, _colormap, &color);
	    }
	}
    }
}

}
}
