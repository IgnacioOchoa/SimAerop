#ifndef DIALOGCONFPLATAFORMAS_H
#define DIALOGCONFPLATAFORMAS_H

#include <QDialog>

namespace Ui {
class DialogConfPlataformas;
}

class DialogConfPlataformas : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConfPlataformas(QWidget *parent = nullptr);
    ~DialogConfPlataformas();

private:
    Ui::DialogConfPlataformas *ui;
};

#endif // DIALOGCONFPLATAFORMAS_H
