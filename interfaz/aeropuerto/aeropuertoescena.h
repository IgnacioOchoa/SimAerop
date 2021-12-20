#ifndef AEROPUERTOESCENA_H
#define AEROPUERTOESCENA_H

#include <QObject>
#include <QGraphicsScene>

class AeropuertoEscena : public QGraphicsScene
{
    Q_OBJECT
public:
    AeropuertoEscena(QObject* ob = nullptr);
};

#endif // AEROPUERTOESCENA_H

