#ifndef DIALOGCONFPISTA_H
#define DIALOGCONFPISTA_H

#include <QLineEdit>
#include <QTableView>
#include <QGraphicsView>
#include <QComboBox>
#include <QDialog>

namespace Ui {
class DialogConfPista;
}

class DialogConfPista : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfPista(QWidget *parent = nullptr);
    ~DialogConfPista();

private:
    Ui::DialogConfPista *ui;
    void configurarWidgets();

    QPushButton* botonAceptar;
    QPushButton* botonCancelar;
    QPushButton* botonCargar;
    QPushButton* botonGuardar;
    QPushButton* botonOpAvanzadas;
    QLineEdit* leLargoPista;
    QLineEdit* leAnchoPista;
    QLineEdit* leNombreArchivo;
    QLineEdit* leDireccionArchivo;
    QComboBox* cbCabecera1;
    QComboBox* cbCabecera2;
    QTableView* tablaCallesRodaje;
    QGraphicsView* vistaPreliminar;

private slots:
    void dialogoAceptado();
    void dialogoCancelado();
    void poblarCabeceras();

};

#endif // DIALOGCONFPISTA_H
