#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QDebug>
#include <QWheelEvent>

class customGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    customGraphicsView(QWidget* w = nullptr);

    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;


private:
    bool ruedaApretada;
    QPointF puntoInicioRueda;
    QPointF centroAnterior;

};

#endif // CUSTOMGRAPHICSVIEW_H
