#ifndef MODELONOMBRESPLATAFORMAS_H
#define MODELONOMBRESPLATAFORMAS_H

#include <QItemSelection>
#include "modeloverticesplataformas.h"
#include "../../../estructuras-datos/elementosaerop.h"

class ModeloNombresPlataformas : public QAbstractItemModel
{
    Q_OBJECT
    using BaseClass = QAbstractItemModel;

public:
    enum platCol
    {
        E_NOMBRE,
        E_VERTICES,
    };
    enum vertCol
    {
        E_POS_X,
        E_POS_Y,
        _END
    };

    enum misRoles
    {
        tablaRol = Qt::UserRole
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

public slots:
    void sloSeleccionCambiada(const QItemSelection& itemSeleccion, const QItemSelection& itemDeseleccion);

private:
    friend class ModeloVerticesPlataformas;
    QList<Plataforma> &listaPlataformas;
    QList<Plataforma> buffListaPlataformas;
    Plataforma  plataformaDefault = Plataforma {"Foo", QVector<QPointF> {{500,500}, {500,450}, {450,450}, {450,500}}};
    int ultimoSeleccionado;
};

#endif // MODELONOMBRESPLATAFORMAS_H
