/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SpriteEditor/mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      38,   11,   11,   11, 0x08,
      64,   11,   11,   11, 0x08,
      92,   11,   11,   11, 0x08,
     120,   11,   11,   11, 0x08,
     158,  149,   11,   11, 0x08,
     181,   11,   11,   11, 0x08,
     188,   11,   11,   11, 0x08,
     199,   11,   11,   11, 0x08,
     208,   11,   11,   11, 0x08,
     237,   11,   11,   11, 0x08,
     262,   11,   11,   11, 0x08,
     289,   11,   11,   11, 0x08,
     317,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_actionOpen_triggered()\0"
    "on_actionSave_triggered()\0"
    "on_actionImport_triggered()\0"
    "on_actionExport_triggered()\0"
    "on_actionPreview_triggered()\0newValue\0"
    "progressBarUpdate(int)\0next()\0previous()\0"
    "update()\0on_actionSave_as_triggered()\0"
    "on_actionNew_triggered()\0"
    "on_actionClose_triggered()\0"
    "on_actionCommon_triggered()\0"
    "on_newFrameButton_clicked()\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_actionOpen_triggered(); break;
        case 1: _t->on_actionSave_triggered(); break;
        case 2: _t->on_actionImport_triggered(); break;
        case 3: _t->on_actionExport_triggered(); break;
        case 4: _t->on_actionPreview_triggered(); break;
        case 5: _t->progressBarUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->next(); break;
        case 7: _t->previous(); break;
        case 8: _t->update(); break;
        case 9: _t->on_actionSave_as_triggered(); break;
        case 10: _t->on_actionNew_triggered(); break;
        case 11: _t->on_actionClose_triggered(); break;
        case 12: _t->on_actionCommon_triggered(); break;
        case 13: _t->on_newFrameButton_clicked(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
