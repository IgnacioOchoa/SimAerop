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

    QRect rectPista = QRect(-pista.largo/2,-pista.ancho/2,pista.largo,pista.ancho);
    limpiar();
    QPen borde;
    borde.setWidth(2);
    borde.setCosmetic(true);
    grRectItm = addRect(rectPista,borde);

    QPointF p1 = {grRectItm->rect().x(),grRectItm->rect().y()+grRectItm->rect().height()};
    QPointF p2 = {grRectItm->rect().x()+grRectItm->rect().width(),
                  grRectItm->rect().y()+grRectItm->rect().height()};

    QPointF p3 = {grRectItm->rect().x(), grRectItm->rect().y()};
    QPointF p4 = {grRectItm->rect().x() + grRectItm->rect().width(),grRectItm->rect().y()};

    CotaGrafica* cota1 = new CotaGrafica(p3,p4,CotaGrafica::Sentido::HOR,QString::number(pista.largo), -100);
    addItem(cota1);
    cota1->hide();

    listaCotas.append(cota1);

    CotaGrafica* cota2 = new CotaGrafica(p1,p3,CotaGrafica::Sentido::VER,QString::number(pista.ancho), -100);
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
