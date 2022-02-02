#include "rodajeedicionvista.h"

RodajeEdicionVista::RodajeEdicionVista(QWidget* parent) :
    VistaGraficaBase(parent)
{

}

void RodajeEdicionVista::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    actualizarVista();
}

void RodajeEdicionVista::configEscena(QGraphicsScene* es)
{
    setScene(es);
    connect(es, &QGraphicsScene::changed, this, &RodajeEdicionVista::actualizarVista);
}

void RodajeEdicionVista::actualizarVista()
{
    if(scene()->items().size() > 0) contenidoGraficado = true;
    centerOn(0,0);
    actualizarScRect();
}
