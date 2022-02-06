#ifndef MODELOVERTICESPLATAFORMAS_H
#define MODELOVERTICESPLATAFORMAS_H

#include <QAbstractTableModel>
#include "modelonombresplataformas.h"
#include "../../../estructuras-datos/elementosaerop.h"

class ModeloVerticesPlataformas : public QAbstractItemModel
{
    Q_OBJECT
    using BaseClass = QAbstractItemModel;

public:
    enum Columns
    {
        E_POS_X,
        E_POS_Y,
        _END
    };
    ModeloVerticesPlataformas(const QModelIndex& index, QObject* parent);
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

private:
    Plataforma* plataforma;
    QPointF puntoDefault = QPointF (500,500);
};
Q_DECLARE_METATYPE(ModeloVerticesPlataformas*)

#endif // MODELOVERTICESPLATAFORMAS_H
