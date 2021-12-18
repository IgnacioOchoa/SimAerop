#include "cotagrafica.h"

CotaGrafica::CotaGrafica(QPointF p1, QPointF p2, Sentido sen, QString valor, float dist, QFont font) :
    sentido(sen),
    texto(valor),
    hover(false)
{
    // Para entender que es cada variable, ver el archivo referenciaCotas.png, en la misma carpeta
    // que este codigo fuente
    setAcceptHoverEvents(true);
    setZValue(1);

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
    tramoAdicional = altoTexto;
    anchoRect = margin; //Ancho del rectangulo alrededor de las lineas creado para la shape
    procesarTexto();
    calcularBoundingRect();
    calcularShape();
}

void CotaGrafica::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
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
            painter->drawLine(punto1.x(),punto1.y(),punto1.x(), coordLim + distanciaPerp + tramoAdicional);
            painter->drawLine(punto2.x(),punto2.y(),punto2.x(), coordLim + distanciaPerp + tramoAdicional);
            painter->drawLine(punto1.x(),coordLim + distanciaPerp,
                              punto2.x(),coordLim + distanciaPerp);
        }
        else    // cota por encima de los puntos
        {
            float coordLim = qMin(punto1.y(), punto2.y());
            painter->drawLine(punto1.x(),punto1.y(),punto1.x(), coordLim + distanciaPerp - tramoAdicional);
            painter->drawLine(punto2.x(),punto2.y(),punto2.x(), coordLim + distanciaPerp - tramoAdicional);
            painter->drawLine(punto1.x(),coordLim + distanciaPerp,
                              punto2.x(),coordLim + distanciaPerp);
        }
    }
    else    //ori == VER
    {
        if (distanciaPerp > 0) // cota a la derecha de los puntos
        {
            float coordLim = qMax(punto1.x(), punto2.x());
            painter->drawLine(punto1.x(),punto1.y(),coordLim + distanciaPerp + tramoAdicional , punto1.y());
            painter->drawLine(punto2.x(),punto2.y(),coordLim + distanciaPerp + tramoAdicional, punto2.y());
            painter->drawLine(coordLim + distanciaPerp, punto1.y(),
                              coordLim + distanciaPerp, punto2.y());
        }
        else // cota a la izquierda de los puntos
        {
            float coordLim = qMin(punto1.x(), punto2.x());
            painter->drawLine(punto1.x(),punto1.y(),coordLim + distanciaPerp - tramoAdicional , punto1.y());
            painter->drawLine(punto2.x(),punto2.y(),coordLim + distanciaPerp - tramoAdicional, punto2.y());
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
    graficarTexto(posInfIzqTexto, texto, painter);

//    painter->setBrush(Qt::NoBrush);
//    painter->setPen(QColor("green"));
//    painter->drawPath(pPath);

//    painter->setBrush(Qt::NoBrush);
//    painter->setPen(QColor("red"));
//    painter->drawRect(bRect);
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

void CotaGrafica::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    //QGraphicsItem::mousePressEvent(event); -> no hay que llamarlo porque si no el arrastrar no funciona
}

void CotaGrafica::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    float delta = 0.0;
    if (event->buttons() == Qt::LeftButton)
    {
        QPointF puntoActual = event->scenePos();
        QPointF puntoAnterior = event->lastScenePos();
        if(sentido == Sentido::HOR)
        {
            delta = (puntoActual-puntoAnterior).y();
        }
        if(sentido == Sentido::VER)
        {
            delta = (puntoActual-puntoAnterior).x();
        }
    }
    actualizarPosicion(delta);
}

void CotaGrafica::ordenarPuntos(QPointF p1, QPointF p2)
{
    if (sentido == Sentido::HOR)
    {
        //Esto garantiza que P1 esta siempre a la izquierda de p2
        if (p1.x() < p2.x()) {punto1 = p1; punto2 = p2;}
        else {punto1 = p2; punto2 = p1;}
    }
    else //ori == "VER"
    {
        //Esto garantiza que P1 esta siempre arriba de p2
        if (p1.y() < p2.y()) {punto1 = p1; punto2 = p2;}
        else {punto1 = p2; punto2 = p1;}
    }
}

void CotaGrafica::procesarTexto()
{
    if (sentido == Sentido::HOR)
    {
        float offset = anchoTexto/2;
        posInfIzqTexto = punto1/2 + punto2/2 + QPointF(-offset,distanciaPerp-margin);
    }
    else if (sentido == Sentido::VER)
    {
        float hOffset = anchoTexto;
        float vOffset = altoTexto/2.0;
        posInfIzqTexto = punto1/2 + punto2/2 + QPointF(distanciaPerp-margin-hOffset,vOffset);
    }
}

void CotaGrafica::calcularBoundingRect()
{
    float xMin,xMax,yMin,yMax;

    if(sentido == Sentido::HOR)
    {
        if(distanciaPerp > 0) //La linea de cota está por debajo de los puntos
        {
            yMin = qMin(punto1.y(), punto2.y());
            xMin = qMin(punto1.x(), punto2.x());
            yMax = qMax(punto1.y(), punto2.y()) + distanciaPerp + tramoAdicional;
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
            xMax = qMax(punto1.x(), punto2.x()) + distanciaPerp + tramoAdicional;
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
    bRect.adjust(-anchoRect/2,-anchoRect/2,anchoRect/2,anchoRect/2);
}

void CotaGrafica::calcularShape()
{
    pPath.clear();
    QRectF r1, r2, r3;
    if(sentido == Sentido::HOR)
    {
        if(distanciaPerp > 0) // La línea de cota está por debajo de los puntos
        {
            float yInferior = qMax(punto1.y(),punto2.y());
            r1 = QRectF(punto1 + QPointF(-anchoRect/2,0),
                        QPointF(punto1.x() + anchoRect/2,yInferior+distanciaPerp+tramoAdicional));
            r2 = QRectF(punto2 + QPointF(-anchoRect/2,0),
                        QPointF(punto2.x() + anchoRect/2,yInferior+distanciaPerp+tramoAdicional));
            r3 = QRectF(QPointF(punto1.x(),yInferior+distanciaPerp-anchoRect/2),
                        QPointF(punto2.x(),yInferior+distanciaPerp+anchoRect/2));
        }
        else if(distanciaPerp < 0) // La línea de cota está por encima de los puntos
        {
            float ySuperior = qMin(punto1.y(),punto2.y());
            r1 = QRectF(QPointF(punto1.x() - anchoRect/2,ySuperior+distanciaPerp-tramoAdicional),
                        punto1 + QPointF(anchoRect/2,0));
            r2 = QRectF(QPointF(punto2.x() - anchoRect/2,ySuperior+distanciaPerp-tramoAdicional),
                        punto2 + QPointF(anchoRect/2,0));
            r3 = QRectF(QPointF(punto1.x(),ySuperior+distanciaPerp-anchoRect/2),
                        QPointF(punto2.x(),ySuperior+distanciaPerp+anchoRect/2));
        }
    }
    else if (sentido == Sentido::VER)
    {
        if(distanciaPerp > 0) // La línea de cota está a la derecha de los puntos
        {
            float xDerecho = qMax(punto1.x(),punto2.x());
            r1 = QRectF(punto1 + QPointF(0,-anchoRect/2),
                        QPointF(xDerecho+distanciaPerp+tramoAdicional,punto1.y()+anchoRect/2));
            r2 = QRectF(punto2 + QPointF(0,-anchoRect/2),
                        QPointF(xDerecho+distanciaPerp+tramoAdicional,punto2.y()+anchoRect/2));
            r3 = QRectF(QPointF(xDerecho+distanciaPerp-anchoRect/2,punto1.y()),
                        QPointF(xDerecho+distanciaPerp+anchoRect/2,punto2.y()));
        }
        else if(distanciaPerp < 0) // La línea de cota está a la izquierda de los puntos
        {
            float xIzquierdo = qMin(punto1.x(),punto2.x());
            r1 = QRectF(QPointF(xIzquierdo+distanciaPerp-tramoAdicional,punto1.y()-anchoRect/2),
                        punto1 + QPointF(0,anchoRect/2));
            r2 = QRectF(QPointF(xIzquierdo+distanciaPerp-tramoAdicional,punto2.y()-anchoRect/2),
                        punto2 + QPointF(0,anchoRect/2));
            r3 = QRectF(QPointF(xIzquierdo+distanciaPerp-anchoRect/2, punto1.y()),
                        QPointF(xIzquierdo+distanciaPerp+anchoRect/2, punto2.y()));
        }
    }

    QRectF r4 = QRectF(posInfIzqTexto + QPointF(0,-altoTexto),
                      posInfIzqTexto + QPointF(anchoTexto,0));

    pPath.setFillRule(Qt::WindingFill);
    pPath.addRect(r1.normalized());
    pPath.addRect(r2.normalized());
    pPath.addRect(r3.normalized());
    pPath.addRect(r4.normalized());

    pPath = pPath.simplified();

}

void CotaGrafica::actualizarPosicion(float delta)
{
    distanciaPerp += delta;
    prepareGeometryChange();
    procesarTexto();
    calcularShape();
    calcularBoundingRect();
}

QPainterPath CotaGrafica::shape() const
{
    return pPath;
}

