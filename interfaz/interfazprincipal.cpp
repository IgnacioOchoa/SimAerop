#include "interfazprincipal.h"
#include "ui_interfazprincipal.h"

InterfazPrincipal::InterfazPrincipal(Kernel* k, QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::interfazPrincipal),
    escenaAeropuerto(new AeropuertoEscena(this)),
    pistaParser(),
    pistaCargado(false), rodajeCargado(false), plataformaCargado(false)
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
    configurarWidgets();
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
    dialogConfPista = new PistaDialogo(listaPistas, this);
    dialogConfRodaje = new RodajeDialogo(listaRodajes, listaPistas, this);
    dialogConfPlataformas = new PlataformaDialogo(listaPlataformas, this);

    connect(ui->botonGraficarPista, &QAbstractButton::pressed, this, &InterfazPrincipal::crearPista);
    connect(this, SIGNAL(sigPistaCambiada()), k, SLOT(graficarPista()));

    connect(ui->pbConfigurarPista, &QAbstractButton::pressed, [this](){dialogConfPista->show();});
    connect(ui->pbConfigurarCallesRodaje, &QAbstractButton::pressed, this, &InterfazPrincipal::slotActivarDialogoRodaje);
    connect(ui->pbConfigurarPlataformas, &QAbstractButton::pressed, [this](){dialogConfPlataformas->show();});

    //Conexiones Página Aeronaves
    connect(ui->pbCargarFlota, &QAbstractButton::pressed, this, &InterfazPrincipal::sloCargarFlota);
    connect(this, SIGNAL(sigCargarFlota(QString)), k, SLOT(sloCargarFlota(QString)));

    connect(ui->pbGuardarFlota, &QAbstractButton::pressed, this, &InterfazPrincipal::sloGuardarFlota);
    connect(this, SIGNAL(sigGuardarFlota(QString, QList<Aeronave>)), k, SLOT(sloGuardarFlota(QString, QList<Aeronave>)));

    //Conexiones Diálogo Configuración de Pista
    connect(dialogConfPista, SIGNAL(sigPistaActualizada()), this, SLOT(actualizarDatosPista()));

    //Conexion del boton para establecer defaults
    connect(ui->pbDefaults, &QAbstractButton::pressed, this, &InterfazPrincipal::setDefaults);

    //Conexion de boton para cargar aeropuerto
    connect(ui->pbCargarAeropuerto, &QAbstractButton::pressed, this, &InterfazPrincipal::slotCargarAeropuerto);

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

void InterfazPrincipal::configurarWidgets()
{
    ui->confPlatChk->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->confPlatChk->setFocusPolicy(Qt::NoFocus);
    ui->confPistaChk->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->confPistaChk->setFocusPolicy(Qt::NoFocus);
    ui->confCalleRodChk->setAttribute(Qt::WA_TransparentForMouseEvents);
    ui->confCalleRodChk->setFocusPolicy(Qt::NoFocus);
}

void InterfazPrincipal::setDefaults()
{
    listaPistas.clear();
    listaRodajes.clear();
    listaPlataformas.clear();
    // VALORES POR DEFAULT OBJETOS DE PRUEBA
    //********
    listaPistas.append({2500,45,80,"01","19"});
    listaRodajes.append({{"",-200,90,23,200,550}, {"",200,90,23,200,550}});
    listaRodajes.append({{"",-50,-135,23,300,550}, {"",50,-45,23,300,550}});
    listaPlataformas.append(Plataforma ("Norte", {QPointF (-300,-300), QPointF (-300,-200),  QPointF (300,-200), QPointF (300,-300)}));
    listaPlataformas.append(Plataforma ("Sur", {QPointF (-300,300), QPointF (-300,200),  QPointF (300,200), QPointF (300,300)}));
    //********
    statusBar()->showMessage("Valores por default establecidos", 3000);
    actualizarDatosPista();
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
    if(listaPistas.isEmpty()) {
        QMessageBox::warning(this, "No hay pista cargada",
                             "Por favor carge los datos de pista");
        return;
    }

    emit sigPistaCambiada();
}


void InterfazPrincipal::actualizarDatosPista()
{
    Pista pista;
    if (listaPistas.size() > 0) {
        pista = listaPistas.last();
        ui->confPistaChk->setChecked(true);
    }
    else
    {
        qInfo() << "No hay datos en la lista de pistas";
    }
    escenaAeropuerto->clear();
    ui->lbValorAncho->setText(QString::number(pista.ancho) + " m");
    ui->lbValorLongitud->setText(QString::number(pista.largo) + " m");
}

void InterfazPrincipal::slotActivarDialogoRodaje()
{
    if(listaPistas.isEmpty()) {
        QMessageBox::warning(this, "Pista sin configurar", "No existe una pista configurada, por favor ingrese"
                                                           " los datos de pista antes de proceder con las calles de"
                                                           " rodaje");
    }
    else {
        dialogConfRodaje->show();
    }
}

void InterfazPrincipal::slotCargarAeropuerto()
{
    QString nombreArchivoAeropuerto = QFileDialog::getOpenFileName(this, "Abrir archivo de aeropuerto", "../","(*.json)");
    PistaParser pp;
    pp.cargarEscenario(nombreArchivoAeropuerto, listaPistas, listaRodajes, listaPlataformas);
    actualizarDatosPista();

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
        for (int j = 0; j<ui->tablaFlota->columnCount()-1; ++j){
            QTableWidgetItem* item = ui->tablaFlota->item(i, j);
            item->setFlags(item->flags() & (~Qt::ItemIsEditable));
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
