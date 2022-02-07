#include "rodajeediciondialogo.h"
#include "ui_rodajeediciondialogo.h"

RodajeEdicionDialogo::RodajeEdicionDialogo(const QList<Pista>& listaPistas, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RodajeEdicionDialogo)
{
    ui->setupUi(this);
    vista = ui->gvRodajeEdicion;
    escena = new RodajeEdicionEscena(ui->gvRodajeEdicion,listaPistas, this);
    RodajeParametros rp;
    ui->cbModoEdicion->addItems(rp.tiposRodaje);
    ui->gvRodajeEdicion->configEscena(escena);
    ui->cbGrilla->setChecked(false);
    connect(ui->cbGrilla, &QCheckBox::stateChanged, escena, &RodajeEdicionEscena::slotChckMostrarGrilla);
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
