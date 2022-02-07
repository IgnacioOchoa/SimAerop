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
    void configEscena(QGraphicsScene* es);
    void actualizarVista();

    void mouseMoveEvent(QMouseEvent* event) override;

private:
    bool lineaIniciada;
    QPoint puntoInicioLinea;

};

#endif // RODAJEEDICIONVISTA_H
