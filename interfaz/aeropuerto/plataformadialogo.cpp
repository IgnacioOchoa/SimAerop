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

    poblarTablaPlataformas();
    poblarTablaVertices(0);
}

PlataformaDialogo::~PlataformaDialogo()
{
    delete ui;
}

void PlataformaDialogo::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    poblarTablaPlataformas();
}

void PlataformaDialogo::configurarWidgets()
{
    botonAceptar = ui->pbAceptar;
    botonCancelar = ui->pbCancelar;
    botonAgregarPlat = ui->pbAgregarPlat;
    botonEliminarPlat = ui->pbEliminarPlat;
    botonAgregarVert = ui->pbAgregarVert;
    botonEliminarVert = ui->pbEliminarVert;
    tablaPlataformas = ui->twPlataformas;
    tablaVertices = ui->twVertices;

    //Configuración tabla plataformas
    tablaPlataformas->setColumnCount(1);
    tablaPlataformas->setHorizontalHeaderLabels({"Nombre Plataforma"});
    tablaPlataformas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (int i=0; i<1; i++) {
        tablaPlataformas->setColumnWidth(i,150);
    }

    int anchoMinPl = tablaPlataformas->horizontalHeader()->length();
    tablaPlataformas->verticalHeader()->hide();
    tablaPlataformas->setMinimumWidth(anchoMinPl);
    tablaPlataformas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //Configuración tabla vértices
    tablaVertices->setColumnCount(3);
    tablaVertices->setHorizontalHeaderLabels({"# Vértice", "Posición X", "Posición Y"});
    tablaVertices->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (int i=0; i<3; i++) {
        tablaVertices->setColumnWidth(i,150);
    }

    int anchoMinVr = tablaVertices->horizontalHeader()->length();
    tablaVertices->verticalHeader()->hide();
    tablaVertices->setMinimumWidth(anchoMinVr);
    tablaVertices->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void PlataformaDialogo::poblarTablaPlataformas()
{
    tablaPlataformas->setRowCount(listaPlataformas.size());
    for (int i=0; i < listaPlataformas.size(); i++)
    {
        tablaPlataformas->setItem(i,0, new QTableWidgetItem(listaPlataformas[i].nombre));
    }

    tablaPlataformas->setEditTriggers(QAbstractItemView::DoubleClicked
                                 | QAbstractItemView::CurrentChanged);
}

void PlataformaDialogo::poblarTablaVertices(int index)
{
    tablaVertices->setRowCount(listaPlataformas.at(index).coordPerimetro.size());
    for (int i=0; i < listaPlataformas.at(index).coordPerimetro.size(); i++)
    {
        tablaVertices->setItem(i,0, new QTableWidgetItem(QString::number(i)));
        tablaVertices->setItem(i,1, new QTableWidgetItem(QString::number(listaPlataformas.at(index).coordPerimetro[i].x())));
        tablaVertices->setItem(i,2, new QTableWidgetItem(QString::number(listaPlataformas.at(index).coordPerimetro[i].y())));
    }
    tablaPlataformas->setEditTriggers(QAbstractItemView::DoubleClicked
                                 | QAbstractItemView::CurrentChanged);
}

void PlataformaDialogo::dialogoAceptado()
{
    this->close();
}

void PlataformaDialogo::dialogoCancelado()
{
    this->close();
}

void PlataformaDialogo::slotBotonAgregarPlat()
{
    tablaPlataformas->insertRow(tablaPlataformas->rowCount());
}

void PlataformaDialogo::slotBotonEliminarPlat()
{
    tablaPlataformas->removeRow(tablaPlataformas->currentRow());
}

void PlataformaDialogo::slotBotonAgregarVert()
{
    tablaVertices->insertRow(tablaVertices->rowCount());
}

void PlataformaDialogo::slotBotonEliminarVert()
{
    tablaVertices->removeRow(tablaVertices->currentRow());
}


