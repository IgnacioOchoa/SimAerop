#include "dialogconfrodaje.h"
#include "ui_dialogconfrodaje.h"

DialogConfRodaje::DialogConfRodaje(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfRodaje)
{
    ui->setupUi(this);
}

DialogConfRodaje::~DialogConfRodaje()
{
    delete ui;
}
