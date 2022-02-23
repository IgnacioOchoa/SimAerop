#include "plataformaescena.h"

PlataformaEscena::PlataformaEscena(PlataformaVista* v, const QList<Pista>& listaPistas, QObject* parent) :
    QGraphicsScene(parent),
    vista(v),
    pistas(listaPistas)
{

}

void PlataformaEscena::graficar()
{
    QPen p("black");
    p.setWidth(3);
    p.setCosmetic(true);
    graficarPistas();
    vista->actualizarVista();
    vista->centrarVista();
}

QRectF PlataformaEscena::brectPpal()
{
    QRectF rectangulo;
    foreach(QGraphicsItem* itm, elementosPpales)
    {
        rectangulo = rectangulo.united(itm->boundingRect());
    }
    return rectangulo;
}

void PlataformaEscena::graficarPistas()
{
    QPen penPista("black");
    penPista.setWidth(5);
    penPista.setCosmetic(true);
    penPista.setCapStyle(Qt::RoundCap);

    foreach(Pista p, pistas)
    {
        QPointF p1 = p.getPuntoCabecera(Pista::CAB1);
        QPointF p2 = p.getPuntoCabecera(Pista::CAB2);
        elementosPpales.append(addLine(QLineF(p1,p2),penPista));
    }
}

void PlataformaEscena::limpiarEscena()
{
    clear();
    elementosPpales.clear();
}
