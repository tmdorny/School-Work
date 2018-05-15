/****************************************************************************
** Meta object code from reading C++ file 'editorserver.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SpriteEditor/editorserver.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editorserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_EditorServer[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      35,   14,   13,   13, 0x05,
      66,   60,   13,   13, 0x05,

 // slots: signature, parameters, type, tag, flags
      88,   13,   13,   13, 0x0a,
     105,   96,   13,   13, 0x0a,
     121,   96,   13,   13, 0x0a,
     137,   96,   13,   13, 0x0a,
     155,   96,   13,   13, 0x0a,
     173,   13,   13,   13, 0x0a,
     188,   13,  181,   13, 0x0a,
     208,  206,   13,   13, 0x0a,
     225,   13,   13,   13, 0x0a,
     237,   13,   13,   13, 0x0a,
     260,   13,  253,   13, 0x0a,
     276,   13,  253,   13, 0x0a,
     310,  301,   13,   13, 0x0a,
     338,   13,  334,   13, 0x0a,
     350,   13,  334,   13, 0x0a,
     367,  361,   13,   13, 0x0a,
     413,   13,  393,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_EditorServer[] = {
    "EditorServer\0\0low_value,high_value\0"
    "setProcessRange(int,int)\0value\0"
    "setProcessStatus(int)\0f_new()\0filename\0"
    "f_open(QString)\0f_save(QString)\0"
    "f_import(QString)\0f_export(QString)\0"
    "close()\0QImage\0getCurrentImage()\0n\0"
    "selectFrame(int)\0nextFrame()\0"
    "previousFrame()\0size_t\0getFrameCount()\0"
    "getSelectedFrameNumber()\0position\0"
    "insertEmptyFrameAt(int)\0int\0getHeight()\0"
    "getWidth()\0x,y,p\0writePixel(int,int,Pixel)\0"
    "std::vector<QImage>\0getAnimation()\0"
};

void EditorServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        EditorServer *_t = static_cast<EditorServer *>(_o);
        switch (_id) {
        case 0: _t->setProcessRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->setProcessStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->f_new(); break;
        case 3: _t->f_open((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->f_save((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->f_import((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->f_export((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->close(); break;
        case 8: { QImage _r = _t->getCurrentImage();
            if (_a[0]) *reinterpret_cast< QImage*>(_a[0]) = _r; }  break;
        case 9: _t->selectFrame((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->nextFrame(); break;
        case 11: _t->previousFrame(); break;
        case 12: { size_t _r = _t->getFrameCount();
            if (_a[0]) *reinterpret_cast< size_t*>(_a[0]) = _r; }  break;
        case 13: { size_t _r = _t->getSelectedFrameNumber();
            if (_a[0]) *reinterpret_cast< size_t*>(_a[0]) = _r; }  break;
        case 14: _t->insertEmptyFrameAt((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 15: { int _r = _t->getHeight();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 16: { int _r = _t->getWidth();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: _t->writePixel((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< Pixel(*)>(_a[3]))); break;
        case 18: { std::vector<QImage> _r = _t->getAnimation();
            if (_a[0]) *reinterpret_cast< std::vector<QImage>*>(_a[0]) = _r; }  break;
        default: ;
        }
    }
}

const QMetaObjectExtraData EditorServer::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject EditorServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EditorServer,
      qt_meta_data_EditorServer, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &EditorServer::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *EditorServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *EditorServer::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_EditorServer))
        return static_cast<void*>(const_cast< EditorServer*>(this));
    return QObject::qt_metacast(_clname);
}

int EditorServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void EditorServer::setProcessRange(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EditorServer::setProcessStatus(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
