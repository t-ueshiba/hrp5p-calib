/****************************************************************************
** Meta object code from reading C++ file 'Menu_.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../work/src/hrp5p-comps/TUControlPanelPlugin/Menu_.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Menu_.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TU__v__Menu_t {
    QByteArrayData data[16];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TU__v__Menu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TU__v__Menu_t qt_meta_stringdata_TU__v__Menu = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TU::v::Menu"
QT_MOC_LITERAL(1, 12, 3), // "set"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 8), // "CmdVals&"
QT_MOC_LITERAL(4, 26, 4), // "vals"
QT_MOC_LITERAL(5, 31, 3), // "get"
QT_MOC_LITERAL(6, 35, 5), // "range"
QT_MOC_LITERAL(7, 41, 7), // "refresh"
QT_MOC_LITERAL(8, 49, 3), // "ids"
QT_MOC_LITERAL(9, 53, 4), // "read"
QT_MOC_LITERAL(10, 58, 5), // "write"
QT_MOC_LITERAL(11, 64, 5), // "onSet"
QT_MOC_LITERAL(12, 70, 5), // "onGet"
QT_MOC_LITERAL(13, 76, 9), // "onRefresh"
QT_MOC_LITERAL(14, 86, 6), // "onRead"
QT_MOC_LITERAL(15, 93, 7) // "onWrite"

    },
    "TU::v::Menu\0set\0\0CmdVals&\0vals\0get\0"
    "range\0refresh\0ids\0read\0write\0onSet\0"
    "onGet\0onRefresh\0onRead\0onWrite"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TU__v__Menu[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    2,   67,    2, 0x06 /* Public */,
       7,    1,   72,    2, 0x06 /* Public */,
       9,    1,   75,    2, 0x06 /* Public */,
      10,    2,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   83,    2, 0x08 /* Private */,
      12,    2,   86,    2, 0x08 /* Private */,
      13,    1,   91,    2, 0x08 /* Private */,
      14,    1,   94,    2, 0x08 /* Private */,
      15,    2,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    6,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    6,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    6,

       0        // eod
};

void TU::v::Menu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Menu *_t = static_cast<Menu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 1: _t->get((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->refresh((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 3: _t->read((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 4: _t->write((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->onSet((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 6: _t->onGet((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 7: _t->onRefresh((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 8: _t->onRead((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 9: _t->onWrite((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Menu::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Menu::set)) {
                *result = 0;
            }
        }
        {
            typedef void (Menu::*_t)(CmdVals & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Menu::get)) {
                *result = 1;
            }
        }
        {
            typedef void (Menu::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Menu::refresh)) {
                *result = 2;
            }
        }
        {
            typedef void (Menu::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Menu::read)) {
                *result = 3;
            }
        }
        {
            typedef void (Menu::*_t)(CmdVals & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Menu::write)) {
                *result = 4;
            }
        }
    }
}

const QMetaObject TU::v::Menu::staticMetaObject = {
    { &QMenu::staticMetaObject, qt_meta_stringdata_TU__v__Menu.data,
      qt_meta_data_TU__v__Menu,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TU::v::Menu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TU::v::Menu::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TU__v__Menu.stringdata0))
        return static_cast<void*>(const_cast< Menu*>(this));
    return QMenu::qt_metacast(_clname);
}

int TU::v::Menu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMenu::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void TU::v::Menu::set(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TU::v::Menu::get(CmdVals & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TU::v::Menu::refresh(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TU::v::Menu::read(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void TU::v::Menu::write(CmdVals & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
struct qt_meta_stringdata_TU__v__MenuItem_t {
    QByteArrayData data[11];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TU__v__MenuItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TU__v__MenuItem_t qt_meta_stringdata_TU__v__MenuItem = {
    {
QT_MOC_LITERAL(0, 0, 15), // "TU::v::MenuItem"
QT_MOC_LITERAL(1, 16, 3), // "set"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "CmdVals&"
QT_MOC_LITERAL(4, 30, 4), // "vals"
QT_MOC_LITERAL(5, 35, 4), // "read"
QT_MOC_LITERAL(6, 40, 5), // "write"
QT_MOC_LITERAL(7, 46, 5), // "range"
QT_MOC_LITERAL(8, 52, 11), // "onTriggered"
QT_MOC_LITERAL(9, 64, 6), // "onRead"
QT_MOC_LITERAL(10, 71, 7) // "onWrite"

    },
    "TU::v::MenuItem\0set\0\0CmdVals&\0vals\0"
    "read\0write\0range\0onTriggered\0onRead\0"
    "onWrite"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TU__v__MenuItem[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,
       6,    2,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   55,    2, 0x08 /* Private */,
       9,    1,   56,    2, 0x08 /* Private */,
      10,    2,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3, QMetaType::Bool,    4,    7,

       0        // eod
};

void TU::v::MenuItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MenuItem *_t = static_cast<MenuItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->set((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 1: _t->read((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 2: _t->write((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 3: _t->onTriggered(); break;
        case 4: _t->onRead((*reinterpret_cast< CmdVals(*)>(_a[1]))); break;
        case 5: _t->onWrite((*reinterpret_cast< CmdVals(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MenuItem::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MenuItem::set)) {
                *result = 0;
            }
        }
        {
            typedef void (MenuItem::*_t)(CmdVals & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MenuItem::read)) {
                *result = 1;
            }
        }
        {
            typedef void (MenuItem::*_t)(CmdVals & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MenuItem::write)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject TU::v::MenuItem::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_TU__v__MenuItem.data,
      qt_meta_data_TU__v__MenuItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TU::v::MenuItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TU::v::MenuItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TU__v__MenuItem.stringdata0))
        return static_cast<void*>(const_cast< MenuItem*>(this));
    return QAction::qt_metacast(_clname);
}

int TU::v::MenuItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void TU::v::MenuItem::set(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TU::v::MenuItem::read(CmdVals & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TU::v::MenuItem::write(CmdVals & _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
