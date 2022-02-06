#ifndef MODELONOMBRESPLATAFORMAS_H
#define MODELONOMBRESPLATAFORMAS_H

#include <QAbstractTableModel>
#include "modeloverticesplataformas.h"
#include "../../../estructuras-datos/elementosaerop.h"

class ModeloNombresPlataformas : public QAbstractItemModel
{
    Q_OBJECT
    using BaseClass = QAbstractItemModel;

public:
    enum Columns
    {
        E_NOMBRE,
        E_VERTICES,
        _END
    };
    ModeloNombresPlataformas(QList<Plataforma>& bl, QObject *parent);
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override
        {
            return createIndex(row, column, nullptr);
        }
    virtual QModelIndex parent(const QModelIndex &child) const override
    {
        return QModelIndex();
    }

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void sincListas();
    void guardarLista();

private:
    friend class ModeloVerticesPlataformas;
    QList<Plataforma> &listaPlataformas;
    QList<Plataforma> buffListaPlataformas;
    Plataforma  plataformaDefault = Plataforma {"Foo", QVector<QPointF> {{500,500}, {500,450}, {450,450}, {450,500}}};

};

#endif // MODELONOMBRESPLATAFORMAS_H
