#include "interfazprincipalalternativa.h"
#include "ui_interfazPrincipalAlt.h"

InterfazPrincipalAlternativa::InterfazPrincipalAlternativa(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterfazPrincipalAlt)
{
    ui->setupUi(this);
    setWindowTitle("SimAerop");

    QList<QString> secciones = {"AERONAVES", "AEROPUERTO", "OPERACIONES", "SIMULACIÓN"};
    colores = {"#daf2f7", "#ffffe6", "#f2e6ff", "#e6fff7"};

    QFont fnt;
    fnt.setPointSize(14);
    for (int i = 0; i < secciones.size(); i++)
    {
        QListWidgetItem* itm = new QListWidgetItem(secciones[i]);
        itm->setFont(fnt);
        ui->listWidget->addItem(itm);
        itm->setTextAlignment(Qt::AlignCenter);
    }

    ui->listWidget->setCurrentRow(0);
    ui->stackedWidget->setCurrentIndex(0);
    connect(ui->listWidget, &QListWidget::currentItemChanged, this, &InterfazPrincipalAlternativa::listItemSelected);
}

InterfazPrincipalAlternativa::~InterfazPrincipalAlternativa()
{
    delete ui;
}

void InterfazPrincipalAlternativa::listItemSelected(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->stackedWidget->setCurrentIndex(ui->listWidget->currentRow());
}
