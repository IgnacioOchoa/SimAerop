#ifndef EDITORPISTA_H
#define EDITORPISTA_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>

class EditorPista
{
public:
    EditorPista(QGraphicsView* gv);

private:
    void reportarDatosEscena();

    QGraphicsView* vistaPista;
    QGraphicsScene* escenaPista;
};

#endif // EDITORPISTA_H
