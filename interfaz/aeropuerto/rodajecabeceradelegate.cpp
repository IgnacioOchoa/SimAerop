#include "rodajecabeceradelegate.h"

RodajeCabeceraDelegate::RodajeCabeceraDelegate(QObject* parent) :
    QStyledItemDelegate(parent)
{

}

QWidget *RodajeCabeceraDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox* comboBox = new QComboBox(parent);
    comboBox->addItems({"Cabecera 1", "Cabecera 2"});
    return comboBox;
}

void RodajeCabeceraDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString nombre = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setCurrentIndex(comboBox->findText(nombre));
}

void RodajeCabeceraDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString nombre = comboBox->currentText();
    model->setData(index, nombre, Qt::EditRole);
}

void RodajeCabeceraDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}


