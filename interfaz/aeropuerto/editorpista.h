#ifndef EDITORPISTA_H
#define EDITORPISTA_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include <QFloat16>

#include "../../estructuras-datos/elementosaerop.h"

//Q_DECLARE_METATYPE(Pista)

class EditorPista : public QObject
{
    Q_OBJECT

public:
    EditorPista(QGraphicsView* gv);

public slots:
    void actualizarPista(const Pista& p);

private:
    void reportarDatosEscena();

    QGraphicsView* vistaPista;
    QGraphicsScene* escenaPista;

    QLinearGradient* gradienteFondoPista;
    QBrush* fondoPista;
    QBrush* colorPista;
    QPen* bordePista;
    qint8 fajas;
    double anchoFajasUm;
    double anchoFajasLa;
};

#endif // EDITORPISTA_H
