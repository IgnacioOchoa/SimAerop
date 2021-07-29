#include "interfazprincipal.h"
#include "ui_interfazprincipal.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>

InterfazPrincipal::InterfazPrincipal(Kernel* k, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::interfazPrincipal)
    , escenaPista(new customGraphicsScene(this))
    , pistaParser()
{
    ui->setupUi(this);
    setWindowTitle("SimAerop");

    QStringList titles {"ID", "Nombre", "Envergadura [m]", "Vel. App [kt]", "LDA [m]","MTOW [kg]","%"};
    ui->tablaFlota->setColumnCount(titles.size());
    ui->tablaFlota->setHorizontalHeaderLabels(titles);
    ui->tablaFlota->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

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

    //Conexiones Página Aeropuertos
    DialogConfPista* dialogConfPista = new DialogConfPista;
    DialogConfRodaje* dialogConfRodaje = new DialogConfRodaje;
    DialogConfPlataformas* dialogConfPlataformas = new DialogConfPlataformas;

    connect(ui->botonGraficarPista, &QAbstractButton::pressed, this, &InterfazPrincipal::crearPista);
    connect(this, SIGNAL(pistaCambiada()), k, SLOT(graficarPista()));

    connect(ui->pbConfigurarPista, &QAbstractButton::pressed, [dialogConfPista](){dialogConfPista->show();});
    connect(ui->pbConfigurarCallesRodaje, &QAbstractButton::pressed, [dialogConfRodaje](){dialogConfRodaje->show();});
    connect(ui->pbConfigurarPlataformas, &QAbstractButton::pressed, [dialogConfPlataformas](){dialogConfPlataformas->show();});

    //Conexiones Página Aeronaves
    connect(ui->pbCargarFlota, &QAbstractButton::pressed, this, &InterfazPrincipal::slotCargarFlota);
    connect(this, SIGNAL(signalCargarFlota()), k, SLOT(slotGuardarFlota()));

    connect(ui->pbGuardarFlota, &QAbstractButton::pressed, this, &InterfazPrincipal::slotCargarFlota);
    connect(this, SIGNAL(signalGuardarFlota()), k, SLOT(slotGuardarFlota()));

    connect(dialogConfPista, SIGNAL(pistaActualizada(const Pista&)), this, SLOT(actualizarDatosPista(const Pista&)));

    // Valores por default
    pista = {1250,45,0,"",""};
    actualizarDatosPista(pista);

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
    //Pista pis = pistaParser.cargarPista("miPistaNueva.json");
    //QList<Rodaje> rod = pistaParser.cargarRodaje("miPistaNueva.json");
    //QList<Plataforma> plat = pistaParser.cargarPlataforma("miPistaNueva.json");

    //pista = pis;
    //pista = {1250,45,0,"",""};
    emit pistaCambiada();
}

<<<<<<< HEAD
void InterfazPrincipal::slotCargarFlota()
=======
void InterfazPrincipal::actualizarDatosPista(const Pista& p)
{
    escenaPista->clear();
    pista = p;
    ui->lbValorAncho->setText(QString::number(pista.ancho) + " m");
    ui->lbValorLongitud->setText(QString::number(pista.largo) + " m");
}

void InterfazPrincipal::on_botonCargarFlota_clicked()
{
    ui->tablaFlota->clearContents();
    ui->tablaFlota->setRowCount(0);
    auto filename = QFileDialog::getOpenFileName(this, "Abrir datos", QDir::rootPath(), "XML file (*.xml)");
    if (filename.isEmpty()){
        return;
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    QDomDocument doc;
    doc.setContent(&file);
    file.close();
    auto root = doc.firstChild().toElement();
    auto ix = root.firstChild().toElement();
    while (!ix.isNull()){
        auto id = ix.attribute("id");
        auto nombre = ix.firstChild().toElement().text();
        auto envergadura = ix.firstChild().nextSibling().toElement().text();
        auto appspd = ix.firstChild().nextSibling().nextSibling().toElement().text();
        auto lda = ix.firstChild().nextSibling().nextSibling().nextSibling().toElement().text();
        auto mtow = ix.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text();
        auto perc = ix.firstChild().nextSibling().nextSibling().nextSibling().nextSibling().nextSibling().toElement().text();
        agregaAeronave(Aeronave(id, nombre, envergadura, appspd, lda, mtow, perc));
        ix = ix.nextSibling().toElement();
    }
}

void InterfazPrincipal::on_botonGuardarFlota_clicked()
>>>>>>> cfb5d4d (Se conectó DialogConfPista con InterfazPpal)
{
    emit signalCargarFlota();
}

void InterfazPrincipal::slotGuardarFlota()
{
    emit signalGuardarFlota();
}
