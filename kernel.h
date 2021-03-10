#ifndef KERNEL_H
#define KERNEL_H

#include "editorpista.h"
#include "interfazprincipal.h"

class InterfazPrincipal;

class Kernel
{
public:
    Kernel();
    ~Kernel();
    bool inicializar(InterfazPrincipal* ip);

private:
    InterfazPrincipal* interfazPpal;
    EditorPista* editorPista;
};

#endif // KERNEL_H
