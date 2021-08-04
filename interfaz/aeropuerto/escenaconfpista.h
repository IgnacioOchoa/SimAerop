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
    void mostrarCotas(bool);
    void limpiar();

signals:
    void contenidoCambiado();

private:
    QList<CotaGrafica*> listaCotas;
    QGraphicsRectItem* grRectItm;
};

#endif // ESCENACONFPISTA_H
