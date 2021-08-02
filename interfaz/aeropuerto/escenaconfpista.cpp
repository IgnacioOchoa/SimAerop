#include "escenaconfpista.h"

EscenaConfPista::EscenaConfPista(QObject* ob) :
    QGraphicsScene(ob)
{
    setSceneRect(QRect(-10000,-3000,20000,6000));
}
