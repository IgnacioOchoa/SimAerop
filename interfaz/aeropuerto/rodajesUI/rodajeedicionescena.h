#ifndef RODAJEEDICIONESCENA_H
#define RODAJEEDICIONESCENA_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "RodajeEdicionVista.h"
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

public slots:
    void slotCentroVistaMovido();
    void slotMostrarGrilla(bool);

private:
    int gridSize;
    bool gridCreada;
    QVector<QGraphicsLineItem*> elementosGridX;
    QVector<QGraphicsLineItem*> elementosGridY;
    QVector<QGraphicsItem*> elementosPpales;

    QGraphicsView* vista;

    static constexpr int NRO_LIN = 14;
    int xMayor;
    int yMayor;
    int xMenor;
    int yMenor;
    int indxXmenor;
    int indxYmenor;

    float sceneXmin;
    float sceneYmin;
    float sceneXmax;
    float sceneYmax;

    QPointF centroVisible;
};

#endif // RODAJEEDICIONESCENA_H
