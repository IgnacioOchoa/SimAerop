#ifndef COTAGRAFICA_H
#define COTAGRAFICA_H

#include <QGraphicsItem>
#include <QFont>
#include <QPainter>
#include <QDebug>

class CotaGrafica : public QGraphicsItem
{

public:
    CotaGrafica(QPointF p1, QPointF p2, QString orient, float dist = 0, QFont font = QFont());
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;
    void graficarFlecha(QPointF posVertice, float size, QString direccion); //direccion = {DER,IZQ,ARR,ABA}
    void graficarTexto(QPointF posCentro, QString texto);

private:
    QPointF punto1;
    QPointF punto2;
    QString ori;
    float distanciaPerp; //Distancia perpendicular al eje entre los dos puntos en que se encuentra la linea de cota
    float longitud;      //Longitud entre los puntos
    QFont fuente;
    qreal margin;
    QRectF bRect;

    QPen penCota;
};

#endif // COTAGRAFICA_H
