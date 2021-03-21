#include "interfazprincipal.h"
#include "ui_interfazprincipal.h"

InterfazPrincipal::InterfazPrincipal(Kernel* k, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::interfazPrincipal)
    , escenaPista(new QGraphicsScene(this))
{
    ui->setupUi(this);
    setWindowTitle("SimAerop");

    ui->graficoPista->setScene(escenaPista);

    crearMenu();
    k->inicializar(this, escenaPista);

    ui->graficoPista->fitInView(-500,-25,1000,50,Qt::KeepAspectRatioByExpanding);
    reportarDatosEscena();

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
        connect(btn , &QAbstractButton::toggled, this, &InterfazPrincipal::botonPrincipalSeleccionado);
        id++;
    }
    btnGroup->setExclusive(true);
    listaBotones[0]->setChecked(true);

    //connect(ui->botonGraficarPista, &QAbstractButton::pressed, k, &Kernel::botonGraficarPistaApretado);

}

InterfazPrincipal::~InterfazPrincipal()
{
    delete ui;
}

void InterfazPrincipal::crearMenu()
{
    menuArchivo = menuBar()->addMenu("Archivo");
    menuEditar = menuBar()->addMenu("Editar");
    menuAjustes = menuBar()->addMenu("Ajustes");
    menuExportar = menuBar()->addMenu("Exportar");
    menuExportar = menuBar()->addMenu("Ayuda");
}

void InterfazPrincipal::reportarDatosEscena()
{
    qInfo() << "escenaPista->sceneRect() = " << escenaPista->sceneRect();
    qInfo() << "ui->graficoPista->sceneRect() = " << ui->graficoPista->sceneRect();
    qInfo() << "Item at (0,0): " << ui->graficoPista->itemAt(ui->graficoPista->mapFromScene(0,0));
    qInfo() << "ui->graficoPista->transform() = " << ui->graficoPista->transform();
    qInfo() << "ui->graficoPista->rect() (from QWidget) = " << ui->graficoPista->rect();
    qInfo() << "ui->graficoPista->contentsRect() (from QWidget) = " << ui->graficoPista->contentsRect();
    qInfo() << "ui->graficoPista->mapToScene(ui->graficoPista->viewport()->geometry()).boundingRect() "
               "(from QAbstractScrollArea) = "
            << ui->graficoPista->mapToScene(ui->graficoPista->viewport()->geometry()).boundingRect();

}

void InterfazPrincipal::botonPrincipalSeleccionado(bool checked)
{
    if(checked)
    {
        ui->stackedWidget->setCurrentIndex(btnGroup->checkedId());
    }
}
