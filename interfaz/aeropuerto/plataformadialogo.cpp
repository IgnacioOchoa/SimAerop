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
    connect(botonGuardarVert, &QPushButton::pressed, this, &PlataformaDialogo::slotBotonGuardarVert);
    connect(tablaPlataformas, &QTableWidget::itemSelectionChanged, this, &PlataformaDialogo::slotMostrarVert);

    poblarTablaPlataformas();
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
    botonGuardarVert = ui->pbGuardarVert;
    tablaPlataformas = ui->twPlataformas;
    tablaVertices = ui->twVertices;

    //Configuración lista nombres plataformas
    tablaPlataformas->setColumnCount(1);
    tablaPlataformas->setHorizontalHeaderLabels({"Nombre"});
    tablaPlataformas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tablaPlataformas->setColumnWidth(1,150);

    int anchoMinPl = tablaPlataformas->horizontalHeader()->length();
    tablaPlataformas->verticalHeader()->hide();
    tablaPlataformas->setMinimumWidth(anchoMinPl);
    tablaPlataformas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    tablaPlataformas->setSelectionMode( QAbstractItemView::SingleSelection );
    ;

    //Configuración tabla vértices
    tablaVertices->setColumnCount(2);
    tablaVertices->setHorizontalHeaderLabels({"Posición X", "Posición Y"});
    tablaVertices->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    for (int i=0; i<2; i++) {
        tablaVertices->setColumnWidth(i,150);
    }

    int anchoMinVr = tablaVertices->horizontalHeader()->length();
    tablaVertices->verticalHeader()->hide();
    tablaVertices->setMinimumWidth(anchoMinVr);
    tablaVertices->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tablaVertices->setSelectionMode( QAbstractItemView::SingleSelection );
}

void PlataformaDialogo::poblarTablaPlataformas()
{
    tablaPlataformas->setRowCount(listaPlataformas.size());
    for (int i=0; i < listaPlataformas.size(); i++)
    {
        tablaPlataformas->setItem(i,0, new QTableWidgetItem(listaPlataformas[i].nombre));
    }
}

void PlataformaDialogo::poblarTablaVertices(int index)
{
    tablaVertices->setRowCount(listaPlataformas.at(index).coordPerimetro.size());
    for (int i=0; i < listaPlataformas.at(index).coordPerimetro.size(); i++)
    {
        tablaVertices->setItem(i,0, new QTableWidgetItem(QString::number(listaPlataformas.at(index).coordPerimetro[i].x())));
        tablaVertices->setItem(i,1, new QTableWidgetItem(QString::number(listaPlataformas.at(index).coordPerimetro[i].y())));
    }
}

void PlataformaDialogo::slotBotonAgregarPlat()
{
    int indx = tablaPlataformas->rowCount();
    tablaPlataformas->insertRow(indx);
    tablaPlataformas->setItem(indx,0, new QTableWidgetItem(0));
}

void PlataformaDialogo::slotBotonEliminarPlat()
{
    tablaPlataformas->removeRow(tablaPlataformas->currentRow());
}

void PlataformaDialogo::slotBotonAgregarVert()
{
    int indx = tablaVertices->currentRow();
    tablaVertices->insertRow(indx);
    tablaVertices->setItem(indx,0, new QTableWidgetItem(0));
    tablaVertices->setItem(indx,1, new QTableWidgetItem(0));
}

void PlataformaDialogo::slotBotonEliminarVert()
{
    tablaVertices->removeRow(tablaVertices->currentRow());
}

void PlataformaDialogo::slotMostrarVert()
{
    QString toFind = tablaPlataformas->currentItem()->data(Qt::DisplayRole).toString();
    qDebug() << toFind;
    bool found = false;
    for (int i=0; i < listaPlataformas.size(); i++)
    {
        if (listaPlataformas[i].nombre == toFind)
        {
            found = true;
            poblarTablaVertices(i);
        }
    }
    if (!found)
    {
        tablaVertices->setRowCount(0);
        tablaVertices->insertRow(0);
        tablaVertices->setItem(0,0, new QTableWidgetItem(0));
        tablaVertices->setItem(0,1, new QTableWidgetItem(0));
    }
}

void PlataformaDialogo::slotBotonGuardarVert()
{
    // esta función debe modificar los valores de coordPuntos en listaPlataforma
    qDebug()<< "Guardar Vértices";
}

void PlataformaDialogo::dialogoAceptado()
{
    // Debería guardar el listaPlataformas solo las plataformas válidas de la tablaPlataforma
    qDebug()<< "Aceptar";
    this->close();
}

void PlataformaDialogo::dialogoCancelado()
{
    qDebug()<< "Cancelar";
    this->close();
}

