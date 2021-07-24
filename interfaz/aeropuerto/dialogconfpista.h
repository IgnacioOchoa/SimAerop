#ifndef DIALOGCONFPISTA_H
#define DIALOGCONFPISTA_H

#include <QLineEdit>
#include <QTableView>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QComboBox>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QDialog>
#include <QDebug>
#include <QDir>
#include <QLabel>
#include "../../input-output/pistaparser.h"
#include "../../estructuras-datos/elementosaerop.h"

namespace Ui {
class DialogConfPista;
}

class DialogConfPista : public QDialog
{
    Q_OBJECT
    enum Orientacion {HOR, VER};

public:
    explicit DialogConfPista(QWidget *parent = nullptr);
    ~DialogConfPista();

private:
    Ui::DialogConfPista *ui;
    void configurarWidgets();
    void poblarDatos();
    void dibujarPista();
    void ajustarContenido();
    void graficarCota(QPointF p1, QPointF p2, float distancia, Orientacion);

    QPushButton* botonAceptar;
    QPushButton* botonCancelar;
    QPushButton* botonCargar;
    QPushButton* botonGuardar;
    QPushButton* botonOpAvanzadas;
    QLineEdit* leLargoPista;
    QLineEdit* leAnchoPista;
    QLineEdit* leNombreArchivo;
    QLineEdit* leRutaArchivo;
    QComboBox* cbCabecera1;
    QComboBox* cbCabecera2;
    QGraphicsView* vistaPreliminar;
    QVBoxLayout* layoutDial;
    QLineEdit* leOrientacion;
    QLineEdit* leUmbral1;
    QLineEdit* leUmbral2;
    QLabel* lbUmbral1;
    QLabel* lbUmbral2;
    QGraphicsScene* escenaPreliminar;

    QCheckBox* cbUmbral1;
    QCheckBox* cbUmbral2;

    Pista pista;

private slots:
    void dialogoAceptado();
    void dialogoCancelado();
    void poblarCabeceras();
    void seleccionarAbrirArchivo();
};

#endif // DIALOGCONFPISTA_H
