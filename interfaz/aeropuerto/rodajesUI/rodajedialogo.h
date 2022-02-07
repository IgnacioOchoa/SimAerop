#ifndef RODAJEDIALOGO_H
#define RODAJEDIALOGO_H

#include <QDialog>
#include <QTableWidget>
#include <QDebug>
#include <QStatusBar>
#include "rodajecabeceradelegate.h"
#include "modelorodajes.h"
#include "rodajeediciondialogo.h"
#include "../../../estructuras-datos/elementosaerop.h"

namespace Ui {
class RodajeDialogo;
}

class RodajeDialogo : public QDialog
{
    Q_OBJECT

public:
    explicit RodajeDialogo(QList<Rodaje>& lr, const QList<Pista> &lp, QWidget* parent = nullptr);
    ~RodajeDialogo();

protected:
    void showEvent(QShowEvent *event) override;
    virtual bool eventFilter(QObject* ob, QEvent* event) override;

private:
    Ui::RodajeDialogo *ui;
    QList<Rodaje>& listaRodajes;
    const QList<Pista>& listaPistas;

    void configurarWidgets();

    QPushButton* botonAceptar;
    QPushButton* botonCancelar;
    QPushButton* botonAgregar;
    QPushButton* botonEliminar;
    QPushButton* botonPrevisualizar;
    QPushButton* botonAbrirEditor;

    QTableView* tablaRodaje;
    ModeloRodajes* modelo;

    RodajeEdicionDialogo* rodajeEdicionDialogo;

private slots:
    void dialogoAceptado();
    void dialogoCancelado();
    void slotBotonAgregar();
    void slotBotonEliminar();
    void slotBotonPrevisualizar();
    void slotLanzarEditorRodaje();
};

#endif // RODAJEDIALOGO_H
