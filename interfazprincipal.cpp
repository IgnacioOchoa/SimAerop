#include "interfazprincipal.h"
#include "ui_interfazprincipal.h"

InterfazPrincipal::InterfazPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterfazPrincipal)
{
    ui->setupUi(this);
    setWindowTitle("SimAerop");
}

InterfazPrincipal::~InterfazPrincipal()
{
    delete ui;
}

