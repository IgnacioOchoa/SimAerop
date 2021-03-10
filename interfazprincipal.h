#ifndef INTERFAZPRINCIPAL_H
#define INTERFAZPRINCIPAL_H

#include "kernel.h"
#include <QMainWindow>
#include <QButtonGroup>
#include <QListWidgetItem>
#include <QDebug>

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

private:
    void crearMenu();
    Ui::interfazPrincipal *ui;
    QList<QColor> colores;
    QList<QPushButton*> listaBotones;
    QButtonGroup* btnGroup;

    QMenu* menuArchivo;
    QMenu* menuEditar;
    QMenu* menuAjustes;
    QMenu* menuExportar;
    QMenu* menuAyuda;

private slots:
    void botonPrincipalSeleccionado(bool checked);

};

#endif // INTERFAZPRINCIPAL_H
