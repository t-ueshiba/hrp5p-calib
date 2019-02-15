// This file is generated by omniidl (C++ backend)- omniORB_4_1. Do not edit.
#ifndef __Img_hh__
#define __Img_hh__

#ifndef __CORBA_H_EXTERNAL_GUARD__
#include <omniORB4/CORBA.h>
#endif

#ifndef  USE_stub_in_nt_dll
# define USE_stub_in_nt_dll_NOT_DEFINED_Img
#endif
#ifndef  USE_core_stub_in_nt_dll
# define USE_core_stub_in_nt_dll_NOT_DEFINED_Img
#endif
#ifndef  USE_dyn_stub_in_nt_dll
# define USE_dyn_stub_in_nt_dll_NOT_DEFINED_Img
#endif



#ifndef __BasicDataType_hh_EXTERNAL_GUARD__
#define __BasicDataType_hh_EXTERNAL_GUARD__
#include <BasicDataType.hh>
#endif



#ifdef USE_stub_in_nt_dll
# ifndef USE_core_stub_in_nt_dll
#  define USE_core_stub_in_nt_dll
# endif
# ifndef USE_dyn_stub_in_nt_dll
#  define USE_dyn_stub_in_nt_dll
# endif
#endif

#ifdef _core_attr
# error "A local CPP macro _core_attr has already been defined."
#else
# ifdef  USE_core_stub_in_nt_dll
#  define _core_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _core_attr
# endif
#endif

#ifdef _dyn_attr
# error "A local CPP macro _dyn_attr has already been defined."
#else
# ifdef  USE_dyn_stub_in_nt_dll
#  define _dyn_attr _OMNIORB_NTDLL_IMPORT
# else
#  define _dyn_attr
# endif
#endif





_CORBA_MODULE Img

_CORBA_MODULE_BEG

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_Vec3;

  typedef ::CORBA::Double Vec3[3];
  typedef ::CORBA::Double Vec3_slice;

  _CORBA_MODULE_INLINE Vec3_slice* Vec3_alloc() {
    return new Vec3_slice[3];
  }

  _CORBA_MODULE_INLINE Vec3_slice* Vec3_dup(const Vec3_slice* _s) {
    if (!_s) return 0;
    Vec3_slice* _data = Vec3_alloc();
    if (_data) {
      for (_CORBA_ULong _0i0 = 0; _0i0 < 3; _0i0++){
        
        _data[_0i0] = _s[_0i0];

      }
  
    }
    return _data;
  }

  _CORBA_MODULE_INLINE void Vec3_copy(Vec3_slice* _to, const Vec3_slice* _from){
    for (_CORBA_ULong _0i0 = 0; _0i0 < 3; _0i0++){
      
      _to[_0i0] = _from[_0i0];

    }
  
  }

  _CORBA_MODULE_INLINE void Vec3_free(Vec3_slice* _s) {
    delete [] _s;
  }

  class Vec3_copyHelper {
  public:
    static inline Vec3_slice* alloc() { return ::Img::Vec3_alloc(); }
    static inline Vec3_slice* dup(const Vec3_slice* p) { return ::Img::Vec3_dup(p); }
    static inline void free(Vec3_slice* p) { ::Img::Vec3_free(p); }
  };

  typedef _CORBA_Array_Fix_Var<Vec3_copyHelper,Vec3_slice> Vec3_var;
  typedef _CORBA_Array_Fix_Forany<Vec3_copyHelper,Vec3_slice> Vec3_forany;

  typedef Vec3_slice* Vec3_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_Mat44;

  typedef ::CORBA::Double Mat44[4][4];
  typedef ::CORBA::Double Mat44_slice[4];

  _CORBA_MODULE_INLINE Mat44_slice* Mat44_alloc() {
    return new Mat44_slice[4];
  }

  _CORBA_MODULE_INLINE Mat44_slice* Mat44_dup(const Mat44_slice* _s) {
    if (!_s) return 0;
    Mat44_slice* _data = Mat44_alloc();
    if (_data) {
      for (_CORBA_ULong _0i0 = 0; _0i0 < 4; _0i0++){
        for (_CORBA_ULong _0i1 = 0; _0i1 < 4; _0i1++){
          
          _data[_0i0][_0i1] = _s[_0i0][_0i1];

        }
      }
  
    }
    return _data;
  }

  _CORBA_MODULE_INLINE void Mat44_copy(Mat44_slice* _to, const Mat44_slice* _from){
    for (_CORBA_ULong _0i0 = 0; _0i0 < 4; _0i0++){
      for (_CORBA_ULong _0i1 = 0; _0i1 < 4; _0i1++){
        
        _to[_0i0][_0i1] = _from[_0i0][_0i1];

      }
    }
  
  }

  _CORBA_MODULE_INLINE void Mat44_free(Mat44_slice* _s) {
    delete [] _s;
  }

  class Mat44_copyHelper {
  public:
    static inline Mat44_slice* alloc() { return ::Img::Mat44_alloc(); }
    static inline Mat44_slice* dup(const Mat44_slice* p) { return ::Img::Mat44_dup(p); }
    static inline void free(Mat44_slice* p) { ::Img::Mat44_free(p); }
  };

  typedef _CORBA_Array_Fix_Var<Mat44_copyHelper,Mat44_slice> Mat44_var;
  typedef _CORBA_Array_Fix_Forany<Mat44_copyHelper,Mat44_slice> Mat44_forany;

  typedef Mat44_slice* Mat44_out;

  enum ColorFormat { CF_UNKNOWN, CF_GRAY, CF_RGB, CF_GRAY_JPEG, CF_RGB_JPEG, CF_DEPTH /*, __max_ColorFormat=0xffffffff */ };
  typedef ColorFormat& ColorFormat_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_ColorFormat;

  struct ImageData {
    typedef _CORBA_ConstrType_Variable_Var<ImageData> _var_type;

    
    ::CORBA::Long width;

    ::CORBA::Long height;

    ColorFormat format;

    typedef _CORBA_Unbounded_Sequence_Octet _raw_data_seq;
    _raw_data_seq raw_data;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef ImageData::_var_type ImageData_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< ImageData,ImageData_var > ImageData_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_ImageData;

  struct CameraIntrinsicParameter {
    typedef _CORBA_ConstrType_Variable_Var<CameraIntrinsicParameter> _var_type;

    
    typedef ::CORBA::Double _0RL_matrix_element[5];
    typedef ::CORBA::Double _matrix_element_slice;

    ::CORBA::Double matrix_element[5];

    typedef _CORBA_Unbounded_Sequence_w_FixSizeElement< ::CORBA::Double, 8, 8 >  _distortion_coefficient_seq;
    _distortion_coefficient_seq distortion_coefficient;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef CameraIntrinsicParameter::_var_type CameraIntrinsicParameter_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< CameraIntrinsicParameter,CameraIntrinsicParameter_var > CameraIntrinsicParameter_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_CameraIntrinsicParameter;

  struct CameraImage {
    typedef _CORBA_ConstrType_Variable_Var<CameraImage> _var_type;

    
    RTC::Time captured_time;

    ImageData image;

    CameraIntrinsicParameter intrinsic;

    Mat44 extrinsic;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef CameraImage::_var_type CameraImage_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< CameraImage,CameraImage_var > CameraImage_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_CameraImage;

  struct TimedCameraImage {
    typedef _CORBA_ConstrType_Variable_Var<TimedCameraImage> _var_type;

    
    RTC::Time tm;

    CameraImage data;

    ::CORBA::Long error_code;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef TimedCameraImage::_var_type TimedCameraImage_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< TimedCameraImage,TimedCameraImage_var > TimedCameraImage_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_TimedCameraImage;

  struct MultiCameraImage {
    typedef _CORBA_ConstrType_Variable_Var<MultiCameraImage> _var_type;

    
    typedef _CORBA_Unbounded_Sequence< CameraImage >  _image_seq_seq;
    _image_seq_seq image_seq;

    ::CORBA::Long camera_set_id;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef MultiCameraImage::_var_type MultiCameraImage_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< MultiCameraImage,MultiCameraImage_var > MultiCameraImage_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_MultiCameraImage;

  struct TimedMultiCameraImage {
    typedef _CORBA_ConstrType_Variable_Var<TimedMultiCameraImage> _var_type;

    
    RTC::Time tm;

    MultiCameraImage data;

    ::CORBA::Long error_code;

  

    void operator>>= (cdrStream &) const;
    void operator<<= (cdrStream &);
  };

  typedef TimedMultiCameraImage::_var_type TimedMultiCameraImage_var;

  typedef _CORBA_ConstrType_Variable_OUT_arg< TimedMultiCameraImage,TimedMultiCameraImage_var > TimedMultiCameraImage_out;

  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_TimedMultiCameraImage;

#ifndef __Img_mCameraCaptureService__
#define __Img_mCameraCaptureService__

  class CameraCaptureService;
  class _objref_CameraCaptureService;
  class _impl_CameraCaptureService;
  
  typedef _objref_CameraCaptureService* CameraCaptureService_ptr;
  typedef CameraCaptureService_ptr CameraCaptureServiceRef;

  class CameraCaptureService_Helper {
  public:
    typedef CameraCaptureService_ptr _ptr_type;

    static _ptr_type _nil();
    static _CORBA_Boolean is_nil(_ptr_type);
    static void release(_ptr_type);
    static void duplicate(_ptr_type);
    static void marshalObjRef(_ptr_type, cdrStream&);
    static _ptr_type unmarshalObjRef(cdrStream&);
  };

  typedef _CORBA_ObjRef_Var<_objref_CameraCaptureService, CameraCaptureService_Helper> CameraCaptureService_var;
  typedef _CORBA_ObjRef_OUT_arg<_objref_CameraCaptureService,CameraCaptureService_Helper > CameraCaptureService_out;

#endif

  // interface CameraCaptureService
  class CameraCaptureService {
  public:
    // Declarations for this interface type.
    typedef CameraCaptureService_ptr _ptr_type;
    typedef CameraCaptureService_var _var_type;

    static _ptr_type _duplicate(_ptr_type);
    static _ptr_type _narrow(::CORBA::Object_ptr);
    static _ptr_type _unchecked_narrow(::CORBA::Object_ptr);
    
    static _ptr_type _nil();

    static inline void _marshalObjRef(_ptr_type, cdrStream&);

    static inline _ptr_type _unmarshalObjRef(cdrStream& s) {
      omniObjRef* o = omniObjRef::_unMarshal(_PD_repoId,s);
      if (o)
        return (_ptr_type) o->_ptrToObjRef(_PD_repoId);
      else
        return _nil();
    }

    static _core_attr const char* _PD_repoId;

    // Other IDL defined within this scope.
    
  };

  class _objref_CameraCaptureService :
    public virtual ::CORBA::Object,
    public virtual omniObjRef
  {
  public:
    void take_one_frame();
    void start_continuous();
    void stop_continuous();

    inline _objref_CameraCaptureService()  { _PR_setobj(0); }  // nil
    _objref_CameraCaptureService(omniIOR*, omniIdentity*);

  protected:
    virtual ~_objref_CameraCaptureService();

    
  private:
    virtual void* _ptrToObjRef(const char*);

    _objref_CameraCaptureService(const _objref_CameraCaptureService&);
    _objref_CameraCaptureService& operator = (const _objref_CameraCaptureService&);
    // not implemented

    friend class CameraCaptureService;
  };

  class _pof_CameraCaptureService : public _OMNI_NS(proxyObjectFactory) {
  public:
    inline _pof_CameraCaptureService() : _OMNI_NS(proxyObjectFactory)(CameraCaptureService::_PD_repoId) {}
    virtual ~_pof_CameraCaptureService();

    virtual omniObjRef* newObjRef(omniIOR*,omniIdentity*);
    virtual _CORBA_Boolean is_a(const char*) const;
  };

  class _impl_CameraCaptureService :
    public virtual omniServant
  {
  public:
    virtual ~_impl_CameraCaptureService();

    virtual void take_one_frame() = 0;
    virtual void start_continuous() = 0;
    virtual void stop_continuous() = 0;
    
  public:  // Really protected, workaround for xlC
    virtual _CORBA_Boolean _dispatch(omniCallHandle&);

  private:
    virtual void* _ptrToInterface(const char*);
    virtual const char* _mostDerivedRepoId();
    
  };


  _CORBA_MODULE_VAR _dyn_attr const ::CORBA::TypeCode_ptr _tc_CameraCaptureService;

_CORBA_MODULE_END



_CORBA_MODULE POA_Img
_CORBA_MODULE_BEG

  class CameraCaptureService :
    public virtual Img::_impl_CameraCaptureService,
    public virtual ::PortableServer::ServantBase
  {
  public:
    virtual ~CameraCaptureService();

    inline ::Img::CameraCaptureService_ptr _this() {
      return (::Img::CameraCaptureService_ptr) _do_this(::Img::CameraCaptureService::_PD_repoId);
    }
  };

_CORBA_MODULE_END



_CORBA_MODULE OBV_Img
_CORBA_MODULE_BEG

_CORBA_MODULE_END





#undef _core_attr
#undef _dyn_attr

void operator<<=(::CORBA::Any& _a, const Img::Vec3_forany& _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Img::Vec3_forany& _s);

void operator<<=(::CORBA::Any& _a, const Img::Mat44_forany& _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Img::Mat44_forany& _s);

inline void operator >>=(Img::ColorFormat _e, cdrStream& s) {
  ::operator>>=((::CORBA::ULong)_e, s);
}

inline void operator <<= (Img::ColorFormat& _e, cdrStream& s) {
  ::CORBA::ULong _0RL_e;
  ::operator<<=(_0RL_e,s);
  if (_0RL_e <= Img::CF_DEPTH) {
    _e = (Img::ColorFormat) _0RL_e;
  }
  else {
    OMNIORB_THROW(MARSHAL,_OMNI_NS(MARSHAL_InvalidEnumValue),
                  (::CORBA::CompletionStatus)s.completion());
  }
}

void operator<<=(::CORBA::Any& _a, Img::ColorFormat _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Img::ColorFormat& _s);

extern void operator<<=(::CORBA::Any& _a, const Img::ImageData& _s);
extern void operator<<=(::CORBA::Any& _a, Img::ImageData* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Img::ImageData*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Img::ImageData*& _sp);

extern void operator<<=(::CORBA::Any& _a, const Img::CameraIntrinsicParameter& _s);
extern void operator<<=(::CORBA::Any& _a, Img::CameraIntrinsicParameter* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Img::CameraIntrinsicParameter*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Img::CameraIntrinsicParameter*& _sp);

extern void operator<<=(::CORBA::Any& _a, const Img::CameraImage& _s);
extern void operator<<=(::CORBA::Any& _a, Img::CameraImage* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Img::CameraImage*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Img::CameraImage*& _sp);

extern void operator<<=(::CORBA::Any& _a, const Img::TimedCameraImage& _s);
extern void operator<<=(::CORBA::Any& _a, Img::TimedCameraImage* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Img::TimedCameraImage*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Img::TimedCameraImage*& _sp);

extern void operator<<=(::CORBA::Any& _a, const Img::MultiCameraImage& _s);
extern void operator<<=(::CORBA::Any& _a, Img::MultiCameraImage* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Img::MultiCameraImage*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Img::MultiCameraImage*& _sp);

extern void operator<<=(::CORBA::Any& _a, const Img::TimedMultiCameraImage& _s);
extern void operator<<=(::CORBA::Any& _a, Img::TimedMultiCameraImage* _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Img::TimedMultiCameraImage*& _sp);
extern _CORBA_Boolean operator>>=(const ::CORBA::Any& _a, const Img::TimedMultiCameraImage*& _sp);

void operator<<=(::CORBA::Any& _a, Img::CameraCaptureService_ptr _s);
void operator<<=(::CORBA::Any& _a, Img::CameraCaptureService_ptr* _s);
_CORBA_Boolean operator>>=(const ::CORBA::Any& _a, Img::CameraCaptureService_ptr& _s);



inline void
Img::CameraCaptureService::_marshalObjRef(::Img::CameraCaptureService_ptr obj, cdrStream& s) {
  omniObjRef::_marshal(obj->_PR_getobj(),s);
}




#ifdef   USE_stub_in_nt_dll_NOT_DEFINED_Img
# undef  USE_stub_in_nt_dll
# undef  USE_stub_in_nt_dll_NOT_DEFINED_Img
#endif
#ifdef   USE_core_stub_in_nt_dll_NOT_DEFINED_Img
# undef  USE_core_stub_in_nt_dll
# undef  USE_core_stub_in_nt_dll_NOT_DEFINED_Img
#endif
#ifdef   USE_dyn_stub_in_nt_dll_NOT_DEFINED_Img
# undef  USE_dyn_stub_in_nt_dll
# undef  USE_dyn_stub_in_nt_dll_NOT_DEFINED_Img
#endif

#endif  // __Img_hh__

