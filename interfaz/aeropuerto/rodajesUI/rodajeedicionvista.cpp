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
        //qobject_cast<RodajeEdicionEscena*>(scene())->actualizarGrid();
    }
    //qInfo() << "RodajeEdicionVista::resizeEvent";
}

void RodajeEdicionVista::configEscena(QGraphicsScene* es)
{
    setScene(es);
    connect(this, &RodajeEdicionVista::centroMovido, qobject_cast<RodajeEdicionEscena*>(es), &RodajeEdicionEscena::slotCentroVistaMovido);
}

void RodajeEdicionVista::actualizarVista()
{
    if(scene()->items().size() > 0) contenidoGraficado = true;
    actualizarScRect(qobject_cast<RodajeEdicionEscena*>(scene())->brectPpal());
    centerOn(0,0);
}

void RodajeEdicionVista::mouseMoveEvent(QMouseEvent* event)
{
    VistaGraficaBase::mouseMoveEvent(event);
    emit centroMovido();
}
