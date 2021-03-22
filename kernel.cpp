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
    connect(this, SIGNAL(pistaActualizada(const Pista&)), editorPista, SLOT(actualizarPista(const Pista&)));
    //connect(ip->ui->botonGraficarPista, SIGNAL(clicked()), editor)
    return true;
}

void Kernel::graficarPista()
{
    emit pistaActualizada(interfazPpal->getPista());
}


