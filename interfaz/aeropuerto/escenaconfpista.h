#ifndef ESCENACONFPISTA_H
#define ESCENACONFPISTA_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsRectItem>
#include "dibujo/cotagrafica.h"

class EscenaConfPista : public QGraphicsScene
{
public:
    EscenaConfPista(QObject* ob = nullptr);
    void graficarPista(QRectF rectPista);

signals:
    void contenidoCambiado();
};

#endif // ESCENACONFPISTA_H
