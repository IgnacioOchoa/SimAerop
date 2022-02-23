#include "plataformavista.h"

PlataformaVista::PlataformaVista(QWidget* parent) :
    VistaGraficaBase(parent)
{
    setCursor(Qt::CrossCursor);
}

void PlataformaVista::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    if(contenidoGraficado) actualizarVista();
}

void PlataformaVista::wheelEvent(QWheelEvent *event)
{
    emit sigVistaZoom();
    VistaGraficaBase::wheelEvent(event);
}

void PlataformaVista::configEscena(QGraphicsScene* es)
{
    setScene(es);
    escena = qobject_cast<PlataformaEscena*>(scene());
}


void PlataformaVista::actualizarVista()
{
    if(!scene()) qInfo() << "scene() no es valido";
    if(scene()->items().size() > 0) contenidoGraficado = true;
    actualizarScRect(qobject_cast<PlataformaEscena*>(scene())->brectPpal());
    centerOn(0,0);
}
