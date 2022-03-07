#include "rodajeedicionvista.h"

RodajeEdicionVista::RodajeEdicionVista(QWidget* parent) :
    VistaGraficaBase(parent),
    lineaIniciada(false),
    indxPistaSeleccionada(0)
{
    setCursor(Qt::CrossCursor);
    mSnapAnterior = modoSnap::PTOPISTA;
    mSnap = modoSnap::PTOPISTA;
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
                escena->seleccionarCabecera(indxPistaSeleccionada,escena->posSnapCabecera());
                emit sigCabeceraSeleccionada(escena->posSnapCabecera());
                break;
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
}

void RodajeEdicionVista::actualizarVista()
{
    if(!scene()) qInfo() << "scene() no es valido";
    if(scene()->items().size() > 0) contenidoGraficado = true;
    actualizarScRect(qobject_cast<RodajeEdicionEscena*>(scene())->brectPpal());
    centerOn(0,0);
}

void RodajeEdicionVista::slotSetModEdicion(modoEdicion m)
{
    mEdicion = m;
}

void RodajeEdicionVista::slotSetModSnap(modoSnap m)
{
//    QString ms;
//    switch(m) {
//    case modoSnap::CABECERAS: {ms = "CABECERAS"; break;}
//    case modoSnap::PISTA: {ms = "PISTA"; break;}
//    case modoSnap::PTOPISTA: {ms = "PTOPISTA"; break;}
//    case modoSnap::NULO: {ms = "NULO"; break;}
//    }
//    qInfo() << "Modo snap: " << ms;

    mSnapAnterior = mSnap;
    mSnap = m;

    if (mEdicion == modoEdicion::PISTA)
    {
        switch(mSnap) {
        case(modoSnap::CABECERAS):
            escena->mostrarCabPuntero(true);
            escena->mostrarSnapPuntero(false);
            break;
        case(modoSnap::PTOPISTA):
            escena->mostrarCabPuntero(false);
            escena->mostrarSnapPuntero(true);
            break;
        case(modoSnap::PISTA):
            escena->mostrarCabPuntero(false);
            escena->mostrarSnapPuntero(false);
            break;
        case(modoSnap::NULO):
            escena->mostrarCabPuntero(false);
            escena->mostrarSnapPuntero(false);
            break;
        default:
            break;
        }
    }
}

void RodajeEdicionVista::guardarModoSnap(modoSnap m)
{
    mSnapAnterior = m;
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
          escena->resaltarPista(escena->pistaMasCercana(pFinal));
          break;
        default:
          break;
        }
    }
    VistaGraficaBase::mouseMoveEvent(event);
}

void RodajeEdicionVista::enterEvent(QEvent *ev)
{
    slotSetModSnap(mSnapAnterior);
    QAbstractScrollArea::enterEvent(ev);
}

void RodajeEdicionVista::leaveEvent(QEvent *ev)
{
    slotSetModSnap(modoSnap::NULO);
    QAbstractScrollArea::leaveEvent(ev);
}
