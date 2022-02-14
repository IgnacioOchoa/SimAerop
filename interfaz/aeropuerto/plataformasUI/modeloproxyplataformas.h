#ifndef MODELOPROXYPLATAFORMAS_H
#define MODELOPROXYPLATAFORMAS_H

#include <QObject>
#include <QPointF>
#include <QPolygonF>
#include <QDebug>
#include <QAbstractProxyModel>

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
    ModeloProxyPlataformas(QObject *parent);
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
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    virtual QModelIndex mapFromSource(const QModelIndex & sourceIndex) const;
    virtual QModelIndex mapToSource(const QModelIndex & proxyIndex) const;
signals:

};

#endif // MODELOPROXYPLATAFORMAS_H
