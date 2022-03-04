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

signals:
    void sigVistaZoom();
    void sigMouseIngresado(bool);
    //void sigCambiarModoEdicion(int modo);
    void sigCabeceraSeleccionada(QPointF pto);

public slots:
    void slotSetModEdicion(RodajeEdicionVista::modoEdicion m);
    void slotSetModSnap(RodajeEdicionVista::modoSnap m);

private:
    bool lineaIniciada;
    QPoint puntoInicioLinea;
    RodajeEdicionEscena* escena;
    modoEdicion mEdicion;
    modoSnap mSnap;
    int indxPistaSeleccionada;
};

#endif // RODAJEEDICIONVISTA_H
