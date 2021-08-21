#ifndef VISTACONFPISTA_H
#define VISTACONFPISTA_H

#include <QGraphicsView>
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QCheckBox>
#include <QBoxLayout>
#include "escenaconfpista.h"
#include "../../estructuras-datos/elementosaerop.h"

class VistaConfPista : public QGraphicsView
{
public:
    VistaConfPista(QWidget* = nullptr);

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;

    void centrarVista(QPointF p = QPointF());
    void ajustarContenidos();

    void graficarPista(Pista p);
    void vaciarContenido();

public slots:
    void chBoxCotasAccionada(int state);

private:
    QPointF inicioRueda;
    QPointF centroVista;
    QCheckBox* cbActivarCotas;
    EscenaConfPista* escena;
    QPointF centroAnterior;
    qreal escala;
};

#endif // VISTACONFPISTA_H
