#include "pistaescena.h"

PistaEscena::PistaEscena(QObject* ob) :
    QGraphicsScene(ob),
    umbral1Visible(false),
    umbral2Visible(false)
{
    setSceneRect(QRect(-10000,-3000,20000,6000));
    setBackgroundBrush(QBrush("#f5f0f3"));
    crearLineasUmbral();
    escenaLimpia = true;
}

void PistaEscena::graficarPista(Pista pista)
{
    if(!escenaLimpia) limpiar();
    pistaGraficada = pista;
    crearRectanguloPista();
    crearCotas();
    actualizarLineasUmbral();
    escenaLimpia = false;
}

void PistaEscena::mostrarCotas(bool mostrar)
{
    if(mostrar) foreach(CotaGrafica* cot, listaCotas) {cot->show();}
    else        foreach(CotaGrafica* cot, listaCotas) {cot->hide();}
}

void PistaEscena::limpiar()
{
    listaCotas.clear();
    lineaUmbral1->setVisible(false);
    lineaUmbral2->setVisible(false);
    removeItem(grRectItm);
    if(grRectItm) delete grRectItm;
    escenaLimpia = true;
}

void PistaEscena::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void PistaEscena::slotUmbralActivado(PistaEscena::Umbral um, bool estado)
{
    if(um == Umbral::UMBRAL1) {
        umbral1Visible = estado;
        if(!lineaUmbral1) return;
        if(!escenaLimpia) lineaUmbral1->setVisible(estado);
    }
    else if (um == Umbral::UMBRAL2) {
        umbral2Visible = estado;
        if(!lineaUmbral2) return;
        if(!escenaLimpia) lineaUmbral2->setVisible(estado);
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

void PistaEscena::slotSetLimUmbrales(int limUmbral1, int limUmbral2)
{
    lineaUmbral1->setLimiteSup(limUmbral1-rectPista.width()/2);
    lineaUmbral2->setLimiteInf(rectPista.width()/2-limUmbral2);
}

void PistaEscena::crearRectanguloPista()
{
    rectPista = QRect(-pistaGraficada.largo/2,
                      -pistaGraficada.ancho/2,
                      pistaGraficada.largo,
                      pistaGraficada.ancho);
    QPen borde;
    borde.setWidth(2);
    borde.setCosmetic(true);
    grRectItm = addRect(rectPista,borde);
    grRectItm->setZValue(0);
}

void PistaEscena::crearCotas()
{
    QPointF p1 = {grRectItm->rect().x(),grRectItm->rect().y()+grRectItm->rect().height()};
    QPointF p2 = {grRectItm->rect().x()+grRectItm->rect().width(),
                  grRectItm->rect().y()+grRectItm->rect().height()};
    QPointF p3 = {grRectItm->rect().x(), grRectItm->rect().y()};
    QPointF p4 = {grRectItm->rect().x() + grRectItm->rect().width(),grRectItm->rect().y()};

    cota1 = new CotaGrafica(p3,p4,CotaGrafica::Sentido::HOR,QString::number(pistaGraficada.largo), -100);
    addItem(cota1);
    cota1->hide();
    cota2 = new CotaGrafica(p1,p3,CotaGrafica::Sentido::VER,QString::number(pistaGraficada.ancho), -100);
    addItem(cota2);
    cota2->hide();
    listaCotas.append(cota1);
    listaCotas.append(cota2);
}

void PistaEscena::crearLineasUmbral()
{
    lineaUmbral1 = new LineaUmbral();
    lineaUmbral1->setProperty("Nombre", "LineaUmbral1");
    addItem(lineaUmbral1);
    lineaUmbral1->hide();
    lineaUmbral2 = new LineaUmbral();
    lineaUmbral2->setProperty("Nombre", "LineaUmbral2");
    addItem(lineaUmbral2);
    lineaUmbral2->hide();

    connect(lineaUmbral1, &LineaUmbral::sigPosCambiada, this, &PistaEscena::slotLineaUmbralMovida);
    connect(lineaUmbral2, &LineaUmbral::sigPosCambiada, this, &PistaEscena::slotLineaUmbralMovida);
}

void PistaEscena::actualizarLineasUmbral()
{
    lineaUmbral1->setLimiteInf(-pistaGraficada.largo/2);
    lineaUmbral1->setLimiteSup(pistaGraficada.largo/2);
    lineaUmbral1->setDimensiones(-pistaGraficada.largo/2,
                                 pistaGraficada.ancho);
    lineaUmbral1->setVisible(umbral1Visible);

    lineaUmbral2->setLimiteSup(pistaGraficada.largo/2);
    lineaUmbral2->setLimiteInf(-pistaGraficada.largo/2);
    lineaUmbral2->setDimensiones(pistaGraficada.largo/2,
                                 pistaGraficada.ancho);
    lineaUmbral2->setVisible(umbral2Visible);
}
