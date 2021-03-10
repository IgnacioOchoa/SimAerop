#ifndef EDITORPISTA_H
#define EDITORPISTA_H

#include <QObject>
#include <QGraphicsScene>

class EditorPista
{
public:
    EditorPista(QGraphicsScene* gs);

private:
    QGraphicsScene* escena;
};

#endif // EDITORPISTA_H
