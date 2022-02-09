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
    snapPuntero = new QGraphicsEllipseItem(QRectF(-6,-6,12,12));
    QPen penPuntero(QBrush("red"),3);
    penPuntero.setCosmetic(true);
    snapPuntero->setPen(penPuntero);
    snapPuntero->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    addItem(snapPuntero);
    snapPuntero->hide();
    connect(vista, &RodajeEdicionVista::sigVistaZoom, this, &RodajeEdicionEscena::slotVistaZoomeada);
    connect(vista, &RodajeEdicionVista::sigMostrarSnapPuntero, this, &RodajeEdicionEscena::slotMostrarSnapPuntero);
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

        elementosPpales.append(addLine(QLineF(p1,p2),penPista));

        float deltaX;
        float deltaY;
        deltaX = p2.x() - p1.x();
        deltaY = p2.y() - p1.y();
        if (p2.x() < p1.x()) {
            deltaX *= -1;
            deltaY *= -1;
        }

        paramRectasPistas.append({deltaY/deltaX,0,qMin(float(p1.x()),float(p2.x())),
                                  qMax(float(p1.x()),float(p2.x()))});
    }
}

void RodajeEdicionEscena::iniciarLinea(QPointF pos)
{
    inicioLineaActiva = pos;
}

void RodajeEdicionEscena::setLineaActiva(QPointF p2)
{
    lineaActiva->setLine(QLineF(inicioLineaActiva,p2));
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

void RodajeEdicionEscena::slotVistaZoomeada()
{
    grilla.verificarEscala();
}

void RodajeEdicionEscena::slotMostrarSnapPuntero(bool mostrar)
{
    snapPuntero->setVisible(mostrar);
}


void RodajeEdicionEscena::proyectarSobrePista(QPointF posCursor)
{
    snapPuntero->show();

    float y1 = posCursor.y();
    float x1 = posCursor.x();
    float m = paramRectasPistas[0][0];
    float a = paramRectasPistas[0][1];
    float xMin = paramRectasPistas[0][2];
    float xMax = paramRectasPistas[0][3];

    float b = y1 + 1/m * x1;
    float x = (b-a)/(m+1/m);
    x = qMin(x,xMax);
    x = qMax(x,xMin);
    float y = (-1/m)*x + b;
    y = qMin(y,xMax*m+a);
    y = qMax(y,xMin*m+a);

    snapPuntero->setPos(x,y);
}

QPointF RodajeEdicionEscena::posSnapPuntero()
{
    return snapPuntero->pos();
}

QPoint RodajeEdicionEscena::calcularPuntoEnParalela(QPointF posCursor)
{
    float m = paramRectasPistas[0][0];
    //float a = paramRectasPistas[0][1];

    //Hay que recalcular a
    float a = lineaActiva->line().p1().y() - m * lineaActiva->line().p1().x();

    float y1 = posCursor.y();
    float x1 = posCursor.x();

    float b = y1 + 1/m * x1;
    float x = (b-a)/(m+1/m);
    float y = (-1/m)*x + b;

    return QPoint(x,y);
}
