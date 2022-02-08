#include "rodajeediciondialogo.h"
#include "ui_rodajeediciondialogo.h"

RodajeEdicionDialogo::RodajeEdicionDialogo(const QList<Pista>& listaPistas, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RodajeEdicionDialogo),
    btnsEdicionRodaje(new QButtonGroup(this))
{
    ui->setupUi(this);
    vista = ui->gvRodajeEdicion;
    escena = new RodajeEdicionEscena(ui->gvRodajeEdicion,listaPistas, this);
    RodajeParametros rp;
    ui->cbModoEdicion->addItems(rp.tiposRodaje);
    ui->gvRodajeEdicion->configEscena(escena);
    ui->cbGrilla->setChecked(false);
    connect(ui->cbGrilla, &QCheckBox::stateChanged, escena, &RodajeEdicionEscena::slotChckMostrarGrilla);

    btnsEdicionRodaje->addButton(ui->pbEditorRodaje1,1);
    btnsEdicionRodaje->addButton(ui->pbEditorRodaje2,2);
    btnsEdicionRodaje->addButton(ui->pbEditorRodaje3,3);

    connect(btnsEdicionRodaje, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &RodajeEdicionDialogo::slotModoEdicion);
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

void RodajeEdicionDialogo::slotModoEdicion(int id)
{
    switch (id) {
    case 1: {vista->setModEdicion(RodajeEdicionVista::modoEdicion::PISTA); break;}
    case 2: {vista->setModEdicion(RodajeEdicionVista::modoEdicion::DOSPUNTOS); break;}
    case 3: {vista->setModEdicion(RodajeEdicionVista::modoEdicion::PARALELA); break;}
    }
}
