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
    void graficarCabeceras();
    void iniciarLinea(QPointF pos);
    void setLineaActiva(QPointF p2);
    void proyectarSobrePista(QPointF posMouse);
    void proyectarSobreCabecera(QPointF posMouse);
    QPointF posSnapPuntero() {return snapPista->pos();}
    QPointF posSnapCabecera() {return snapCabecera->pos();};
    QPoint calcularPuntoEnParalela(QPointF posCursor);
    void seleccionarCabecera(int indicePista, QPointF pos);

public slots:
    void slotCentroVistaMovido();
    void slotChckMostrarGrilla(bool);
    void slotMostrarCabeceras(bool);
    void slotVistaZoomeada();
    void slotMostrarSnapPuntero(bool mostrar);
    void slotMostrarCabPuntero(bool mostrar);

private:
    void prepararSimbolosSnap();
    GrillaGuia grilla;
    bool mostrarGrilla;

    QVector<QGraphicsItem*> elementosPpales;
    QVector<QGraphicsTextItem*> textoCabeceras;

    RodajeEdicionVista* vista;
    QGraphicsLineItem* lineaActiva;
    QGraphicsEllipseItem* snapPista;
    QGraphicsRectItem* snapCabecera;
    QGraphicsRectItem* selCabecera;

    QPointF inicioLineaActiva;
    const QList<Pista>& pistas;
    QVector<QVector<float>> paramRectasPistas;  // vector que contiene dx, dy y a, de la ecuacion y = (dy/dx)*x + a
    QVector<QList<QPointF>> extremosPista;
    QVector<QGraphicsRectItem*> vecSeleccionesCabecera;
};


#endif // RODAJEEDICIONESCENA_H
