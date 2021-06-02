#include "interfazprincipal.h"
#include "ui_interfazprincipal.h"

InterfazPrincipal::InterfazPrincipal(Kernel* k, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::interfazPrincipal)
    , escenaPista(new customGraphicsScene(this))
{
    ui->setupUi(this);
    setWindowTitle("SimAerop");

    vistaPista = ui->graficoPista;
    ui->graficoPista->setScene(escenaPista);

    crearMenu();
    k->inicializar(this);

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

    DialogConfPista* dialogConfPista = new DialogConfPista;

    connect(ui->botonGraficarPista, &QAbstractButton::pressed, this, &InterfazPrincipal::crearPista);
    connect(this, SIGNAL(pistaCambiada()), k, SLOT(graficarPista()));

    connect(ui->pbConfigurarPista, &QAbstractButton::pressed, [dialogConfPista](){dialogConfPista->show();});

}

InterfazPrincipal::~InterfazPrincipal()
{
    delete ui;
}

QGraphicsView *InterfazPrincipal::getVistaPista()
{
    return vistaPista;
}

void InterfazPrincipal::crearMenu()
{
    menuArchivo = menuBar()->addMenu("Archivo");
    menuEditar = menuBar()->addMenu("Editar");
    menuAjustes = menuBar()->addMenu("Ajustes");
    menuExportar = menuBar()->addMenu("Exportar");
    menuExportar = menuBar()->addMenu("Ayuda");
}

void InterfazPrincipal::botonPrincipalSeleccionado(bool checked)
{
    if(checked)
    {
        ui->stackedWidget->setCurrentIndex(btnGroup->checkedId());
    }
}

void InterfazPrincipal::crearPista()
{
    pista = Pista{2000,100,0,0};
    ui->lbValorAncho->setText(QString::number(pista.ancho) + " m");
    ui->lbValorLongitud->setText(QString::number(pista.largo) + " m");

    emit pistaCambiada();
}
