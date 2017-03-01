/*
 *  $Id: Rectify.h 1495 2014-02-27 15:07:51Z ueshiba $
 */
#ifndef __TU_RECTIFY_H
#define __TU_RECTIFY_H

#include "TU/Warp.h"

namespace TU
{
/************************************************************************
*  class Rectify							*
************************************************************************/
class Rectify
{
  public:
    typedef double					element_type;
    typedef Camera<IntrinsicWithDistortion<
		       IntrinsicBase<element_type> > >	camera_type;
    typedef Homography<element_type>			homography_type;
    
  public:
    Rectify()								{}

    Rectify(const camera_type& cameraL,
	    const camera_type& cameraR,
	    size_t widthL, size_t heightL,
	    size_t widthR, size_t heightR,
	    element_type scale=1.0,
	    int disparitySearchWidth=0, int disparityMax=0)
    {
	initialize(cameraL, cameraR, widthL, heightL, widthR, heightR,
		   scale, disparitySearchWidth, disparityMax);
    }
    
    Rectify(const ImageBase& imageL,
	    const ImageBase& imageR,
	    element_type scale=1.0,
	    int disparitySearchWidth=0, int disparityMax=0)
    {
	initialize(imageL, imageR,
		   scale, disparitySearchWidth, disparityMax);
    }

    Rectify(const camera_type& cameraL,
	    const camera_type& cameraR,
	    const camera_type& cameraV,
	    size_t widthL, size_t heightL,
	    size_t widthR, size_t heightR,
	    size_t widthV, size_t heightV,
	    element_type scale=1.0,
	    int disparitySearchWidth=0, int disparityMax=0)
    {
	initialize(cameraL, cameraR, cameraV,
		   widthL, heightL, widthR, heightR, widthV, heightV,
		   scale, disparitySearchWidth, disparityMax);
    }

    Rectify(const ImageBase& imageL,
	    const ImageBase& imageR,
	    const ImageBase& imageV,
	    element_type scale=1.0,
	    int disparitySearchWidth=0, int disparityMax=0)
    {
	initialize(imageL, imageR, imageV,
		   scale, disparitySearchWidth, disparityMax);
    }

    element_type	initialize(const camera_type& cameraL,
				   const camera_type& cameraR,
				   size_t widthL, size_t heightL,
				   size_t widthR, size_t heightR,
				   element_type scale=1.0,
				   size_t disparitySearchWidth=0,
				   size_t disparityMax=0)		;
    element_type	initialize(const camera_type& cameraL,
				   const camera_type& cameraR,
				   size_t widthL, size_t heightL,
				   size_t widthR, size_t heightR,
				   element_type scale,
				   element_type detphMin,
				   element_type depthMax,
				   size_t& disparitySearchWidth,
				   size_t& disparityMax)		;
    element_type	initialize(const ImageBase& imageL,
				   const ImageBase& imageR,
				   element_type scale=1.0,
				   size_t disparitySearchWidth=0,
				   size_t disparityMax=0)		;
    element_type	initialize(const ImageBase& imageL,
				   const ImageBase& imageR,
				   element_type scale,
				   element_type detphMin,
				   element_type depthMax,
				   size_t& disparitySearchWidth,
				   size_t& disparityMax)		;
    element_type	initialize(const camera_type& cameraL,
				   const camera_type& cameraR,
				   const camera_type& cameraV,
				   size_t widthL, size_t heightL,
				   size_t widthR, size_t heightR,
				   size_t widthV, size_t heightV,
				   element_type scale=1.0,
				   size_t disparitySearchWidth=0,
				   size_t disparityMax=0)		;
    element_type	initialize(const camera_type& cameraL,
				   const camera_type& cameraR,
				   const camera_type& cameraV,
				   size_t widthL, size_t heightL,
				   size_t widthR, size_t heightR,
				   size_t widthV, size_t heightV,
				   element_type scale,
				   element_type detphMin,
				   element_type depthMax,
				   size_t& disparitySearchWidth,
				   size_t& disparityMax)		;
    element_type	initialize(const ImageBase& imageL,
				   const ImageBase& imageR,
				   const ImageBase& imageV,
				   element_type scale=1.0,
				   size_t disparitySearchWidth=0,
				   size_t disparityMax=0)		;
    element_type	initialize(const ImageBase& imageL,
				   const ImageBase& imageR,
				   const ImageBase& imageV,
				   element_type scale,
				   element_type detphMin,
				   element_type depthMax,
				   size_t& disparitySearchWidth,
				   size_t& disparityMax)		;

    template <class T>
    void	operator ()(const Image<T>& inL,
			    const Image<T>& inR,
			    Image<T>& outL,
			    Image<T>& outR)			const	;
    template <class T>
    void	operator ()(const Image<T>& inL,
			    const Image<T>& inR,
			    const Image<T>& inV,
			    Image<T>& outL,
			    Image<T>& outR,
			    Image<T>& outV)			const	;
    
    const homography_type&
		H(int i)		const	{return _H[i];}
    const Warp&	warp(int i)		const	{return _warp[i];}
    size_t	width(int i)		const	{return _warp[i].width();}
    size_t	height(int i)		const	{return _warp[i].height();}
    int		lmost(int i, int v)	const	{return _warp[i].lmost(v);}
    int		rmost(int i, int v)	const	{return _warp[i].rmost(v);}
    
  private:
    void	computeBaseHomographies(const camera_type& cameraL,
					const camera_type& cameraR,
					size_t widthL, size_t heightL,
					size_t widthR, size_t heightR)	;
    void	computeBaseHomographies(const camera_type& cameraL,
					const camera_type& cameraR,
					const camera_type& cameraV)	;
    void	scaleHomographies(size_t widthL, size_t heightL,
				  element_type scale)			;
    element_type
		translateHomographies(const camera_type& cameraL,
				      const camera_type& cameraR,
				      size_t widthL, size_t heightL,
				      size_t widthR, size_t heightR,
				      size_t disparitySearchWidth,
				      size_t disparityMax)		;
    element_type
		translateHomographies(const camera_type& cameraL,
				      const camera_type& cameraR,
				      const camera_type& cameraV,
				      size_t widthL, size_t heightL,
				      size_t widthR, size_t heightR,
				      size_t widthV, size_t heightV,
				      size_t disparitySearchWidth,
				      size_t disparityMax)		;
    element_type
		baselineLength(const camera_type& cameraL,
			       const camera_type& cameraR)	const	;

  private:
    homography_type	_H[3];
    Warp		_warp[3];
};

inline Rectify::element_type
Rectify::initialize(const camera_type& cameraL,
		    const camera_type& cameraR,
		    size_t widthL, size_t heightL,
		    size_t widthR, size_t heightR,
		    element_type scale,
		    size_t disparitySearchWidth, size_t disparityMax)
{
    computeBaseHomographies(cameraL, cameraR,
			    widthL, heightL, widthR, heightR);
    scaleHomographies(widthL, heightL, scale);

    return translateHomographies(cameraL, cameraR,
				 widthL, heightL, widthR, heightR,
				 disparitySearchWidth, disparityMax);
}

inline Rectify::element_type
Rectify::initialize(const camera_type& cameraL,
		    const camera_type& cameraR,
		    size_t widthL, size_t heightL,
		    size_t widthR, size_t heightR,
		    element_type scale,
		    element_type depthMin, element_type depthMax,
		    size_t& disparitySearchWidth, size_t& disparityMax)
{
    computeBaseHomographies(cameraL, cameraR,
			    widthL, heightL, widthR, heightR);
    scaleHomographies(widthL, heightL, scale);

    element_type	b = baselineLength(cameraL, cameraR);
    disparityMax = int(b/depthMin + 0.5);
    if (depthMax >= depthMin)
	disparitySearchWidth = int(b/depthMin - b/depthMax + 0.5);
    else
	disparitySearchWidth = disparityMax;
    
    return translateHomographies(cameraL, cameraR,
				 widthL, heightL, widthR, heightR,
				 disparitySearchWidth, disparityMax);
}

inline Rectify::element_type
Rectify::initialize(const ImageBase& imageL,
		    const ImageBase& imageR,
		    element_type scale,
		    size_t disparitySearchWidth, size_t disparityMax)
{
    camera_type	cameraL(imageL.P), cameraR(imageR.P);
    cameraL.setDistortion(imageL.d1, imageL.d2);
    cameraR.setDistortion(imageR.d1, imageR.d2);

    return initialize(cameraL, cameraR,
		      imageL.width(), imageL.height(),
		      imageR.width(), imageR.height(),
		      scale, disparitySearchWidth, disparityMax);
}

inline Rectify::element_type
Rectify::initialize(const ImageBase& imageL,
		    const ImageBase& imageR,
		    element_type scale,
		    element_type depthMin, element_type depthMax,
		    size_t& disparitySearchWidth, size_t& disparityMax)
{
    camera_type	cameraL(imageL.P), cameraR(imageR.P);
    cameraL.setDistortion(imageL.d1, imageL.d2);
    cameraR.setDistortion(imageR.d1, imageR.d2);

    return initialize(cameraL, cameraR,
		      imageL.width(), imageL.height(),
		      imageR.width(), imageR.height(),
		      scale, depthMin, depthMax,
		      disparitySearchWidth, disparityMax);
}

inline Rectify::element_type
Rectify::initialize(const camera_type& cameraL,
		    const camera_type& cameraR,
		    const camera_type& cameraV,
		    size_t widthL, size_t heightL,
		    size_t widthR, size_t heightR,
		    size_t widthV, size_t heightV,
		    element_type scale,
		    size_t disparitySearchWidth, size_t disparityMax)
{
    computeBaseHomographies(cameraL, cameraR, cameraV);
    scaleHomographies(widthL, heightL, scale);
	
    return translateHomographies(cameraL, cameraR, cameraV,
				 widthL, heightL,
				 widthR, heightR,
				 widthV, heightV,
				 disparitySearchWidth, disparityMax);
}

inline Rectify::element_type
Rectify::initialize(const camera_type& cameraL,
		    const camera_type& cameraR,
		    const camera_type& cameraV,
		    size_t widthL, size_t heightL,
		    size_t widthR, size_t heightR,
		    size_t widthV, size_t heightV,
		    element_type scale,
		    element_type depthMin, element_type depthMax,
		    size_t& disparitySearchWidth, size_t& disparityMax)
{
    computeBaseHomographies(cameraL, cameraR, cameraV);
    scaleHomographies(widthL, heightL, scale);
	
    element_type	b = baselineLength(cameraL, cameraR);
    disparityMax = int(b/depthMin + 0.5);
    if (depthMax >= depthMin)
	disparitySearchWidth = int(b/depthMin - b/depthMax + 0.5);
    else
	disparitySearchWidth = disparityMax;
    
    return translateHomographies(cameraL, cameraR, cameraV,
				 widthL, heightL,
				 widthR, heightR,
				 widthV, heightV,
				 disparitySearchWidth, disparityMax);
}

inline Rectify::element_type
Rectify::initialize(const ImageBase& imageL,
		    const ImageBase& imageR,
		    const ImageBase& imageV,
		    element_type scale,
		    size_t disparitySearchWidth, size_t disparityMax)
{
    camera_type	cameraL(imageL.P), cameraR(imageR.P), cameraV(imageV.P);
    cameraL.setDistortion(imageL.d1, imageL.d2);
    cameraR.setDistortion(imageR.d1, imageR.d2);
    cameraV.setDistortion(imageV.d1, imageV.d2);

    return initialize(cameraL, cameraR, cameraV,
		      imageL.width(), imageL.height(),
		      imageR.width(), imageR.height(),
		      imageV.width(), imageV.height(),
		      scale, disparitySearchWidth, disparityMax);
}
    
inline Rectify::element_type
Rectify::initialize(const ImageBase& imageL,
		    const ImageBase& imageR,
		    const ImageBase& imageV,
		    element_type scale,
		    element_type depthMin, element_type depthMax,
		    size_t& disparitySearchWidth, size_t& disparityMax)
{
    camera_type	cameraL(imageL.P), cameraR(imageR.P), cameraV(imageV.P);
    cameraL.setDistortion(imageL.d1, imageL.d2);
    cameraR.setDistortion(imageR.d1, imageR.d2);
    cameraV.setDistortion(imageV.d1, imageV.d2);

    return initialize(cameraL, cameraR, cameraV,
		      imageL.width(), imageL.height(),
		      imageR.width(), imageR.height(),
		      imageV.width(), imageV.height(),
		      scale, depthMin, depthMax,
		      disparitySearchWidth, disparityMax);
}
    
template <class T> inline void
Rectify::operator ()(const Image<T>& inL, const Image<T>& inR,
		     Image<T>& outL, Image<T>& outR) const
{
    outL.resize(_warp[0].height(), _warp[0].width());
    outR.resize(_warp[1].height(), _warp[1].width());
    
    _warp[0](inL.cbegin(), outL.begin());
    _warp[1](inR.cbegin(), outR.begin());
}

template <class T> inline void
Rectify::operator ()(const Image<T>& inL,
		     const Image<T>& inR,
		     const Image<T>& inV,
		     Image<T>& outL,
		     Image<T>& outR,
		     Image<T>& outV) const
{
    outL.resize(_warp[0].height(), _warp[0].width());
    outR.resize(_warp[1].height(), _warp[1].width());
    outV.resize(_warp[2].height(), _warp[2].width());
    
    _warp[0](inL.cbegin(), outL.begin());
    _warp[1](inR.cbegin(), outR.begin());
    _warp[2](inV.cbegin(), outV.begin());
}

}
#endif	// !__TU_RECTIFY_H
