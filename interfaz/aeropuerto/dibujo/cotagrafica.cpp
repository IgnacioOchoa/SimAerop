#include "cotagrafica.h"

CotaGrafica::CotaGrafica(QPointF p1, QPointF p2, QString orient, float dist, QFont font)
{
    // Para entender que es cada variable, ver el archivo referenciaCotas.png, en la misma carpeta
    // que este codigo fuente
    penCota = QPen(QBrush("blue"),2);

    ori = orient;
    if (ori == "HOR")
    {
        if (p1.x() < p2.x())   //Esto garantiza que P1 esta siempre a la izquierda de p2
        {
            punto1 = p1; punto2 = p2;
        }
        else
        {
            punto1 = p2; punto2 = p1;
        }
    }
    else //ori == "VER"
    {
        if (p1.y() < p2.y())
        {
            punto1 = p1; punto2 = p2;  //Esto garantiza que P1 esta siempre arriba de p2
        }
        else
        {
            punto1 = p2; punto2 = p1;
        }
    }

    //Distancia entre los dos puntos, depende de si la orientacion es horizontal o vertical
    longitud = ori == "HOR" ? abs(punto1.x()-punto2.x()) : abs(punto1.y()-punto2.y());

    //Si no se ingresa un valor para dist se lo calcula como 1/4 de la distancia
    //entre puntos, y la posicion de la cota es por debajo de los puntos (caso HOR) o a la
    //derecha de los puntos (caso VER), o sea, distanciaPerp > 0
    distanciaPerp = dist == 0 ? longitud*0.25 : dist;

    //Si no se ingresa una fuente (o sea que font es un QFont vacio) pongo una por default.
    fuente = font == QFont() ? QFont("Arial",12) : font;

    qreal alturaFont = fuente.pointSizeF();
    margin = alturaFont/2;

    //Calculo de bounding Rect

    float xMin,xMax,yMin,yMax;

    if(ori == "HOR")
    {
        if(distanciaPerp > 0) //La linea de cota está por debajo de los puntos
        {
            yMin = qMin(punto1.y(), punto2.y());
            xMin = qMin(punto1.x(), punto2.x());
            yMax = qMax(punto1.y(), punto2.y()) + distanciaPerp + margin;
            xMax = xMin + longitud;
        }
        else //La linea de cota está por arriba de los puntos
        {
            yMin = qMin(punto1.y(),punto2.y()) + distanciaPerp - margin - alturaFont; //aca distanciaPerp es negativo
            xMin = qMin(punto1.x(),punto2.x());
            yMax = qMax(punto1.y(), punto2.y());
            xMax = xMin + longitud;
        }
    }
    else
    {
        if(distanciaPerp > 0) // La linea de cota está a la derecha de los puntos
        {
            yMin = qMin(punto1.y(), punto2.y());
            xMin = qMin(punto1.x(), punto2.x());
            yMax = yMin + longitud;
            xMax = qMax(punto1.x(), punto2.x()) + distanciaPerp + margin;
        }
        else // La linea de cota está a la izquierda de los puntos
        {
            yMin = qMin(punto1.y(), punto2.y());
            xMin = qMin(punto1.x(), punto2.x()) + distanciaPerp - margin - alturaFont; //aca distanciaPerp es negativo
            yMax = yMin + longitud;
            xMax = qMax(punto1.x(), punto2.x());
        }
    }
    QPointF topLeft(xMin,yMin);
    QPointF botRight(xMax,yMax);
    bRect = QRectF(topLeft,botRight);
}

void CotaGrafica::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(penCota);
    if(ori == "HOR")
    {
        if (distanciaPerp > 0) // cota por debajo de los puntos
        {
            float coordLim = qMax(punto1.y(), punto2.y());
            painter->drawLine(punto1.x(),punto1.y(),punto1.x(), coordLim + distanciaPerp + margin);
            painter->drawLine(punto2.x(),punto2.y(),punto2.x(), coordLim + distanciaPerp + margin);
            painter->drawLine(punto1.x(),coordLim + distanciaPerp,
                              punto2.x(),coordLim + distanciaPerp);
        }
        else    // cota por encima de los puntos
        {
            float coordLim = qMin(punto1.y(), punto2.y());
            painter->drawLine(punto1.x(),punto1.y(),punto1.x(), coordLim + distanciaPerp - margin);
            painter->drawLine(punto2.x(),punto2.y(),punto2.x(), coordLim + distanciaPerp - margin);
            painter->drawLine(punto1.x(),coordLim + distanciaPerp,
                              punto2.x(),coordLim + distanciaPerp);
        }
    }
    else    //ori == VER
    {
        if (distanciaPerp > 0) // cota a la derecha de los puntos
        {
            float coordLim = qMax(punto1.x(), punto2.x());
            painter->drawLine(punto1.x(),punto1.y(),coordLim + distanciaPerp + margin , punto1.y());
            painter->drawLine(punto2.x(),punto2.y(),coordLim + distanciaPerp + margin, punto2.y());
            painter->drawLine(coordLim + distanciaPerp, punto1.y(),
                              coordLim + distanciaPerp, punto2.y());
        }
        else // cota a la izquierda de los puntos
        {
            float coordLim = qMin(punto1.x(), punto2.x());
            painter->drawLine(punto1.x(),punto1.y(),coordLim + distanciaPerp - margin , punto1.y());
            painter->drawLine(punto2.x(),punto2.y(),coordLim + distanciaPerp - margin, punto2.y());
            painter->drawLine(coordLim + distanciaPerp, punto1.y(),
                              coordLim + distanciaPerp, punto2.y());
        }
    }
}

QRectF CotaGrafica::boundingRect() const
{
    return bRect;
}

void CotaGrafica::graficarFlecha(QPointF posVertice, float size, QString direccion)
{
    /*QVector<QPointF> v1 = {pInter1, pInter1+QPointF(20,-10), pInter1+QPointF(20,10)};
    QVector<QPointF> v2 = {pInter2, pInter2+QPointF(-20,-10), pInter2+QPointF(-20,10)};

    escenaPreliminar->addPolygon(QPolygonF(v1),penCota, brushFlecha);
    escenaPreliminar->addPolygon(QPolygonF(v2),penCota, brushFlecha);*/
}

void CotaGrafica::graficarTexto(QPointF posCentro, QString texto)
{
    /*QGraphicsTextItem* txt1 = escenaPreliminar->addText(QString::number(pista.largo), QFont("Arial",30));
    txt1->setPos((pInter1+pInter2)/2 + QPointF(txt1->textWidth()*5,20));*/
}

