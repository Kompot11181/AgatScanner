/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "serialReceive"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 4), // "pack"
QT_MOC_LITERAL(4, 31, 10), // "serialSend"
QT_MOC_LITERAL(5, 42, 3), // "snd"
QT_MOC_LITERAL(6, 46, 7), // "sending"
QT_MOC_LITERAL(7, 54, 17), // "on_pbSave_clicked"
QT_MOC_LITERAL(8, 72, 17), // "on_pbLoad_clicked"
QT_MOC_LITERAL(9, 90, 18), // "on_pbClear_clicked"
QT_MOC_LITERAL(10, 109, 17), // "on_pbScan_clicked"
QT_MOC_LITERAL(11, 127, 18), // "on_pbStart_clicked"
QT_MOC_LITERAL(12, 146, 17), // "on_pbStop_clicked"
QT_MOC_LITERAL(13, 164, 24), // "on_cbCommonLoop_released"
QT_MOC_LITERAL(14, 189, 21), // "cbCommonLoop_toChange"
QT_MOC_LITERAL(15, 211, 4), // "loop"
QT_MOC_LITERAL(16, 216, 23), // "on_spinBox_valueChanged"
QT_MOC_LITERAL(17, 240, 4) // "arg1"

    },
    "MainWindow\0serialReceive\0\0pack\0"
    "serialSend\0snd\0sending\0on_pbSave_clicked\0"
    "on_pbLoad_clicked\0on_pbClear_clicked\0"
    "on_pbScan_clicked\0on_pbStart_clicked\0"
    "on_pbStop_clicked\0on_cbCommonLoop_released\0"
    "cbCommonLoop_toChange\0loop\0"
    "on_spinBox_valueChanged\0arg1"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x08 /* Private */,
       4,    1,   77,    2, 0x08 /* Private */,
       6,    0,   80,    2, 0x08 /* Private */,
       7,    0,   81,    2, 0x08 /* Private */,
       8,    0,   82,    2, 0x08 /* Private */,
       9,    0,   83,    2, 0x08 /* Private */,
      10,    0,   84,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    0,   86,    2, 0x08 /* Private */,
      13,    0,   87,    2, 0x08 /* Private */,
      14,    1,   88,    2, 0x08 /* Private */,
      16,    1,   91,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   15,
    QMetaType::Void, QMetaType::Int,   17,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->serialReceive((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->serialSend((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->sending(); break;
        case 3: _t->on_pbSave_clicked(); break;
        case 4: _t->on_pbLoad_clicked(); break;
        case 5: _t->on_pbClear_clicked(); break;
        case 6: _t->on_pbScan_clicked(); break;
        case 7: _t->on_pbStart_clicked(); break;
        case 8: _t->on_pbStop_clicked(); break;
        case 9: _t->on_cbCommonLoop_released(); break;
        case 10: _t->cbCommonLoop_toChange((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_spinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
