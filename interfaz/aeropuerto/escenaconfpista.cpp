#include "escenaconfpista.h"

EscenaConfPista::EscenaConfPista(QObject* ob) :
    QGraphicsScene(ob)
{
    setSceneRect(QRect(-10000,-3000,20000,6000));
    setBackgroundBrush(QBrush("#f5f0f3"));
    listaCotas = QList<CotaGrafica*>();
}

void EscenaConfPista::graficarPista(Pista pista)
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
}

void EscenaConfPista::mostrarCotas(bool mostrar)
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

void EscenaConfPista::limpiar()
{
    clear();
    listaCotas.clear();
}

void EscenaConfPista::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void EscenaConfPista::graficarUmbral(float despl, Lado lado)
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
