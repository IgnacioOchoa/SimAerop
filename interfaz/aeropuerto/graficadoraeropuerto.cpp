#include "graficadoraeropuerto.h"

GraficadorAeropuerto::GraficadorAeropuerto(QGraphicsView *gv) :
    vistaPista(gv)
{
    escenaPista = gv->scene();
    gradienteFondoPista = new QLinearGradient(QPointF(-1000, -1000), QPointF(1000, 1000));
    gradienteFondoPista->setColorAt(0, "#faf0e3");
    gradienteFondoPista->setColorAt(1, "#e0d1bc");
    fondoPista = new QBrush(*gradienteFondoPista);
    colorPista = new QBrush("#A4B3B6");
    colorMargen = new QBrush("#828282");
    escenaPista->setBackgroundBrush(*fondoPista);
    bordePista = new QPen;
    bordePista->setWidth(0);
}

void GraficadorAeropuerto::actualizarPista(const Pista& p)
{
    escenaPista->clear();
    escenaPista->setBackgroundBrush(*fondoPista);

    QPen penArea(Qt::NoPen);

    //Grafica márgenes de pista y áreas anterior al umbral
    QGraphicsRectItem* pavFlexible = new QGraphicsRectItem;
    if(p.ancho <60){
        pavFlexible = escenaPista->addRect(-p.largo/2.0-30,-p.ancho/2.0-(60-p.ancho)/2.0,p.largo+60,60, penArea, *colorMargen);
    }
    else{
        pavFlexible = escenaPista->addRect(-p.largo/2.0-30,-p.ancho/2.0,p.largo+60,p.ancho, penArea, *colorMargen);
    }

    QGraphicsRectItem* rectItm = new QGraphicsRectItem;
    rectItm = escenaPista->addRect(-p.largo/2.0,-p.ancho/2.0,p.largo,p.ancho, *bordePista, *colorPista);

    escenaPista->addRect(-p.largo/2.0 - 200, -p.ancho/2.0, p.largo + 400, p.ancho, penArea);


    //GRAFICADOR DE PINTURA DE PISTA

    QPen penw(Qt::white, 0);
    QPen penb(Qt::black, 0);

    //Determinación de Parámetros según ancho de pista
    if (p.ancho<23){
        fajas = 2;
        anchoFajasLa = 0.3;
        anchoFajasUm = (p.ancho-6.0)/(fajas*4);
    }
    else if(p.ancho<30){
        fajas = 3;
        anchoFajasLa = 0.45;
        anchoFajasUm = (p.ancho-6.0)/(fajas*4);
    }
    else if(p.ancho<45){
        fajas = 4;
        anchoFajasLa = 0.9;
        anchoFajasUm = (p.ancho-6.0)/(fajas*4);
    }
    else if(p.ancho<60){
        fajas = 6;
        anchoFajasLa = 0.9;
        anchoFajasUm = (p.ancho-6.0)/(fajas*4);
    }
    else {
        fajas = 8;
        anchoFajasLa = 0.9;
        anchoFajasUm = (54.0)/(fajas*4);
    }

    //Determinación de Parámetros según largo de pista
    if (p.largo<800){
        distanciaUmVi = 150;
        anchoFajasVi = 4;
        espaciadoFajasVi = 6;
    }
    else if(p.largo<1200){
        distanciaUmVi = 250;
        anchoFajasVi = 6;
        espaciadoFajasVi = 9;
    }
    else if(p.largo<2400){
        distanciaUmVi = 300;
        anchoFajasVi = 6;
        espaciadoFajasVi = 18;
    }
    else {
        distanciaUmVi = 400;
        anchoFajasVi = 10;
        espaciadoFajasVi = 22.5;
    }

    //Graficación de barras de umbral
    for (int i=0; i<fajas; i++)
    {
        QGraphicsRectItem* barraUm1 = escenaPista->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, penw, QBrush("white"));
        barraUm1->moveBy(-(p.largo/2.0 - 21),-(p.ancho/2.0 - 3  -anchoFajasUm/2) + i*anchoFajasUm*2);

        QGraphicsRectItem* barraUm2 = escenaPista->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, penw, QBrush("white"));
        barraUm2->moveBy(-(p.largo/2.0 - 21),(p.ancho/2.0 - 3  -anchoFajasUm/2) - i*anchoFajasUm*2);

        QGraphicsRectItem* barraUm3 = escenaPista->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, penw, QBrush("white"));
        barraUm3->moveBy((p.largo/2.0 - 21),-(p.ancho/2.0 - 3 - anchoFajasUm/2) + i*anchoFajasUm*2);

        QGraphicsRectItem* barraUm4 = escenaPista->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, penw, QBrush("white"));
        barraUm4->moveBy((p.largo/2.0 - 21),(p.ancho/2.0 - 3 - anchoFajasUm/2) - i*anchoFajasUm*2);
    }

    //Graficación de fajas transversales de umbral y fajas laterales de pista
    //Nota: No se programó limitación a 60 m de ancho de pista.
    QPainterPath outer;
    outer.addRect(-p.largo/2.0,-p.ancho/2.0,p.largo,p.ancho);
    QPainterPath inner;
    inner.addRect(-p.largo/2.0+1.8,-p.ancho/2.0+anchoFajasLa,p.largo-3.6,p.ancho-anchoFajasLa*2);
    outer = outer.subtracted(inner);

    QGraphicsPathItem* fajasTransyLat = escenaPista->addPath(outer, penw,  QBrush("white"));

    //Graficación de centerline

    //Nota: Dadas la definición de centerline, y con el fin de facilitar la graficación, se fija el valor del
    //intervalo a 2/3 de la longitud de la faja de eje. Dada la formulación matemática, el valor del largo de
    //faja de eje se mantendrá entre 30 y 35 m para pistas de mas de 500 m. ANCHO DEPENDE DE CAT APP.

    largoEjes = (p.largo-138)/(5*((p.largo-138+20)/50)/3.0-2/3.0);

    for (int i=0; i<(p.largo-138+20)/50; i++)
    {
        QGraphicsRectItem* ejePista = escenaPista->addRect(-largoEjes/2.0,-0.45,largoEjes,0.9, penw, QBrush("white"));
        ejePista->moveBy(-(p.largo/2.0-69-largoEjes/2.0)+5*largoEjes*i/3.0,0);
    }

    //Graficación de puntos de visada

    //Nota: En esta versión se simplifica la graficación. Algunos de los parámetros deberían poder variar en rangos determinados.

    QGraphicsRectItem* barraVi1 = escenaPista->addRect(-22.5,-anchoFajasVi/2.0,45,anchoFajasVi, penw, QBrush("white"));
    barraVi1->moveBy(-(p.largo/2.0-distanciaUmVi+22.5),(espaciadoFajasVi/2.0+anchoFajasVi/2.0));

    QGraphicsRectItem* barraVi2 = escenaPista->addRect(-22.5,-anchoFajasVi/2.0,45,anchoFajasVi, penw, QBrush("white"));
    barraVi2->moveBy(-(p.largo/2.0-distanciaUmVi+22.5),-(espaciadoFajasVi/2.0+anchoFajasVi/2.0));

    QGraphicsRectItem* barraVi3 = escenaPista->addRect(-22.5,-anchoFajasVi/2.0,45,anchoFajasVi, penw, QBrush("white"));
    barraVi3->moveBy((p.largo/2.0-distanciaUmVi+22.5),(espaciadoFajasVi/2.0+anchoFajasVi/2.0));

    QGraphicsRectItem* barraVi4 = escenaPista->addRect(-22.5,-anchoFajasVi/2.0,45,anchoFajasVi, penw, QBrush("white"));
    barraVi4->moveBy((p.largo/2.0-distanciaUmVi+22.5),-(espaciadoFajasVi/2.0+anchoFajasVi/2.0));

    //Grafica centro de la pista
    escenaPista->addLine(QLineF(-5,-5,5,5),penb);
    escenaPista->addLine(QLineF(-5,5,5,-5),penb);

    rectItm->setPen(penb);

    vistaPista->fitInView(pavFlexible,Qt::KeepAspectRatio);
    //vistaPista->scale(0.98, 0.98);
}

void GraficadorAeropuerto::reportarDatosEscena()
{
    qInfo() << "escenaPista->sceneRect() = " << escenaPista->sceneRect();
    qInfo() << "ui->graficoPista->sceneRect() = " << vistaPista->sceneRect();
    qInfo() << "Item at (0,0): " << vistaPista->itemAt(vistaPista->mapFromScene(0,0));
    qInfo() << "ui->graficoPista->transform() = " << vistaPista->transform();
    qInfo() << "ui->graficoPista->rect() (from QWidget) = " << vistaPista->rect();
    qInfo() << "ui->graficoPista->contentsRect() (from QWidget) = " << vistaPista->contentsRect();
    qInfo() << "ui->graficoPista->mapToScene(ui->graficoPista->viewport()->geometry()).boundingRect() "
               "(from QAbstractScrollArea) = "
            << vistaPista->mapToScene(vistaPista->viewport()->geometry()).boundingRect();

}
