#ifndef EDITORPISTA_H
#define EDITORPISTA_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include <QFloat16>

#include "../../estructuras-datos/elementosaerop.h"

//Q_DECLARE_METATYPE(Pista)

class GraficadorAeropuerto : public QObject
{
    Q_OBJECT

public:
    GraficadorAeropuerto(QGraphicsView* gv);

public slots:
    void actualizarPista(const Pista& p);

private:
    void reportarDatosEscena();

    QGraphicsView* vistaPista;
    QGraphicsScene* escenaPista;

    QLinearGradient* gradienteFondoPista;
    QBrush* fondoPista;
    QBrush* colorPista;
    QBrush* colorMargen;
    QPen* bordePista;
    qint8 fajas;
    double anchoFajasUm;
    double anchoFajasLa;
    double largoEjes;
    double distanciaUmVi;
    double anchoFajasVi;
    double espaciadoFajasVi;
};

#endif // EDITORPISTA_H
