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
    bordePista->setWidth(2);
}

void EditorPista::actualizarPista(const Pista& p)
{
    escenaPista->clear();
    escenaPista->setBackgroundBrush(*fondoPista);
    QGraphicsRectItem* rectItm = new QGraphicsRectItem;
    rectItm = escenaPista->addRect(-p.largo/2.0,-p.ancho/2.0,p.largo,p.ancho, *bordePista, *colorPista);

    QPen penArea(Qt::NoPen);
    escenaPista->addRect(-p.largo/2.0 - 200, -p.ancho/2.0, p.largo + 400, p.ancho, penArea);

    for (int i=0; i<5; i++)
    {
        QGraphicsRectItem* barraBlanca = escenaPista->addRect(-20,-1.5,40,3, QPen("white"), QBrush("white"));
        barraBlanca->moveBy(-p.largo/2.0 + 60,-p.ancho/2.0 + (1 + i)*(p.ancho/2)/6.0);
    }

    for (int i=0; i<5; i++)
    {
        QGraphicsRectItem* barraBlanca = escenaPista->addRect(-20,-1.5,40,3, QPen("white"), QBrush("white"));
        barraBlanca->moveBy(-p.largo/2.0 + 60, p.ancho/2.0 - (1 + i)*(p.ancho/2)/6.0);
    }

    for (int i=0; i<5; i++)
    {
        QGraphicsRectItem* barraBlanca = escenaPista->addRect(-20,-1.5,40,3, QPen("white"), QBrush("white"));
        barraBlanca->moveBy(p.largo/2.0 - 60,-p.ancho/2.0 + (1 + i)*(p.ancho/2)/6.0);
    }

    for (int i=0; i<5; i++)
    {
        QGraphicsRectItem* barraBlanca = escenaPista->addRect(-20,-1.5,40,3, QPen("white"), QBrush("white"));
        barraBlanca->moveBy(p.largo/2.0 - 60, p.ancho/2.0 - (1 + i)*(p.ancho/2)/6.0);
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
