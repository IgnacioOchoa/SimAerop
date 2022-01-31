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
#include "../vistagraficabase.h"
#include "../../../estructuras-datos/elementosaerop.h"

class PistaVista : public VistaGraficaBase
{
public:
    PistaVista(QWidget* = nullptr);
    void graficarPista(Pista p);
    void borrar();

public slots:
    void chBoxCotasAccionada(int state);

private:
    QCheckBox* cbActivarCotas;
    PistaEscena* escena;
};

#endif // PISTAVISTA_H
