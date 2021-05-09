#include "dialogconfpista.h"
#include "ui_dialogconfpista.h"

DialogConfPista::DialogConfPista(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfPista)
{
    ui->setupUi(this);
}

DialogConfPista::~DialogConfPista()
{
    delete ui;
}
