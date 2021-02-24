#include "interfazprincipalalternativa.h"
#include "ui_interfazPrincipalAlt.h"

InterfazPrincipalAlternativa::InterfazPrincipalAlternativa(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::InterfazPrincipalAlt)
{
    ui->setupUi(this);
    setWindowTitle("SimAerop");

    QList<QString> secciones = {"AERONAVES", "AEROPUERTOS", "OPERACIONES", "SIMULACIÓN"};
    colores = {"#daf2f7", "#ffffe6", "#f2e6ff", "#e6fff7"};

    QFont fnt;
    fnt.setPointSize(14);
    for (int i = 0; i < secciones.size(); i++)
    {
        QListWidgetItem* itm = new QListWidgetItem(secciones[i]);
        itm->setFont(fnt);
        //itm->setFocusPolicy(Qt::NoFocus)
        ui->listWidget->addItem(itm);
        itm->setTextAlignment(Qt::AlignCenter);
    }

    ui->listWidget->setCurrentRow(0);
    ui->stackedWidget->setCurrentIndex(0);
    //ui->listWidget->setMouseTracking(true);
    connect(ui->listWidget, &QListWidget::currentItemChanged, this, &InterfazPrincipalAlternativa::listItemSelected);
    //connect(ui->listWidget, &QListWidget::itemEntered, this, &InterfazPrincipalAlternativa::listItemHovered);

    //ui->stackedWidget->setCurrentIndex(0);
}

InterfazPrincipalAlternativa::~InterfazPrincipalAlternativa()
{
    delete ui;
}

void InterfazPrincipalAlternativa::listItemSelected(QListWidgetItem *current, QListWidgetItem *previous)
{
    //current->setBackground(colores[ ui->listWidget->currentRow()]);
    //previous->setBackground(Qt::white);
    ui->stackedWidget->setCurrentIndex(ui->listWidget->currentRow());
}

void InterfazPrincipalAlternativa::listItemHovered(QListWidgetItem *hoveredItm)
{
        qInfo() << "List item hovered";
        QListWidgetItem* selectedItem = ui->listWidget->currentItem();
        for(int i=0; i<ui->listWidget->count(); i++)
        {
            QListWidgetItem* itm = ui->listWidget->item(i);
            if(itm != hoveredItm && itm != selectedItem)
            {
                itm->setBackground(Qt::white);
            }
            else if(itm != selectedItem && itm == hoveredItm)
            {
                itm->setBackground(QColor("#f9ecf2"));
            }
        }
}
