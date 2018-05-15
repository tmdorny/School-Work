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
    QByteArrayData data[33];
    char stringdata0[328];
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
QT_MOC_LITERAL(14, 127, 15), // "getCurrentImage"
QT_MOC_LITERAL(15, 143, 11), // "selectFrame"
QT_MOC_LITERAL(16, 155, 1), // "n"
QT_MOC_LITERAL(17, 157, 9), // "nextFrame"
QT_MOC_LITERAL(18, 167, 13), // "previousFrame"
QT_MOC_LITERAL(19, 181, 13), // "getFrameCount"
QT_MOC_LITERAL(20, 195, 6), // "size_t"
QT_MOC_LITERAL(21, 202, 22), // "getSelectedFrameNumber"
QT_MOC_LITERAL(22, 225, 18), // "insertEmptyFrameAt"
QT_MOC_LITERAL(23, 244, 8), // "position"
QT_MOC_LITERAL(24, 253, 9), // "getHeight"
QT_MOC_LITERAL(25, 263, 8), // "getWidth"
QT_MOC_LITERAL(26, 272, 10), // "writePixel"
QT_MOC_LITERAL(27, 283, 1), // "x"
QT_MOC_LITERAL(28, 285, 1), // "y"
QT_MOC_LITERAL(29, 287, 5), // "Pixel"
QT_MOC_LITERAL(30, 293, 1), // "p"
QT_MOC_LITERAL(31, 295, 12), // "getAnimation"
QT_MOC_LITERAL(32, 308, 19) // "std::vector<QImage>"

    },
    "EditorServer\0setProcessRange\0\0low_value\0"
    "high_value\0setProcessStatus\0value\0"
    "f_new\0f_open\0filename\0f_save\0f_import\0"
    "f_export\0close\0getCurrentImage\0"
    "selectFrame\0n\0nextFrame\0previousFrame\0"
    "getFrameCount\0size_t\0getSelectedFrameNumber\0"
    "insertEmptyFrameAt\0position\0getHeight\0"
    "getWidth\0writePixel\0x\0y\0Pixel\0p\0"
    "getAnimation\0std::vector<QImage>"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EditorServer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  109,    2, 0x06 /* Public */,
       5,    1,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,  117,    2, 0x0a /* Public */,
       8,    1,  118,    2, 0x0a /* Public */,
      10,    1,  121,    2, 0x0a /* Public */,
      11,    1,  124,    2, 0x0a /* Public */,
      12,    1,  127,    2, 0x0a /* Public */,
      13,    0,  130,    2, 0x0a /* Public */,
      14,    0,  131,    2, 0x0a /* Public */,
      15,    1,  132,    2, 0x0a /* Public */,
      17,    0,  135,    2, 0x0a /* Public */,
      18,    0,  136,    2, 0x0a /* Public */,
      19,    0,  137,    2, 0x0a /* Public */,
      21,    0,  138,    2, 0x0a /* Public */,
      22,    1,  139,    2, 0x0a /* Public */,
      24,    0,  142,    2, 0x0a /* Public */,
      25,    0,  143,    2, 0x0a /* Public */,
      26,    3,  144,    2, 0x0a /* Public */,
      31,    0,  151,    2, 0x0a /* Public */,

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
    QMetaType::QImage,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 20,
    0x80000000 | 20,
    QMetaType::Void, QMetaType::Int,   23,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, 0x80000000 | 29,   27,   28,   30,
    0x80000000 | 32,

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
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
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
