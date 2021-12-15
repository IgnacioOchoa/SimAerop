#ifndef DIALPISTA_H
#define DIALPISTA_H

#include <QDial>
#include <QPainter>
#include <QDebug>

class QPainter;

class DialPista : public QDial
{
    Q_OBJECT
public:
    DialPista(QWidget* parent = nullptr);
    virtual void paintEvent(QPaintEvent *pe) override;

private:
    QPen penLineaBlanca = QPen(QBrush(QColor("white")), 1.5);
    QPen penLineaBlancaPunteada = QPen(QBrush(QColor("white")), /*linewidth*/ 1, Qt::DashLine);
    QBrush brushFondo = QBrush(QColor("#d9d9d9"));
    QBrush brushPista = QBrush(QColor("#737373"));

};

#endif // DIALPISTA_H
