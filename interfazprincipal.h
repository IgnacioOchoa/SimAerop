#ifndef INTERFAZPRINCIPAL_H
#define INTERFAZPRINCIPAL_H

#include "kernel.h"
#include "elementosaerop.h"
#include "customgraphicsview.h"
#include "customgraphicsscene.h"
#include "dialogconfpista.h"
#include "aeronave.h"
#include <QXmlStreamReader>
#include <QMainWindow>
#include <QButtonGroup>
#include <QListWidgetItem>
#include <QDebug>
#include <QString>

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

signals:
    void pistaCambiada();

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

    Pista pista;

private slots:
    void botonPrincipalSeleccionado(bool checked);
    void validarDatosPista();

    void on_botonCargarFlota_clicked();

    void on_botonGuardarFlota_clicked();

    void on_pushButton_4_clicked();

    void on_botonCargarAcft_triggered(QAction *arg1);

    void on_comboBoxAcft_activated(const QString &arg1);

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
    void agregaAeronave(const Aeronave &aeronave);
};

#endif // INTERFAZPRINCIPAL_H
