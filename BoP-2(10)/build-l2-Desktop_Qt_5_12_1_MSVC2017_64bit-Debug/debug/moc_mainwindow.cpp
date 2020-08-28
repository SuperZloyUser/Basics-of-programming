/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../BoP-6(14)/l6/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[188];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "addTrack"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 11), // "deleteTrack"
QT_MOC_LITERAL(4, 33, 9), // "editTrack"
QT_MOC_LITERAL(5, 43, 9), // "editLine6"
QT_MOC_LITERAL(6, 53, 9), // "editCombo"
QT_MOC_LITERAL(7, 63, 7), // "editIsp"
QT_MOC_LITERAL(8, 71, 8), // "editName"
QT_MOC_LITERAL(9, 80, 8), // "editYear"
QT_MOC_LITERAL(10, 89, 9), // "editMonth"
QT_MOC_LITERAL(11, 99, 8), // "editItem"
QT_MOC_LITERAL(12, 108, 17), // "QTableWidgetItem*"
QT_MOC_LITERAL(13, 126, 7), // "binOpen"
QT_MOC_LITERAL(14, 134, 7), // "binSave"
QT_MOC_LITERAL(15, 142, 8), // "textOpen"
QT_MOC_LITERAL(16, 151, 8), // "textSave"
QT_MOC_LITERAL(17, 160, 10), // "sortByUser"
QT_MOC_LITERAL(18, 171, 9), // "showError"
QT_MOC_LITERAL(19, 181, 6) // "report"

    },
    "MainWindow\0addTrack\0\0deleteTrack\0"
    "editTrack\0editLine6\0editCombo\0editIsp\0"
    "editName\0editYear\0editMonth\0editItem\0"
    "QTableWidgetItem*\0binOpen\0binSave\0"
    "textOpen\0textSave\0sortByUser\0showError\0"
    "report"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    0,  101,    2, 0x08 /* Private */,
       5,    1,  102,    2, 0x08 /* Private */,
       6,    0,  105,    2, 0x08 /* Private */,
       7,    1,  106,    2, 0x08 /* Private */,
       8,    1,  109,    2, 0x08 /* Private */,
       9,    1,  112,    2, 0x08 /* Private */,
      10,    1,  115,    2, 0x08 /* Private */,
      11,    1,  118,    2, 0x08 /* Private */,
      13,    0,  121,    2, 0x08 /* Private */,
      14,    0,  122,    2, 0x08 /* Private */,
      15,    0,  123,    2, 0x08 /* Private */,
      16,    0,  124,    2, 0x08 /* Private */,
      17,    0,  125,    2, 0x08 /* Private */,
      18,    0,  126,    2, 0x08 /* Private */,
      19,    0,  127,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addTrack(); break;
        case 1: _t->deleteTrack(); break;
        case 2: _t->editTrack(); break;
        case 3: _t->editLine6((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->editCombo(); break;
        case 5: _t->editIsp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->editName((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->editYear((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->editMonth((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->editItem((*reinterpret_cast< QTableWidgetItem*(*)>(_a[1]))); break;
        case 10: _t->binOpen(); break;
        case 11: _t->binSave(); break;
        case 12: _t->textOpen(); break;
        case 13: _t->textSave(); break;
        case 14: _t->sortByUser(); break;
        case 15: _t->showError(); break;
        case 16: _t->report(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
