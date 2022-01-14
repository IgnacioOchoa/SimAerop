#include "kernel.h"

Kernel::Kernel()
{

}

Kernel::~Kernel()
{

}

void Kernel::inicializar(InterfazPrincipal *ip)
{
    interfazPpal = ip;
    inicializarGraficadorAeropuerto(ip);
}

bool Kernel::inicializarGraficadorAeropuerto(InterfazPrincipal* ip)
{
    graficadorAeropuerto = new GraficadorAeropuerto(ip->getVistaAeropuerto());
    connect(this, SIGNAL(aeropuertoActualizado(const QList<Pista>&, const QList<Rodaje>&, const QList<Plataforma>&)), graficadorAeropuerto, SLOT(actualizarAeropuerto(const QList<Pista>&, const QList<Rodaje>&, const QList<Plataforma>&)));
    //connect(ip->ui->botonGraficarPista, SIGNAL(clicked()), editor)
    return true;
}

void Kernel::graficarPista()
{
    emit aeropuertoActualizado(interfazPpal->getPistas(), interfazPpal->getRodajes(), interfazPpal->getPlataformas());
}

void Kernel::sloCargarFlota(QString filename)
{
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Acá debería correr código para devolver Interfaz el error";
        //QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    Flota* miFlota = new Flota();
    listaFlotas.append(miFlota);
    miFlota->cargadorFlota(file);
    file.close();
    interfazPpal->mostradorFlota(miFlota->getListaFlota());
}

void Kernel::sloGuardarFlota(QString filename, QList<Aeronave> flota)
{
    QString name = QFileInfo(filename).fileName();
    int pos = name.lastIndexOf(QChar('.'));
    Flota* miFlota = new Flota(name.left(pos), flota);
    //Chequea si miFlota está en listaFlota
    if (!listaFlotas.contains(miFlota)){
        listaFlotas.append(miFlota);
    }
    else {
        qDebug() << "Debería emitir error por nombre de flota repetido";
    }
    miFlota->guardadorFlota(filename);
}
