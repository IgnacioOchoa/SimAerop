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

    if (p.ancho<23){
        fajas = 2;
    }
    else if(p.ancho<30){
        fajas = 3;
    }
    else if(p.ancho<45){
        fajas = 4;
    }
    else if(p.ancho<60){
        fajas = 6;
    }
    else {
        fajas = 8;
    }
   anchoFajas = (p.ancho-6.0)/(fajas*4);

    QPen pen(Qt::white, 0);

    for (int i=0; i<fajas; i++)
    {
        QGraphicsRectItem* barraBlanca = escenaPista->addRect(-15,-anchoFajas/2,30,anchoFajas, pen, QBrush("white"));
        barraBlanca->moveBy(-(p.largo/2.0 - 21),-(p.ancho/2.0 - 3  -anchoFajas/2) + i*anchoFajas*2);
    }

    for (int i=0; i<fajas; i++)
    {
        QGraphicsRectItem* barraBlanca = escenaPista->addRect(-15,-anchoFajas/2,30,anchoFajas, pen, QBrush("white"));
        barraBlanca->moveBy(-(p.largo/2.0 - 21),(p.ancho/2.0 - 3  -anchoFajas/2) - i*anchoFajas*2);
    }

    for (int i=0; i<fajas; i++)
    {
        QGraphicsRectItem* barraBlanca = escenaPista->addRect(-15,-anchoFajas/2,30,anchoFajas, pen, QBrush("white"));
        barraBlanca->moveBy((p.largo/2.0 - 21),-(p.ancho/2.0 - 3 - anchoFajas/2) + i*anchoFajas*2);
    }

    for (int i=0; i<fajas; i++)
    {
        QGraphicsRectItem* barraBlanca = escenaPista->addRect(-15,-anchoFajas/2,30,anchoFajas, pen, QBrush("white"));
        barraBlanca->moveBy((p.largo/2.0 - 21),(p.ancho/2.0 - 3 - anchoFajas/2) - i*anchoFajas*2);
    }

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
