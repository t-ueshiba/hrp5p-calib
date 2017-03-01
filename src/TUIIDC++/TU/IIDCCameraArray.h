/*
 *  $Id: IIDCCameraUtility.h 1681 2014-10-17 02:16:17Z ueshiba $
 */
/*!
  \file		IIDCCameraUtility.h
  \brief	クラス TU::IIDCCameraArray の定義と実装
*/
#ifndef __TU_IIDCCAMERAUTILITY_H
#define __TU_IIDCCAMERAUTILITY_H

#include "TU/IIDC++.h"
#include "TU/algorithm.h"
#include "TU/Heap.h"
#include <string>

namespace TU
{
/************************************************************************
*  class IIDCCameraArray						*
************************************************************************/
//! IIDCデジタルカメラの配列を表すクラス
/*!
  TU::IIDCCameraへのポインタの配列として定義される.
*/
class IIDCCameraArray : public Array<IIDCCamera>
{
  public:
  //! デフォルトのカメラ名
    static constexpr const char*
	DEFAULT_CAMERA_NAME = "/usr/local/etc/cameras/IIDCCamera";
    
  public:
    explicit		IIDCCameraArray(size_t ncameras=0)		;
    
    void		restore(const char* name=DEFAULT_CAMERA_NAME,
				IIDCCamera::Speed
				speed=IIDCCamera::SPD_400M)		;
    void		save()					const	;
    const std::string&	name()					const	;
    std::string		configFile()				const	;
    std::string		calibFile()				const	;
    
  private:
    std::string		_name;	//!< カメラ名
};

//! カメラ名を返す.
/*!
  \return	カメラ名
*/
inline const std::string&
IIDCCameraArray::name() const
{
    return _name;
}
    
//! カメラ設定ファイル名を返す.
/*!
  \return	カメラ設定ファイル名
*/
inline std::string
IIDCCameraArray::configFile() const
{
    return _name + ".conf";
}
    
//! キャリブレーションファイル名を返す.
/*!
  \return	キャリブレーションファイル名
*/
inline std::string
IIDCCameraArray::calibFile() const
{
    return _name + ".calib";
}

/************************************************************************
*  global data								*
************************************************************************/
constexpr u_int	IIDCCAMERA_OFFSET_ONOFF = 0x100;
constexpr u_int	IIDCCAMERA_OFFSET_AUTO  = 0x200;
constexpr u_int	IIDCCAMERA_OFFSET_ABS   = 0x300;
constexpr u_int	IIDCCAMERA_OFFSET_VR    = 0x2;
constexpr u_int	IIDCCAMERA_CHOICE	= IIDCCamera::BRIGHTNESS + 1;
constexpr u_int	IIDCCAMERA_ALL		= IIDCCamera::BRIGHTNESS + 2;
    
/************************************************************************
*  global functions							*
************************************************************************/
template <class CAMERAS> auto
setFormat(CAMERAS&& cameras, u_int id, u_int val)
    -> typename std::enable_if<
	  std::is_convertible<
	      typename std::remove_reference<
		  decltype(*std::begin(cameras))>::type, IIDCCamera>::value,
	      bool>::type
{
    switch (id)
    {
      case IIDCCamera::YUV444_160x120:
      case IIDCCamera::YUV422_320x240:
      case IIDCCamera::YUV411_640x480:
      case IIDCCamera::YUV422_640x480:
      case IIDCCamera::RGB24_640x480:
      case IIDCCamera::MONO8_640x480:
      case IIDCCamera::MONO16_640x480:
      case IIDCCamera::YUV422_800x600:
      case IIDCCamera::RGB24_800x600:
      case IIDCCamera::MONO8_800x600:
      case IIDCCamera::YUV422_1024x768:
      case IIDCCamera::RGB24_1024x768:
      case IIDCCamera::MONO8_1024x768:
      case IIDCCamera::MONO16_800x600:
      case IIDCCamera::MONO16_1024x768:
      case IIDCCamera::YUV422_1280x960:
      case IIDCCamera::RGB24_1280x960:
      case IIDCCamera::MONO8_1280x960:
      case IIDCCamera::YUV422_1600x1200:
      case IIDCCamera::RGB24_1600x1200:
      case IIDCCamera::MONO8_1600x1200:
      case IIDCCamera::MONO16_1280x960:
      case IIDCCamera::MONO16_1600x1200:
      case IIDCCamera::Format_7_0:
      case IIDCCamera::Format_7_1:
      case IIDCCamera::Format_7_2:
      case IIDCCamera::Format_7_3:
      case IIDCCamera::Format_7_4:
      case IIDCCamera::Format_7_5:
      case IIDCCamera::Format_7_6:
      case IIDCCamera::Format_7_7:
	std::for_each(std::begin(cameras), std::end(cameras),
		      std::bind(&IIDCCamera::setFormatAndFrameRate,
				std::placeholders::_1,
				IIDCCamera::uintToFormat(id),
				IIDCCamera::uintToFrameRate(val)));
	return true;

      default:
	break;
    }

    return false;
}

inline bool
setFormat(IIDCCamera& camera, u_int id, u_int val)
{
    return setFormat(make_range(&camera, &camera + 1), id, val);
}

template <class CAMERAS> auto
setFeature(CAMERAS&& cameras, u_int id, u_int val, float fval)
    -> typename std::enable_if<
	  std::is_convertible<
	      typename std::remove_reference<
		  decltype(*std::begin(cameras))>::type, IIDCCamera>::value,
	      bool>::type
{
    switch (id)
    {
      case IIDCCamera::BRIGHTNESS:
      case IIDCCamera::AUTO_EXPOSURE:
      case IIDCCamera::SHARPNESS:
      case IIDCCamera::HUE:
      case IIDCCamera::SATURATION:
      case IIDCCamera::GAMMA:
      case IIDCCamera::SHUTTER:
      case IIDCCamera::GAIN:
      case IIDCCamera::IRIS:
      case IIDCCamera::FOCUS:
      case IIDCCamera::TEMPERATURE:
      case IIDCCamera::TRIGGER_DELAY:
      case IIDCCamera::FRAME_RATE:
      case IIDCCamera::ZOOM:
      case IIDCCamera::PAN:
      case IIDCCamera::TILT:
	if (size(cameras) > 0)
	{
	    const auto	feature = IIDCCamera::uintToFeature(id);

	    if (std::begin(cameras)->isAbsControl(feature))
	    {
		IIDCCamera& (IIDCCamera::*pf)(IIDCCamera::Feature, float)
		    = &IIDCCamera::setValue;
	  
		std::for_each(std::begin(cameras), std::end(cameras),
			      std::bind(pf, std::placeholders::_1,
					feature, fval));
	    }
	    else
	    {
		IIDCCamera& (IIDCCamera::*pf)(IIDCCamera::Feature, u_int)
		    = &IIDCCamera::setValue;
	  
		std::for_each(std::begin(cameras), std::end(cameras),
			      std::bind(pf, std::placeholders::_1,
					feature, val));
	    }
	}
	return true;
	
      case IIDCCamera::TRIGGER_MODE:
	std::for_each(std::begin(cameras), std::end(cameras),
		      std::bind(&IIDCCamera::setTriggerMode,
				std::placeholders::_1,
				IIDCCamera::uintToTriggerMode(val)));
	return true;

      case IIDCCamera::WHITE_BALANCE:
      case IIDCCamera::WHITE_BALANCE + IIDCCAMERA_OFFSET_VR:
	if (size(cameras) > 0)
	{
	    if (std::begin(cameras)->isAbsControl(IIDCCamera::WHITE_BALANCE))
		for (auto& camera : cameras)
		{
		    float	ub, vr;
		    camera.getWhiteBalance(ub, vr);
		    if (id == IIDCCamera::WHITE_BALANCE)
			camera.setWhiteBalance(fval, vr);
		    else
			camera.setWhiteBalance(ub, fval);
		}
	    else
		for (auto& camera : cameras)
		{
		    u_int	ub, vr;
		    camera.getWhiteBalance(ub, vr);
		    if (id == IIDCCamera::WHITE_BALANCE)
			camera.setWhiteBalance(val, vr);
		    else
			camera.setWhiteBalance(ub, val);
		}
	}
	return true;
	
      case IIDCCamera::BRIGHTNESS    + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::AUTO_EXPOSURE + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::SHARPNESS     + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::WHITE_BALANCE + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::HUE	     + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::SATURATION    + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::GAMMA	     + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::SHUTTER	     + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::GAIN	     + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::IRIS	     + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::FOCUS	     + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::TEMPERATURE   + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::TRIGGER_MODE  + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::TRIGGER_DELAY + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::FRAME_RATE    + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::ZOOM	     + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::PAN	     + IIDCCAMERA_OFFSET_ONOFF:
      case IIDCCamera::TILT	     + IIDCCAMERA_OFFSET_ONOFF:
      {
	IIDCCamera& (IIDCCamera::*pf)(IIDCCamera::Feature, bool)
	    = &IIDCCamera::setActive;
	std::for_each(std::begin(cameras), std::end(cameras),
		      std::bind(pf, std::placeholders::_1,
				IIDCCamera::uintToFeature(
				    id - IIDCCAMERA_OFFSET_ONOFF), bool(val)));
      }
	return true;

      case IIDCCamera::BRIGHTNESS    + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::AUTO_EXPOSURE + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::SHARPNESS     + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::WHITE_BALANCE + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::HUE	     + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::SATURATION    + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::GAMMA	     + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::SHUTTER	     + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::GAIN	     + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::IRIS	     + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::FOCUS	     + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::TEMPERATURE   + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::FRAME_RATE    + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::ZOOM	     + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::PAN	     + IIDCCAMERA_OFFSET_AUTO:
      case IIDCCamera::TILT	     + IIDCCAMERA_OFFSET_AUTO:
	std::for_each(std::begin(cameras), std::end(cameras),
		      std::bind(&IIDCCamera::setAuto, std::placeholders::_1,
				IIDCCamera::uintToFeature(
				    id - IIDCCAMERA_OFFSET_AUTO), bool(val)));
        return true;

      case IIDCCamera::TRIGGER_MODE  + IIDCCAMERA_OFFSET_AUTO:
	std::for_each(std::begin(cameras), std::end(cameras),
		      std::bind(&IIDCCamera::setTriggerPolarity,
				std::placeholders::_1, bool(val)));
	return true;

      case IIDCCamera::BRIGHTNESS    + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::AUTO_EXPOSURE + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::SHARPNESS     + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::WHITE_BALANCE + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::HUE	     + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::SATURATION    + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::GAMMA	     + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::SHUTTER	     + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::GAIN	     + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::IRIS	     + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::FOCUS	     + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::TEMPERATURE   + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::TRIGGER_DELAY + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::FRAME_RATE    + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::ZOOM	     + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::PAN	     + IIDCCAMERA_OFFSET_ABS:
      case IIDCCamera::TILT	     + IIDCCAMERA_OFFSET_ABS:
	std::for_each(std::begin(cameras), std::end(cameras),
		      std::bind(&IIDCCamera::setAbsControl,
				std::placeholders::_1,
				IIDCCamera::uintToFeature(
				    id - IIDCCAMERA_OFFSET_ABS), bool(val)));
        return true;

      default:
	break;
    }

    return false;
}

inline bool
setFeature(IIDCCamera& camera, u_int id, u_int val, float fval)
{
    return setFeature(make_range(&camera, &camera + 1), id, val, fval);
}

bool
getFeature(const IIDCCamera& camera, u_int id, u_int& val, float& fval)	;

//! 複数のカメラから同期した画像を保持する．
/*!
  \param cameras	カメラの配列
  \param maxSkew	画像間のタイムスタンプの許容ずれ幅(nsec単位)
*/
template <class CAMERAS> auto
syncedSnap(CAMERAS&& cameras, uint64_t maxSkew=1000)
    -> typename std::enable_if<
	  std::is_convertible<
	      typename std::remove_reference<
		  decltype(*std::begin(cameras))>::type,
	      IIDCCamera>::value>::type
{
    typedef decltype(std::begin(cameras))	iterator;
    typedef std::pair<uint64_t, iterator>	timestamp_t;
    
    Heap<timestamp_t,
	 std::greater<timestamp_t> >	timestamps(size(cameras));

    std::for_each(std::begin(cameras), std::end(cameras),
		  std::bind(&IIDCCamera::snap, std::placeholders::_1));

    timestamp_t	last(0, std::end(cameras));
    for (auto camera = std::begin(cameras); camera != std::end(cameras);
	 ++camera)
    {
	timestamp_t	timestamp(camera->getTimestamp(), camera);
	timestamps.push(timestamp);
	if (timestamp > last)
	    last = timestamp;
    }

    for (timestamp_t top; last.first > (top = timestamps.pop()).first + maxSkew;
	 timestamps.push(last))
	last = {top.second->snap().getTimestamp(), top.second};
}
    
}
#endif	// ! __TU_IIDCCAMERAUTILITY_H
