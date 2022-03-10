#ifndef BOTONCANDADO_H
#define BOTONCANDADO_H

#include <QPushButton>
#include <QObject>

class BotonCandado : public QPushButton
{
    Q_OBJECT
public:
    BotonCandado(QWidget* parent = nullptr);

    virtual bool hasHeightForWidth() const override {return true;}
    virtual int heightForWidth(int w) const override {return w;}

public slots:
    void slotActualizarIcono(bool checked);
    void slotCerrarCandado();

signals:
    void sigValorFijado(bool fijado);

private:
    QIcon iconoCerrado;
    QIcon iconoAbierto;

};

#endif // BOTONCANDADO_H
