#ifndef GRILLAGUIA_H
#define GRILLAGUIA_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QtMath>

class GrillaGuia : public QObject
{
    Q_OBJECT
public:
    GrillaGuia(QGraphicsView* vista, QGraphicsScene* gs, QObject* parent = nullptr);

    void crearGrid();
    void actualizarGrid();
    void regenerarGrid();
    void mostrarGrilla(bool mostrar);
    void centroMovido();
    int calcularGridSize();
    void verificarEscala();
    void setVista(const QGraphicsView* v) {vista = v;}
    void setPen(QPen p) {penGrilla = p;}

private:
    QGraphicsScene* escena;
    const QGraphicsView* vista;
    int gridSize;
    bool grillaCreada;

    QVector<QGraphicsLineItem*> elementosGridX;
    QVector<QGraphicsLineItem*> elementosGridY;

    QPen penGrilla;

    QPointF centroVisible;

    static constexpr int NRO_LIN = 24;

    float sceneXmin;
    float sceneYmin;
    float sceneXmax;
    float sceneYmax;

    int xMayor;
    int yMayor;
    int xMenor;
    int yMenor;
    int indxXmenor;
    int indxYmenor;

};

#endif // GRILLAGUIA_H
