#include "sombralinea.h"

SombraLinea::SombraLinea(QRectF rect) :
    QGraphicsItem(),
    rectBase(rect),
    rectEscalado(rect)
{

}

void SombraLinea::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    QColor colorFondo("#c2f2fc");
    colorFondo.setAlpha(150);
    QPen penFondo(Qt::NoPen);
    QBrush brushFondo(colorFondo);
    painter->setPen(penFondo);
    painter->setBrush(brushFondo);
    painter->drawRect(rectEscalado);
    penFondo.setStyle(Qt::SolidLine);
    penFondo.setWidth(4);
    penFondo.setColor(Qt::black);
    painter->setPen(penFondo);
    painter->drawLine(QLine(-10,-10,10,10));
    painter->drawLine(QLine(-10,10,10,-10));
    calcularShape();
}

void SombraLinea::calcularShape()
{
    float sc = scene()->views()[0]->transform().m11();
    rectEscalado = QRectF(-rectBase.width()/(2*sc),-rectBase.height()/2,rectBase.width()/sc,rectBase.height());
}
