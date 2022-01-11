#ifndef EDITORPISTA_H
#define EDITORPISTA_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include <QFloat16>
#include "aeropuertoescena.h"
#include "aeropuertovista.h"

#include "../../estructuras-datos/elementosaerop.h"

//Q_DECLARE_METATYPE(Pista)

class GraficadorAeropuerto : public QObject
{
    Q_OBJECT

public:
    GraficadorAeropuerto(AeropuertoVista* gv);

public slots:
    void actualizarAeropuerto(const Pista&, const Rodaje&, const Rodaje&, const Plataforma&);

private:
    void reportarDatosEscena();

    AeropuertoVista* vistaAeropuerto;
    AeropuertoEscena* escenaAeropuerto;

    QLinearGradient* gradienteFondoPista;
    QBrush* fondoPista;
    QBrush* colorPavimento;
    QBrush* colorMargen;
    QPen* bordeNegro;
    QPen* bordeBlanco;
    QPen* bordeTransparente;
    qint8 fajas;
    double anchoFajasUm;
    double anchoFajasLa;
    double largoEjes;
    double distanciaUmVi;
    double anchoFajasVi;
    double espaciadoFajasVi;
};

#endif // EDITORPISTA_H
