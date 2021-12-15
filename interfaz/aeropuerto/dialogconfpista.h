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
#include <QMessageBox>
#include "../../input-output/pistaparser.h"
#include "../../estructuras-datos/elementosaerop.h"
#include "escenaconfpista.h"
#include "vistaconfpista.h"
#include "dialpista.h"

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
    void poblarPista();
    void graficarCota(QPointF p1, QPointF p2, float distancia, Orientacion);
    bool datosCompletos();

    QPushButton* botonAceptar;
    QPushButton* botonCancelar;
    QPushButton* botonCargar;
    QPushButton* botonGuardar;
    QPushButton* botonReset;
    QPushButton* botonOpAvanzadas;
    QPushButton* botonGraficar;
    QPushButton* botonCentrarVista;
    QLineEdit* leLargoPista;
    QLineEdit* leAnchoPista;
    DialPista* dialPista;
    QLineEdit* leNombreArchivo;
    QLineEdit* leRutaArchivo;
    QComboBox* cbCabecera1;
    QComboBox* cbCabecera2;
    QVBoxLayout* layoutDial;
    QLineEdit* leOrientacion;
    QLineEdit* leUmbral1;
    QLineEdit* leUmbral2;
    QLabel* lbUmbral1;
    QLabel* lbUmbral2;
    VistaConfPista* vistaPreliminar;

    QCheckBox* cbUmbral1;
    QCheckBox* cbUmbral2;

    QCheckBox* cbActivarCotas;

    Pista pista;

private slots:
    void dialogoAceptado();
    void dialogoCancelado();
    void poblarCabeceras();
    void seleccionarAbrirArchivo();
    void seleccionarGuardarArchivo();
    void resetDialogoPista();
    void dibujarPista();
    void botonGraficarApretado();
    void actualizarCBUmbrales(const QString& s1, const QString& s2);
    void actualizarLEOrientacion(int value);

signals:
    void pistaActualizada(const Pista&);

};

#endif // DIALOGCONFPISTA_H
