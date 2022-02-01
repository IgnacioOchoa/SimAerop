#include "rodajeedicionvista.h"

RodajeEdicionVista::RodajeEdicionVista(QWidget* parent) :
    VistaGraficaBase(parent)
{

}

void RodajeEdicionVista::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
//    centerOn(0,0);
//    actualizarScRect();
}
