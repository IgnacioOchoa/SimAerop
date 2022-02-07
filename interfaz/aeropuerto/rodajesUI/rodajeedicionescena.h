#ifndef RODAJEEDICIONESCENA_H
#define RODAJEEDICIONESCENA_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "rodajeedicionvista.h"
#include <QtMath>
#include <QDebug>

class RodajeEdicionVista;

class RodajeEdicionEscena : public QGraphicsScene
{
    Q_OBJECT
public:
    RodajeEdicionEscena(const QList<Pista>& listaPistas, QObject* parent = nullptr);
    void actualizarGrid();
    void graficar();
    QRectF brectPpal();
    void graficarPistas();
    void crearGrid();
    void setLineaActiva(QPointF p1, QPointF p2);

public slots:
    void slotCentroVistaMovido();
    void slotMostrarGrilla(bool);

private:
    int gridSize;
    bool gridCreada;
    QVector<QGraphicsLineItem*> elementosGridX;
    QVector<QGraphicsLineItem*> elementosGridY;
    QVector<QGraphicsItem*> elementosPpales;

    RodajeEdicionVista* vista;
    QGraphicsLineItem* lineaActiva;

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
    const QList<Pista>& pistas;
};

#endif // RODAJEEDICIONESCENA_H
