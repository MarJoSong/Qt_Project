#include "qwcomboboxdelegate.h"
#include <QComboBox>
#include <QStringList>

QWComboBoxDelegate::QWComboBoxDelegate()
{

}

QWidget *QWComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox* editor = new QComboBox(parent);
    editor->setFrame(false);
    QStringList level;
    level << "优" << "良" << "一般";
    editor->addItems(level);
    return editor;
}

void QWComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    comboBox->setFont(value);
}

void QWComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox* comboBox = static_cast<QComboBox*>(editor);
    //comboBox->interpretText();
    QString value = comboBox->currentText();
    model->setData(index, value, Qt::EditRole);
}

void QWComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
