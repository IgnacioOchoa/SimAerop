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
    virtual bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void slotModoEdicionCambiado(RodajeEdicionVista::modoEdicion m);
    void slotCabeceraSeleccionada(QString cabecera) const;
    void slotPistaSeleccionada(int nroPista);
    void slotBotonModoEdicionAccionado(int nroBoton);

private:
    void prepararEscena();
    void configurarWidgets();
    void actualizarPanelParametros();
    void parametrosIniciales();
    Ui::RodajeEdicionDialogo *ui;
    RodajeEdicionEscena* escena;
    RodajeEdicionVista* vista;
    QButtonGroup* btnsEdicionRodaje;
    const QList<Pista>& pistas;

};

#endif // RODAJEEDICIONDIALOGO_H
