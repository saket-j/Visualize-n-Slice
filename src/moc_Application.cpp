/****************************************************************************
** Meta object code from reading C++ file 'Application.h'
**
** Created: Sat Jul 11 05:23:51 2009
**      by: The Qt Meta Object Compiler version 61 (Qt 4.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "Application.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Application.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 61
#error "This file was generated using the moc from 4.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Application[] = {

 // content:
       2,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   12, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x08,
      30,   12,   12,   12, 0x08,
      44,   12,   12,   12, 0x08,
      58,   12,   12,   12, 0x08,
      76,   12,   12,   12, 0x08,
      86,   12,   12,   12, 0x08,
      96,   12,   12,   12, 0x08,
     106,   12,   12,   12, 0x08,
     119,   12,   12,   12, 0x08,
     133,   12,   12,   12, 0x08,
     146,   12,   12,   12, 0x08,
     159,   12,   12,   12, 0x08,
     172,   12,   12,   12, 0x08,
     184,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Application[] = {
    "Application\0\0openvtkclicked()\0"
    "OpenClicked()\0SaveClicked()\0"
    "PathviewClicked()\0slcvalc()\0slsvalc()\0"
    "slavalc()\0showisotog()\0saveAxialcl()\0"
    "savecorocl()\0savesagicl()\0savepathcl()\0"
    "volinfotr()\0defineptr()\0"
};

const QMetaObject Application::staticMetaObject = {
    { &GUI::staticMetaObject, qt_meta_stringdata_Application,
      qt_meta_data_Application, 0 }
};

const QMetaObject *Application::metaObject() const
{
    return &staticMetaObject;
}

void *Application::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Application))
        return static_cast<void*>(const_cast< Application*>(this));
    return GUI::qt_metacast(_clname);
}

int Application::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = GUI::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: openvtkclicked(); break;
        case 1: OpenClicked(); break;
        case 2: SaveClicked(); break;
        case 3: PathviewClicked(); break;
        case 4: slcvalc(); break;
        case 5: slsvalc(); break;
        case 6: slavalc(); break;
        case 7: showisotog(); break;
        case 8: saveAxialcl(); break;
        case 9: savecorocl(); break;
        case 10: savesagicl(); break;
        case 11: savepathcl(); break;
        case 12: volinfotr(); break;
        case 13: defineptr(); break;
        default: ;
        }
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
