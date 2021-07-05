#ifndef CUSTOMGRAPHICSSCENE_H
#define CUSTOMGRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>

class customGraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    customGraphicsScene(QObject* ob = nullptr);
};

#endif // CUSTOMGRAPHICSSCENE_H
