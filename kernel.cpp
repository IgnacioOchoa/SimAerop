#include "kernel.h"

Kernel::Kernel()
{

}

Kernel::Kernel(InterfazPrincipal* ip)
{
    inicializarEditorPista(ip);
}

Kernel::~Kernel()
{

}

void Kernel::inicializar(InterfazPrincipal *ip)
{
    inicializarEditorPista(ip);
}

bool Kernel::inicializarEditorPista(InterfazPrincipal* ip)
{
    interfazPpal = ip;
    editorPista = new EditorPista(ip->getVistaPista());
    return true;
}

void Kernel::botonGraficarPistaApretado()
{

}


