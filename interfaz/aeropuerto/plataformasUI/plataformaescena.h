#ifndef PLATAFORMAESCENA_H
#define PLATAFORMAESCENA_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include "plataformavista.h"
#include <QtMath>
#include <QDebug>

class PlataformaVista;

class PlataformaEscena : public QGraphicsScene
{
    Q_OBJECT
public:
    PlataformaEscena(PlataformaVista* vista, const QList<Pista>& listaPistas, QObject* parent = nullptr);

    void graficar();
    QRectF brectPpal();
    void graficarPistas();
    void limpiarEscena();

private:
    QVector<QGraphicsItem*> elementosPpales;
    QVector<QGraphicsTextItem*> textoCabeceras;

    PlataformaVista* vista;
    const QList<Pista>& pistas;
    QVector<QVector<float>> paramRectasPistas;  // vector que contiene dx, dy y a, de la ecuacion y = (dy/dx)*x + a
    QVector<QList<QPointF>> extremosPista;
};

#endif // PLATAFORMAESCENA_H
