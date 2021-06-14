QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    customgraphicsscene.cpp \
    customgraphicsview.cpp \
    dialogconfpista.cpp \
    dialogconfplataformas.cpp \
    dialogconfrodaje.cpp \
    editorpista.cpp \
    interfazprincipal.cpp \
    kernel.cpp \
    main.cpp \
    pistaparser.cpp

HEADERS += \
    customgraphicsscene.h \
    customgraphicsview.h \
    dialogconfpista.h \
    dialogconfplataformas.h \
    dialogconfrodaje.h \
    editorpista.h \
    elementosaerop.h \
    interfazprincipal.h \
    kernel.h \
    pistaparser.h

FORMS += \
    dialogconfpista.ui \
    dialogconfplataformas.ui \
    dialogconfrodaje.ui \
    interfazprincipal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc
