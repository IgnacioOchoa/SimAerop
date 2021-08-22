#ifndef COTAGRAFICA_H
#define COTAGRAFICA_H

#include <QGraphicsItem>
#include <QFont>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneEvent>

class CotaGrafica : public QGraphicsItem
{

public:
    enum class Direccion {ARRIBA,ABAJO,DERECHA,IZQUIERDA};
    enum class Sentido {HOR,VER};

    CotaGrafica(QPointF p1, QPointF p2, Sentido sen, QString valor, float dist = 0, QFont font = QFont());
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void graficarFlecha(QPointF posVertice, Direccion ori, QPainter *painter);
    void graficarTexto(QPointF posCentro, QString texto, QPainter *painter);

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;

    void ordenarPuntos(QPointF p1, QPointF p2);
    void procesarTexto();
    void calcularBoundingRect();
    void calcularShape();

    virtual QPainterPath shape() const override;
    virtual QRectF boundingRect() const override;


private:
    QPointF punto1;
    QPointF punto2;
    Sentido sentido;
    float distanciaPerp; //Distancia perpendicular al eje entre los dos puntos en que se encuentra la linea de cota
    float longitud;      //Longitud entre los puntos
    QFont fuente;
    qreal margin;
    qreal tramoAdicional;

    QRectF bRect;
    QPainterPath pPath;
    float anchoRect;

    QString texto;
    qreal anchoTexto;
    qreal altoTexto;
    QPointF posInfIzqTexto;

    const int sizeFlechaRef = 30;

    QPen penCota;
    QBrush brushCota;
    QPen penCotaHover;
    QBrush brushCotaHover;

    bool hover;
};

#endif // COTAGRAFICA_H
