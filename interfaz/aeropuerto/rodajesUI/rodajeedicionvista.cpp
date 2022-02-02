#include "rodajeedicionvista.h"

RodajeEdicionVista::RodajeEdicionVista(QWidget* parent) :
    VistaGraficaBase(parent)
{

}

void RodajeEdicionVista::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    if(contenidoGraficado)
    {
        actualizarVista();
        qobject_cast<RodajeEdicionEscena*>(scene())->actualizarGrid();
    }
    //qInfo() << "RodajeEdicionVista::resizeEvent";
}

void RodajeEdicionVista::configEscena(QGraphicsScene* es)
{
    setScene(es);
}

void RodajeEdicionVista::actualizarVista()
{
    if(scene()->items().size() > 0) contenidoGraficado = true;
    actualizarScRect(qobject_cast<RodajeEdicionEscena*>(scene())->brectPpal());
    centerOn(0,0);
}
