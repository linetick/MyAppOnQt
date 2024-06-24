/****************************************************************************
** Meta object code from reading C++ file 'basketwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Kursach/Kursach/basketwindow.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'basketwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSBasketWindowENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSBasketWindowENDCLASS = QtMocHelpers::stringData(
    "BasketWindow",
    "Return",
    "",
    "openBuyWindow",
    "takeCountMoney",
    "fillTableWithCartItems",
    "QList<Basket::CartItem>",
    "cart",
    "Update",
    "on_Return_button_Clicked_clicked",
    "on_Buy_button_clicked_clicked",
    "on_Clear_button_Clicked_clicked",
    "on_Delete_button_Clicked_clicked",
    "on_DeleteFull_button_Clicked__clicked"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSBasketWindowENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[13];
    char stringdata1[7];
    char stringdata2[1];
    char stringdata3[14];
    char stringdata4[15];
    char stringdata5[23];
    char stringdata6[24];
    char stringdata7[5];
    char stringdata8[7];
    char stringdata9[33];
    char stringdata10[30];
    char stringdata11[32];
    char stringdata12[33];
    char stringdata13[38];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSBasketWindowENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSBasketWindowENDCLASS_t qt_meta_stringdata_CLASSBasketWindowENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "BasketWindow"
        QT_MOC_LITERAL(13, 6),  // "Return"
        QT_MOC_LITERAL(20, 0),  // ""
        QT_MOC_LITERAL(21, 13),  // "openBuyWindow"
        QT_MOC_LITERAL(35, 14),  // "takeCountMoney"
        QT_MOC_LITERAL(50, 22),  // "fillTableWithCartItems"
        QT_MOC_LITERAL(73, 23),  // "QList<Basket::CartItem>"
        QT_MOC_LITERAL(97, 4),  // "cart"
        QT_MOC_LITERAL(102, 6),  // "Update"
        QT_MOC_LITERAL(109, 32),  // "on_Return_button_Clicked_clicked"
        QT_MOC_LITERAL(142, 29),  // "on_Buy_button_clicked_clicked"
        QT_MOC_LITERAL(172, 31),  // "on_Clear_button_Clicked_clicked"
        QT_MOC_LITERAL(204, 32),  // "on_Delete_button_Clicked_clicked"
        QT_MOC_LITERAL(237, 37)   // "on_DeleteFull_button_Clicked_..."
    },
    "BasketWindow",
    "Return",
    "",
    "openBuyWindow",
    "takeCountMoney",
    "fillTableWithCartItems",
    "QList<Basket::CartItem>",
    "cart",
    "Update",
    "on_Return_button_Clicked_clicked",
    "on_Buy_button_clicked_clicked",
    "on_Clear_button_Clicked_clicked",
    "on_Delete_button_Clicked_clicked",
    "on_DeleteFull_button_Clicked__clicked"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSBasketWindowENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   74,    2, 0x06,    1 /* Public */,
       3,    0,   75,    2, 0x06,    2 /* Public */,
       4,    1,   76,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   79,    2, 0x0a,    5 /* Public */,
       8,    0,   82,    2, 0x0a,    7 /* Public */,
       9,    0,   83,    2, 0x08,    8 /* Private */,
      10,    0,   84,    2, 0x08,    9 /* Private */,
      11,    0,   85,    2, 0x08,   10 /* Private */,
      12,    0,   86,    2, 0x08,   11 /* Private */,
      13,    0,   87,    2, 0x08,   12 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject BasketWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSBasketWindowENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSBasketWindowENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSBasketWindowENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<BasketWindow, std::true_type>,
        // method 'Return'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'openBuyWindow'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'takeCountMoney'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'fillTableWithCartItems'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QList<Basket::CartItem> &, std::false_type>,
        // method 'Update'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Return_button_Clicked_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Buy_button_clicked_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Clear_button_Clicked_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_Delete_button_Clicked_clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'on_DeleteFull_button_Clicked__clicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void BasketWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BasketWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->Return(); break;
        case 1: _t->openBuyWindow(); break;
        case 2: _t->takeCountMoney((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 3: _t->fillTableWithCartItems((*reinterpret_cast< std::add_pointer_t<QList<Basket::CartItem>>>(_a[1]))); break;
        case 4: _t->Update(); break;
        case 5: _t->on_Return_button_Clicked_clicked(); break;
        case 6: _t->on_Buy_button_clicked_clicked(); break;
        case 7: _t->on_Clear_button_Clicked_clicked(); break;
        case 8: _t->on_Delete_button_Clicked_clicked(); break;
        case 9: _t->on_DeleteFull_button_Clicked__clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BasketWindow::*)();
            if (_t _q_method = &BasketWindow::Return; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BasketWindow::*)();
            if (_t _q_method = &BasketWindow::openBuyWindow; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BasketWindow::*)(QString );
            if (_t _q_method = &BasketWindow::takeCountMoney; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *BasketWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BasketWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSBasketWindowENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BasketWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void BasketWindow::Return()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void BasketWindow::openBuyWindow()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BasketWindow::takeCountMoney(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
