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
    QByteArrayData data[16];
    char stringdata0[160];
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
QT_MOC_LITERAL(5, 39, 7), // "setAddr"
QT_MOC_LITERAL(6, 47, 3), // "adr"
QT_MOC_LITERAL(7, 51, 7), // "setLoop"
QT_MOC_LITERAL(8, 59, 6), // "looped"
QT_MOC_LITERAL(9, 66, 7), // "setData"
QT_MOC_LITERAL(10, 74, 11), // "QByteArray&"
QT_MOC_LITERAL(11, 86, 4), // "data"
QT_MOC_LITERAL(12, 91, 12), // "updateValues"
QT_MOC_LITERAL(13, 104, 15), // "restorFromBlink"
QT_MOC_LITERAL(14, 120, 29), // "on_CustomContextMenuRequested"
QT_MOC_LITERAL(15, 150, 9) // "showGraph"

    },
    "cAgatSetting\0loopChanged\0\0setType\0"
    "type\0setAddr\0adr\0setLoop\0looped\0setData\0"
    "QByteArray&\0data\0updateValues\0"
    "restorFromBlink\0on_CustomContextMenuRequested\0"
    "showGraph"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_cAgatSetting[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   67,    2, 0x0a /* Public */,
       5,    1,   70,    2, 0x0a /* Public */,
       7,    1,   73,    2, 0x0a /* Public */,
       7,    0,   76,    2, 0x0a /* Public */,
       9,    1,   77,    2, 0x0a /* Public */,
      12,    0,   80,    2, 0x0a /* Public */,
      13,    0,   81,    2, 0x0a /* Public */,
      14,    1,   82,    2, 0x08 /* Private */,
      15,    0,   85,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
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
        case 2: _t->setAddr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setLoop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->setLoop(); break;
        case 5: _t->setData((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: _t->updateValues(); break;
        case 7: _t->restorFromBlink(); break;
        case 8: _t->on_CustomContextMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 9: _t->showGraph(); break;
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
void cAgatSetting::loopChanged(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
