#ifndef ESCENACONFPISTA_H
#define ESCENACONFPISTA_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsRectItem>
#include "dibujo/cotagrafica.h"
#include "../../estructuras-datos/elementosaerop.h"

class EscenaConfPista : public QGraphicsScene
{
public:
    EscenaConfPista(QObject* ob = nullptr);
    void graficarPista(Pista p);
    void mostrarCotas(bool);
    void limpiar();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void graficarUmbral(float);

signals:
    void contenidoCambiado();

private:
    QList<CotaGrafica*> listaCotas;
    QGraphicsRectItem* grRectItm;
    CotaGrafica* cota1;
    CotaGrafica* cota2;
    QRect rectPista;
};

#endif // ESCENACONFPISTA_H
