#ifndef KERNEL_H
#define KERNEL_H

#include <QtCore>

#include "editorpista.h"
#include "interfazprincipal.h"
#include "elementosaerop.h"

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

private:
    bool inicializarEditorPista(InterfazPrincipal* ip);
    InterfazPrincipal* interfazPpal;
    EditorPista* editorPista;

signals:
    void pistaActualizada(const Pista& p);

};

#endif // KERNEL_H
