#include "dialogconfrodaje.h"
#include "ui_dialogconfrodaje.h"

DialogConfRodaje::DialogConfRodaje(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfRodaje)
{
    ui->setupUi(this);
    configurarWidgets();

    connect(botonAceptar, &QPushButton::pressed, this, &DialogConfRodaje::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &DialogConfRodaje::dialogoCancelado);
}

DialogConfRodaje::~DialogConfRodaje()
{
    delete ui;
}

void DialogConfRodaje::configurarWidgets()
{
    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
}

void DialogConfRodaje::dialogoAceptado()
{
    this->close();
}

void DialogConfRodaje::dialogoCancelado()
{
    this->close();
}
