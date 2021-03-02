#ifndef INTERFAZPRINCIPALALTERNATIVA_H
#define INTERFAZPRINCIPALALTERNATIVA_H
#include <QMainWindow>
#include <QButtonGroup>
#include <QListWidgetItem>
#include <QDebug>

class QAction;
class QPushButton;

QT_BEGIN_NAMESPACE
namespace Ui { class InterfazPrincipalAlt; }
QT_END_NAMESPACE


class InterfazPrincipalAlternativa : public QMainWindow
{

    Q_OBJECT

public:
    InterfazPrincipalAlternativa(QWidget* partent = nullptr);
    ~InterfazPrincipalAlternativa();

private:
    void crearMenu();
    Ui::InterfazPrincipalAlt *ui;
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

#endif // INTERFAZPRINCIPALALTERNATIVA_H
