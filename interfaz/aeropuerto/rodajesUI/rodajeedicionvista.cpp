#include "rodajeedicionvista.h"

RodajeEdicionVista::RodajeEdicionVista(QWidget* parent) :
    VistaGraficaBase(parent),
    lineaIniciada(false)
{
    setCursor(Qt::CrossCursor);
    mSnap = modoSnap::NULO;
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
            switch(mSnap) {
            case modoSnap::PTOPISTA:
                escena->iniciarLinea(escena->posSnapPuntero());
                lineaIniciada = true;
                break;
            case modoSnap::CABECERAS:
                escena->seleccionarCabecera(escena->posSnapCabecera());
                emit sigCabeceraSeleccionada(escena->posSnapCabecera());
                mSnap = modoSnap::NULO;
                actualizarSnapEscena();
                break;
            case modoSnap::PISTA:
                escena->seleccionarPista();
                mSnap = modoSnap::NULO;
                actualizarSnapEscena();
                emit sigPistaSeleccionada(escena->pistaSeleccionada());
            default:
                break;
            }
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
    escena->seleccionarPista();
}

void RodajeEdicionVista::actualizarVista()
{
    if(!scene()) qInfo() << "scene() no es valido";
    if(scene()->items().size() > 0) contenidoGraficado = true;
    actualizarScRect(qobject_cast<RodajeEdicionEscena*>(scene())->brectPpal());
    centerOn(0,0);
}

void RodajeEdicionVista::actualizarSnapEscena()
{
    if (mEdicion == modoEdicion::PISTA)
    {
        switch(mSnap) {
        case(modoSnap::CABECERAS):
            escena->mostrarCabPuntero(true);
            escena->mostrarSnapPuntero(false);
            escena->mostrarSelPista(false);
            break;
        case(modoSnap::PTOPISTA):
            escena->mostrarCabPuntero(false);
            escena->mostrarSnapPuntero(true);
            escena->mostrarSelPista(false);
            break;
        case(modoSnap::PISTA):
            escena->mostrarCabPuntero(false);
            escena->mostrarSnapPuntero(false);
            escena->mostrarSelPista(true);
            break;
        case(modoSnap::NULO):
            escena->mostrarCabPuntero(false);
            escena->mostrarSnapPuntero(false);
            escena->mostrarSelPista(false);
            break;
        default:
            break;
        }
    }
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
        switch(mSnap) {
        case modoSnap::PTOPISTA:
          escena->proyectarSobrePista(mapToScene(pFinal));
          break;
        case modoSnap::CABECERAS:
          escena->proyectarSobreCabecera(mapToScene(pFinal));
          break;
        case modoSnap::PISTA:
          escena->resaltarPista(mapToScene(pFinal));
          break;
        default:
          break;
        }
    }
    VistaGraficaBase::mouseMoveEvent(event);
}

void RodajeEdicionVista::enterEvent(QEvent *ev)
{
    escena->permitirSnap(true);
    actualizarSnapEscena();
    QAbstractScrollArea::enterEvent(ev);
}

void RodajeEdicionVista::leaveEvent(QEvent *ev)
{
    escena->permitirSnap(false);
    actualizarSnapEscena();
    QAbstractScrollArea::leaveEvent(ev);
}
