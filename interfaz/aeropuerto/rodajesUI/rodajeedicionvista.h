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
    void configEscena(QGraphicsScene* es);
    void actualizarVista();

    void mouseMoveEvent(QMouseEvent* event) override;

signals:
    void centroMovido();

};

#endif // RODAJEEDICIONVISTA_H
