#include "cotagrafica.h"

CotaGrafica::CotaGrafica(QPointF p1, QPointF p2, Orientacion h, float dist, QFont font)
{
    punto1 = p1;
    punto2 = p2;
    ori = h;

    //Distancia entre los dos puntos, depende de si la orientacion es horizontal o vertical
    longitud = ori == HOR ? abs(punto1.x()-punto2.x()) : abs(punto1.y()-punto2.y());

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

    if(ori == HOR)
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

}

QRectF CotaGrafica::boundingRect() const
{
    return bRect;
}

