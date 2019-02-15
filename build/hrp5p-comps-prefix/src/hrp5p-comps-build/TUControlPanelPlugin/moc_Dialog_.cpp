/****************************************************************************
** Meta object code from reading C++ file 'Dialog_.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../work/src/hrp5p-comps/TUControlPanelPlugin/Dialog_.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Dialog_.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TU__v__Dialog_t {
    QByteArrayData data[17];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TU__v__Dialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TU__v__Dialog_t qt_meta_stringdata_TU__v__Dialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TU::v::Dialog"
QT_MOC_LITERAL(1, 14, 3), // "set"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 8), // "CmdVals&"
QT_MOC_LITERAL(4, 28, 4), // "vals"
QT_MOC_LITERAL(5, 33, 3), // "get"
QT_MOC_LITERAL(6, 37, 5), // "range"
QT_MOC_LITERAL(7, 43, 7), // "refresh"
QT_MOC_LITERAL(8, 51, 3), // "ids"
QT_MOC_LITERAL(9, 55, 4), // "read"
QT_MOC_LITERAL(10, 60, 5), // "write"
QT_MOC_LITERAL(11, 66, 6), // "accept"
QT_MOC_LITERAL(12, 73, 5), // "onSet"
QT_MOC_LITERAL(13, 79, 5), // "onGet"
QT_MOC_LITERAL(14, 85, 9), // "onRefresh"
QT_MOC_LITERAL(15, 95, 6), // "onRead"
QT_MOC_LITERAL(16, 102, 7) // "onWrite"

    },
    "TU::v::Dialog\0set\0\0CmdVals&\0vals\0get\0"
    "range\0refresh\0ids\0read\0write\0accept\0"
    "onSet\0onGet\0onRefresh\0onRead\0onWrite"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TU__v__Dialog[] = {

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

void TU::v::Dialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Dialog *_t = static_cast<Dialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 1: _t->get((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->refresh((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 3: _t->read((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 4: _t->write((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->accept(); break;
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
            typedef void (Dialog::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog::set)) {
                *result = 0;
            }
        }
        {
            typedef void (Dialog::*_t)(CmdVals & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog::get)) {
                *result = 1;
            }
        }
        {
            typedef void (Dialog::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog::refresh)) {
                *result = 2;
            }
        }
        {
            typedef void (Dialog::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog::read)) {
                *result = 3;
            }
        }
        {
            typedef void (Dialog::*_t)(CmdVals & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Dialog::write)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject TU::v::Dialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TU__v__Dialog.data,
      qt_meta_data_TU__v__Dialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TU::v::Dialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TU::v::Dialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TU__v__Dialog.stringdata0))
        return static_cast<void*>(const_cast< Dialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int TU::v::Dialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void TU::v::Dialog::set(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TU::v::Dialog::get(CmdVals & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TU::v::Dialog::refresh(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TU::v::Dialog::read(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TU::v::Dialog::write(CmdVals & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
