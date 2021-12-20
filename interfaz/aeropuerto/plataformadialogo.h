#ifndef PLATAFORMADIALOGO_H
#define PLATAFORMADIALOGO_H

#include <QDialog>

namespace Ui {
class PlataformaDialogo;
}

class PlataformaDialogo : public QDialog
{
    Q_OBJECT

public:
    explicit PlataformaDialogo(QWidget *parent = nullptr);
    ~PlataformaDialogo();

private:
    Ui::PlataformaDialogo *ui;
    void configurarWidgets();

    QPushButton* botonAceptar;
    QPushButton* botonCancelar;

private slots:
    void dialogoAceptado();
    void dialogoCancelado();
};

#endif // PLATAFORMADIALOGO_H
