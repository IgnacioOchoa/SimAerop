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
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    void configEscena(QGraphicsScene* es);
    void actualizarVista();

signals:
    void sigVistaZoom();

private:
    bool lineaIniciada;
    QPoint puntoInicioLinea;
};

#endif // RODAJEEDICIONVISTA_H
