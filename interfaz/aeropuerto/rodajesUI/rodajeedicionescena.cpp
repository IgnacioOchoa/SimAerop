#include "rodajeedicionescena.h"

RodajeEdicionEscena::RodajeEdicionEscena(QObject* parent) :
    QGraphicsScene(parent),
    elementosGridX(NRO_LIN),
    elementosGridY(NRO_LIN)
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
    centroVisible = rVisible.center();
    float w = rVisible.width();
    float h = rVisible.height();

    float d = w > h ? w : h;

    if (d <= 20) gridSize = 1;
    else if (d > 20 && w <= 200) gridSize = 10;
    else if (d > 200 && w <= 2000) gridSize = 100;
    else if (d > 2000) gridSize = 1000;

    sceneXmin = sceneRect().x();
    sceneYmin = sceneRect().y();
    sceneXmax = sceneRect().x() + sceneRect().width();
    sceneYmax = sceneRect().y() + sceneRect().height();

    //Busco las lineas en x e y redondos mas cerca del centro
    int xProximo = qRound(centroVisible.x()/gridSize)*gridSize;
    int yProximo = qRound(centroVisible.y()/gridSize)*gridSize;

    //Calculo la posicion de x e y de la primera linea
    xMenor = xProximo - qFloor(NRO_LIN/2)*gridSize;
    yMenor = yProximo - qFloor(NRO_LIN/2)*gridSize;

    //A partir de ese valor calculado calculo y guardo el resto de las lineas`
    for(int i = 0; i < NRO_LIN; i++)
    {
        elementosGridX[i]->setLine(xMenor+i*gridSize,
                                   sceneYmin,
                                   xMenor+i*gridSize,
                                   sceneYmax);
        elementosGridY[i]->setLine(sceneXmin,
                                   yMenor+i*gridSize,
                                   sceneXmax,
                                   yMenor+i*gridSize);
    }
    indxXmenor = 0;
    indxYmenor = 0;
}

void RodajeEdicionEscena::graficar()
{
    QPen p("black");
    p.setWidth(3);
    p.setCosmetic(true);
    QGraphicsItem* gr = qgraphicsitem_cast<QGraphicsItem*>(addRect(QRectF(-100,-100,200,200), p));
    elementosPpales.append(gr);
    vista = views()[0];
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

void RodajeEdicionEscena::slotCentroVistaMovido()
{
    // Calculo donde está el viewport después de moverse
    QRectF nuevoRect = vista->mapToScene(vista->viewport()->rect()).boundingRect();
    QPointF desplazamiento = nuevoRect.center() - centroVisible;
    //En función de la direccción de desplazamiento actualizo el lado correspondiente de la grilla
    if (desplazamiento.x() > 0)
    {
       //El viewport se movió hacia la derecha sobre la escena
       //Mirar cual elemento en el vector es el que tiene la linea vertical con X mas grande
       int indxXmayor = (indxXmenor + NRO_LIN - 1) % NRO_LIN; //Restar 1 circular
       xMayor = elementosGridX[indxXmayor]->line().p1().x();
       // Si me fui mas alla de la zona graficada tengo que actualizar posicion de las lineas
       while((xMayor + gridSize*0.9) < nuevoRect.right())
       {
           indxXmayor = (indxXmayor+1)%NRO_LIN;  // Suma 1 circular
           elementosGridX[indxXmayor]->setLine(xMayor+gridSize,
                                              sceneYmin,
                                              xMayor+gridSize,
                                              sceneYmax);
           indxXmenor = (indxXmenor+1)%NRO_LIN; // Suma 1 circular
           xMayor += gridSize;
       }
    }
    else
    {
        //El viewport se movió hacia la izquierda sobre la escena
        xMenor = elementosGridX[indxXmenor]->line().p1().x();
        while((xMenor - gridSize*0.9) > nuevoRect.left())
        {
            indxXmenor = (indxXmenor + NRO_LIN - 1) % NRO_LIN; // Resta 1 circular
            elementosGridX[indxXmenor]->setLine(xMenor-gridSize,
                                                sceneYmin,
                                                xMenor-gridSize,
                                                sceneYmax);
            xMenor -= gridSize;
        }
    }
    if (desplazamiento.y() > 0)
    {
        //El viewport se movió hacia arriba sobre la escena
        int indxYmayor = (indxYmenor + NRO_LIN -1) % NRO_LIN;
        yMayor = elementosGridY[indxYmayor]->line().p1().y();
        while((yMayor + gridSize*0.9) < nuevoRect.bottom())
        {
            indxYmayor = (indxYmayor+1)%NRO_LIN;  // Suma 1 circular
            elementosGridY[indxYmayor]->setLine(sceneXmin,
                                                yMayor + gridSize,
                                                sceneXmax,
                                                yMayor + gridSize);
            indxYmenor = (indxYmenor+1)%NRO_LIN; // Suma 1 circular
            yMayor += gridSize;
        }
    }
    else
    {
        //El viewport se movió hacia abajo sobre la escena
        yMenor = elementosGridY[indxYmenor]->line().p1().y();
        while((yMenor - gridSize*0.9) > nuevoRect.top())
        {
            indxYmenor = (indxYmenor + NRO_LIN - 1) % NRO_LIN; //Resta 1 circular
            elementosGridY[indxYmenor]->setLine(sceneXmin,
                                                yMenor - gridSize,
                                                sceneXmax,
                                                yMenor - gridSize);
            yMenor -= gridSize;
        }
    }
    // El nuevo centro pasa a ser el viejo centro para la siguiente llamada a esta función
    centroVisible = nuevoRect.center();
}
