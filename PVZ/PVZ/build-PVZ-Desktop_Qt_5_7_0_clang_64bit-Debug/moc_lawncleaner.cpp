/****************************************************************************
** Meta object code from reading C++ file 'lawncleaner.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../PVZ/lawncleaner.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lawncleaner.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_LawnCleaner_t {
    QByteArrayData data[4];
    char stringdata0[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LawnCleaner_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LawnCleaner_t qt_meta_stringdata_LawnCleaner = {
    {
QT_MOC_LITERAL(0, 0, 11), // "LawnCleaner"
QT_MOC_LITERAL(1, 12, 10), // "slot_enter"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 18) // "slot_movingForward"

    },
    "LawnCleaner\0slot_enter\0\0slot_movingForward"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LawnCleaner[] = {

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
       1,    0,   24,    2, 0x0a /* Public */,
       3,    0,   25,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LawnCleaner::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LawnCleaner *_t = static_cast<LawnCleaner *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_enter(); break;
        case 1: _t->slot_movingForward(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject LawnCleaner::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_LawnCleaner.data,
      qt_meta_data_LawnCleaner,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *LawnCleaner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LawnCleaner::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_LawnCleaner.stringdata0))
        return static_cast<void*>(const_cast< LawnCleaner*>(this));
    return QLabel::qt_metacast(_clname);
}

int LawnCleaner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
