#include "rodajeedicionescena.h"

RodajeEdicionEscena::RodajeEdicionEscena(RodajeEdicionVista* v, const QList<Pista>& listaPistas, QObject* parent) :
    QGraphicsScene(parent),
    grilla(v,this),
    mostrarGrilla(false),
    permSnap(false),
    pistaActiva(0),
    pistaResaltada(0),
    vista(v),
    lineaActiva(new QGraphicsLineItem),
    pistas(listaPistas)
{
    prepararSimbolosSnap();
    lineaActiva->setLine(QLine());
    QPen pLineaActiva("orange");
    pLineaActiva.setWidth(3) ; pLineaActiva.setCosmetic(true);
    lineaActiva->setPen(pLineaActiva);
    lineaActiva->hide();
    connect(vista, &RodajeEdicionVista::sigVistaZoom, this, &RodajeEdicionEscena::slotVistaZoomeada);
}

void RodajeEdicionEscena::graficar()
{
    QPen p("black");
    p.setWidth(3);
    p.setCosmetic(true);
    graficarPistas();
    vista->actualizarVista();
    vista->centrarVista();
    graficarCabeceras();
    grilla.crearGrid();
    grilla.mostrarGrilla(mostrarGrilla);
    addItem(lineaActiva);
    snapCabecera->setPos(pistas[0].getPuntoCabecera(Pista::CAB1));
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
        QPointF p1 = p.getPuntoCabecera(Pista::CAB1);
        QPointF p2 = p.getPuntoCabecera(Pista::CAB2);

        elementosPpales.append(addLine(QLineF(p1,p2),penPista));

        //Calcular deltaX y deltaY de la pista para luego calcular la pendiente
        double deltaX;
        double deltaY;

        if (p1.x() > p2.x()) std::swap(p1,p2);

        deltaX = p2.x() - p1.x();
        deltaY = p2.y() - p1.y();

        if (abs(deltaX) < 1e-4f) deltaX = 0; //Como son floats, redondeo

        double min;
        double max;

        if(deltaX != 0) { //Linea no vertical
        min = qMin(p1.x(),p2.x());
        max = qMax(p1.x(),p2.x());
        }
        else {  //Linea vertical
        min = qMin(p1.y(),p2.y());
        max = qMax(p1.y(),p2.y());
        }
        //Guardar pendiente, ordenada al origen, punto inicio y punto final de la pista
        double m = deltaY/deltaX;
        paramRectasPistas.append({deltaX, deltaY, p2.y()-p2.x()*m, min, max});
    }
}

void RodajeEdicionEscena::graficarCabeceras()
{
    foreach(Pista p, pistas)
    {
    QPointF p1 = p.getPuntoCabecera(Pista::CAB1);
    QPointF p2 = p.getPuntoCabecera(Pista::CAB2);

    QFont font("arial",15);
    QFontMetrics fontMetrics(font);
    int height = fontMetrics.height();

    QGraphicsTextItem* textoCabecera1 = addText(p.getCabecera(Pista::CAB1),font);
    textoCabecera1->setDefaultTextColor("blue");
    QTransform t1;
    t1.translate(-textoCabecera1->boundingRect().width()/2,-height);
    textoCabecera1->setTransform(t1,true);
    textoCabecera1->setPos(p1);
    textoCabecera1->setFlags(textoCabecera1->flags() | QGraphicsItem::ItemIgnoresTransformations);

    QGraphicsTextItem* textoCabecera2 = addText(p.getCabecera(Pista::CAB2),font);
    textoCabecera2->setDefaultTextColor("blue");
    QTransform t2;
    t2.translate(-textoCabecera2->boundingRect().width()/2,0);
    textoCabecera2->setTransform(t2,true);
    textoCabecera2->setPos(p2);
    textoCabecera2->setFlags(textoCabecera2->flags() | QGraphicsItem::ItemIgnoresTransformations);
\
    textoCabeceras.append(textoCabecera1);
    textoCabeceras.append(textoCabecera2);
    }

    foreach(QGraphicsTextItem* itm, textoCabeceras)
    {
        itm->hide();
    }
}

void RodajeEdicionEscena::iniciarLinea(QPointF pos)
{
    inicioLineaActiva = pos;
    lineaActiva->show();
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

void RodajeEdicionEscena::slotMostrarCabeceras(bool visible)
{
    foreach(QGraphicsTextItem* itm, textoCabeceras)
    {
        itm->setVisible(visible);
    }
}

void RodajeEdicionEscena::slotVistaZoomeada()
{
    grilla.verificarEscala();
}

void RodajeEdicionEscena::mostrarSnapPuntero(bool mostrar)
{
    snapPista->setVisible(mostrar && permSnap);
}

void RodajeEdicionEscena::mostrarCabPuntero(bool mostrar)
{
    snapCabecera->setVisible(mostrar && permSnap);
}

void RodajeEdicionEscena::mostrarSelPista(bool mostrar)
{
    resaltadoPista->setVisible(mostrar && permSnap);
}

void RodajeEdicionEscena::permitirSnap(bool permitir)
{
    permSnap = permitir;
}

float RodajeEdicionEscena::distanciaPunteroACabecera()
{
    QPointF p1 = snapPista->pos();
    QPointF p2 = cabeceraActiva;
    float distancia = sqrt(qPow(p1.x()-p2.x(),2)+qPow(p1.y()-p2.y(),2));
    return distancia;
}

void RodajeEdicionEscena::cancelarLinea()
{
    lineaActiva->setLine(QLine());
    lineaActiva->hide();
}

void RodajeEdicionEscena::prepararSimbolosSnap()
{
    snapPista = new QGraphicsEllipseItem(QRectF(-6,-6,12,12));
    QPen penPuntero(QBrush("red"),3);
    penPuntero.setCosmetic(true);
    snapPista->setPen(penPuntero);
    snapPista->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    addItem(snapPista);
    snapPista->hide();

    snapCabecera = new QGraphicsRectItem(QRectF(-7,-7,14,14));
    QPen penSnapCabecera(QBrush("green"),4);
    penSnapCabecera.setCosmetic(true);
    snapCabecera->setPen(penSnapCabecera);
    snapCabecera->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    addItem(snapCabecera);
    snapCabecera->hide();

    selCabecera = new QGraphicsRectItem(QRectF(-6,-6,12,12));
    QBrush br(QColor(101, 171, 118));
    QPen penSelCabecera(br,1);
    penSelCabecera.setCosmetic(true);
    selCabecera->setPen(penSelCabecera);
    selCabecera->setBrush(br);
    selCabecera->setFlag(QGraphicsItem::ItemIgnoresTransformations);
    addItem(selCabecera);
    selCabecera->hide();

    //Crear simbolos snap para pista

    Pista p = pistas[0];

    QRectF rectFondo(-8, -p.largo/2, 16, p.largo);
    resaltadoPista = new SombraLinea(rectFondo, colorAzulOscuro);
    addItem(resaltadoPista);
    resaltadoPista->hide();

    seleccionPista = new SombraLinea(rectFondo, colorAzulClaro);
    addItem(seleccionPista);
    seleccionPista->show();
}

void RodajeEdicionEscena::proyectarSobrePista(QPointF posCursor)
{
    // Toma la posicion del cursor sobre la escena, calcula y muestra el punto
    // mas cercano sobre la pist activa
    QPointF p = calcularPuntoEnPista(pistaActiva,posCursor);
    snapPista->setPos(p);
}

void RodajeEdicionEscena::posicionarSnapPista(float distancia)
{
    QPointF p1,p2;
    p1 = cabeceraActiva;
    if (pistas[pistaActiva].getCabecera(cabeceraActiva) == pistas[pistaActiva].getCabecera(Pista::CAB1))
        p2 = pistas[pistaActiva].getPuntoCabecera(Pista::CAB2); // La cabecera activa es la CAB1
    else
        p2 = pistas[pistaActiva].getPuntoCabecera(Pista::CAB1);
    qInfo() << "Distancia = " << distancia;
    float largoPista = pistas[pistaActiva].largo;
    float factor = distancia/largoPista;
    qInfo() << "p1 = " << p1;
    qInfo() << "p2 = " << p2;
    qInfo() << "factor = " << factor;
    qInfo() << "Pto = " << p1*(1-factor) + p2*factor;
    snapPista->setPos(p1*(1-factor) + p2*factor);

}

void RodajeEdicionEscena::proyectarSobreCabecera(QPointF posMouse)
{
    QPointF puntoCercano;
    float distMin = 1e7;
    foreach(auto pair, extremosPista)
    {
        foreach(QPointF pto, pair) {
            float distancia = sqrt(qPow(posMouse.x()-pto.x(),2)+qPow(posMouse.y()-pto.y(),2));
            if ( distancia < distMin)
            {
                distMin = distancia;
                puntoCercano = pto;
            }
        }
    }
    snapCabecera->setPos(puntoCercano);
}

QPoint RodajeEdicionEscena::calcularPuntoEnParalela(QPointF posCursor)
{
    float deltaX = paramRectasPistas[0][0];
    float deltaY = paramRectasPistas[0][1];
    float m = deltaY/deltaX;

    //Hay que recalcular a
    float a = lineaActiva->line().p1().y() - m * lineaActiva->line().p1().x();

    float y1 = posCursor.y();
    float x1 = posCursor.x();

    float b = y1 + 1/m * x1;
    float x = (b-a)/(m+1/m);
    float y = (-1/m)*x + b;

    return QPoint(x,y);
}

QPointF RodajeEdicionEscena::calcularPuntoEnPista(int nroPista, QPointF posCursor)
{
    QPointF p1 = pistas[nroPista].getPuntoCabecera(Pista::CAB1);
    QPointF p2 = pistas[nroPista].getPuntoCabecera(Pista::CAB2);
    return proyectarSobreRecta(p1,p2,posCursor);
}

int RodajeEdicionEscena::pistaMasCercana(QPointF posCursor)
{
    //Hay que determinar que pista esta mas cerca al cursor
    float dist;
    float minDist = 1e6;
    int minIndx = 0;
    for (int i = 0; i<pistas.count(); i++)
    {
       QPointF ptoEnPista = calcularPuntoEnPista(i, posCursor);
       dist = sqrt(qPow(ptoEnPista.x()-posCursor.x(),2)+qPow(ptoEnPista.y()-posCursor.y(),2));
       if (dist < minDist) {
           minDist = dist;
           minIndx = i;
       }
    }
    return minIndx;
}

void RodajeEdicionEscena::resaltarPista(QPointF pto)
{
    pistaResaltada = pistaMasCercana(pto);
    Pista p = pistas[pistaResaltada];
    QRectF rectFondo(-8, -p.largo/2, 16, p.largo);
    resaltadoPista->setRect(rectFondo);
    resaltadoPista->setPos(p.puntoOrigen);
    resaltadoPista->setRotation(p.orientacion);
    resaltadoPista->show();
}

QPointF RodajeEdicionEscena::proyectarSobreRecta(QPointF pInicio, QPointF pFin, QPointF pLibre)
{
    //Funcion que toma la recta delimitada por pInicio y pFin, y proyecta el punto pLibre sobre
    //la misma. Proyectar implica devolver el punto sobre la recta que se encuentra mas cerca de
    //pLibre
    double x,y,m,a,b;
    // m = pendiente de la recta sobre la que quiero proyectar el punto
    // a = punto donde la recta sobre la que quiero proyectar corta al eje y
    // b = punto donde la recta que une el punto libre con la recta sobre la que quiero proyectar, corta al eje y
    if(pInicio.y() == pFin.y()) {   // Recta horizontal
        //qInfo() << "Recta horizontal";
        x = pLibre.x();
        y = pInicio.y();
        x = qMin(x,qMax(pInicio.x(), pFin.x()));
        x = qMax(x,qMin(pInicio.x(), pFin.x()));
    }
    else if (pInicio.x() == pFin.x()) { //Recta vertical
        //qInfo() << "Recta vertical";
        y = pLibre.y();
        x = pInicio.x();
        y = qMin(y,qMax(pInicio.y(),pFin.y()));
        y = qMax(y,qMin(pInicio.y(),pFin.y()));
    }
    else {
        //qInfo() << "Recta oblicua";
        if(pFin.x() > pInicio.x()) {
            m = (pFin.y()-pInicio.y())/(pFin.x() - pInicio.x());
        }
        else {
            m = (pInicio.y()-pFin.y())/(pInicio.x() - pFin.x());
        }
        b = pLibre.y() + 1/m * pLibre.x();
        a = pInicio.y() - pInicio.x()*m;
        x = (b-a)/(m+1/m); // El punto en x donde se cruzan las dos rectas perpendiculares,
                           // Sale de igualar las ecuaciones de las dos rectas
        x = qMin(x,qMax(pInicio.x(), pFin.x()));
        x = qMax(x,qMin(pInicio.x(), pFin.x()));
        y = m*x + a;
    }
    return QPointF(x,y);
}

float RodajeEdicionEscena::longitudRodaje()
{
    return lineaActiva->line().length();
}

float RodajeEdicionEscena::anguloRodaje()
{
    //Para calcular el angulo, uso el producto punto entre dos vectores
    // cos(alpha) = A.B/(|A||B|)
    QPointF vecDirRodaje = lineaActiva->line().p2() - lineaActiva->line().p1();
    float prodPto = vecDirRodaje.x() * vecDirPista.x() + vecDirRodaje.y() * vecDirPista.y();
    float cosAlpha = prodPto/(pistas[pistaActiva].largo * lineaActiva->line().length());
    float alpha = qRadiansToDegrees(qAcos(cosAlpha));
    if (alpha < 0) alpha += 180;
    return alpha;
}

void RodajeEdicionEscena::seleccionarCabecera(QPointF pos)
{
    selCabecera->setPos(pos);
    selCabecera->show();
    cabeceraActiva = pos;
    vecDirPista = pistas[pistaActiva].getVectorDireccion(pos);
}

void RodajeEdicionEscena::seleccionarPista()
{
    pistaActiva = pistaResaltada;
    Pista p = pistas[pistaActiva];
    QRectF rectFondo(-8, -p.largo/2, 16, p.largo);
    seleccionPista->setRect(rectFondo);
    seleccionPista->setPos(p.puntoOrigen);
    seleccionPista->setRotation(p.orientacion);
    seleccionPista->setZValue(-1);
    seleccionPista->show();
    extremosPista = {{p.getPuntoCabecera(Pista::CAB1), p.getPuntoCabecera(Pista::CAB2)}};
    seleccionarCabecera(p.getPuntoCabecera(Pista::CAB1));
}
