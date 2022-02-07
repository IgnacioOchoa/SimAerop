#include "rodajeedicionescena.h"

RodajeEdicionEscena::RodajeEdicionEscena(RodajeEdicionVista* v, const QList<Pista>& listaPistas, QObject* parent) :
    QGraphicsScene(parent),
    grilla(v,this),
    mostrarGrilla(false),
    vista(v),
    lineaActiva(new QGraphicsLineItem),
    pistas(listaPistas)
{
    lineaActiva->setLine(QLine());
    QPen pLineaActiva("orange");
    pLineaActiva.setWidth(3) ; pLineaActiva.setCosmetic(true);
    lineaActiva->setPen(pLineaActiva);
}

void RodajeEdicionEscena::graficar()
{
    QPen p("black");
    p.setWidth(3);
    p.setCosmetic(true);
    graficarPistas();
    vista->actualizarVista();
    vista->centrarVista();
    grilla.crearGrid();
    grilla.mostrarGrilla(mostrarGrilla);
    addItem(lineaActiva);
}

QRectF RodajeEdicionEscena::brectPpal()
{
    QRectF rectangulo;
    foreach(QGraphicsItem* itm, elementosPpales)
    {
        rectangulo = rectangulo.united(itm->boundingRect());
    }
    return rectangulo;
}

void RodajeEdicionEscena::graficarPistas()
{
    QPen penPista("black");
    penPista.setWidth(5);
    penPista.setCosmetic(true);
    penPista.setCapStyle(Qt::RoundCap);

    foreach(Pista p, pistas)
    {
        QPointF p1(p.largo/2.0*qCos(qDegreesToRadians(float(p.orientacion))),
                   p.largo/2.0*qSin(qDegreesToRadians(float(p.orientacion))));

        QPointF p2(-p.largo/2.0*qCos(qDegreesToRadians(float(p.orientacion))),
                   -p.largo/2.0*qSin(qDegreesToRadians(float(p.orientacion))));

        elementosPpales.append(addLine(QLineF(p1,p2 ),penPista));
    }
}

void RodajeEdicionEscena::setLineaActiva(QPointF p1, QPointF p2)
{
    lineaActiva->setLine(QLineF(p1,p2));
}

void RodajeEdicionEscena::slotCentroVistaMovido()
{
    grilla.centroMovido();
}

void RodajeEdicionEscena::slotChckMostrarGrilla(bool mostrar)
{
    mostrarGrilla = mostrar;
    grilla.mostrarGrilla(mostrar);
}
