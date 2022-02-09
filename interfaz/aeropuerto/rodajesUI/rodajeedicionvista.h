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
    enum modoEdicion {NULO, PISTA, DOSPUNTOS, PARALELA};
    Q_ENUM(modoEdicion)

    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    void configEscena(QGraphicsScene* es);
    void actualizarVista();

signals:
    void sigVistaZoom();
    void sigMostrarSnapPuntero(bool);

public slots:
    void slotSetModEdicion(int m);

private:
    bool lineaIniciada;
    QPoint puntoInicioLinea;
    RodajeEdicionEscena* escena;
    modoEdicion mEdicion;
};

#endif // RODAJEEDICIONVISTA_H
