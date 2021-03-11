#include "kernel.h"

Kernel::Kernel()
{

}

Kernel::~Kernel()
{

}

bool Kernel::inicializar(InterfazPrincipal* ip, QGraphicsScene* gs)
{
    interfazPpal = ip;
    editorPista = new EditorPista(gs);
    return true;
}

void Kernel::botonGraficarPistaApretado()
{

}


