#include "vistaconfpista.h"

VistaConfPista::VistaConfPista(QWidget* w) :
    QGraphicsView(w)
{
    this->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    centroVista = QPointF();
}

void VistaConfPista::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::MidButton)
       {
           QPointF movimiento = mapToScene(event->pos())-inicioRueda;
           centroVista -= movimiento;
           centerOn(centroVista);
           inicioRueda = mapToScene(event->pos());
       }
       QGraphicsView::mouseMoveEvent(event);
       viewport()->update(); //Esto es clave para que no sucedan cosas raras en el fondo al mover los items
}

void VistaConfPista::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::MidButton)
    {
        inicioRueda = mapToScene(event->pos());
    }
    QGraphicsView::mousePressEvent(event);
}

void VistaConfPista::wheelEvent(QWheelEvent *event)
{

}

void VistaConfPista::centrarVista(QPointF p)
{
    centerOn(p);
    centroVista = QPointF();
}
