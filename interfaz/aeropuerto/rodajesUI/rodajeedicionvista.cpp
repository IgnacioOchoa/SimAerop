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
    QPoint pos = event->pos();
    if(mEdicion == modoEdicion::PISTA)
    {
        pos = mapFromScene(qobject_cast<RodajeEdicionEscena*>(scene())->posSnapPuntero());
    }
    if (event->button() == Qt::LeftButton)
    {
        if(lineaIniciada == false) {
            lineaIniciada = true;
            puntoInicioLinea = pos;
        }
        else {
            lineaIniciada = false;
        }
    }

    VistaGraficaBase::mousePressEvent(event);
}

void RodajeEdicionVista::wheelEvent(QWheelEvent *event)
{
    emit sigVistaZoom();
    VistaGraficaBase::wheelEvent(event);
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
    if(lineaIniciada) {
        QPoint pFinal = event->pos();
        qobject_cast<RodajeEdicionEscena*>(scene())->setLineaActiva(mapToScene(puntoInicioLinea),
                                                                    mapToScene(pFinal));
    }
    else if(mEdicion == modoEdicion::PISTA)
    {
        // Hacer algo con la escena
        qobject_cast<RodajeEdicionEscena*>(scene())->inputModoPista(mapToScene(event->pos()));
    }
    VistaGraficaBase::mouseMoveEvent(event);
}
