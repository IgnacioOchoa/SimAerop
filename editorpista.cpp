#include "editorpista.h"

EditorPista::EditorPista(QGraphicsView *gv) :
    vistaPista(gv)
{
    escenaPista = gv->scene();
    QLinearGradient linearGrad(QPointF(-1000, -1000), QPointF(1000, 1000));
        linearGrad.setColorAt(0, "#faf0e3");
        linearGrad.setColorAt(1, "#e0d1bc");
    QBrush br(linearGrad);
    escenaPista->setBackgroundBrush(br);
    //escena->addEllipse(QRectF(0,0,50,50));
    escenaPista->addRect(-1000,-50,2000,100);
    //escena->addLine(QLineF(-1000,50,1000,50));
    //escena->addLine(QLineF(-1000,-50,1000,-50));
    //escena->addLine(QLineF(-1000,50,-1000,-50));
    //escena->addLine(QLineF(1000,50,1000,-50));
    escenaPista->addLine(QLineF(-5,-5,5,5));
    escenaPista->addLine(QLineF(-5,5,5,-5));

    vistaPista->fitInView(-500,-25,1000,50,Qt::KeepAspectRatioByExpanding);

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
