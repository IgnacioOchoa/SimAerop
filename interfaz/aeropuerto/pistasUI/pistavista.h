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
#include "../../../estructuras-datos/elementosaerop.h"

class PistaVista : public QGraphicsView
{
public:
    PistaVista(QWidget* = nullptr);

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void centrarVista();
    inline void moverAOrigien() {centerOn(0,0); centroVista = {0,0};};

    void graficarPista(Pista p);
    void vaciarContenido();

public slots:
    void chBoxCotasAccionada(int state);

private:
    void actualizarScRect();
    QPointF inicioRueda;
    QPointF centroVista;
    QCheckBox* cbActivarCotas;
    PistaEscena* escena;
    QPointF centroAnterior;

    QRectF vpRect;

    float minScale;
    float maxScale;

    float vpRectW;
    float vpRectH;

    float sceneWidth;
    float sceneHeight;

    double sceneXmin;
    double sceneYmin;
    double sceneXmax;
    double sceneYmax;

    const int REL_VACIO = 5;
    const int SENS_WHEEL = 5; //Recomendado entre 1 y 10
    bool contenidoGraficado;
};

#endif // PISTAVISTA_H
