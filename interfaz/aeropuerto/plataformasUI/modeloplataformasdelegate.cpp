#include "modeloplataformasdelegate.h"

ModeloPlataformasDelegate::ModeloPlataformasDelegate()
{
    qDebug() << "constructor Delegate";
}

void ModeloPlataformasDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug() << "setEditorData";
    float valor = index.model()->data(index, ModeloNombresPlataformas::misRoles::tablaRol).toFloat();
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(QString::number(valor));
}

QWidget *ModeloPlataformasDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "createEditor";
    QLineEdit* lineEdit = new QLineEdit(parent);
    return lineEdit;
}

void ModeloPlataformasDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
