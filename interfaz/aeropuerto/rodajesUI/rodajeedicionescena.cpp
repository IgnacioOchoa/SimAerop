#include "rodajeedicionescena.h"

RodajeEdicionEscena::RodajeEdicionEscena(RodajeEdicionVista* v, const QList<Pista>& listaPistas, QObject* parent) :
    QGraphicsScene(parent),
    grilla(v,this),
    mostrarGrilla(false),
    vista(v),
    lineaActiva(new QGraphicsLineItem),
    pistas(listaPistas)
{
    prepararSimbolosSnap();
    lineaActiva->setLine(QLine());
    QPen pLineaActiva("orange");
    pLineaActiva.setWidth(3) ; pLineaActiva.setCosmetic(true);
    lineaActiva->setPen(pLineaActiva);

    connect(vista, &RodajeEdicionVista::sigVistaZoom, this, &RodajeEdicionEscena::slotVistaZoomeada);
    connect(vista, &RodajeEdicionVista::sigMouseIngresado, this, &RodajeEdicionEscena::slotHabilitarSnap);
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
        float deltaX;
        float deltaY;

        deltaX = p2.x() - p1.x();
        deltaY = p2.y() - p1.y();

        if (abs(deltaX) < 1e-4f) deltaX = 0; //Como son floats, redondeo

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
        extremosPista.append({p1,p2});
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
    qInfo() << "InicioLineaActiva = " << pos;
}

void RodajeEdicionEscena::setLineaActiva(QPointF p2)
{
    lineaActiva->setLine(QLineF(inicioLineaActiva,p2));
    qInfo() << "Linea activa: " << lineaActiva->line();
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

void RodajeEdicionEscena::slotHabilitarSnap(bool hab)
{
    habilitarSnap = hab;
}

void RodajeEdicionEscena::mostrarSnapPuntero(bool mostrar)
{
    snapPista->setVisible(mostrar);
}

void RodajeEdicionEscena::mostrarCabPuntero(bool mostrar)
{
    snapCabecera->setVisible(mostrar);
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

    for(int i=0; i<pistas.count(); i++)
    {
        selCabecera = new QGraphicsRectItem(QRectF(-6,-6,12,12));
        QBrush br("#9dedb1");
        QPen penSelCabecera(br,1);
        penSelCabecera.setCosmetic(true);
        selCabecera->setPen(penSelCabecera);
        selCabecera->setBrush(br);
        selCabecera->setFlag(QGraphicsItem::ItemIgnoresTransformations);
        addItem(selCabecera);
        selCabecera->hide();
        vecSeleccionesCabecera.append(selCabecera);
    }
}

void RodajeEdicionEscena::proyectarSobrePista(QPointF posCursor)
{
    snapPista->show();

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
        //qInfo() << "Recta horizontal";
        x = x1;
        y = a;
        x = qMin(x,max);
        x = qMax(x,min);
    }
    else if (dx == 0) { //Recta vertical
        //qInfo() << "Recta vertical";
        y = y1;
        x = 0; //Esto hay que actualizarlo cuando se implementen pistas que no pasen por 0
        y = qMin(y,max);
        y = qMax(y,min);
    }
    else {
        //qInfo() << "Recta oblicua";
        float m = dy/dx;
        float b = y1 + 1/m * x1;
        x = (b-a)/(m+1/m);
        x = qMin(x,max);
        x = qMax(x,min);
       // qInfo() << "x = " << x;
        y = (-1/m)*x + b;
        if(m < 0) {std::swap(min,max);}
        y = qMin(y,max*m+a);
        y = qMax(y,min*m+a);
        //qInfo() << "y = " << y;
    }
    snapPista->setPos(x,y);
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

void RodajeEdicionEscena::seleccionarCabecera(int indicePista, QPointF pos)
{
    vecSeleccionesCabecera[indicePista]->setPos(pos);
    vecSeleccionesCabecera[indicePista]->show();
    //Dibujar cuadrado verde sobre esa posicion
}
