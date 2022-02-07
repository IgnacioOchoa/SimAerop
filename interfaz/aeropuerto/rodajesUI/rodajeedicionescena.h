#ifndef RODAJEEDICIONESCENA_H
#define RODAJEEDICIONESCENA_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
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

public slots:
    void slotCentroVistaMovido();
    void slotChckMostrarGrilla(bool);

private:
    GrillaGuia grilla;
    bool mostrarGrilla;

    QVector<QGraphicsItem*> elementosPpales;

    RodajeEdicionVista* vista;
    QGraphicsLineItem* lineaActiva;

    const QList<Pista>& pistas;
};

#endif // RODAJEEDICIONESCENA_H
