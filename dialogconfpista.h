#ifndef DIALOGCONFPISTA_H
#define DIALOGCONFPISTA_H

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
};

#endif // DIALOGCONFPISTA_H
