/****************************************************************************
** Meta object code from reading C++ file 'LabelCmd_.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../work/src/hrp5p-comps/TUControlPanelPlugin/LabelCmd_.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LabelCmd_.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TU__v__LabelCmd_t {
    QByteArrayData data[5];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TU__v__LabelCmd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TU__v__LabelCmd_t qt_meta_stringdata_TU__v__LabelCmd = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TU::v::LabelCmd"
QT_MOC_LITERAL(1, 16, 9), // "onRefresh"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "CmdVals&"
QT_MOC_LITERAL(4, 36, 3) // "ids"

    },
    "TU::v::LabelCmd\0onRefresh\0\0CmdVals&\0"
    "ids"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TU__v__LabelCmd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void TU::v::LabelCmd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LabelCmd *_t = static_cast<LabelCmd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onRefresh((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TU::v::LabelCmd::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_TU__v__LabelCmd.data,
      qt_meta_data_TU__v__LabelCmd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TU::v::LabelCmd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TU::v::LabelCmd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TU__v__LabelCmd.stringdata0))
        return static_cast<void*>(const_cast< LabelCmd*>(this));
    return QLabel::qt_metacast(_clname);
}

int TU::v::LabelCmd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
