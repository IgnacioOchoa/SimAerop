#ifndef LINEAUMBRAL_H
#define LINEAUMBRAL_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFont>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneEvent>
class CirculoLlenoConst;

class LineaUmbral : public QGraphicsItem
{
public:
    LineaUmbral(int posX, int anchoPista, int longitudPista);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void calcularBoundingRect();
    void calcularShape();

    virtual QPainterPath shape() const override;
    virtual QRectF boundingRect() const override;
private:
    CirculoLlenoConst* circ1;
    CirculoLlenoConst* circ2;

    qreal ancho;
    qreal radio;
    qreal radioAumentado;
    qreal posicion;

    QRectF bRect;
    QPainterPath pPath;

    const QColor cNaranja = QColor("#fcba03");
    const QColor cRojo = QColor("#f56342");
    const QBrush brush1 = QBrush(cNaranja, Qt::SolidPattern);
    const QBrush brush2 = QBrush(cRojo, Qt::SolidPattern);
    QPen pincel1 = QPen(brush1,5,Qt::SolidLine);
    QPen pincel2 = QPen(brush2,7,Qt::SolidLine);

    bool hover;
};

class CirculoLlenoConst : public QGraphicsEllipseItem
{
public:
    CirculoLlenoConst(QRectF rect, QColor color, QGraphicsItem *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setColor(QColor);
    void unsetColor();
private:
    QPen pincel1;
    QBrush brush1;
    QColor colorBase;
};

#endif // LINEAUMBRAL_H