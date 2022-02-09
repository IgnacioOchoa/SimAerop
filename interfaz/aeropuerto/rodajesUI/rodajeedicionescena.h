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
    void iniciarLinea(QPointF pos);
    void setLineaActiva(QPointF p2);
    void proyectarSobrePista(QPointF posMouse);
    QPointF posSnapPuntero();
    QPoint calcularPuntoEnParalela(QPointF posCursor);

public slots:
    void slotCentroVistaMovido();
    void slotChckMostrarGrilla(bool);
    void slotVistaZoomeada();
    void slotMostrarSnapPuntero(bool mostrar);

private:
    GrillaGuia grilla;
    bool mostrarGrilla;

    QVector<QGraphicsItem*> elementosPpales;

    RodajeEdicionVista* vista;
    QGraphicsLineItem* lineaActiva;
    QGraphicsEllipseItem* snapPuntero;
    QPointF inicioLineaActiva;
    const QList<Pista>& pistas;
    QVector<QVector<float>> paramRectasPistas;  // vector que contiene m y a, de la ecuacion y = mx + a
};


#endif // RODAJEEDICIONESCENA_H
