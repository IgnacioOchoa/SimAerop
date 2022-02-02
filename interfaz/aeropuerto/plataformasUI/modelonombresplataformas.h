#ifndef MODELONOMBRESPLATAFORMAS_H
#define MODELONOMBRESPLATAFORMAS_H

#include <QAbstractTableModel>
#include "../../../estructuras-datos/elementosaerop.h"

class ModeloNombresPlataformas : public QAbstractListModel
{
    Q_OBJECT

public:
    ModeloNombresPlataformas(QList<Plataforma>& bl, QObject *parent);

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void sincListas();

private:
    QList<Plataforma> &buffListaPlataformas;
    Plataforma  plataformaDefault = Plataforma{"Foo", {QPointF (500,500), QPointF (500,450),  QPointF (450,450), QPointF (450,500)}};

};

#endif // MODELONOMBRESPLATAFORMAS_H
