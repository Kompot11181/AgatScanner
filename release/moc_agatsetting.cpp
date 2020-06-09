/****************************************************************************
** Meta object code from reading C++ file 'agatsetting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../agatsetting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'agatsetting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_cAgatSetting_t {
    QByteArrayData data[18];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_cAgatSetting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_cAgatSetting_t qt_meta_stringdata_cAgatSetting = {
    {
QT_MOC_LITERAL(0, 0, 12), // "cAgatSetting"
QT_MOC_LITERAL(1, 13, 11), // "loopChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 7), // "setType"
QT_MOC_LITERAL(4, 34, 4), // "type"
QT_MOC_LITERAL(5, 39, 14), // "setTypeWithLen"
QT_MOC_LITERAL(6, 54, 3), // "num"
QT_MOC_LITERAL(7, 58, 7), // "setAddr"
QT_MOC_LITERAL(8, 66, 3), // "adr"
QT_MOC_LITERAL(9, 70, 7), // "setLoop"
QT_MOC_LITERAL(10, 78, 6), // "looped"
QT_MOC_LITERAL(11, 85, 7), // "setData"
QT_MOC_LITERAL(12, 93, 11), // "QByteArray&"
QT_MOC_LITERAL(13, 105, 4), // "data"
QT_MOC_LITERAL(14, 110, 12), // "updateValues"
QT_MOC_LITERAL(15, 123, 15), // "restorFromBlink"
QT_MOC_LITERAL(16, 139, 29), // "on_CustomContextMenuRequested"
QT_MOC_LITERAL(17, 169, 9) // "showGraph"

    },
    "cAgatSetting\0loopChanged\0\0setType\0"
    "type\0setTypeWithLen\0num\0setAddr\0adr\0"
    "setLoop\0looped\0setData\0QByteArray&\0"
    "data\0updateValues\0restorFromBlink\0"
    "on_CustomContextMenuRequested\0showGraph"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cAgatSetting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   72,    2, 0x0a /* Public */,
       5,    2,   75,    2, 0x0a /* Public */,
       7,    1,   80,    2, 0x0a /* Public */,
       9,    1,   83,    2, 0x0a /* Public */,
       9,    0,   86,    2, 0x0a /* Public */,
      11,    1,   87,    2, 0x0a /* Public */,
      14,    0,   90,    2, 0x0a /* Public */,
      15,    0,   91,    2, 0x0a /* Public */,
      16,    1,   92,    2, 0x08 /* Private */,
      17,    0,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    4,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void,

       0        // eod
};

void cAgatSetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        cAgatSetting *_t = static_cast<cAgatSetting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loopChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->setType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->setTypeWithLen((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->setAddr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->setLoop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setLoop(); break;
        case 6: _t->setData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->updateValues(); break;
        case 8: _t->restorFromBlink(); break;
        case 9: _t->on_CustomContextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 10: _t->showGraph(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (cAgatSetting::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&cAgatSetting::loopChanged)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject cAgatSetting::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_cAgatSetting.data,
      qt_meta_data_cAgatSetting,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *cAgatSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *cAgatSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_cAgatSetting.stringdata0))
        return static_cast<void*>(const_cast< cAgatSetting*>(this));
    return QWidget::qt_metacast(_clname);
}

int cAgatSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void cAgatSetting::loopChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
