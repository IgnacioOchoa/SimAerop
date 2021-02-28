#ifndef INTERFAZPRINCIPALALTERNATIVA_H
#define INTERFAZPRINCIPALALTERNATIVA_H
#include <QMainWindow>
#include <QListWidgetItem>
#include <QDebug>

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
    QList<QColor> colores;

private slots:
    void listItemSelected(QListWidgetItem *current, QListWidgetItem *previous);

};

#endif // INTERFAZPRINCIPALALTERNATIVA_H
