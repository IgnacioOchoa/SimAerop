#include "escenaconfpista.h"

EscenaConfPista::EscenaConfPista(QObject* ob) :
    QGraphicsScene(ob)
{
    setSceneRect(QRect(-10000,-3000,20000,6000));
    setBackgroundBrush(QBrush("#f5f0f3"));
}

void EscenaConfPista::graficarPista(QRectF rectPista)
{
    clear();
    QPen borde;
    borde.setWidth(2);
    borde.setCosmetic(true);
    QGraphicsRectItem* rectItm = addRect(rectPista,borde);

    QPointF p1 = {rectItm->rect().x(),rectItm->rect().y()+rectItm->rect().height()};
    QPointF p2 = {rectItm->rect().x()+rectItm->rect().width(),
                  rectItm->rect().y()+rectItm->rect().height()};

    QPointF p3 = {rectItm->rect().x(), rectItm->rect().y()};
    QPointF p4 = {rectItm->rect().x() + rectItm->rect().width(),rectItm->rect().y()};

    CotaGrafica* cota1 = new CotaGrafica(p3,p4,"HOR",-100);
    addItem(cota1);

    CotaGrafica* cota2 = new CotaGrafica(p1,p3,"VER",-100);
    addItem(cota2);
}
