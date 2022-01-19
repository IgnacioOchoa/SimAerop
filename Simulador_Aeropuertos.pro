QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    input-output/pistaparser.cpp \
    interfaz/aeronaves/aeronave.cpp \
    interfaz/aeronaves/flota.cpp \
    interfaz/aeropuerto/aeropuertoescena.cpp \
    interfaz/aeropuerto/aeropuertovista.cpp \
    interfaz/aeropuerto/dibujo/cotagrafica.cpp \
    interfaz/aeropuerto/dibujo/lineaumbral.cpp \
    interfaz/aeropuerto/graficadoraeropuerto.cpp \
    interfaz/aeropuerto/pistadial.cpp \
    interfaz/aeropuerto/pistadialogo.cpp \
    interfaz/aeropuerto/pistaescena.cpp \
    interfaz/aeropuerto/pistavista.cpp \
    interfaz/aeropuerto/plataformadialogo.cpp \
    interfaz/aeropuerto/rodajecabeceradelegate.cpp \
    interfaz/aeropuerto/rodajedialogo.cpp \
    interfaz/interfazprincipal.cpp \
    kernel/kernel.cpp \
    main.cpp

HEADERS += \
    estructuras-datos/elementosaerop.h \
    input-output/pistaparser.h \
    interfaz/aeronaves/aeronave.h \
    interfaz/aeronaves/flota.h \
    interfaz/aeropuerto/aeropuertoescena.h \
    interfaz/aeropuerto/aeropuertovista.h \
    interfaz/aeropuerto/dibujo/cotagrafica.h \
    interfaz/aeropuerto/dibujo/lineaumbral.h \
    interfaz/aeropuerto/graficadoraeropuerto.h \
    interfaz/aeropuerto/pistadial.h \
    interfaz/aeropuerto/pistadialogo.h \
    interfaz/aeropuerto/pistaescena.h \
    interfaz/aeropuerto/pistavista.h \
    interfaz/aeropuerto/plataformadialogo.h \
    interfaz/aeropuerto/rodajecabeceradelegate.h \
    interfaz/aeropuerto/rodajedialogo.h \
    interfaz/interfazprincipal.h \
    kernel/kernel.h

FORMS += \
    interfaz/aeropuerto/pistadialogo.ui \
    interfaz/aeropuerto/plataformadialogo.ui \
    interfaz/aeropuerto/rodajedialogo.ui \
    interfaz/interfazprincipal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc
