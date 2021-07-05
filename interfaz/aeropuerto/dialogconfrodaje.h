#ifndef DIALOGCONFRODAJE_H
#define DIALOGCONFRODAJE_H

#include <QDialog>

namespace Ui {
class DialogConfRodaje;
}

class DialogConfRodaje : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfRodaje(QWidget *parent = nullptr);
    ~DialogConfRodaje();

private:
    Ui::DialogConfRodaje *ui;
    void configurarWidgets();

    QPushButton* botonAceptar;
    QPushButton* botonCancelar;

private slots:
    void dialogoAceptado();
    void dialogoCancelado();
};

#endif // DIALOGCONFRODAJE_H
