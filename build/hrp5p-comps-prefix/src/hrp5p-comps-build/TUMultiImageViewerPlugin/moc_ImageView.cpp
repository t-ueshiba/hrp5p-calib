/****************************************************************************
** Meta object code from reading C++ file 'ImageView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../../../work/src/hrp5p-comps/TUMultiImageViewerPlugin/ImageView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TU__ImageView_t {
    QByteArrayData data[6];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TU__ImageView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TU__ImageView_t qt_meta_stringdata_TU__ImageView = {
    {
QT_MOC_LITERAL(0, 0, 13), // "TU::ImageView"
QT_MOC_LITERAL(1, 14, 8), // "setScale"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "scale"
QT_MOC_LITERAL(4, 30, 15), // "showContextMenu"
QT_MOC_LITERAL(5, 46, 1) // "p"

    },
    "TU::ImageView\0setScale\0\0scale\0"
    "showContextMenu\0p"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TU__ImageView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08 /* Private */,
       4,    1,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, QMetaType::QPoint,    5,

       0        // eod
};

void TU::ImageView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ImageView *_t = static_cast<ImageView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setScale((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->showContextMenu((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TU::ImageView::staticMetaObject = {
    { &QGraphicsView::staticMetaObject, qt_meta_stringdata_TU__ImageView.data,
      qt_meta_data_TU__ImageView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TU::ImageView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TU::ImageView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TU__ImageView.stringdata0))
        return static_cast<void*>(const_cast< ImageView*>(this));
    return QGraphicsView::qt_metacast(_clname);
}

int TU::ImageView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_TU__MenuItem_t {
    QByteArrayData data[3];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TU__MenuItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TU__MenuItem_t qt_meta_stringdata_TU__MenuItem = {
    {
QT_MOC_LITERAL(0, 0, 12), // "TU::MenuItem"
QT_MOC_LITERAL(1, 13, 11), // "onTriggered"
QT_MOC_LITERAL(2, 25, 0) // ""

    },
    "TU::MenuItem\0onTriggered\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TU__MenuItem[] = {

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
       1,    0,   19,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void TU::MenuItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MenuItem *_t = static_cast<MenuItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onTriggered(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TU::MenuItem::staticMetaObject = {
    { &QAction::staticMetaObject, qt_meta_stringdata_TU__MenuItem.data,
      qt_meta_data_TU__MenuItem,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TU::MenuItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TU::MenuItem::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TU__MenuItem.stringdata0))
        return static_cast<void*>(const_cast< MenuItem*>(this));
    return QAction::qt_metacast(_clname);
}

int TU::MenuItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAction::qt_metacall(_c, _id, _a);
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
