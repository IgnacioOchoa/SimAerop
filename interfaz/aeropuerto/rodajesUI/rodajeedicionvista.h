#ifndef RODAJEEDICIONVISTA_H
#define RODAJEEDICIONVISTA_H

#include "../vistagraficabase.h"
#include "rodajeedicionescena.h"
#include <QGraphicsItem>
#include <QObject>

class RodajeEdicionVista : public VistaGraficaBase
{
    Q_OBJECT
public:
    RodajeEdicionVista(QWidget* parent = nullptr);
    enum modoEdicion {NULO, PISTA, DOSPUNTOS, PARALELA};
    Q_ENUM(modoEdicion)

    void setModEdicion(modoEdicion m) {mEdicion = m; emit sigModoEdicion(m);};
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    void configEscena(QGraphicsScene* es);
    void actualizarVista();

signals:
    void sigVistaZoom();
    void sigModoEdicion(modoEdicion m);

private:
    bool lineaIniciada;
    QPoint puntoInicioLinea;
    modoEdicion mEdicion;
};

#endif // RODAJEEDICIONVISTA_H
