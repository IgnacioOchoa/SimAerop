#ifndef MODELOPROXYPLATAFORMAS_H
#define MODELOPROXYPLATAFORMAS_H

#include <QObject>
#include <QPointF>
#include <QPolygonF>
#include <QDebug>
#include <QAbstractProxyModel>
#include "modeloplataformas.h"

class ModeloPlataformas;

class ModeloProxyPlataformas : public QAbstractProxyModel
{
    Q_OBJECT
public:
    enum Columns
    {
        E_POS_X,
        E_POS_Y,
        _END
    };
    ModeloProxyPlataformas(ModeloPlataformas* mod, QObject *parent);
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
    QVariant data(const QModelIndex &Index, int role = Qt::DisplayRole) const override;
    virtual QModelIndex mapFromSource(const QModelIndex & sourceIndex) const override {return sourceIndex;}
    virtual QModelIndex mapToSource(const QModelIndex & proxyIndex) const override {return proxyIndex;}

public slots:
    void slotPlatCambiada(const QItemSelection &selected, const QItemSelection &deselected);

private:
    //ModeloPlataformas* modeloPlataformas;
    void setNumRows();
    int currentRow;
    int numRows;

};

#endif // MODELOPROXYPLATAFORMAS_H
