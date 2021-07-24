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

    DialogConfPista* dialogConfPista = new DialogConfPista;
    DialogConfRodaje* dialogConfRodaje = new DialogConfRodaje;
    DialogConfPlataformas* dialogConfPlataformas = new DialogConfPlataformas;

    connect(ui->botonGraficarPista, &QAbstractButton::pressed, this, &InterfazPrincipal::crearPista);
    connect(this, SIGNAL(pistaCambiada()), k, SLOT(graficarPista()));

    connect(ui->pbConfigurarPista, &QAbstractButton::pressed, [dialogConfPista](){dialogConfPista->show();});
    connect(ui->pbConfigurarCallesRodaje, &QAbstractButton::pressed, [dialogConfRodaje](){dialogConfRodaje->show();});
    connect(ui->pbConfigurarPlataformas, &QAbstractButton::pressed, [dialogConfPlataformas](){dialogConfPlataformas->show();});

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

    //qInfo() << pis;
    //qInfo() << rod[0];
    //qInfo() << plat[0];

    //qInfo() << "Current path: " << QDir::currentPath();

    //ui->lbValorAncho->setText(QString::number(pis.ancho) + " m");
    //ui->lbValorLongitud->setText(QString::number(pis.largo) + " m");

    //pista = pis;
    pista = {500,45,0,"",""};

    emit pistaCambiada();
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
{
    auto filename = QFileDialog::getSaveFileName(this, "Guardar",
                                                 QDir::rootPath(),
                                                 "XML file (*.xml)");
    if (filename.isEmpty()){
        return;
    }
    QDomDocument doc;
    auto root = doc.createElement("aeronave");
    doc.appendChild(root);
    const int rowCount = ui->tablaFlota->rowCount();
    for (int ix = 0; ix<rowCount; ++ix){
        Aeronave aeronave(ui->tablaFlota->item(ix, ID)->text(),
                          ui->tablaFlota->item(ix, NOMBRE)->text(),
                          ui->tablaFlota->item(ix, ENVERGADURA)->text(),
                          ui->tablaFlota->item(ix, APPSPD)->text(),
                          ui->tablaFlota->item(ix, LDA)->text(),
                          ui->tablaFlota->item(ix, MTOW)->text(),
                          ui->tablaFlota->item(ix, PORCENTAJE)->text());
        auto eAeronave = doc.createElement("aeronave");
        eAeronave.setAttribute("id", aeronave.getId());
        auto eNombre = doc.createElement("name");
        auto eEnvergadura = doc.createElement("wspan");
        auto eApp_spd = doc.createElement("appspd");
        auto eLda = doc.createElement("lda");
        auto eMtow = doc.createElement("mtow");
        auto ePerc = doc.createElement("perc");
        eNombre.appendChild(doc.createTextNode(aeronave.getNombre()));
        eEnvergadura.appendChild(doc.createTextNode(aeronave.getEnvergadura()));
        eApp_spd.appendChild(doc.createTextNode(aeronave.getVel_app()));
        eLda.appendChild(doc.createTextNode(aeronave.getLda()));
        eMtow.appendChild(doc.createTextNode(aeronave.getMtow()));
        ePerc.appendChild(doc.createTextNode(aeronave.getPerc()));
        eAeronave.appendChild(eNombre);
        eAeronave.appendChild(eEnvergadura);
        eAeronave.appendChild(eApp_spd);
        eAeronave.appendChild(eLda);
        eAeronave.appendChild(eMtow);
        eAeronave.appendChild(ePerc);
        root.appendChild(eAeronave);
    }
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    QTextStream xout(&file);
    xout << doc.toString();
    file.flush();
    file.close();
}

void InterfazPrincipal::on_pushButton_4_clicked()
{

}

void InterfazPrincipal::on_botonCargarAcft_triggered(QAction *arg1)
{

}

void InterfazPrincipal::on_comboBoxAcft_activated(const QString &arg1)
{

}

void InterfazPrincipal::agregaAeronave(const Aeronave &aeronave)
{
    const int row = ui->tablaFlota->rowCount();
    ui->tablaFlota->insertRow(row);
    ui->tablaFlota->setItem(row, ID, new QTableWidgetItem(aeronave.getId()));
    ui->tablaFlota->setItem(row, NOMBRE, new QTableWidgetItem(aeronave.getNombre()));
    ui->tablaFlota->setItem(row, ENVERGADURA, new QTableWidgetItem(aeronave.getEnvergadura()));
    ui->tablaFlota->setItem(row, APPSPD, new QTableWidgetItem(aeronave.getVel_app()));
    ui->tablaFlota->setItem(row, LDA, new QTableWidgetItem(aeronave.getLda()));
    ui->tablaFlota->setItem(row, MTOW, new QTableWidgetItem(aeronave.getMtow()));
    ui->tablaFlota->setItem(row, PORCENTAJE, new QTableWidgetItem(aeronave.getPerc()));
    for (int i = 0; i < ui->tablaFlota->columnCount() - 1; i++) {
        QTableWidgetItem* pItem = ui->tablaFlota->item(row, i);
        pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
    }
}
