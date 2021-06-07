#include "dialogconfpista.h"
#include "ui_dialogconfpista.h"

#include <QFileDialog>

DialogConfPista::DialogConfPista(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfPista)
{
    ui->setupUi(this);
    configurarWidgets();
    //poblarCabeceras();

    connect(botonAceptar, &QPushButton::pressed, this, &DialogConfPista::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &DialogConfPista::dialogoCancelado);
    connect(botonCargar, &QPushButton::pressed, this, &DialogConfPista::seleccionarAbrirArchivo);

}

DialogConfPista::~DialogConfPista()
{
    delete ui;
}

void DialogConfPista::configurarWidgets()
{
    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
    botonCargar = ui->pbCargar;
    botonGuardar = ui->pbGuardar;
    botonOpAvanzadas = ui->pbOpcionesAvanzadas;
    leLargoPista = ui->leLargo;
    leAnchoPista = ui->leAncho;
    leNombreArchivo = ui->leNombreArchivo;
    leRutaArchivo = ui->leRutaArchivo;
    vistaPreliminar = ui->gvPreVisualizacion;
    layoutDial = ui->vlDial;
    leOrientacion = ui->leOrientacion;
    layoutDial->setAlignment(leOrientacion,Qt::AlignCenter);
}

void DialogConfPista::dialogoAceptado()
{
    this->close();
}

void DialogConfPista::dialogoCancelado()
{
    this->close();
}

void DialogConfPista::poblarCabeceras()
{
    /*for (int i=0; i<18; i++)
    {
        cbCabecera1->addItem(QString::number(i).rightJustified(2,'0'));
        cbCabecera2->addItem(QString::number(i+18).rightJustified(2,'0'));
    }

    connect(cbCabecera1, QOverload<int>::of(&QComboBox::currentIndexChanged), cbCabecera2, &QComboBox::setCurrentIndex);
    connect(cbCabecera2, QOverload<int>::of(&QComboBox::currentIndexChanged), cbCabecera1, &QComboBox::setCurrentIndex);
    */
}

void DialogConfPista::seleccionarAbrirArchivo()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Seleccionar archivo");
    QUrl direccion(file_name);
    leNombreArchivo->setText(direccion.fileName());
    leRutaArchivo->setText(direccion.adjusted(QUrl::RemoveFilename).url());
    leRutaArchivo->setCursorPosition(0);
}
