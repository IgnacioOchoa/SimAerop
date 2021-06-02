#include "dialogconfplataformas.h"
#include "ui_dialogconfplataformas.h"

DialogConfPlataformas::DialogConfPlataformas(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConfPlataformas)
{
    ui->setupUi(this);
}

DialogConfPlataformas::~DialogConfPlataformas()
{
    delete ui;
}
