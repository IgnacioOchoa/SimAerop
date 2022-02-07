#include "rodajeedicionvista.h"

RodajeEdicionVista::RodajeEdicionVista(QWidget* parent) :
    VistaGraficaBase(parent),
    lineaIniciada(false)
{
    setCursor(Qt::CrossCursor);
}

void RodajeEdicionVista::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    if(contenidoGraficado) actualizarVista();
}

void RodajeEdicionVista::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(lineaIniciada == false) {
            lineaIniciada = true;
            puntoInicioLinea = event->pos();
        }
        else {
            lineaIniciada = false;
        }
    }

    VistaGraficaBase::mousePressEvent(event);
}

void RodajeEdicionVista::configEscena(QGraphicsScene* es)
{
    setScene(es);
    connect(this, &VistaGraficaBase::centroMovido, qobject_cast<RodajeEdicionEscena*>(es), &RodajeEdicionEscena::slotCentroVistaMovido);
}

void RodajeEdicionVista::actualizarVista()
{
    if(!scene()) qInfo() << "scene() no es valido";
    if(scene()->items().size() > 0) contenidoGraficado = true;
    actualizarScRect(qobject_cast<RodajeEdicionEscena*>(scene())->brectPpal());
    centerOn(0,0);
}

void RodajeEdicionVista::mouseMoveEvent(QMouseEvent* event)
{
    if(event->modifiers() == Qt::ShiftModifier) lineaIniciada = false;
    else if(lineaIniciada) {
        QPoint pFinal = event->pos();
        qobject_cast<RodajeEdicionEscena*>(scene())->setLineaActiva(mapToScene(puntoInicioLinea),
                                                                    mapToScene(pFinal));
    }
    VistaGraficaBase::mouseMoveEvent(event);
}
