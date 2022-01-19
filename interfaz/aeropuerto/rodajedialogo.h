#ifndef RODAJEDIALOGO_H
#define RODAJEDIALOGO_H

#include <QDialog>
#include <QTableWidget>
#include <QDebug>
#include "rodajecabeceradelegate.h"
#include "../../estructuras-datos/elementosaerop.h"

namespace Ui {
class RodajeDialogo;
}

class RodajeDialogo : public QDialog
{
    Q_OBJECT

public:
    explicit RodajeDialogo(QList<Rodaje>& lr, QWidget* parent = nullptr);
    ~RodajeDialogo();

private:
    Ui::RodajeDialogo *ui;
    QList<Rodaje>& listaRodajes;

    void configurarWidgets();
    void poblarTabla();

    QPushButton* botonAceptar;
    QPushButton* botonCancelar;
    QPushButton* botonAgregar;
    QPushButton* botonEliminar;

    QTableWidget* tablaRodaje;

private slots:
    void dialogoAceptado();
    void dialogoCancelado();
    void slotBotonAgregar();
    void slotBotonEliminar();
};

#endif // RODAJEDIALOGO_H
