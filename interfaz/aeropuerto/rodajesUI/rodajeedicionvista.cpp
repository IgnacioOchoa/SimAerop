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
    if (event->button() == Qt::LeftButton && lineaIniciada==false) {
        switch(mEdicion) {
        case modoEdicion::PISTA:
            escena->iniciarLinea(escena->posSnapPuntero());
            break;
        case modoEdicion::DOSPUNTOS:
            escena->iniciarLinea(mapToScene(pos));
            break;
        case modoEdicion::PARALELA:
            escena->iniciarLinea(mapToScene(pos));
            break;
        case modoEdicion::NULO:
            break;
        }
        lineaIniciada = true;
    }
    else if (event->button() == Qt::LeftButton && lineaIniciada==true)
    {
        lineaIniciada = false;
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
    escena = qobject_cast<RodajeEdicionEscena*>(scene());
    connect(this, &VistaGraficaBase::centroMovido, qobject_cast<RodajeEdicionEscena*>(es), &RodajeEdicionEscena::slotCentroVistaMovido);
}

void RodajeEdicionVista::actualizarVista()
{
    if(!scene()) qInfo() << "scene() no es valido";
    if(scene()->items().size() > 0) contenidoGraficado = true;
    actualizarScRect(qobject_cast<RodajeEdicionEscena*>(scene())->brectPpal());
    centerOn(0,0);
}

void RodajeEdicionVista::slotSetModEdicion(int m)
{
    mEdicion = static_cast<RodajeEdicionVista::modoEdicion>(m);
    escena->slotMostrarSnapPuntero(m == modoEdicion::PISTA);
}

void RodajeEdicionVista::mouseMoveEvent(QMouseEvent* event)
{
    QPoint pFinal = event->pos();
    if (lineaIniciada) {
      switch(mEdicion) {
        case modoEdicion::PISTA:
            escena->setLineaActiva(mapToScene(pFinal));
            break;
        case modoEdicion::DOSPUNTOS:
            escena->setLineaActiva(mapToScene(pFinal));
            break;
        case modoEdicion::PARALELA:
            escena->setLineaActiva(escena->calcularPuntoEnParalela(mapToScene(pFinal)));
            break;
        case modoEdicion::NULO:
            break;
        }
    }
    else  //lineaIniciada != true
    {
        switch(mEdicion) {
        case modoEdicion::PISTA:
            escena->proyectarSobrePista(mapToScene(pFinal));
            break;
        default:
            break;
        }
    }
    VistaGraficaBase::mouseMoveEvent(event);
}
