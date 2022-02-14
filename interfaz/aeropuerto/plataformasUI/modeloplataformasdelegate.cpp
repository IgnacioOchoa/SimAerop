#include "modeloplataformasdelegate.h"

ModeloPlataformasDelegate::ModeloPlataformasDelegate(QObject* parent) :
    QStyledItemDelegate(parent)
{
    qDebug() << "constructor Delegate";
}

void ModeloPlataformasDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug() << "setEditorData";
    float valor = index.model()->data(index, ModeloNombresPlataformas::misRoles::tablaRol).toFloat();
    QLineEdit* lineEdit = static_cast<QLineEdit*>(editor);
    //QLabel *label = static_cast<QLabel*>(editor);
    lineEdit->setText(QString::number(valor));
}

QWidget *ModeloPlataformasDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "createEditor";
    QLineEdit* lineEdit = new QLineEdit(parent);
    //QLabel* lb = new QLabel(parent);
    return lineEdit;
}

void ModeloPlataformasDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "updateEditorGeometry";
    editor->setGeometry(option.rect);
}

void ModeloPlataformasDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    float nro = index.data(ModeloNombresPlataformas::tablaRol).toFloat();
    //qInfo() << "Consultado el elemento de row: " << index.row() << " , col: " << index.column();
    QApplication::style()->drawItemText(painter,
                 option.rect,
                 option.displayAlignment,
                 option.palette,
                 true,
                 QString::number(nro));
}
