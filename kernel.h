#ifndef KERNEL_H
#define KERNEL_H

#include "editorpista.h"
#include "interfazprincipal.h"

class InterfazPrincipal;

class Kernel : public QObject
{
    Q_OBJECT

public:
    Kernel();
    virtual ~Kernel();
    bool inicializar(InterfazPrincipal* ip, QGraphicsScene* gs);

public slots:
    void botonGraficarPistaApretado();

private:
    InterfazPrincipal* interfazPpal;
    EditorPista* editorPista;
};

#endif // KERNEL_H
