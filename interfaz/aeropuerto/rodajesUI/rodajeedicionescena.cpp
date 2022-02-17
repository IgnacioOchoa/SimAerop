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

        //Calcular deltaX y deltaY de la pista para luego calcular la pendiente
        float deltaX;
        float deltaY;
        deltaX = p2.x() - p1.x();
        deltaY = p2.y() - p1.y();
        if (p2.x() < p1.x()) {
            deltaX *= -1;
            deltaY *= -1;
        }
        if (deltaX < 1e-4f) deltaX = 0;
        float min;
        float max;

        if(deltaX != 0) { //Linea no vertical
        min = qMin(float(p1.x()),float(p2.x()));
        max = qMax(float(p1.x()),float(p2.x()));
        }
        else {  //Linea vertical
        min = qMin(float(p1.y()),float(p2.y()));
        max = qMax(float(p1.y()),float(p2.y()));
        }
        //Guardar pendiente, ordenada al origen, punto inicio y punto final de la pista
        paramRectasPistas.append({deltaX, deltaY, 0, min, max});
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
    float dx = paramRectasPistas[0][0];
    float dy = paramRectasPistas[0][1];
    float a = paramRectasPistas[0][2];
    float min = paramRectasPistas[0][3];
    float max = paramRectasPistas[0][4];

    float x;
    float y;

    if(dy == 0) {   // Recta horizontal
        x = x1;
        y = a;
        x = qMin(x,max);
        x = qMax(x,min);
    }
    else if (dx == 0) { //Recta vertical
        y = y1;
        x = 0; //Esto hay que actualizarlo cuando se implementen pistas que no pasen por 0
        y = qMin(y,max);
        y = qMax(y,min);
    }
    else {
        float m = dy/dx;
        float b = y1 + 1/m * x1;
        x = (b-a)/(m+1/m);
        x = qMin(x,max);
        x = qMax(x,min);
        y = (-1/m)*x + b;
        y = qMin(y,max*m+a);
        y = qMax(y,min*m+a);
    }

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
