#ifndef KERNEL_H
#define KERNEL_H

#include <QtCore>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>

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
    virtual ~Kernel();
    void inicializar(InterfazPrincipal *ip);

public slots:
    void graficarPista();
    void sloCargarFlota(QString);
    void sloGuardarFlota(QString, QList<Aeronave>);

private:
    bool inicializarEditorPista(InterfazPrincipal* ip);
    QList<Flota*> listaFlotas;
    InterfazPrincipal* interfazPpal;
    EditorPista* editorPista;  

signals:
    void pistaActualizada(const Pista& p);
};

#endif // KERNEL_H
