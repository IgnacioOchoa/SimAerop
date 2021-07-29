#ifndef KERNEL_H
#define KERNEL_H

#include <QtCore>

#include "../interfaz/aeropuerto/editorpista.h"
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
    Kernel(InterfazPrincipal* ip);
    virtual ~Kernel();
    void inicializar(InterfazPrincipal *ip);

public slots:
    void graficarPista();
    void slotCargarFlota();
    void slotGuardarFlota();

private:
    bool inicializarEditorPista(InterfazPrincipal* ip);
    bool inicializarFlota(InterfazPrincipal* ip);
    InterfazPrincipal* interfazPpal;
    EditorPista* editorPista;
    Flota* flota;

signals:
    void pistaActualizada(const Pista& p);
    void signalCargarFlota();
    void signalGuardarFlota();
};

#endif // KERNEL_H
