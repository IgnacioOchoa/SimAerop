#include "interfazprincipalalternativa.h"
#include "ui_interfazPrincipalAlt.h"

InterfazPrincipalAlternativa::InterfazPrincipalAlternativa(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterfazPrincipalAlt)
{
    ui->setupUi(this);
    setWindowTitle("SimAerop");

    crearMenu();

    QList<QString> secciones = {"AERONAVES", "AEROPUERTO", "OPERACIONES", "SIMULACIÓN"};
    btnGroup = new QButtonGroup(this);

    QFont fnt;
    fnt.setPointSize(14);


    listaBotones = {ui->pbAeronaves, ui->pbAeropuerto, ui->pbOperaciones, ui->pbSimulacion};

    int id=0;
    foreach(QPushButton* btn, listaBotones)
    {
        btn->setFont(fnt);
        btn->setCheckable(true);
        btnGroup->addButton(btn,id);
        connect(btn , &QAbstractButton::toggled, this, &InterfazPrincipalAlternativa::botonPrincipalSeleccionado);
        id++;
    }
    btnGroup->setExclusive(true);
    listaBotones[0]->setChecked(true);

}

InterfazPrincipalAlternativa::~InterfazPrincipalAlternativa()
{
    delete ui;
}

void InterfazPrincipalAlternativa::crearMenu()
{
    menuArchivo = menuBar()->addMenu("Archivo");
    menuEditar = menuBar()->addMenu("Editar");
    menuAjustes = menuBar()->addMenu("Ajustes");
    menuExportar = menuBar()->addMenu("Exportar");
    menuExportar = menuBar()->addMenu("Ayuda");
}

void InterfazPrincipalAlternativa::botonPrincipalSeleccionado(bool checked)
{
    if(checked)
    {
        ui->stackedWidget->setCurrentIndex(btnGroup->checkedId());
    }
}
