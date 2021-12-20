#ifndef PISTADIAL_H
#define PISTADIAL_H

#include <QDial>
#include <QPainter>
#include <QDebug>

class QPainter;

class PistaDial : public QDial
{
    Q_OBJECT
public:
    PistaDial(QWidget* parent = nullptr);
    virtual void paintEvent(QPaintEvent *pe) override;

private:
    QPen penLineaBlanca = QPen(QBrush(QColor("white")), 1.5);
    QPen penLineaBlancaPunteada = QPen(QBrush(QColor("white")), /*linewidth*/ 1, Qt::DashLine);
    QBrush brushFondo = QBrush(QColor("#d9d9d9"));
    QBrush brushPista = QBrush(QColor("#737373"));

};

#endif // PISTADIAL_H
