#include "customgraphicsview.h"

customGraphicsView::customGraphicsView(QWidget* w) :
    QGraphicsView(w)
{

}

void customGraphicsView::wheelEvent(QWheelEvent *event)
{

    qreal sc = 1+event->angleDelta().y()/1000.0;
    this->scale(sc,sc);

    QPoint r(this->size().width(), this->size().height());

    QPointF puntoCentroView = this->mapToScene(r/2);
    QPointF puntoMouse = this->mapToScene(event->pos());
    QPointF centroZoom = (puntoCentroView+puntoMouse)/2;

    this->centerOn(centroZoom);

    //qInfo() << "Matrix = " << this->matrix();
}
