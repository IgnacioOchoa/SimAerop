#ifndef RODAJEEDICIONVISTA_H
#define RODAJEEDICIONVISTA_H

#include "../vistagraficabase.h"
#include "rodajeedicionescena.h"
#include <QGraphicsItem>
#include <QObject>

class RodajeEdicionVista : public VistaGraficaBase
{
public:
    RodajeEdicionVista(QWidget* parent = nullptr);    
    virtual void resizeEvent(QResizeEvent *event) override;
    void configEscena(QGraphicsScene* es);
    void actualizarVista();
};

#endif // RODAJEEDICIONVISTA_H
