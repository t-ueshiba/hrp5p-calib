/****************************************************************************
** Meta object code from reading C++ file 'SliderCmd_.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../work/src/hrp5p-comps/TUControlPanelPlugin/SliderCmd_.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SliderCmd_.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TU__v__SliderCmd_t {
    QByteArrayData data[14];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TU__v__SliderCmd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TU__v__SliderCmd_t qt_meta_stringdata_TU__v__SliderCmd = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TU::v::SliderCmd"
QT_MOC_LITERAL(1, 17, 3), // "set"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "CmdVals&"
QT_MOC_LITERAL(4, 31, 4), // "vals"
QT_MOC_LITERAL(5, 36, 3), // "get"
QT_MOC_LITERAL(6, 40, 5), // "range"
QT_MOC_LITERAL(7, 46, 9), // "onRefresh"
QT_MOC_LITERAL(8, 56, 3), // "ids"
QT_MOC_LITERAL(9, 60, 6), // "onRead"
QT_MOC_LITERAL(10, 67, 7), // "onWrite"
QT_MOC_LITERAL(11, 75, 20), // "onSliderValueChanged"
QT_MOC_LITERAL(12, 96, 3), // "val"
QT_MOC_LITERAL(13, 100, 21) // "onSpinBoxValueChanged"

    },
    "TU::v::SliderCmd\0set\0\0CmdVals&\0vals\0"
    "get\0range\0onRefresh\0ids\0onRead\0onWrite\0"
    "onSliderValueChanged\0val\0onSpinBoxValueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TU__v__SliderCmd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       5,    2,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   57,    2, 0x08 /* Private */,
       9,    1,   60,    2, 0x08 /* Private */,
      10,    2,   63,    2, 0x08 /* Private */,
      11,    1,   68,    2, 0x08 /* Private */,
      13,    1,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    6,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Double,   12,

       0        // eod
};

void TU::v::SliderCmd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SliderCmd *_t = static_cast<SliderCmd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 1: _t->get((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->onRefresh((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 3: _t->onRead((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 4: _t->onWrite((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->onSliderValueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onSpinBoxValueChanged((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SliderCmd::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SliderCmd::set)) {
                *result = 0;
            }
        }
        {
            typedef void (SliderCmd::*_t)(CmdVals & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SliderCmd::get)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject TU::v::SliderCmd::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TU__v__SliderCmd.data,
      qt_meta_data_TU__v__SliderCmd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TU::v::SliderCmd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TU::v::SliderCmd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TU__v__SliderCmd.stringdata0))
        return static_cast<void*>(const_cast< SliderCmd*>(this));
    return QWidget::qt_metacast(_clname);
}

int TU::v::SliderCmd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TU::v::SliderCmd::set(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TU::v::SliderCmd::get(CmdVals & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
