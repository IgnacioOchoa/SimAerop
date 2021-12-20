#include "plataformadialogo.h"
#include "ui_plataformadialogo.h"

PlataformaDialogo::PlataformaDialogo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlataformaDialogo)
{
    ui->setupUi(this);
    configurarWidgets();

    connect(botonAceptar, &QPushButton::pressed, this, &PlataformaDialogo::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &PlataformaDialogo::dialogoCancelado);
}

void PlataformaDialogo::dialogoAceptado()
{
    this->close();
}

void PlataformaDialogo::dialogoCancelado()
{
    this->close();
}

PlataformaDialogo::~PlataformaDialogo()
{
    delete ui;
}

void PlataformaDialogo::configurarWidgets()
{
    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
}
