/****************************************************************************
** Meta object code from reading C++ file 'UDPclient.hpp'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.12)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../UDPclient.hpp"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UDPclient.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.12. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UdpClient_t {
    QByteArrayData data[7];
    char stringdata0[85];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UdpClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UdpClient_t qt_meta_stringdata_UdpClient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "UdpClient"
QT_MOC_LITERAL(1, 10, 14), // "SendBtnClicked"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "dataReceived"
QT_MOC_LITERAL(4, 39, 16), // "clearMassageText"
QT_MOC_LITERAL(5, 56, 13), // "setOwnAddress"
QT_MOC_LITERAL(6, 70, 14) // "setSendAddress"

    },
    "UdpClient\0SendBtnClicked\0\0dataReceived\0"
    "clearMassageText\0setOwnAddress\0"
    "setSendAddress"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UdpClient[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x0a /* Public */,
       3,    0,   40,    2, 0x0a /* Public */,
       4,    0,   41,    2, 0x0a /* Public */,
       5,    0,   42,    2, 0x0a /* Public */,
       6,    0,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UdpClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UdpClient *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->SendBtnClicked(); break;
        case 1: _t->dataReceived(); break;
        case 2: _t->clearMassageText(); break;
        case 3: _t->setOwnAddress(); break;
        case 4: _t->setSendAddress(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject UdpClient::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_UdpClient.data,
    qt_meta_data_UdpClient,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *UdpClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UdpClient::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UdpClient.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int UdpClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE