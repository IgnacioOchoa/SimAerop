#ifndef KERNEL_H
#define KERNEL_H

#include "editorpista.h"
#include "interfazprincipal.h"
#include "elementosaerop.h"

class InterfazPrincipal;
Q_DECLARE_METATYPE(Pista)

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
    struct Pista;

signals:
    void pistaActualizada(Pista* p);

};

#endif // KERNEL_H
