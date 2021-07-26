#ifndef COTAGRAFICA_H
#define COTAGRAFICA_H

#include <QGraphicsItem>
#include <QFont>

class CotaGrafica : public QGraphicsItem
{
    enum Orientacion {HOR, VER};

public:
    CotaGrafica(QPointF p1, QPointF p2, Orientacion h, float dist = 0, QFont font = QFont());
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;

private:
    QPointF punto1;
    QPointF punto2;
    Orientacion ori;
    float distanciaPerp; //Distancia perpendicular al eje entre los dos puntos en que se encuentra la linea de cota
    float longitud;      //Longitud entre los puntos
    QFont fuente;
    qreal margin;
    QRectF bRect;
};

#endif // COTAGRAFICA_H
