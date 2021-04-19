#include "customgraphicsview.h"

customGraphicsView::customGraphicsView(QWidget* w) :
    QGraphicsView(w)
{
    this->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    this->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    ruedaApretada = false;
    centroAnterior = QPointF(0,0);
}

void customGraphicsView::wheelEvent(QWheelEvent *event)
{
    QPoint puntoMouseEnView1 = event->pos();
    QPointF puntoMouseEnScene1 = this->mapToScene(puntoMouseEnView1);
    qreal sc = 1+event->angleDelta().y()/1000.0;

    this->scale(sc,sc);

    QPointF puntoMouseEnScene2 = this->mapToScene(puntoMouseEnView1);

    //QPoint puntoDelta = this->mapFromScene(puntoMouseEnScene2-puntoMouseEnScene1) - puntoCentroView;
    QPointF puntoDelta = puntoMouseEnScene2-puntoMouseEnScene1;
    centroAnterior+=puntoDelta;

    qInfo() << "puntoMouseEnView1 : " << puntoMouseEnView1;
    qInfo() << "puntoMouseEnScene1 : " << puntoMouseEnScene1;
    qInfo() << "puntoMouseEnScene2 : " << puntoMouseEnScene2;
    qInfo() << "puntoDelta : " << puntoDelta;

    this->centerOn(-centroAnterior);


    //QPointF puntoMouse = this->mapToScene(event->pos());
    //QPointF centroZoom = (puntoCentroView+puntoMouse)/2;
    //QPointF centroZoom = puntoMouse;

    //qreal sc = 1+event->angleDelta().y()/1000.0;
    //if(sc>1) this->centerOn(centroZoom);

    //this->scale(sc,sc);

    //qInfo() << "Matrix = " << this->matrix();
}

void customGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        ruedaApretada = true;
        puntoInicioRueda = event->pos();
    }
}

void customGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::MiddleButton)
    {
        ruedaApretada = false;
    }
}


void customGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(ruedaApretada)
    {
        QPointF delta = (event->pos() - puntoInicioRueda);
        centroAnterior += delta;
        this->centerOn(-centroAnterior);
        puntoInicioRueda = event->pos();
    }

}

