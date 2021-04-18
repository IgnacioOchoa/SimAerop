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

};

#endif // CUSTOMGRAPHICSVIEW_H
