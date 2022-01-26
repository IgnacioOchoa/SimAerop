#ifndef RODAJETABLEITEM_H
#define RODAJETABLEITEM_H

#include <QStyledItemDelegate>
#include <QComboBox>

class RodajeCabeceraDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    RodajeCabeceraDelegate(QStringList cabeceras, QObject* parent = nullptr);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,const QModelIndex &index) const override;
private:
    QStringList cabecerasPista;

};

#endif // RODAJETABLEITEM_H
