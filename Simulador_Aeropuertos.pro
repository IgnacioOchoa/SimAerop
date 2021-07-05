QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    input-output/pistaparser.cpp \
    interfaz/aeronaves/aeronave.cpp \
    interfaz/aeropuerto/customgraphicsscene.cpp \
    interfaz/aeropuerto/customgraphicsview.cpp \
    interfaz/aeropuerto/dialogconfpista.cpp \
    interfaz/aeropuerto/dialogconfplataformas.cpp \
    interfaz/aeropuerto/dialogconfrodaje.cpp \
    interfaz/aeropuerto/editorpista.cpp \
    interfaz/interfazprincipal.cpp \
    kernel/kernel.cpp \
    main.cpp

HEADERS += \
    estructuras-datos/elementosaerop.h \
    input-output/pistaparser.h \
    interfaz/aeronaves/aeronave.h \
    interfaz/aeropuerto/customgraphicsscene.h \
    interfaz/aeropuerto/customgraphicsview.h \
    interfaz/aeropuerto/dialogconfpista.h \
    interfaz/aeropuerto/dialogconfplataformas.h \
    interfaz/aeropuerto/dialogconfrodaje.h \
    interfaz/aeropuerto/editorpista.h \
    interfaz/interfazprincipal.h \
    kernel/kernel.h

FORMS += \
    interfaz/aeropuerto/dialogconfpista.ui \
    interfaz/aeropuerto/dialogconfplataformas.ui \
    interfaz/aeropuerto/dialogconfrodaje.ui \
    interfaz/interfazprincipal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc
