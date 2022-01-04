#include "lineaumbral.h"

LineaUmbral::LineaUmbral(int posX, int anchoPista, int longitudPista) :
    ancho(anchoPista),
    radio(8),
    hover(false)
{
    setAcceptHoverEvents(true);
    radioAumentado = radio+3;
    pincel1.setCosmetic(true);
    pincel2.setCosmetic(true);
    punto1 = QPoint(-longitudPista/2+posX, anchoPista/2);
    punto2 = QPoint(-longitudPista/2+posX, -anchoPista/2);
    calcularBoundingRect();
    calcularShape();
}

void LineaUmbral::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(hover)
    {
        painter->setPen(pincel2);
        painter->setBrush(brush2);
    }
    else
    {
        painter->setPen(pincel1);
        painter->setBrush(brush1);
    }
    painter->drawLine(QLine(punto1,punto2));
    painter->drawEllipse(punto1.x()-radio, punto1.y()-radio,2*radio,2*radio);
    painter->drawEllipse(punto2.x()-radio, punto2.y()-radio,2*radio,2*radio);

//    painter->setBrush(Qt::NoBrush);
//    painter->setPen(QPen("red"));
//    painter->drawPath(shape());
//    painter->setPen(QPen("green"));
//    painter->drawRect(boundingRect());
}

void LineaUmbral::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    hover = true;
    QGraphicsItem::hoverEnterEvent(event);
}

void LineaUmbral::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    hover = false;
    QGraphicsItem::hoverLeaveEvent(event);
}

void LineaUmbral::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

}

void LineaUmbral::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qreal delta = 0.0;
    if (event->buttons() == Qt::LeftButton)
    {
        QPointF puntoActual = event->scenePos();
        QPointF puntoAnterior = event->lastScenePos();
        delta = (puntoActual-puntoAnterior).x();
    }
    actualizarPosicion(delta);
}

void LineaUmbral::calcularBoundingRect()
{
    bRect = QRectF(punto2.x()-radioAumentado, punto2.y()-radioAumentado, 2*radioAumentado, ancho + 2*radioAumentado);
}

void LineaUmbral::calcularShape()
{
    pPath.clear();
    pPath.addRect(QRect(punto2.x()-5, punto2.y()-5, 10, ancho + 10));
    pPath.addEllipse(punto2.x()-radioAumentado,punto2.y()-radioAumentado,2*radioAumentado,2*radioAumentado);
    pPath.addEllipse(punto1.x()-radioAumentado,punto1.y()-radioAumentado,2*radioAumentado,2*radioAumentado);
    pPath.setFillRule(Qt::WindingFill);
    pPath = pPath.simplified();
}

void LineaUmbral::actualizarPosicion(qreal delta)
{

    punto1 += QPoint(delta,0);
    punto2 += QPoint(delta,0);
    prepareGeometryChange();
    calcularShape();
    calcularBoundingRect();
}

QPainterPath LineaUmbral::shape() const
{
    return pPath;
}

QRectF LineaUmbral::boundingRect() const
{
    return bRect;
}
