#ifndef RODAJEEDICIONVISTA_H
#define RODAJEEDICIONVISTA_H

#include "../vistagraficabase.h"
#include "rodajeedicionescena.h"
#include <QGraphicsItem>
#include <QObject>

class RodajeEdicionEscena;

class RodajeEdicionVista : public VistaGraficaBase
{
    Q_OBJECT
public:
    RodajeEdicionVista(QWidget* parent = nullptr);
    enum class modoEdicion {NULO, PISTA, DOSPUNTOS, PARALELA};
    enum class modoSnap {NULO, PTOPISTA, PISTA, CABECERAS};
    Q_ENUM(modoEdicion)

    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;

    virtual void enterEvent(QEvent* ev) override;
    virtual void leaveEvent(QEvent* ev) override;

    void configEscena(QGraphicsScene* es);
    void actualizarVista();
    void actualizarSnapEscena();

    void setModEdicion(RodajeEdicionVista::modoEdicion m) {mEdicion = m;}
    void setModSnap(RodajeEdicionVista::modoSnap m) {mSnap = m;}

    void fijarPosPista(float distancia);
    void liberarPista();

signals:
    void sigVistaZoom();
    void sigMouseIngresado(bool);
    void sigCabeceraSeleccionada(QString cabecera);
    void sigPistaSeleccionada(int nroPista);
    void sigPosEnPistaMovido(float distancia);

private:
    bool lineaIniciada;
    bool posEnPistaFijado;
    QPoint puntoInicioLinea;
    RodajeEdicionEscena* escena;
    modoEdicion mEdicion;
    modoSnap mSnap;

};

#endif // RODAJEEDICIONVISTA_H
