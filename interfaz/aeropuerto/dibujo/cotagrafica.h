#ifndef COTAGRAFICA_H
#define COTAGRAFICA_H

#include <QGraphicsItem>
#include <QFont>
#include <QPainter>
#include <QDebug>

class CotaGrafica : public QGraphicsItem
{

public:
    enum class Direccion {ARRIBA,ABAJO,DERECHA,IZQUIERDA};
    enum class Sentido {HOR,VER};

    CotaGrafica(QPointF p1, QPointF p2, Sentido sen, float dist = 0, QFont font = QFont());
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QRectF boundingRect() const override;
    void graficarFlecha(QPointF posVertice, Direccion ori, QPainter *painter);
    void graficarTexto(QPointF posCentro, QString texto);

private:
    QPointF punto1;
    QPointF punto2;
    Sentido sentido;
    float distanciaPerp; //Distancia perpendicular al eje entre los dos puntos en que se encuentra la linea de cota
    float longitud;      //Longitud entre los puntos
    QFont fuente;
    qreal margin;
    QRectF bRect;

    const int sizeFlechaRef = 30;

    QPen penCota;
    QBrush brushCota;
};

#endif // COTAGRAFICA_H
