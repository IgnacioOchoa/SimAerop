#include "lineaumbral.h"

LineaUmbral::LineaUmbral() :
    radio(8),
    radioAumentado(11),
    hover(false)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    setAcceptHoverEvents(true);


    circ1 = new CirculoLlenoConst(QRectF(-radio,-radio,2*radio,2*radio),cNaranja,this);
    circ2 = new CirculoLlenoConst(QRectF(-radio,-radio,2*radio,2*radio),cNaranja,this);

    calcularBoundingRect();
    calcularShape();
}

void LineaUmbral::setDimensiones(int posX, int anchoPista)
{
    posicion = posX;
    setPos(posX,0);
    ancho = anchoPista;
    circ1->setPos(QPointF(0,-ancho/2));
    circ2->setPos(QPointF(0,ancho/2));
}

void LineaUmbral::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    pincel1.setCosmetic(true);
    pincel2.setCosmetic(true);
    if(hover)
    {
        painter->setPen(pincel2);
        painter->setBrush(brush2);
        circ1->setColor(cRojo);
        circ2->setColor(cRojo);
    }
    else
    {
        painter->setPen(pincel1);
        painter->setBrush(brush1);
        circ1->setColor(cNaranja);
        circ2->setColor(cNaranja);
    }
    painter->drawLine(0,-ancho/2,0, ancho/2);

//    painter->setBrush(Qt::NoBrush);
//    painter->setPen(QPen("red"));
//    painter->drawPath(shape());
//    painter->setPen(QPen("green"));
//    painter->drawRect(boundingRect());

    calcularBoundingRect();
    calcularShape();
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

QVariant LineaUmbral::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
        if (change == ItemPositionChange && scene()) {
            QPointF nuevaPos = value.toPointF();
            nuevaPos.setY(0);

            if (nuevaPos.x()<limiteInf) nuevaPos.setX(limiteInf);
            else if (nuevaPos.x()>limiteSup) nuevaPos.setX(limiteSup);

            emit sigPosCambiada(nuevaPos.x());
            return nuevaPos;
        }
        return QGraphicsItem::itemChange(change, value);
}

void LineaUmbral::calcularBoundingRect()
{
    qreal escala = 1;
    if (scene()) {
        escala = scene()->views()[0]->viewportTransform().m11();
    }
    qreal radioShape = radio/escala*1.2;
    bRect = QRectF(-radioShape, -ancho/2-radioShape, 2*radioShape, ancho + 2*radioShape);
}

void LineaUmbral::calcularShape()
{
    pPath.clear();
    qreal escala = 1;
    if (scene()) {
        escala = scene()->views()[0]->viewportTransform().m11();
    }
    qreal radioShape = radio/escala;
    qreal ladoRect = 10.0/escala;

    pPath.addRect(QRectF(-ladoRect/2, -ancho/2, ladoRect, ancho));
    pPath.addEllipse(-radioShape,-ancho/2-radioShape,2*radioShape,2*radioShape);
    pPath.addEllipse(-radioShape, ancho/2-radioShape,2*radioShape,2*radioShape);

    pPath.setFillRule(Qt::WindingFill);
    pPath = pPath.simplified();
}

QPainterPath LineaUmbral::shape() const
{
    return pPath;
}

QRectF LineaUmbral::boundingRect() const
{
    return bRect;
}

CirculoLlenoConst::CirculoLlenoConst(QRectF rect, QColor color, QGraphicsItem *parent) :
    QGraphicsEllipseItem(rect,parent),
    colorBase(color)
{   
    setFlag(QGraphicsItem::ItemIgnoresTransformations);
    brush1 = QBrush(color,Qt::SolidPattern);
    pincel1 = QPen(brush1,1);
    pincel1.setCosmetic(true);
}

void CirculoLlenoConst::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setPen(pincel1);
    painter->setBrush(brush1);
    painter->drawEllipse(rect());
}

void CirculoLlenoConst::setColor(QColor nuevoColor)
{
    brush1.setColor(nuevoColor);
    pincel1.setColor(nuevoColor);
}

void CirculoLlenoConst::setPosicion(QPointF pos)
{
    setPos(pos);
}

void CirculoLlenoConst::unsetColor()
{
    brush1.setColor(colorBase);
    pincel1.setColor(colorBase);
}
