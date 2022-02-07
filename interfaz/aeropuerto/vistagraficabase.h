#ifndef VISTAGRAFICABASE_H
#define VISTAGRAFICABASE_H

#include <QGraphicsView>
#include <QObject>
#include <QMouseEvent>
#include <QDebug>
#include <QCheckBox>
#include <QPushButton>
#include <QBoxLayout>
#include "../../estructuras-datos/elementosaerop.h"

class VistaGraficaBase : public QGraphicsView
{
    Q_OBJECT
public:
    VistaGraficaBase(QWidget* = nullptr);

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void centrarVista();
    inline void moverAOrigien() {centerOn(0,0); centroVista = {0,0};};

protected:
    void actualizarScRect(QRectF rectElementos = QRectF());
    bool contenidoGraficado;
    int REL_VACIO = 5;
    int SENS_WHEEL = 5; //Recomendado entre 1 y 10

signals:
    void centroMovido();

private:
    QPointF inicioRueda;
    QPointF centroVista;
    QCheckBox* cbActivarCotas;
    QGraphicsScene* escena;
    QPointF centroAnterior;

    QRectF vpRect;

    double minScale;
    double maxScale;

    double vpRectW;
    double vpRectH;

    double sceneWidth;
    double sceneHeight;

    double sceneXmin;
    double sceneYmin;
    double sceneXmax;
    double sceneYmax;
};

#endif // VISTAGRAFICABASE_H
