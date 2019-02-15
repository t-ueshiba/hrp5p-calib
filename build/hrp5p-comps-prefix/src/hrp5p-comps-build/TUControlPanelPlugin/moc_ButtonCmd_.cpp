/****************************************************************************
** Meta object code from reading C++ file 'ButtonCmd_.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../work/src/hrp5p-comps/TUControlPanelPlugin/ButtonCmd_.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ButtonCmd_.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TU__v__ButtonCmd_t {
    QByteArrayData data[17];
    char stringdata0[116];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TU__v__ButtonCmd_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TU__v__ButtonCmd_t qt_meta_stringdata_TU__v__ButtonCmd = {
    {
QT_MOC_LITERAL(0, 0, 16), // "TU::v::ButtonCmd"
QT_MOC_LITERAL(1, 17, 3), // "set"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "CmdVals&"
QT_MOC_LITERAL(4, 31, 4), // "vals"
QT_MOC_LITERAL(5, 36, 3), // "get"
QT_MOC_LITERAL(6, 40, 5), // "range"
QT_MOC_LITERAL(7, 46, 7), // "refresh"
QT_MOC_LITERAL(8, 54, 3), // "ids"
QT_MOC_LITERAL(9, 58, 4), // "read"
QT_MOC_LITERAL(10, 63, 5), // "write"
QT_MOC_LITERAL(11, 69, 9), // "onPressed"
QT_MOC_LITERAL(12, 79, 5), // "onSet"
QT_MOC_LITERAL(13, 85, 5), // "onGet"
QT_MOC_LITERAL(14, 91, 9), // "onRefresh"
QT_MOC_LITERAL(15, 101, 6), // "onRead"
QT_MOC_LITERAL(16, 108, 7) // "onWrite"

    },
    "TU::v::ButtonCmd\0set\0\0CmdVals&\0vals\0"
    "get\0range\0refresh\0ids\0read\0write\0"
    "onPressed\0onSet\0onGet\0onRefresh\0onRead\0"
    "onWrite"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TU__v__ButtonCmd[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       5,    2,   72,    2, 0x06 /* Public */,
       7,    1,   77,    2, 0x06 /* Public */,
       9,    1,   80,    2, 0x06 /* Public */,
      10,    2,   83,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   88,    2, 0x08 /* Private */,
      12,    1,   89,    2, 0x08 /* Private */,
      13,    2,   92,    2, 0x08 /* Private */,
      14,    1,   97,    2, 0x08 /* Private */,
      15,    1,  100,    2, 0x08 /* Private */,
      16,    2,  103,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    6,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    6,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    6,

       0        // eod
};

void TU::v::ButtonCmd::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ButtonCmd *_t = static_cast<ButtonCmd *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 1: _t->get((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->refresh((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 3: _t->read((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 4: _t->write((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->onPressed(); break;
        case 6: _t->onSet((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 7: _t->onGet((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->onRefresh((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 9: _t->onRead((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 10: _t->onWrite((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ButtonCmd::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ButtonCmd::set)) {
                *result = 0;
            }
        }
        {
            typedef void (ButtonCmd::*_t)(CmdVals & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ButtonCmd::get)) {
                *result = 1;
            }
        }
        {
            typedef void (ButtonCmd::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ButtonCmd::refresh)) {
                *result = 2;
            }
        }
        {
            typedef void (ButtonCmd::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ButtonCmd::read)) {
                *result = 3;
            }
        }
        {
            typedef void (ButtonCmd::*_t)(CmdVals & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ButtonCmd::write)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject TU::v::ButtonCmd::staticMetaObject = {
    { &QPushButton::staticMetaObject, qt_meta_stringdata_TU__v__ButtonCmd.data,
      qt_meta_data_TU__v__ButtonCmd,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TU::v::ButtonCmd::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TU::v::ButtonCmd::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TU__v__ButtonCmd.stringdata0))
        return static_cast<void*>(const_cast< ButtonCmd*>(this));
    return QPushButton::qt_metacast(_clname);
}

int TU::v::ButtonCmd::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void TU::v::ButtonCmd::set(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TU::v::ButtonCmd::get(CmdVals & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TU::v::ButtonCmd::refresh(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TU::v::ButtonCmd::read(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TU::v::ButtonCmd::write(CmdVals & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
