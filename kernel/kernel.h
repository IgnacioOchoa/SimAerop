#ifndef KERNEL_H
#define KERNEL_H

#include <QtCore>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

#include "../interfaz/aeropuerto/graficadoraeropuerto.h"
#include "interfaz/interfazprincipal.h"
#include "../estructuras-datos/elementosaerop.h"
#include "interfaz/aeronaves/flota.h"


class InterfazPrincipal;
//Q_DECLARE_METATYPE(Pista)

class Kernel : public QObject
{
    Q_OBJECT

public:
    Kernel();
    virtual ~Kernel();
    void inicializar(InterfazPrincipal *ip);

public slots:
    void graficarPista();
    void sloCargarFlota(QString);
    void sloGuardarFlota(QString, QList<Aeronave>);

private:
    bool inicializarGraficadorAeropuerto(InterfazPrincipal* ip);
    QList<Flota*> listaFlotas;
    InterfazPrincipal* interfazPpal;
    GraficadorAeropuerto* graficadorAeropuerto;

signals:
    void pistaActualizada(const Pista& p);
};

#endif // KERNEL_H
