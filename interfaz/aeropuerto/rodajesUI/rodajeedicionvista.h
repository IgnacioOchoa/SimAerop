#ifndef RODAJEEDICIONVISTA_H
#define RODAJEEDICIONVISTA_H

#include "../vistagraficabase.h"
#include <QObject>

class RodajeEdicionVista : public VistaGraficaBase
{
public:
    RodajeEdicionVista(QWidget* parent = nullptr);    
    virtual void resizeEvent(QResizeEvent *event) override;

    friend class RodajeEdicionDialogo;
};

#endif // RODAJEEDICIONVISTA_H
