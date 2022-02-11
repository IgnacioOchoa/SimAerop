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
    interfaz/aeropuerto/pistasUI/pistadial.cpp \
    interfaz/aeropuerto/pistasUI/pistadialogo.cpp \
    interfaz/aeropuerto/pistasUI/pistavista.cpp \
    interfaz/aeropuerto/pistasUI/pistaescena.cpp \
    interfaz/aeropuerto/plataformasUI/modelonombresplataformas.cpp \
    interfaz/aeropuerto/plataformasUI/modeloplataformasdelegate.cpp \
    interfaz/aeropuerto/plataformasUI/modeloverticesplataformas.cpp \
    interfaz/aeropuerto/plataformasUI/plataformadialogo.cpp \
    interfaz/aeropuerto/grillaguia.cpp \
    interfaz/aeropuerto/rodajesUI/modelorodajes.cpp \
    interfaz/aeropuerto/rodajesUI/rodajecabeceradelegate.cpp \
    interfaz/aeropuerto/rodajesUI/rodajedialogo.cpp \
    interfaz/aeropuerto/rodajesUI/rodajeediciondialogo.cpp \
    interfaz/aeropuerto/rodajesUI/rodajeedicionescena.cpp \
    interfaz/aeropuerto/rodajesUI/rodajeedicionvista.cpp \
    interfaz/aeropuerto/vistagraficabase.cpp \
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
    interfaz/aeropuerto/pistasUI/pistadial.h \
    interfaz/aeropuerto/pistasUI/pistadialogo.h \
    interfaz/aeropuerto/pistasUI/pistavista.h \
    interfaz/aeropuerto/pistasUI/pistaescena.h \
    interfaz/aeropuerto/plataformasUI/modelonombresplataformas.h \
    interfaz/aeropuerto/plataformasUI/modeloplataformasdelegate.h \
    interfaz/aeropuerto/plataformasUI/modeloverticesplataformas.h \
    interfaz/aeropuerto/plataformasUI/plataformadialogo.h \
    interfaz/aeropuerto/grillaguia.h \
    interfaz/aeropuerto/rodajesUI/modelorodajes.h \
    interfaz/aeropuerto/rodajesUI/rodajecabeceradelegate.h \
    interfaz/aeropuerto/rodajesUI/rodajedialogo.h \
    interfaz/aeropuerto/rodajesUI/rodajeediciondialogo.h \
    interfaz/aeropuerto/rodajesUI/rodajeedicionescena.h \
    interfaz/aeropuerto/rodajesUI/rodajeedicionvista.h \
    interfaz/aeropuerto/vistagraficabase.h \
    interfaz/interfazprincipal.h \
    kernel/kernel.h

FORMS += \
    interfaz/aeropuerto/pistasUI/pistadialogo.ui \
    interfaz/aeropuerto/plataformasUI/plataformadialogo.ui \
    interfaz/aeropuerto/rodajesUI/rodajedialogo.ui \
    interfaz/aeropuerto/rodajesUI/rodajeediciondialogo.ui \
    interfaz/interfazprincipal.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Recursos.qrc
