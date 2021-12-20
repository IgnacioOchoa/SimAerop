#ifndef PISTAESCENA_H
#define PISTAESCENA_H

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsRectItem>
#include "dibujo/cotagrafica.h"
#include "../../estructuras-datos/elementosaerop.h"

class PistaEscena : public QGraphicsScene
{

public:
    PistaEscena(QObject* ob = nullptr);
    enum class Lado {IZQ, DER};
    void graficarPista(Pista p);
    void mostrarCotas(bool);
    void limpiar();
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void graficarUmbral(float, Lado);
signals:
    void contenidoCambiado();

private:
    QList<CotaGrafica*> listaCotas;
    QGraphicsRectItem* grRectItm;
    CotaGrafica* cota1;
    CotaGrafica* cota2;
    QRect rectPista;
};

#endif // PISTAESCENA_H
