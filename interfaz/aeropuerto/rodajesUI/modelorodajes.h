#ifndef MODELORODAJES_H
#define MODELORODAJES_H

#include <QAbstractTableModel>
#include "../../../estructuras-datos/elementosaerop.h"

class ModeloRodajes : public QAbstractTableModel
{
    Q_OBJECT

public:
    ModeloRodajes(const QList<Rodaje>& lstRodaje, QObject *parent);

    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void sincListas();
    void setCabecerasActivas(const QString& c1, const QString& c2);

private:
    const QList<Rodaje>& listaRodajes;
    QList<Rodaje> buffListaRodajes;
    const QStringList listaHeaders = {"Cabecera", "Posición", "Ángulo", "Ancho", "Largo", "Radio"};
    QString cabActiva1;
    QString cabActiva2;
    Pista pistaDefault = Pista{0,0,0,"",""};
    Rodaje rodajeDefault = Rodaje{"",0,0,0,0,0};
};

#endif // MODELORODAJES_H
