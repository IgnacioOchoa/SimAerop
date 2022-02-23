#ifndef PLATAFORMAVISTA_H
#define PLATAFORMAVISTA_H

#include "../vistagraficabase.h"
#include "plataformaescena.h"
#include <QGraphicsItem>
#include <QObject>

class PlataformaEscena;

class PlataformaVista : public VistaGraficaBase
{
    Q_OBJECT
public:
    PlataformaVista(QWidget* parent = nullptr);

    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void wheelEvent(QWheelEvent* event) override;
    void configEscena(QGraphicsScene* es);
    void actualizarVista();

signals:
    void sigVistaZoom();

private:
    PlataformaEscena* escena;
};

#endif // PLATAFORMAVISTA_H
