#ifndef CUSTOMGRAPHICSVIEW_H
#define CUSTOMGRAPHICSVIEW_H

#include <QObject>
#include <QGraphicsView>

class customGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    customGraphicsView(QWidget* w = nullptr);
};

#endif // CUSTOMGRAPHICSVIEW_H
