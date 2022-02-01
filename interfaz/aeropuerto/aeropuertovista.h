#ifndef AEROPUERTOVISTA_H
#define AEROPUERTOVISTA_H

#include <QObject>
#include <QGraphicsView>
#include <QDebug>
#include <QWheelEvent>
#include "vistagraficabase.h"

class AeropuertoVista : public VistaGraficaBase
{
    Q_OBJECT
public:
    AeropuertoVista(QWidget* w = nullptr);
    void actualizarEntorno() {actualizarScRect();};
};

#endif // AEROPUERTOVISTA_H
