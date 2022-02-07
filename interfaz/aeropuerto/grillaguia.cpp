#include "grillaguia.h"

GrillaGuia::GrillaGuia(QGraphicsView* vw, QGraphicsScene* gs, QObject* parent) :
    QObject(parent),
    escena(gs),
    vista(vw),
    grillaCreada(false),
    elementosGridX(NRO_LIN),
    elementosGridY(NRO_LIN)
{
    penGrilla.setWidth(1);
    penGrilla.setStyle(Qt::DashLine);
    penGrilla.setColor("#fae1bb");
    penGrilla.setCosmetic(true);
}

void GrillaGuia::crearGrid()
{
    if (grillaCreada) return;
    for(int i=0; i<NRO_LIN; i++) {
        QGraphicsLineItem* itmX = new QGraphicsLineItem;
        QGraphicsLineItem* itmY = new QGraphicsLineItem;
        itmX->setPen(penGrilla); itmY->setPen(penGrilla);
        escena->addItem(itmX); escena->addItem(itmY);
        itmX->setZValue(-1); itmY->setZValue(-1);
        elementosGridX[i] = itmX;
        elementosGridY[i] = itmY;
    }
    centroVisible = QPointF();
    grillaCreada = true;
    actualizarGrid();
}

void GrillaGuia::actualizarGrid()
{
    if(!vista) {qInfo() << "No hay una vista asociada a la grilla"; return;}
    QRectF rVisible = vista->mapToScene(vista->viewport()->rect()).boundingRect();
    centroVisible = rVisible.center();
    float w = rVisible.width();
    float h = rVisible.height();
    float d = w > h ? w : h;

    if (d <= 20) gridSize = 1;
    else if (d > 20 && w <= 200) gridSize = 10;
    else if (d > 200 && w <= 2000) gridSize = 100;
    else if (d > 2000) gridSize = 1000;

    sceneXmin = escena->sceneRect().left();
    sceneYmin = escena->sceneRect().top();
    sceneXmax = escena->sceneRect().right();
    sceneYmax = escena->sceneRect().bottom();

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

void GrillaGuia::centroMovido()
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

void GrillaGuia::mostrarGrilla(bool mostrar)
{
    foreach(QGraphicsLineItem* itm, elementosGridX) itm->setVisible(mostrar);
    foreach(QGraphicsLineItem* itm, elementosGridY) itm->setVisible(mostrar);
}
