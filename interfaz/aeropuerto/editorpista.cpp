#include "editorpista.h"

EditorPista::EditorPista(QGraphicsView *gv) :
    vistaPista(gv)
{
    escenaPista = gv->scene();
    gradienteFondoPista = new QLinearGradient(QPointF(-1000, -1000), QPointF(1000, 1000));
    gradienteFondoPista->setColorAt(0, "#faf0e3");
    gradienteFondoPista->setColorAt(1, "#e0d1bc");
    fondoPista = new QBrush(*gradienteFondoPista);
    colorPista = new QBrush("#A4B3B6");
    escenaPista->setBackgroundBrush(*fondoPista);
    bordePista = new QPen;
    bordePista->setWidth(0);
}

void EditorPista::actualizarPista(const Pista& p)
{
    escenaPista->clear();
    escenaPista->setBackgroundBrush(*fondoPista);
    QGraphicsRectItem* rectItm = new QGraphicsRectItem;
    rectItm = escenaPista->addRect(-p.largo/2.0,-p.ancho/2.0,p.largo,p.ancho, *bordePista, *colorPista);

    QPen penArea(Qt::NoPen);
    escenaPista->addRect(-p.largo/2.0 - 200, -p.ancho/2.0, p.largo + 400, p.ancho, penArea);


    //GRAFICADOR DE PINTURA DE PISTA

    //Determinación de Parámetros según ancho de pista
    if (p.ancho<23){
        fajas = 2;
        anchoFajasLa = 0.3;
    }
    else if(p.ancho<30){
        fajas = 3;
        anchoFajasLa = 0.45;
    }
    else if(p.ancho<45){
        fajas = 4;
        anchoFajasLa = 0.9;
    }
    else if(p.ancho<60){
        fajas = 6;
        anchoFajasLa = 0.9;
    }
    else {
        fajas = 8;
        anchoFajasLa = 0.9;
    }

    QPen pen(Qt::white, 0);

   //Determinación de ancho de fajas según ancho de pista
   if (p.ancho>=60){
       anchoFajasUm = (54.0)/(fajas*4);
   }
   else {
       anchoFajasUm = (p.ancho-6.0)/(fajas*4);
   }

    //Graficación de barras de umbral
    for (int i=0; i<fajas; i++)
    {
        QGraphicsRectItem* barraUm1 = escenaPista->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, pen, QBrush("white"));
        barraUm1->moveBy(-(p.largo/2.0 - 21),-(p.ancho/2.0 - 3  -anchoFajasUm/2) + i*anchoFajasUm*2);

        QGraphicsRectItem* barraUm2 = escenaPista->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, pen, QBrush("white"));
        barraUm2->moveBy(-(p.largo/2.0 - 21),(p.ancho/2.0 - 3  -anchoFajasUm/2) - i*anchoFajasUm*2);

        QGraphicsRectItem* barraUm3 = escenaPista->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, pen, QBrush("white"));
        barraUm3->moveBy((p.largo/2.0 - 21),-(p.ancho/2.0 - 3 - anchoFajasUm/2) + i*anchoFajasUm*2);

        QGraphicsRectItem* barraUm4 = escenaPista->addRect(-15,-anchoFajasUm/2,30,anchoFajasUm, pen, QBrush("white"));
        barraUm4->moveBy((p.largo/2.0 - 21),(p.ancho/2.0 - 3 - anchoFajasUm/2) - i*anchoFajasUm*2);
    }

    //Graficación de fajas transversales de umbral
    QGraphicsRectItem* barraTr1 = escenaPista->addRect(-0.9,-p.ancho/2,1.8,p.ancho, pen, QBrush("white"));
    barraTr1->moveBy((p.largo/2.0 - 0.9),0);

    QGraphicsRectItem* barraTr2 = escenaPista->addRect(-0.9,-p.ancho/2,1.8,p.ancho, pen, QBrush("white"));
    barraTr2->moveBy(-(p.largo/2.0 - 0.9),0);

    //Graficación de fajas laterales de pista
    QGraphicsRectItem* barraLa1 = escenaPista->addRect(-p.largo/2,-anchoFajasLa/2,p.largo,anchoFajasLa, pen, QBrush("white"));
    barraLa1->moveBy(0,p.ancho/2-anchoFajasLa/2);

    QGraphicsRectItem* barraLa2 = escenaPista->addRect(-p.largo/2,-anchoFajasLa/2,p.largo,anchoFajasLa, pen, QBrush("white"));
    barraLa2->moveBy(0,-p.ancho/2+anchoFajasLa/2);

    escenaPista->addLine(QLineF(-5,-5,5,5));
    escenaPista->addLine(QLineF(-5,5,5,-5));

    vistaPista->fitInView(rectItm,Qt::KeepAspectRatio);
    //vistaPista->scale(0.98, 0.98);
}

void EditorPista::reportarDatosEscena()
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
