#ifndef INTERFAZPRINCIPALALTERNATIVA_H
#define INTERFAZPRINCIPALALTERNATIVA_H

#include <QMainWindow>

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
    Ui::InterfazPrincipalAlt *ui;
};

#endif // INTERFAZPRINCIPALALTERNATIVA_H
