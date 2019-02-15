/****************************************************************************
** Meta object code from reading C++ file 'ControlPanelView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../work/src/hrp5p-comps/TUControlPanelPlugin/ControlPanelView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ControlPanelView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TU__v__CmdPane_t {
    QByteArrayData data[9];
    char stringdata0[60];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TU__v__CmdPane_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TU__v__CmdPane_t qt_meta_stringdata_TU__v__CmdPane = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TU::v::CmdPane"
QT_MOC_LITERAL(1, 15, 7), // "refresh"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "CmdVals&"
QT_MOC_LITERAL(4, 33, 3), // "ids"
QT_MOC_LITERAL(5, 37, 5), // "onSet"
QT_MOC_LITERAL(6, 43, 4), // "vals"
QT_MOC_LITERAL(7, 48, 5), // "onGet"
QT_MOC_LITERAL(8, 54, 5) // "range"

    },
    "TU::v::CmdPane\0refresh\0\0CmdVals&\0ids\0"
    "onSet\0vals\0onGet\0range"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TU__v__CmdPane[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   32,    2, 0x08 /* Private */,
       7,    2,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    6,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    6,    8,

       0        // eod
};

void TU::v::CmdPane::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CmdPane *_t = static_cast<CmdPane *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->refresh((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 1: _t->onSet((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 2: _t->onGet((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CmdPane::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CmdPane::refresh)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject TU::v::CmdPane::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TU__v__CmdPane.data,
      qt_meta_data_TU__v__CmdPane,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TU::v::CmdPane::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TU::v::CmdPane::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TU__v__CmdPane.stringdata0))
        return static_cast<void*>(const_cast< CmdPane*>(this));
    return QWidget::qt_metacast(_clname);
}

int TU::v::CmdPane::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void TU::v::CmdPane::refresh(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
