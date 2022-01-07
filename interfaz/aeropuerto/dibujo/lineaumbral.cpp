#include "lineaumbral.h"

LineaUmbral::LineaUmbral(int posX, int anchoPista, int longitudPista) :
    ancho(anchoPista),
    radio(8),
    posicion(posX),
    hover(false)
{

    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);

    setAcceptHoverEvents(true);
    setPos(posX,0);
    radioAumentado = radio+3;

    circ1 = new CirculoLlenoConst(QRectF(-radio,-radio,2*radio,2*radio),cNaranja,this);
    circ2 = new CirculoLlenoConst(QRectF(-radio,-radio,2*radio,2*radio),cNaranja,this);
    circ1->setPos(0,-ancho/2);
    circ2->setPos(0,ancho/2);
    circ1->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    circ2->setFlag(QGraphicsItem::ItemIgnoresTransformations);

    calcularBoundingRect();
    calcularShape();

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
    //painter->drawEllipse(-radio, -ancho/2-radio, 2*radio,2*radio);
    //painter->drawEllipse(-radio, ancho/2-radio,2*radio,2*radio);

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
            return nuevaPos;
        }
        return QGraphicsItem::itemChange(change, value);
}

void LineaUmbral::calcularBoundingRect()
{
    bRect = QRectF(-radioAumentado, -ancho/2-radioAumentado, 2*radioAumentado, ancho + 2*radioAumentado);
}

void LineaUmbral::calcularShape()
{
    pPath.clear();
    pPath.addRect(QRect(-5, -ancho/2-5, 10, ancho + 10));
    pPath.addEllipse(-radioAumentado,-ancho/2-radioAumentado,2*radioAumentado,2*radioAumentado);
    pPath.addEllipse(-radioAumentado,ancho/2-radioAumentado,2*radioAumentado,2*radioAumentado);
    //pPath.addRect(circ1->mapRectToParent(circ1->rect()));
    //pPath.addRect(circ2->mapRectToParent(circ2->rect()));

//    if (scene()) {
//        QTransform tr = circ1->deviceTransform(scene()->views()[0]->viewportTransform());
//        pPath.addRect(tr.mapRect(circ1->rect()));
//    }
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

void CirculoLlenoConst::unsetColor()
{
    brush1.setColor(colorBase);
    pincel1.setColor(colorBase);
}
