#include "rodajeedicionescena.h"

RodajeEdicionEscena::RodajeEdicionEscena(const QList<Pista>& listaPistas, QObject* parent) :
    QGraphicsScene(parent),
    gridCreada(false),
    elementosGridX(NRO_LIN),
    elementosGridY(NRO_LIN),
    pistas(listaPistas),
    lineaActiva(new QGraphicsLineItem)
{
    lineaActiva->setLine(QLine());
    QPen pLineaActiva("orange");
    pLineaActiva.setWidth(3) ; pLineaActiva.setCosmetic(true);
    lineaActiva->setPen(pLineaActiva);
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
        elementosGridX[i]->setLine(0,sceneYmin,0,sceneYmax);
        elementosGridX[i]->setPos(xMenor+i*gridSize, 0);

        elementosGridY[i]->setLine(sceneXmin,0,sceneXmax,0);
        elementosGridY[i]->setPos(0,yMenor+i*gridSize);

    }
    indxXmenor = 0;
    indxYmenor = 0;
}

void RodajeEdicionEscena::graficar()
{
    QPen p("black");
    p.setWidth(3);
    p.setCosmetic(true);
    vista = qobject_cast<RodajeEdicionVista*>(views()[0]);
    graficarPistas();
    vista->actualizarVista();
    vista->centrarVista();
    if (!gridCreada) crearGrid();
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
    qInfo() << "GraficarPistas accedida";
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

void RodajeEdicionEscena::crearGrid()
{
    QPen p(Qt::DashLine);
    p.setColor("#e3d4d3") ; p.setCosmetic(true); p.setWidth(1);
    for(int i=0; i<NRO_LIN; i++) {
        QGraphicsLineItem* itmX = new QGraphicsLineItem;
        QGraphicsLineItem* itmY = new QGraphicsLineItem;
        itmX->setPen(p); itmY->setPen(p);
        addItem(itmX); addItem(itmY);
        itmX->setZValue(-1); itmY->setZValue(-1);
        elementosGridX[i] = itmX;
        elementosGridY[i] = itmY;
    }
    gridCreada = true;
    actualizarGrid();
}

void RodajeEdicionEscena::setLineaActiva(QPointF p1, QPointF p2)
{
    lineaActiva->setLine(QLineF(p1,p2));
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
       xMayor = elementosGridX[indxXmayor]->x();
       // Si me fui mas alla de la zona graficada tengo que actualizar posicion de las lineas
       while((xMayor + gridSize*0.9) < nuevoRect.right())
       {
           indxXmayor = (indxXmayor+1)%NRO_LIN;  // Suma 1 circular
           elementosGridX[indxXmayor]->setPos(xMayor+gridSize,0);
           indxXmenor = (indxXmenor+1)%NRO_LIN; // Suma 1 circular
           xMayor += gridSize;
       }
    }
    else
    {
        //El viewport se movió hacia la izquierda sobre la escena
        xMenor = elementosGridX[indxXmenor]->x();
        while((xMenor - gridSize*0.9) > nuevoRect.left())
        {
            indxXmenor = (indxXmenor + NRO_LIN - 1) % NRO_LIN; // Resta 1 circular
            elementosGridX[indxXmenor]->setPos(xMenor-gridSize,0);
            xMenor -= gridSize;
        }
    }
    if (desplazamiento.y() > 0)
    {
        //El viewport se movió hacia arriba sobre la escena
        int indxYmayor = (indxYmenor + NRO_LIN -1) % NRO_LIN;
        yMayor = elementosGridY[indxYmayor]->y();
        while((yMayor + gridSize*0.9) < nuevoRect.bottom())
        {
            indxYmayor = (indxYmayor+1)%NRO_LIN;  // Suma 1 circular
            elementosGridY[indxYmayor]->setPos(0,yMayor + gridSize);
            indxYmenor = (indxYmenor+1)%NRO_LIN; // Suma 1 circular
            yMayor += gridSize;
        }
    }
    else
    {
        //El viewport se movió hacia abajo sobre la escena
        yMenor = elementosGridY[indxYmenor]->y();
        while((yMenor - gridSize*0.9) > nuevoRect.top())
        {
            indxYmenor = (indxYmenor + NRO_LIN - 1) % NRO_LIN; //Resta 1 circular
            elementosGridY[indxYmenor]->setPos(0,yMenor - gridSize);
            yMenor -= gridSize;
        }
    }
    // El nuevo centro pasa a ser el viejo centro para la siguiente llamada a esta función
    centroVisible = nuevoRect.center();
}

void RodajeEdicionEscena::slotMostrarGrilla(bool mostrar)
{
    if(!gridCreada)
    {
        qobject_cast<RodajeEdicionVista*>(vista)->actualizarVista();
        crearGrid();
    }
    else {
        foreach(QGraphicsLineItem* itm, elementosGridX) itm->setVisible(mostrar);
        foreach(QGraphicsLineItem* itm, elementosGridY) itm->setVisible(mostrar);
    }
}
