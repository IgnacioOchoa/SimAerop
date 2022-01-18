#ifndef COTAGRAFICA_H
#define COTAGRAFICA_H

#include <QGraphicsItem>
#include <QFont>
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneEvent>
#include <QtMath>

class CotaGrafica : public QGraphicsObject
{
Q_OBJECT
public:
    enum class Direccion {ARRIBA,ABAJO,DERECHA,IZQUIERDA};
    enum class Sentido {HOR,VER};

    CotaGrafica(QPointF p1, QPointF p2, Sentido sen, float dist = 0, QFont font = QFont());
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual QPainterPath shape() const override;
    virtual QRectF boundingRect() const override;


private:
    void graficarFlecha(QPointF posVertice, Direccion ori, QPainter *painter);
    void graficarTexto(QPointF posCentro, QString texto, QPainter *painter);
    void ordenarPuntos(QPointF p1, QPointF p2);
    void procesarTexto();
    void calcularBoundingRect();
    void calcularShape();
    void actualizarPosicion(float delta);

public slots:
    void slotActualizarLongitud(QPointF p1, QPointF p2);
    void slotActualizarGeometria();

private:
    QPointF punto1;
    QPointF punto2;
    Sentido sentido;
    qreal distanciaPerp; //Distancia perpendicular al eje entre los dos puntos en que se encuentra la linea de cota
    qreal longitud;      //Longitud entre los puntos
    QFont fuente;
    qreal margin;
    qreal tramoAdicional;

    QRectF bRect;
    QPainterPath pPath;
    qreal anchoRect;

    QString texto;
    qreal anchoTexto;
    qreal altoTexto;
    QPointF posInfIzqTexto;

    const int sizeFlechaRef = 30;
    const int sizeLineaFlechaExt = 80;

    QPen penCota;
    QBrush brushCota;
    QPen penCotaHover;
    QBrush brushCotaHover;

    bool hover;
    bool longitudCorta;
};

#endif // COTAGRAFICA_H
