#include "rodajeediciondialogo.h"
#include "ui_rodajeediciondialogo.h"

RodajeEdicionDialogo::RodajeEdicionDialogo(const QList<Pista>& listaPistas, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RodajeEdicionDialogo),
    btnsEdicionRodaje(new QButtonGroup(this))
{
    ui->setupUi(this);
    escena = new RodajeEdicionEscena(ui->gvRodajeEdicion,listaPistas, this);
    configurarWidgets();
    actualizarPanelParametros();
    ui->pbEditorRodaje1->setChecked(true);
    slotModoEdicionCambiado(RodajeEdicionVista::modoEdicion::PISTA);
    vista->slotSetModEdicion(RodajeEdicionVista::modoEdicion::PISTA);
}

RodajeEdicionDialogo::~RodajeEdicionDialogo()
{
    delete ui;
}

void RodajeEdicionDialogo::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    escena->graficar();
}

void RodajeEdicionDialogo::slotModoEdicionCambiado(int m)
{
    RodajeParametros rp;
    RodajeEdicionVista::modoEdicion modo = static_cast<RodajeEdicionVista::modoEdicion>(m);
    switch(modo) {
    case RodajeEdicionVista::modoEdicion::PISTA:
        ui->lbModoEdicion->setText("Modo edición: " + rp.tiposRodaje[0]);
        ui->swPanelParametros->setCurrentIndex(0);
        //ui->gbParametros->
        break;
    case RodajeEdicionVista::modoEdicion::DOSPUNTOS:
        ui->lbModoEdicion->setText("Modo edición: " + rp.tiposRodaje[1]);
        ui->swPanelParametros->setCurrentIndex(1);
        //ui->gbParametros->
        break;
    case RodajeEdicionVista::modoEdicion::PARALELA:
        ui->lbModoEdicion->setText("Modo edición: " + rp.tiposRodaje[2]);
        ui->swPanelParametros->setCurrentIndex(2);
        //ui->gbParametros->
        break;
    case RodajeEdicionVista::modoEdicion::NULO:
        break;
        //ui->gbParametros->
    }
}

void RodajeEdicionDialogo::configurarWidgets()
{
    vista = ui->gvRodajeEdicion;
    RodajeParametros rp;

    ui->gvRodajeEdicion->configEscena(escena);
    ui->cbGrilla->setChecked(false);
    btnsEdicionRodaje->addButton(ui->pbEditorRodaje1, RodajeEdicionVista::modoEdicion::PISTA);
    btnsEdicionRodaje->addButton(ui->pbEditorRodaje2, RodajeEdicionVista::modoEdicion::DOSPUNTOS);
    btnsEdicionRodaje->addButton(ui->pbEditorRodaje3, RodajeEdicionVista::modoEdicion::PARALELA);
    connect(ui->cbGrilla, &QCheckBox::stateChanged, escena, &RodajeEdicionEscena::slotChckMostrarGrilla);
    connect(btnsEdicionRodaje, QOverload<int>::of(&QButtonGroup::idPressed), vista, &RodajeEdicionVista::slotSetModEdicion);
    connect(btnsEdicionRodaje, QOverload<int>::of(&QButtonGroup::idPressed), this, &RodajeEdicionDialogo::slotModoEdicionCambiado);
    ui->pbEditorRodaje1->setToolTip(rp.tiposRodaje[0]);
    ui->pbEditorRodaje2->setToolTip(rp.tiposRodaje[1]);
    ui->pbEditorRodaje3->setToolTip(rp.tiposRodaje[2]);

}

void RodajeEdicionDialogo::actualizarPanelParametros()
{

}
