/****************************************************************************
** Meta object code from reading C++ file 'previewwidget.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SpriteEditor/previewwidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'previewwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PreviewWidget[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x08,
      27,   14,   14,   14, 0x08,
      39,   14,   14,   14, 0x08,
      48,   14,   14,   14, 0x08,
      55,   14,   14,   14, 0x08,
      71,   62,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PreviewWidget[] = {
    "PreviewWidget\0\0nextFrame()\0prevFrame()\0"
    "update()\0play()\0stop()\0newValue\0"
    "changedFPS(int)\0"
};

void PreviewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PreviewWidget *_t = static_cast<PreviewWidget *>(_o);
        switch (_id) {
        case 0: _t->nextFrame(); break;
        case 1: _t->prevFrame(); break;
        case 2: _t->update(); break;
        case 3: _t->play(); break;
        case 4: _t->stop(); break;
        case 5: _t->changedFPS((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PreviewWidget::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PreviewWidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PreviewWidget,
      qt_meta_data_PreviewWidget, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PreviewWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PreviewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PreviewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PreviewWidget))
        return static_cast<void*>(const_cast< PreviewWidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int PreviewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
