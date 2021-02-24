#include "interfazprincipalalternativa.h"
#include "ui_interfazPrincipalAlt.h"

InterfazPrincipalAlternativa::InterfazPrincipalAlternativa(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterfazPrincipalAlt)
{
    ui->setupUi(this);
    setWindowTitle("SimAerop");

    QList<QString> secciones = {"AERONAVES", "AEROPUERTOS", "OPERACIONES", "SIMULACIÓN"};
    QFont fnt;
    fnt.setPointSize(14);
    for (int i = 0; i < secciones.size(); i++)
    {
        QListWidgetItem* itm = new QListWidgetItem(secciones[i]);
        itm->setFont(fnt);
        //itm->setFocusPolicy(Qt::NoFocus)
        ui->listWidget->addItem(itm);
        itm->setTextAlignment(Qt::AlignCenter);
    }

    ui->stackedWidget->setCurrentIndex(0);
}

InterfazPrincipalAlternativa::~InterfazPrincipalAlternativa()
{
    delete ui;
}
