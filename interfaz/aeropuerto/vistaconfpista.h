#ifndef VISTACONFPISTA_H
#define VISTACONFPISTA_H

#include <QGraphicsView>
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QCheckBox>
#include <QBoxLayout>
#include "escenaconfpista.h"

class VistaConfPista : public QGraphicsView
{
public:
    VistaConfPista(QWidget* = nullptr);

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;

    void centrarVista(QPointF p = QPointF());
    void ajustarContenidos();

    void graficarPista(QRectF rectPista);
    void vaciarContenido();

public slots:
    void contenidoCambiado();

private:
    QPointF inicioRueda;
    QPointF centroVista;
    QCheckBox* cbActivarCotas;
    EscenaConfPista* escena;
};

#endif // VISTACONFPISTA_H
