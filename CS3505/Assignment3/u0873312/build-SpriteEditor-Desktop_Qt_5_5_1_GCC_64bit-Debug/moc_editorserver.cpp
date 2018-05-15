/****************************************************************************
** Meta object code from reading C++ file 'editorserver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../SpriteEditor/editorserver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'editorserver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_EditorServer_t {
    QByteArrayData data[16];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EditorServer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EditorServer_t qt_meta_stringdata_EditorServer = {
    {
QT_MOC_LITERAL(0, 0, 12), // "EditorServer"
QT_MOC_LITERAL(1, 13, 15), // "setProcessRange"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 9), // "low_value"
QT_MOC_LITERAL(4, 40, 10), // "high_value"
QT_MOC_LITERAL(5, 51, 16), // "setProcessStatus"
QT_MOC_LITERAL(6, 68, 5), // "value"
QT_MOC_LITERAL(7, 74, 5), // "f_new"
QT_MOC_LITERAL(8, 80, 6), // "f_open"
QT_MOC_LITERAL(9, 87, 8), // "filename"
QT_MOC_LITERAL(10, 96, 6), // "f_save"
QT_MOC_LITERAL(11, 103, 8), // "f_import"
QT_MOC_LITERAL(12, 112, 8), // "f_export"
QT_MOC_LITERAL(13, 121, 5), // "close"
QT_MOC_LITERAL(14, 127, 12), // "getAnimation"
QT_MOC_LITERAL(15, 140, 19) // "std::vector<QImage>"

    },
    "EditorServer\0setProcessRange\0\0low_value\0"
    "high_value\0setProcessStatus\0value\0"
    "f_new\0f_open\0filename\0f_save\0f_import\0"
    "f_export\0close\0getAnimation\0"
    "std::vector<QImage>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditorServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       5,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   67,    2, 0x0a /* Public */,
       8,    1,   68,    2, 0x0a /* Public */,
      10,    1,   71,    2, 0x0a /* Public */,
      11,    1,   74,    2, 0x0a /* Public */,
      12,    1,   77,    2, 0x0a /* Public */,
      13,    0,   80,    2, 0x0a /* Public */,
      14,    0,   81,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    0x80000000 | 15,

       0        // eod
};

void EditorServer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EditorServer *_t = static_cast<EditorServer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setProcessRange((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->setProcessStatus((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->f_new(); break;
        case 3: _t->f_open((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->f_save((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->f_import((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->f_export((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->close(); break;
        case 8: { std::vector<QImage> _r = _t->getAnimation();
            if (_a[0]) *reinterpret_cast< std::vector<QImage>*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (EditorServer::*_t)(int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EditorServer::setProcessRange)) {
                *result = 0;
            }
        }
        {
            typedef void (EditorServer::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&EditorServer::setProcessStatus)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject EditorServer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EditorServer.data,
      qt_meta_data_EditorServer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *EditorServer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EditorServer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_EditorServer.stringdata0))
        return static_cast<void*>(const_cast< EditorServer*>(this));
    return QObject::qt_metacast(_clname);
}

int EditorServer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void EditorServer::setProcessRange(int _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void EditorServer::setProcessStatus(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
