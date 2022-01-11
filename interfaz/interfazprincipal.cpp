#include "interfazprincipal.h"
#include "ui_interfazprincipal.h"

InterfazPrincipal::InterfazPrincipal(Kernel* k, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::interfazPrincipal)
    , escenaAeropuerto(new AeropuertoEscena(this))
    , pistaParser()
{
    ui->setupUi(this);
    setWindowTitle("SimAerop");

    QStringList titles {"ID", "Nombre", "Envergadura [m]", "Vel. App [kt]", "LDA [m]","MTOW [kg]","%"};
    ui->tablaFlota->setColumnCount(titles.size());
    ui->tablaFlota->setHorizontalHeaderLabels(titles);
    ui->tablaFlota->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    vistaAeropuerto = ui->vistaAeropuerto;
    ui->vistaAeropuerto->setScene(escenaAeropuerto);

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
    PistaDialogo* dialogConfPista = new PistaDialogo;
    RodajeDialogo* dialogConfRodaje = new RodajeDialogo;
    PlataformaDialogo* dialogConfPlataformas = new PlataformaDialogo;

    connect(ui->botonGraficarPista, &QAbstractButton::pressed, this, &InterfazPrincipal::crearPista);
    connect(this, SIGNAL(sigPistaCambiada()), k, SLOT(graficarPista()));

    connect(ui->pbConfigurarPista, &QAbstractButton::pressed, [dialogConfPista](){dialogConfPista->show();});
    connect(ui->pbConfigurarCallesRodaje, &QAbstractButton::pressed, [dialogConfRodaje](){dialogConfRodaje->show();});
    connect(ui->pbConfigurarPlataformas, &QAbstractButton::pressed, [dialogConfPlataformas](){dialogConfPlataformas->show();});

    //Conexiones Página Aeronaves
    connect(ui->pbCargarFlota, &QAbstractButton::pressed, this, &InterfazPrincipal::sloCargarFlota);
    connect(this, SIGNAL(sigCargarFlota(QString)), k, SLOT(sloCargarFlota(QString)));

    connect(ui->pbGuardarFlota, &QAbstractButton::pressed, this, &InterfazPrincipal::sloGuardarFlota);
    connect(this, SIGNAL(sigGuardarFlota(QString, QList<Aeronave>)), k, SLOT(sloGuardarFlota(QString, QList<Aeronave>)));

    //Conexiones Diálogo Configuración de Pista
    connect(dialogConfPista, SIGNAL(sigPistaActualizada(const Pista&)), this, SLOT(actualizarDatosPista(const Pista&)));

    // VALORES POR DEFAULT OBJETOS DE PRUEBA
    //********
    pista = {2500,45,0,"",""};
    rodaje1 = {"",-200,90,23,200,550};
    rodaje2 = {"",200,90,23,200,550};
    plataforma.coordPerimetro.append(QPointF (0,0));
    plataforma.coordPerimetro.append(QPointF (100,0));
    plataforma.coordPerimetro.append(QPointF (100,100));
    plataforma.coordPerimetro.append(QPointF (0,100));
    //********

    actualizarDatosPista(pista);
}

InterfazPrincipal::~InterfazPrincipal()
{
    delete ui;
}

 AeropuertoVista *InterfazPrincipal::getVistaAeropuerto()
{
    return vistaAeropuerto;
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
    emit sigPistaCambiada();
}


void InterfazPrincipal::actualizarDatosPista(const Pista& p)
{
    escenaAeropuerto->clear();
    pista = p;
    ui->lbValorAncho->setText(QString::number(pista.ancho) + " m");
    ui->lbValorLongitud->setText(QString::number(pista.largo) + " m");
}

void InterfazPrincipal::mostradorFlota(const QList<Aeronave>& f)
{
    const int row = ui->tablaFlota->rowCount();
    for (int i = 0;i<f.count();++i){
        Aeronave aeronave = f[i];
        ui->tablaFlota->insertRow(row+i);
        ui->tablaFlota->setItem(row+i, ID, new QTableWidgetItem(aeronave.getId()));
        ui->tablaFlota->setItem(row+i, NOMBRE, new QTableWidgetItem(aeronave.getNombre()));
        ui->tablaFlota->setItem(row+i, ENVERGADURA, new QTableWidgetItem(aeronave.getEnvergadura()));
        ui->tablaFlota->setItem(row+i, APPSPD, new QTableWidgetItem(aeronave.getVel_app()));
        ui->tablaFlota->setItem(row+i, LDA, new QTableWidgetItem(aeronave.getLda()));
        ui->tablaFlota->setItem(row+i, MTOW, new QTableWidgetItem(aeronave.getMtow()));
        ui->tablaFlota->setItem(row+i, PORCENTAJE, new QTableWidgetItem(aeronave.getPerc()));
        for (int i = 0; i < ui->tablaFlota->columnCount() - 1; i++) {
            QTableWidgetItem* pItem = ui->tablaFlota->item(row, i);
            pItem->setFlags(pItem->flags() & (~Qt::ItemIsEditable));
        }
    }
}

void InterfazPrincipal::sloCargarFlota()
{
    if (ui->tablaFlota->rowCount() != 0){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, "Advertencia", "Se han encontrado datos en el espacio de trabajo."
                                                    " Si carga una nueva flota los datos se sobreescribirán."
                                                    "¿Desea continuar?",
                                     QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }
    }
    ui->tablaFlota->clearContents();
    ui->tablaFlota->setRowCount(0);
    auto filename = QFileDialog::getOpenFileName(this, "Abrir datos", QDir::rootPath(), "XML file (*.xml)");
    if (filename.isEmpty()){
        return;
    }
    emit sigCargarFlota(filename);
}

void InterfazPrincipal::sloGuardarFlota()
{
    QList<Aeronave> flota;
    for (int i = 0; i < ui->tablaFlota->rowCount(); i++) {
        Aeronave aeronave(ui->tablaFlota->item(i, ID)->text(),
                          ui->tablaFlota->item(i, NOMBRE)->text(),
                          ui->tablaFlota->item(i, ENVERGADURA)->text(),
                          ui->tablaFlota->item(i, APPSPD)->text(),
                          ui->tablaFlota->item(i, LDA)->text(),
                          ui->tablaFlota->item(i, MTOW)->text(),
                          ui->tablaFlota->item(i, PORCENTAJE)->text());
        flota.append(aeronave);
    }
    auto filename = QFileDialog::getSaveFileName(this, "Guardar",
                                                 QDir::rootPath(),
                                                 "XML file (*.xml)");
    if (filename.isEmpty()){
        return;
    }
    emit sigGuardarFlota(filename, flota);
}
