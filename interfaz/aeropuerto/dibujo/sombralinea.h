#ifndef SOMBRALINEA_H
#define SOMBRALINEA_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPen>
#include <QDebug>
#include <QGraphicsEffect>
#include <QRandomGenerator>
#include <QEvent>
#include <QTimer>

class SombraLinea : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    SombraLinea(QRectF rect);
    virtual QRectF boundingRect() const override {return rectEscalado;}
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    void calcularShape();
    QRectF rectBase;
    QRectF rectEscalado;
};

#endif // SOMBRALINEA_H
