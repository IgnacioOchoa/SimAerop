#ifndef AEROPUERTOVISTA_H
#define AEROPUERTOVISTA_H

#include <QObject>
#include <QGraphicsView>
#include <QDebug>
#include <QWheelEvent>

class AeropuertoVista : public QGraphicsView
{
    Q_OBJECT
public:
    AeropuertoVista(QWidget* w = nullptr);

    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;


private:
    bool ruedaApretada;
    QPointF puntoInicioRueda;
    QPointF centroAnterior;

};

#endif // AEROPUERTOVISTA_H
