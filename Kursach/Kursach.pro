QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addperson.cpp \
    addproductwindow.cpp \
    basketclass.cpp \
    basketwindow.cpp \
    buywindow.cpp \
    changedeliverywindow.cpp \
    changepersonwindow.cpp \
    changeproductwindow.cpp \
    database.cpp \
    historywindow.cpp \
    homewindowadmin.cpp \
    homewindowbuyeer.cpp \
    homewindowmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    orderswindow.cpp \
    personalaccountwindow.cpp \
    persons.cpp \
    personswindowadmin.cpp \
    productswindow_buyer.cpp \
    productswindow_manager.cpp \
    registrwindoww.cpp \
    user.cpp \
    warningwindow.cpp

HEADERS += \
    addperson.h \
    addproductwindow.h \
    basketclass.h \
    basketwindow.h \
    buywindow.h \
    changedeliverywindow.h \
    changepersonwindow.h \
    changeproductwindow.h \
    database.h \
    historywindow.h \
    homewindowadmin.h \
    homewindowbuyeer.h \
    homewindowmanager.h \
    mainwindow.h \
    orderswindow.h \
    personalaccountwindow.h \
    persons.h \
    personswindowadmin.h \
    productswindow_buyer.h \
    productswindow_manager.h \
    registrwindoww.h \
    user.h \
    warningwindow.h

FORMS += \
    addperson.ui \
    addproductwindow.ui \
    basketwindow.ui \
    buywindow.ui \
    changedeliverywindow.ui \
    changepersonwindow.ui \
    changeproductwindow.ui \
    historywindow.ui \
    homewindowadmin.ui \
    homewindowbuyeer.ui \
    homewindowmanager.ui \
    mainwindow.ui \
    orderswindow.ui \
    personalaccountwindow.ui \
    persons.ui \
    personswindowadmin.ui \
    productswindow_buyer.ui \
    productswindow_manager.ui \
    registrwindoww.ui \
    warningwindow.ui

TRANSLATIONS += \
    Kursach_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
