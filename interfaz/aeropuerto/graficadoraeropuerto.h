#ifndef EDITORPISTA_H
#define EDITORPISTA_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include <QFloat16>
#include <QtMath>
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
    void actualizarAeropuerto(const QList<Pista>&, const QList<Rodaje>&, const QList<Plataforma>&);

private:
    void reportarDatosEscena();
    void graficarPinturaPista(const Pista&);
    void graficarMargenes(const Pista&);
    qreal largoVector(const QPointF ini, const QPointF fin);
    qreal anguloVector(const QPointF ini, const QPointF fin);
    QPolygonF poligonoVector(const QPointF ini, const QPointF fin, qreal offset);

    AeropuertoVista* vistaAeropuerto;
    AeropuertoEscena* escenaAeropuerto;

    QList<QRectF> listaGraficosPistas;
    QList<QPolygonF> listaGraficosRodajes;
    QList<QPolygonF> listaGraficosPlataformas;

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
