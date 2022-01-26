#include "plataformadialogo.h"
#include "ui_plataformadialogo.h"

PlataformaDialogo::PlataformaDialogo(QList<Plataforma> &la, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlataformaDialogo),
    listaPlataformas(la)
{
    ui->setupUi(this);
    configurarWidgets();

    connect(botonAceptar, &QPushButton::pressed, this, &PlataformaDialogo::dialogoAceptado);
    connect(botonCancelar, &QPushButton::pressed, this, &PlataformaDialogo::dialogoCancelado);
    connect(botonAgregarPlat, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonAgregarPlat);
    connect(botonEliminarPlat, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonEliminarPlat);
    connect(botonAgregarVert, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonAgregarVert);
    connect(botonEliminarVert, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonEliminarVert);
}

PlataformaDialogo::~PlataformaDialogo()
{
    delete ui;
}

void PlataformaDialogo::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    poblarListNomb();
}

void PlataformaDialogo::configurarWidgets()
{
    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
    botonAgregarPlat = ui->pbAgregarPlat;
    botonEliminarPlat = ui->pbEliminarPlat;
    botonAgregarVert = ui->pbAgregarVert;
    botonEliminarVert = ui->pbEliminarVert;
    listaNombres = ui->lvNombres;
    tablaVertices = ui->tvVertices;
}

void PlataformaDialogo::poblarListNomb()
{
    listNomb.clear();

    for (int i = 0; i < listaPlataformas.size(); i++)
    {
        listNomb.append(listaPlataformas.at(i).nombre);
        qDebug() << listNomb.at(listNomb.size()-1);
    }

    //Configuración lista nombres plataformas
    model = new modeloPlataformas(listNomb,this);
    listaNombres->setModel(model);
}

void PlataformaDialogo::slotBotonAgregarPlat()
{

}

void PlataformaDialogo::slotBotonEliminarPlat()
{

}

void PlataformaDialogo::slotBotonAgregarVert()
{

}

void PlataformaDialogo::slotBotonEliminarVert()
{

}

void PlataformaDialogo::dialogoAceptado()
{
    // Debería guardar el listaPlataformas solo las plataformas válidas de la tablaPlataforma
    this->close();
}

void PlataformaDialogo::dialogoCancelado()
{
    this->close();
}

