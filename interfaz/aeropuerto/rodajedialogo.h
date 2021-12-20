#ifndef RODAJEDIALOGO_H
#define RODAJEDIALOGO_H

#include <QDialog>

namespace Ui {
class RodajeDialogo;
}

class RodajeDialogo : public QDialog
{
    Q_OBJECT

public:
    explicit RodajeDialogo(QWidget *parent = nullptr);
    ~RodajeDialogo();

private:
    Ui::RodajeDialogo *ui;
    void configurarWidgets();

    QPushButton* botonAceptar;
    QPushButton* botonCancelar;

private slots:
    void dialogoAceptado();
    void dialogoCancelado();
};

#endif // RODAJEDIALOGO_H
