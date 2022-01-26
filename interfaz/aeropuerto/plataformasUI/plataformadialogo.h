#ifndef PLATAFORMADIALOGO_H
#define PLATAFORMADIALOGO_H

#include <QDialog>
#include <QTableWidget>
#include <QListWidget>
#include <QMessageBox>
#include <QDebug>
#include "../../../estructuras-datos/elementosaerop.h"

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
    QList<Plataforma>& listaPlataformas;

    void configurarWidgets();
    void poblarTablaPlataformas();
    void poblarTablaVertices(int index);

    QPushButton* botonAceptar;
    QPushButton* botonCancelar;
    QPushButton* botonAgregarPlat;
    QPushButton* botonEliminarPlat;
    QPushButton* botonAgregarVert;
    QPushButton* botonEliminarVert;
    QPushButton* botonGuardarVert;

    QTableWidget* tablaPlataformas;
    QTableWidget* tablaVertices;

private slots:
    void dialogoAceptado();
    void dialogoCancelado();
    void slotBotonAgregarPlat();
    void slotBotonEliminarPlat();
    void slotBotonAgregarVert();
    void slotBotonEliminarVert();
    void slotMostrarVert();
    void slotBotonGuardarVert();
};

#endif // PLATAFORMADIALOGO_H
