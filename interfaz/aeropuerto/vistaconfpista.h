#ifndef VISTACONFPISTA_H
#define VISTACONFPISTA_H

#include <QGraphicsView>
#include <QObject>
#include <QMouseEvent>
#include <QDebug>

class VistaConfPista : public QGraphicsView
{
public:
    VistaConfPista(QWidget* = nullptr);

    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;
    void centrarVista(QPointF p = QPointF());

private:
    QPointF inicioRueda;
    QPointF centroVista;

};

#endif // VISTACONFPISTA_H
