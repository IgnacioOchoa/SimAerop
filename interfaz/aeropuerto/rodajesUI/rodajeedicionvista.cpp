#include "rodajeedicionvista.h"

RodajeEdicionVista::RodajeEdicionVista(QWidget* parent) :
    VistaGraficaBase(parent),
    lineaIniciada(false),
    indxPistaSeleccionada(0)
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
            lineaIniciada = true;
            break;
        case modoEdicion::SNAP_CABECERAS:
            escena->seleccionarCabecera(indxPistaSeleccionada,escena->posSnapCabecera());
            emit sigCambiarModo(modoEdicion::PISTA);
            emit sigCabeceraSeleccionada(escena->posSnapCabecera());
            break;
        case modoEdicion::DOSPUNTOS:
            escena->iniciarLinea(mapToScene(pos));
            lineaIniciada = true;
            break;
        case modoEdicion::PARALELA:
            escena->iniciarLinea(mapToScene(pos));
            lineaIniciada = true;
            break;
        case modoEdicion::NULO:
            break;
        }
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
    escena->slotMostrarCabPuntero(m == modoEdicion::SNAP_CABECERAS);
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
        default:
            break;
        }
    }
    else  //lineaIniciada = false
    {
        switch(mEdicion) {
        case modoEdicion::PISTA:
          escena->proyectarSobrePista(mapToScene(pFinal));
          break;
        case modoEdicion::SNAP_CABECERAS:
          escena->proyectarSobreCabecera(mapToScene(pFinal));
          break;
        default:
            break;
        }
    }
    VistaGraficaBase::mouseMoveEvent(event);
}
