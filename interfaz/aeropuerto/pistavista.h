#ifndef PISTAVISTA_H
#define PISTAVISTA_H

#include <QGraphicsView>
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QCheckBox>
#include <QPushButton>
#include <QBoxLayout>
#include "pistaescena.h"
#include "../../estructuras-datos/elementosaerop.h"

class PistaVista : public QGraphicsView
{
public:
    PistaVista(QWidget* = nullptr);

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
    PistaEscena* escena;
    QPointF centroAnterior;
    qreal escala;
};

#endif // PISTAVISTA_H
