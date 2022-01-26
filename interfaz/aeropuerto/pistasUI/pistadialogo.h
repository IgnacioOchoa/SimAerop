#ifndef PISTADIALOGO_H
#define PISTADIALOGO_H

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
#include "../../../input-output/pistaparser.h"
#include "../../../estructuras-datos/elementosaerop.h"
#include "pistaescena.h"
#include "pistavista.h"
#include "pistadial.h"

namespace Ui {
class PistaDialogo;
}

class PistaDialogo : public QDialog
{
    Q_OBJECT
    enum Orientacion {HOR, VER};

public:
    explicit PistaDialogo(QList<Pista>& listaP, QWidget *parent = nullptr);
    ~PistaDialogo();

private:
    Ui::PistaDialogo *ui;
    void configurarWidgets();
    void poblarDatos();
    void poblarPista();
    void graficarCota(QPointF p1, QPointF p2, float distancia, Orientacion);
    bool datosCompletos();
    bool verificarUmbrales(PistaEscena::Umbral umbral, int& desplazamiento);
    void actualizarMaxUmbrales();

    int desplUmbral1 = 0;
    int maxUmbral1;
    int desplUmbral2 = 0;
    int maxUmbral2;

    QString cabecera1;
    QString cabecera2;

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
    PistaDial* dialPista;
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
    PistaVista* vistaPreliminar;

    QCheckBox* cbUmbral1;
    QCheckBox* cbUmbral2;

    QCheckBox* cbActivarCotas;

    Pista pista;
    const int margenMinUmbral = 20;
    QList<Pista>& listaPistas;

private slots:
    void dialogoAceptado();
    void dialogoCancelado();
    void seleccionarAbrirArchivo();
    void seleccionarGuardarArchivo();
    void resetDialogoPista();
    void dibujarPista();
    void botonGraficarApretado();
    void actualizarUmbrales(const QString& s1, const QString& s2);
    void actualizarLEOrientacion(int value);
    void leUmbralModificado();
    void slotLineaUmbralMovida(PistaEscena::Umbral, int valor);

signals:
    void sigPistaActualizada();
    void sigUmbralActualizado(PistaEscena::Umbral umbral, int valor);
    void sigUmbralMaxActualizado(int maxUmbral1, int maxUmbral2);

};

#endif // PISTADIALOGO_H
