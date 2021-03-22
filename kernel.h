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
    Kernel(InterfazPrincipal* ip);
    virtual ~Kernel();
    void inicializar(InterfazPrincipal *ip);

public slots:
    void botonGraficarPistaApretado();

private:
    bool inicializarEditorPista(InterfazPrincipal* ip);
    InterfazPrincipal* interfazPpal;
    EditorPista* editorPista;
};

#endif // KERNEL_H
