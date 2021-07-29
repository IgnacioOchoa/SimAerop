#include "kernel.h"

Kernel::Kernel()
{

}

Kernel::Kernel(InterfazPrincipal* ip)
{
    inicializarEditorPista(ip);
    inicializarFlota(ip);
}

Kernel::~Kernel()
{

}

void Kernel::inicializar(InterfazPrincipal *ip)
{
    inicializarEditorPista(ip);
    inicializarFlota(ip);
}

bool Kernel::inicializarEditorPista(InterfazPrincipal* ip)
{
    interfazPpal = ip;
    editorPista = new EditorPista(ip->getVistaPista());
    connect(this, SIGNAL(pistaActualizada(const Pista&)), editorPista, SLOT(actualizarPista(const Pista&)));
    //connect(ip->ui->botonGraficarPista, SIGNAL(clicked()), editor)
    return true;
}

bool Kernel::inicializarFlota(InterfazPrincipal *ip)
{
    interfazPpal = ip;
    flota = new Flota;
    connect(this, SIGNAL(signalCargarFlota()), flota, SLOT(slotCargarFlota()));
    connect(this, SIGNAL(signalGuardarFlota()), flota, SLOT(slotGuardarFlota()));
    return true;
}

void Kernel::graficarPista()
{
    emit pistaActualizada(interfazPpal->getPista());
}

void Kernel::slotCargarFlota()
{
    emit signalCargarFlota();
}

void Kernel::slotGuardarFlota()
{
    emit signalGuardarFlota();
}

