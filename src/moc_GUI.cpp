/****************************************************************************
** Meta object code from reading C++ file 'GUI.h'
**
** Created: Sat Jul 11 05:23:54 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "GUI.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GUI.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_GUI[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_GUI[] = {
    "GUI\0\0aboutapptr()\0"
};

const QMetaObject GUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_GUI,
      qt_meta_data_GUI, 0 }
};

const QMetaObject *GUI::metaObject() const
{
    return &staticMetaObject;
}

void *GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GUI))
        return static_cast<void*>(const_cast< GUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: aboutapptr(); break;
        default: ;
        }
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
