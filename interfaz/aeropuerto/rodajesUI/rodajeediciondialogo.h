#ifndef RODAJEEDICIONDIALOGO_H
#define RODAJEEDICIONDIALOGO_H

#include <QDialog>
#include <QButtonGroup>
#include "rodajeedicionescena.h"
#include "rodajeedicionvista.h"
#include "../../../estructuras-datos/elementosaerop.h"

namespace Ui {
class RodajeEdicionDialogo;
}

class RodajeEdicionDialogo : public QDialog
{
    Q_OBJECT
public:
    explicit RodajeEdicionDialogo(const QList<Pista>& listaPistas, QWidget *parent = nullptr);
    ~RodajeEdicionDialogo();
    virtual void showEvent(QShowEvent *event) override;

private slots:
    void slotModoEdicionCambiado(int m);

private:
    void prepararEscena();
    void configurarWidgets();
    void actualizarPanelParametros();
    Ui::RodajeEdicionDialogo *ui;
    RodajeEdicionEscena* escena;
    RodajeEdicionVista* vista;
    QButtonGroup* btnsEdicionRodaje;

};

#endif // RODAJEEDICIONDIALOGO_H
