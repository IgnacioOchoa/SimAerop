#ifndef RODAJEEDICIONESCENA_H
#define RODAJEEDICIONESCENA_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsEffect>
#include "rodajeedicionvista.h"
#include "../dibujo/sombralinea.h"
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
    QPoint calcularPuntoEnParalela(QPointF posCursor);
    QPointF calcularPuntoEnPista(int nroPista, QPointF posCursor);
    int pistaMasCercana(QPointF posCursor);
    int pistaSeleccionada() {return pistaActiva;}
    void resaltarPista(QPointF posCursor);

    void seleccionarCabecera(QPointF pos);
    void seleccionarPista();

    void mostrarSnapPuntero(bool mostrar);
    void mostrarCabPuntero(bool mostrar);
    void mostrarSelPista(bool mostrar);
    void permitirSnap(bool permitir);

    QPointF posSnapPuntero() {return snapPista->pos();}
    QPointF posSnapCabecera() {return snapCabecera->pos();};

public slots:

    void slotCentroVistaMovido();
    void slotChckMostrarGrilla(bool);
    void slotMostrarCabeceras(bool);
    void slotVistaZoomeada();

private:
    void prepararSimbolosSnap();
    GrillaGuia grilla;
    bool mostrarGrilla;
    bool permSnap;
    int pistaActiva;
    int pistaResaltada;
    SombraLinea* resaltadoPista;
    SombraLinea* seleccionPista;

    QColor colorAzulClaro = {"#c2f2fc"};
    QColor colorAzulOscuro = {"#74a9b8"};

    QVector<QGraphicsItem*> elementosPpales;
    QVector<QGraphicsTextItem*> textoCabeceras;

    RodajeEdicionVista* vista;
    QGraphicsLineItem* lineaActiva;
    QGraphicsEllipseItem* snapPista;
    QGraphicsRectItem* snapCabecera;
    QGraphicsRectItem* selCabecera;

    QPointF inicioLineaActiva;
    const QList<Pista>& pistas;
    QVector<QVector<double>> paramRectasPistas;  // vector que contiene dx, dy y a, de la ecuacion y = (dy/dx)*x + a
    QVector<QList<QPointF>> extremosPista;
    QVector<QGraphicsRectItem*> vecSeleccionesCabecera;
    QVector<SombraLinea*> vecSeleccionesPista;
};


#endif // RODAJEEDICIONESCENA_H
