#include "editorpista.h"

EditorPista::EditorPista(QGraphicsScene* gs) :
    escena(gs)
{
    QLinearGradient linearGrad(QPointF(-1000, -1000), QPointF(1000, 1000));
        linearGrad.setColorAt(0, "#faf0e3");
        linearGrad.setColorAt(1, "#e0d1bc");
    QBrush br(linearGrad);
    escena->setBackgroundBrush(br);
    //escena->addEllipse(QRectF(0,0,50,50));
    escena->addLine(QLineF(-1000,50,1000,50));
    escena->addLine(QLineF(-1000,-50,1000,-50));
    escena->addLine(QLineF(-1000,50,-1000,-50));
    escena->addLine(QLineF(1000,50,1000,-50));
    escena->addLine(QLineF(-5,-5,5,5));
    escena->addLine(QLineF(-5,5,5,-5));
    escena->setSceneRect(escena->itemsBoundingRect());
    qInfo() << "Scene rect: " << escena->sceneRect();
}
