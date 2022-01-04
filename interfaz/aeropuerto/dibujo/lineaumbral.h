#ifndef LINEAUMBRAL_H
#define LINEAUMBRAL_H

#include <QGraphicsItem>
#include <QFont>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneEvent>

class LineaUmbral : public QGraphicsItem
{
public:
    LineaUmbral(int posX, int anchoPista, int longitudPista);

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    void calcularBoundingRect();
    void calcularShape();
    void actualizarPosicion(qreal delta);

    virtual QPainterPath shape() const override;
    virtual QRectF boundingRect() const override;
private:
    QPoint punto1;
    QPoint punto2;
    qreal ancho;
    qreal radio;
    qreal radioAumentado;

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

#endif // LINEAUMBRAL_H
