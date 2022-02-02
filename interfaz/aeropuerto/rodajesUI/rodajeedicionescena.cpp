#include "rodajeedicionescena.h"

RodajeEdicionEscena::RodajeEdicionEscena(QObject* parent) :
    QGraphicsScene(parent),
    elementosGridX(60),
    elementosGridY(60)
{
    QPen p(Qt::DashLine);
    for(int i=0; i<elementosGridX.size(); i++) elementosGridX[i] = new QGraphicsLineItem;
    for(int i=0; i<elementosGridY.size(); i++) elementosGridY[i] = new QGraphicsLineItem;
    p.setColor("#e3d4d3") ; p.setCosmetic(true); p.setWidth(1);
    foreach(QGraphicsLineItem* itm, elementosGridX)
    {
        itm->setPen(p);
        addItem(itm);
    }
    foreach(QGraphicsLineItem* itm, elementosGridY)
    {
        itm->setPen(p);
        addItem(itm);
    }
}

void RodajeEdicionEscena::actualizarGrid()
{
    QGraphicsView* v = views()[0];
    QRectF rVisible = v->mapToScene(v->viewport()->rect()).boundingRect();
    float w = rVisible.width();
    float h = rVisible.height();

    if (w <= 20) gridSize = 1;
    else if (w > 20 && w <= 200) gridSize = 10;
    else if (w > 200 && w <= 2000) gridSize = 100;
    else if (w > 2000) gridSize = 1000;

//    float sceneXmin = sceneRect().x();
//    float sceneYmin = sceneRect().y();
//    float sceneXmax = sceneRect().x() + sceneRect().width();
//    float sceneYmax = sceneRect().y() + sceneRect().height();

    float visibleXmin = rVisible.x();
    float visibleYmin = rVisible.y();
    float visibleXmax = visibleXmin + w;
    float visibleYmax = visibleYmin + h;

    if(w > h) {}

    int posXinicial = qFloor(visibleXmin/gridSize) * gridSize;
    int posXfinal = qCeil(visibleXmax/gridSize) * gridSize;
    int posYinicial = qFloor(visibleYmin/gridSize) * gridSize;
    int posYfinal = qCeil(visibleYmax/gridSize) * gridSize;

    int indx = 0;
    for(int i = posXinicial; i <= posXfinal; i += gridSize)
    {
        elementosGridX[indx]->setLine(i,posYinicial,i,posYfinal);
        indx++;
    }
    indx = 0;
    for(int i = posYinicial; i <= posYfinal; i += gridSize)
    {
       elementosGridY[indx]->setLine(posXinicial,i,posXfinal,i);
       indx++;
    }
}

void RodajeEdicionEscena::graficar()
{
    QPen p("black");
    p.setWidth(3);
    p.setCosmetic(true);
    QGraphicsItem* gr = qgraphicsitem_cast<QGraphicsItem*>(addRect(QRectF(-100,-100,200,200), p));
    elementosPpales.append(gr);
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
