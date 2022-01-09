#include "pistaescena.h"

PistaEscena::PistaEscena(QObject* ob) :
    QGraphicsScene(ob),
    umbral1Visible(false),
    umbral2Visible(false)
{
    setSceneRect(QRect(-10000,-3000,20000,6000));
    setBackgroundBrush(QBrush("#f5f0f3"));
    listaCotas = QList<CotaGrafica*>();
    lineaUmbral1 = new LineaUmbral();
    lineaUmbral1->setProperty("Nombre", "LineaUmbral1");
    lineaUmbral2 = new LineaUmbral();
    lineaUmbral2->setProperty("Nombre", "LineaUmbral2");

    connect(lineaUmbral1, &LineaUmbral::sigPosCambiada, this, &PistaEscena::slotLineaUmbralMovida);
    connect(lineaUmbral2, &LineaUmbral::sigPosCambiada, this, &PistaEscena::slotLineaUmbralMovida);
}

void PistaEscena::graficarPista(Pista pista)
{

    rectPista = QRect(-pista.largo/2,-pista.ancho/2,pista.largo,pista.ancho);
    limpiar();
    QPen borde;
    borde.setWidth(2);
    borde.setCosmetic(true);
    grRectItm = addRect(rectPista,borde);
    grRectItm->setZValue(0);

    QPointF p1 = {grRectItm->rect().x(),grRectItm->rect().y()+grRectItm->rect().height()};
    QPointF p2 = {grRectItm->rect().x()+grRectItm->rect().width(),
                  grRectItm->rect().y()+grRectItm->rect().height()};

    QPointF p3 = {grRectItm->rect().x(), grRectItm->rect().y()};
    QPointF p4 = {grRectItm->rect().x() + grRectItm->rect().width(),grRectItm->rect().y()};

    cota1 = new CotaGrafica(p3,p4,CotaGrafica::Sentido::HOR,QString::number(pista.largo), -100);
    addItem(cota1);
    cota1->hide();

    listaCotas.append(cota1);

    cota2 = new CotaGrafica(p1,p3,CotaGrafica::Sentido::VER,QString::number(pista.ancho), -100);
    addItem(cota2);
    cota2->hide();

    listaCotas.append(cota2);

    lineaUmbral1->setDimensiones(-pista.largo/2, pista.ancho);
    addItem(lineaUmbral1);
    lineaUmbral1->hide();
    lineaUmbral2->setDimensiones(pista.largo/2, pista.ancho);
    addItem(lineaUmbral2);
    lineaUmbral2->hide();

}

void PistaEscena::mostrarCotas(bool mostrar)
{
    if(mostrar)
    {
        foreach(CotaGrafica* cot, listaCotas)
        {
            cot->show();
        }
    }
    else
    {
        foreach(CotaGrafica* cot, listaCotas)
        {
            cot->hide();
        }
    }
}

void PistaEscena::limpiar()
{
    clear();
    listaCotas.clear();
}

void PistaEscena::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void PistaEscena::graficarUmbral(float despl, Lado lado)
{
    QPointF p1;
    if (lado == Lado::IZQ)
    {
        p1 = QPointF(rectPista.x() + despl, rectPista.y() + rectPista.height());
    }
    else if (lado == Lado::DER)
    {
        p1 = QPointF(rectPista.x()+rectPista.width() - despl, rectPista.y() + rectPista.height());
    }
    QPointF p2 = p1 + QPointF(-40,80);
    QPointF p3 = p1 + QPointF(40,80);
    QPolygonF pol;
    pol.append(p1); pol.append(p2); pol.append(p3);
    addPolygon(pol,QPen(),QBrush(Qt::black));
}

void PistaEscena::slotUmbralActivado(PistaEscena::Umbral um, bool estado)
{
    if(um == Umbral::UMBRAL1) {
        umbral1Visible = estado;
        if(!lineaUmbral1) return;
        lineaUmbral1->setVisible(estado);
    }
    else if (um == Umbral::UMBRAL2) {
        umbral2Visible = estado;
        if(!lineaUmbral2) return;
        lineaUmbral2->setVisible(estado);
    }
}

void PistaEscena::slotUmbralModificado(PistaEscena::Umbral umbral, int valor)
{
    if(umbral == Umbral::UMBRAL1)
    {
        lineaUmbral1->setPos(QPointF(-rectPista.width()/2+valor,0));
    }
    else if (umbral == Umbral::UMBRAL2)
    {
        lineaUmbral2->setPos(QPointF(rectPista.width()/2-valor,0));
    }
}

void PistaEscena::slotLineaUmbralMovida(int pos)
{
    LineaUmbral* linea = static_cast<LineaUmbral*>(sender());
    if(!linea) qInfo() << "La conversion del puntero fallo en slot LineaUmbralMovida";
    if (linea->property("Nombre").toString() == "LineaUmbral1")
    {
        emit sigLineaUmbralMovida(Umbral::UMBRAL1, rectPista.width()/2 + pos);
    }
    else if (linea->property("Nombre").toString() == "LineaUmbral2")
    {
        emit sigLineaUmbralMovida(Umbral::UMBRAL2, rectPista.width()/2 - pos);
    }
}
