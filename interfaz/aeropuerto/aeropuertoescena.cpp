#include "aeropuertoescena.h"

AeropuertoEscena::AeropuertoEscena(QObject* ob) :
    QGraphicsScene(ob)
{
    QLinearGradient gd = QLinearGradient(QPointF(0, 0), QPointF(1, 1));
    gd.setColorAt(0, "#fcf8f2");
    gd.setColorAt(1, "#d4bfa3");
    gd.setCoordinateMode(QGradient::ObjectMode);
    QBrush fondoPista = QBrush(gd);
    setBackgroundBrush(fondoPista);
}
