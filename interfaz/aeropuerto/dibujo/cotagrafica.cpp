#include "cotagrafica.h"

CotaGrafica::CotaGrafica(QPointF p1, QPointF p2, Sentido sen, QString valor, float dist, QFont font) :
    sentido(sen),
    texto(valor),
    hover(false)
{
    // Para entender que es cada variable, ver el archivo referenciaCotas.png, en la misma carpeta
    // que este codigo fuente
    setAcceptHoverEvents(true);

    penCota = QPen(QColor("blue"),2);
    brushCota = QBrush("blue");
    penCotaHover = QPen(QColor("#9f63bf"),6);
    brushCotaHover = QBrush("#9f63bf");

    ordenarPuntos(p1, p2);

    //Distancia entre los dos puntos, depende de si la orientacion es horizontal o vertical
    longitud = sentido == Sentido::HOR ? abs(punto1.x()-punto2.x()) : abs(punto1.y()-punto2.y());

    //Si no se ingresa un valor para dist se lo calcula como 1/4 de la distancia
    //entre puntos, y la posicion de la cota es por debajo de los puntos (caso HOR) o a la
    //derecha de los puntos (caso VER), o sea, distanciaPerp > 0
    distanciaPerp = dist == 0 ? longitud*0.25 : dist;

    //Si no se ingresa una fuente (o sea que font es un QFont vacio) pongo una por default.
    fuente = font == QFont() ? QFont("Arial",30) : font;

    anchoTexto = QFontMetrics(fuente).boundingRect(texto).width();
    altoTexto = QFontMetrics(fuente).ascent();
    margin = altoTexto/2;

    calcularBoundingRect();
    calcularShape();
}

void CotaGrafica::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(!hover)
    {
        painter->setPen(penCota);
        painter->setBrush(brushCota);
        fuente.setBold(false);
    }
    else
    {
        painter->setPen(penCotaHover);
        painter->setBrush(brushCotaHover);
        fuente.setBold(true);
    }

    if(sentido == Sentido::HOR)
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
    if (sentido == Sentido::HOR)
    {
         graficarFlecha(punto1 + QPointF(0,distanciaPerp),Direccion::IZQUIERDA, painter);
         graficarFlecha(punto2 + QPointF(0,distanciaPerp),Direccion::DERECHA, painter);
    }
    else if (sentido == Sentido::VER)
    {
        graficarFlecha(punto1 + QPointF(distanciaPerp,0), Direccion::ARRIBA, painter);
        graficarFlecha(punto2 + QPointF(distanciaPerp,0), Direccion::ABAJO, painter);
    }
    painter->setFont(fuente);
    if (sentido == Sentido::HOR)
    {
        float offset = anchoTexto/2;
        QPointF posCentro = punto1/2 + punto2/2 + QPointF(-offset,distanciaPerp-margin);
        graficarTexto(posCentro, texto, painter);
    }
    else if (sentido == Sentido::VER)
    {
        float hOffset = anchoTexto;
        float vOffset = altoTexto/2.0;
        QPointF posCentro = punto1/2 + punto2/2 + QPointF(distanciaPerp-margin-hOffset,vOffset);
        graficarTexto(posCentro, texto, painter);
    }
}

QRectF CotaGrafica::boundingRect() const
{
    return bRect;
}

void CotaGrafica::graficarFlecha(QPointF posVertice, Direccion ori, QPainter *painter)
{
    float largo = sizeFlechaRef;
    QVector<QPointF> tri;
    if (ori == Direccion::ARRIBA)
    {

         tri = {posVertice, posVertice+QPointF(-largo/2, largo),
                             posVertice+QPointF(largo/2,largo)};
    }
    else if (ori == Direccion::ABAJO)
    {
        tri = {posVertice, posVertice+QPointF(-largo/2, -largo),
                            posVertice+QPointF(largo/2,-largo)};
    }
    else if (ori == Direccion::DERECHA)
    {
        tri = {posVertice, posVertice+QPointF(-largo, -largo/2),
                            posVertice+QPointF(-largo,largo/2)};
    }
    else if (ori == Direccion::IZQUIERDA)
    {
        tri = {posVertice, posVertice+QPointF(largo, -largo/2),
                            posVertice+QPointF(largo,largo/2)};
    }

    painter->drawConvexPolygon(QPolygonF(tri));
}

void CotaGrafica::graficarTexto(QPointF posCentro, QString texto, QPainter *painter)
{
    painter->drawText(posCentro,texto);
}

void CotaGrafica::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneHoverEnter)
        {
            hover = true;
        }
    QGraphicsItem::hoverEnterEvent(event);
}

void CotaGrafica::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (event->type() == QEvent::GraphicsSceneHoverLeave)
        {
            hover = false;
        }
    QGraphicsItem::hoverLeaveEvent(event);
}

void CotaGrafica::ordenarPuntos(QPointF p1, QPointF p2)
{
    if (sentido == Sentido::HOR)
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
}

void CotaGrafica::calcularBoundingRect()
{
    //Calculo de bounding Rect

    float xMin,xMax,yMin,yMax;

    if(sentido == Sentido::HOR)
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
            yMin = qMin(punto1.y(),punto2.y()) + distanciaPerp - margin - altoTexto; //aca distanciaPerp es negativo
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
            xMin = qMin(punto1.x(), punto2.x()) + distanciaPerp - margin - anchoTexto; //aca distanciaPerp es negativo
            yMax = yMin + longitud;
            xMax = qMax(punto1.x(), punto2.x());
        }
    }
    QPointF topLeft(xMin,yMin);
    QPointF botRight(xMax,yMax);
    bRect = QRectF(topLeft,botRight);
}

void CotaGrafica::calcularShape()
{
    QPainterPath painterPath;

    if(sentido == Sentido::HOR)
    {
        if(distanciaPerp > 0) // La línea de cota está por debajo de los puntos
        {

        }
        else if(distanciaPerp < 0) // La línea de cota está por encima de los puntos
        {

        }
    }
    else if (sentido == Sentido::VER)
    {
        if(distanciaPerp > 0) // La línea de cota está a la derecha de los puntos
        {

        }
        else if(distanciaPerp < 0) // La línea de cota está a la izquierda de los puntos
        {

        }
    }
}

QPainterPath CotaGrafica::shape() const
{
    return QGraphicsItem::shape();
}

