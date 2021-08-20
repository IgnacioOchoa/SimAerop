#ifndef INTERFAZPRINCIPAL_H
#define INTERFAZPRINCIPAL_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QDebug>
#include <QString>

#include "kernel/kernel.h"
#include "../estructuras-datos/elementosaerop.h"
#include "aeropuerto/customgraphicsview.h"
#include "aeropuerto/customgraphicsscene.h"
#include "interfaz/aeropuerto/dialogconfpista.h"
#include "aeronaves/aeronave.h"
#include "aeronaves/flota.h"
#include "interfaz/aeropuerto/dialogconfrodaje.h"
#include "interfaz/aeropuerto/dialogconfplataformas.h"
#include "input-output/pistaparser.h"


class QAction;
class QPushButton;
class Kernel;

QT_BEGIN_NAMESPACE
namespace Ui { class interfazPrincipal; }
QT_END_NAMESPACE


class InterfazPrincipal : public QMainWindow
{

    Q_OBJECT

public:
    InterfazPrincipal(Kernel *k, QWidget* parent = nullptr);
    ~InterfazPrincipal();
    QGraphicsView *getVistaPista();
    const Pista& getPista() const {return pista;}
    void mostradorFlota(const QList<Aeronave>&);

signals:
    void pistaCambiada();
    void sigCargarFlota(QString);
    void sigGuardarFlota(QString, QList<Aeronave>);

private:
    void crearMenu();

    Ui::interfazPrincipal *ui;
    QList<QColor> colores;
    QList<QPushButton*> listaBotones;
    QButtonGroup* btnGroup;

    customGraphicsView* vistaPista;
    customGraphicsScene* escenaPista;

    QMenu* menuArchivo;
    QMenu* menuEditar;
    QMenu* menuAjustes;
    QMenu* menuExportar;
    QMenu* menuAyuda;

    PistaParser pistaParser;

    Pista pista;

private slots:
    void botonPrincipalSeleccionado(bool checked);
    void crearPista();
    void sloCargarFlota();
    void sloGuardarFlota();
    void actualizarDatosPista(const Pista&);

private:
    enum{
        ID,
        NOMBRE,
        ENVERGADURA,
        APPSPD,
        LDA,
        MTOW,
        PORCENTAJE,
    };
};

#endif // INTERFAZPRINCIPAL_H
