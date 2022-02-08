#ifndef RODAJEEDICIONESCENA_H
#define RODAJEEDICIONESCENA_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include "rodajeedicionvista.h"
#include "../grillaguia.h"
#include <QtMath>
#include <QDebug>

class RodajeEdicionVista;

class RodajeEdicionEscena : public QGraphicsScene
{
    Q_OBJECT
public:
    RodajeEdicionEscena(RodajeEdicionVista* vista, const QList<Pista>& listaPistas, QObject* parent = nullptr);

    void graficar();
    QRectF brectPpal();
    void graficarPistas();    
    void setLineaActiva(QPointF p1, QPointF p2);
    void inputModoPista(QPointF posMouse);
    QPointF posSnapPuntero();

public slots:
    void slotCentroVistaMovido();
    void slotChckMostrarGrilla(bool);
    void slotVistaZoomeada();
    void slotModoEdicionCambiado(int m);

private:
    GrillaGuia grilla;
    bool mostrarGrilla;

    QVector<QGraphicsItem*> elementosPpales;

    RodajeEdicionVista* vista;
    QGraphicsLineItem* lineaActiva;

    QGraphicsEllipseItem* snapPuntero;

    const QList<Pista>& pistas;

    QVector<QVector<float>> paramRectasPistas;  // vector que contiene m y a, de la ecuacion y = mx + a
};


#endif // RODAJEEDICIONESCENA_H
