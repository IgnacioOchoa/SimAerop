#include "kernel.h"

Kernel::Kernel()
{

}

Kernel::~Kernel()
{

}

bool Kernel::inicializar(InterfazPrincipal* ip)
{
    interfazPpal = ip;
    return true;
}


