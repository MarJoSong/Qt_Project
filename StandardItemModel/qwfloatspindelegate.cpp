#include "qwfloatspindelegate.h"
#include <QDoubleSpinBox>

QWFloatSpinDelegate::QWFloatSpinDelegate()
{

}

QWidget *QWFloatSpinDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QDoubleSpinBox *editor = new QDoubleSpinBox(parent);
    editor->setFrame(false);
    editor->setMinimum(0);
    editor->setMaximum(10000);
    return editor;
}

void QWFloatSpinDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    double value = index.model()->data(index, Qt::EditRole).toDouble();
    QDoubleSpinBox *doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
    doubleSpinBox->setValue(value);
}

void QWFloatSpinDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QDoubleSpinBox* doubleSpinBox = static_cast<QDoubleSpinBox*>(editor);
    doubleSpinBox->interpretText();
    double value = doubleSpinBox->value();
    model->setData(index, value, Qt::EditRole);
}

void QWFloatSpinDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
