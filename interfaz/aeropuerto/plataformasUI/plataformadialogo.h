#ifndef PLATAFORMADIALOGO_H
#define PLATAFORMADIALOGO_H

#include <QDialog>
#include <QTableWidget>
#include <QListWidget>
#include <QMessageBox>
#include <QDebug>
#include "../../../estructuras-datos/elementosaerop.h"
#include "modelonombresplataformas.h"
#include "modeloplataformasdelegate.h"

namespace Ui {
class PlataformaDialogo;
}

class PlataformaDialogo : public QDialog
{
    Q_OBJECT

public:
    explicit PlataformaDialogo(QList<Plataforma>& la, QWidget *parent = nullptr);
    ~PlataformaDialogo();

protected :
    void showEvent(QShowEvent *event);

private:
    Ui::PlataformaDialogo *ui;

    void configurarWidgets();
    void poblarListNomb();

    QPushButton* botonAceptar;
    QPushButton* botonCancelar;
    QPushButton* botonAgregarPlat;
    QPushButton* botonEliminarPlat;
    QPushButton* botonAgregarVert;
    QPushButton* botonEliminarVert;

    QListView* listaNombres;
    QTableView* tablaVertices;
    ModeloNombresPlataformas* modelo1;
    ModeloVerticesPlataformas* modelo2;

private slots:
    //void onSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void dialogoAceptado();
    void dialogoCancelado();
    void slotBotonAgregarPlat();
    void slotBotonEliminarPlat();
    void slotBotonAgregarVert();
    void slotBotonEliminarVert();
};

#endif // PLATAFORMADIALOGO_H
