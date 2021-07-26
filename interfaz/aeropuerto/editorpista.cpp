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

    QPen penw(Qt::white, 0);
    QPen penb(Qt::black, 0);

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
    QPainterPath outer;
    //add outer points
    outer.addRect(-p.largo/2.0,-p.ancho/2.0,p.largo,p.ancho);
    QPainterPath inner;
    //add inner points
    inner.addRect(-p.largo/2.0+1.8,-p.ancho/2.0+anchoFajasLa,p.largo-3.6,p.ancho-anchoFajasLa*2);
    outer = outer.subtracted(inner);

    QGraphicsPathItem* fajasTransyLat = escenaPista->addPath(outer, penw,  QBrush("white"));

    //Graficación de fajas transversales de umbral y fajas laterales de pista
    //36 (umbrales) + 12+9+12 m = 67 -> x2 = p.largo - 134
    //Una señal de eje de pista consistirá en una línea de trazos uniformemente espaciados. La longitud de
    //un trazo más la del intervalo no será menor de 50 m ni mayor de 75 m. La longitud de cada trazo será por lo
    //menos igual a la longitud del intervalo, o de 30 m, tomándose la que sea mayor.
    qDebug() << (p.largo-134);
    for (int i=0; i<(p.largo-134)/50; i++)
    {
        QGraphicsRectItem* ejePista = escenaPista->addRect(-12.5,-0.45,25,0.9, penw, QBrush("white"));
        ejePista->moveBy(-(p.largo/2.0 - 67-12.5)+50*i,0);
    }

    //Grafica centro de la pista
    escenaPista->addLine(QLineF(-5,-5,5,5),penb);
    escenaPista->addLine(QLineF(-5,5,5,-5),penb);

    rectItm->setPen(penb);

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
