#ifndef RODAJEEDICIONESCENA_H
#define RODAJEEDICIONESCENA_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QtMath>
#include <QDebug>

class RodajeEdicionEscena : public QGraphicsScene
{
    Q_OBJECT
public:
    RodajeEdicionEscena(QObject* parent = nullptr);
    void actualizarGrid();
    void graficar();
    QRectF brectPpal();

private:
    int gridSize;
    QVector<QGraphicsLineItem*> elementosGridX;
    QVector<QGraphicsLineItem*> elementosGridY;
    QVector<QGraphicsItem*> elementosPpales;
};

#endif // RODAJEEDICIONESCENA_H
