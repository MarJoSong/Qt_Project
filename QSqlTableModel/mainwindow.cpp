#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QSqlError>
#include <QSqlRecord>

#include "ui_mainwindow.h"

void MainWindow::openTable() {
  tabModel = new QSqlTableModel(this, DB);
  tabModel->setTable("employee");
  tabModel->setSort(tabModel->fieldIndex("EmpNo"), Qt::AscendingOrder);
  tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

  if (!(tabModel->select())) {
    QMessageBox::critical(
        this, "错误信息",
        "打开数据表错误,错误信息\n" + (tabModel->lastError().text()),
        QMessageBox::Ok, QMessageBox::NoButton);

    return;
  }

  tabModel->setHeaderData(tabModel->fieldIndex("EmpNo"), Qt::Horizontal,
                          "工号");
  tabModel->setHeaderData(tabModel->fieldIndex("Name"), Qt::Horizontal, "姓名");
  tabModel->setHeaderData(tabModel->fieldIndex("Gender"), Qt::Horizontal,
                          "性别");
  tabModel->setHeaderData(tabModel->fieldIndex("Height"), Qt::Horizontal,
                          "身高");
  tabModel->setHeaderData(tabModel->fieldIndex("Birthday"), Qt::Horizontal,
                          "出生日期");
  tabModel->setHeaderData(tabModel->fieldIndex("Mobile"), Qt::Horizontal,
                          "手机");
  tabModel->setHeaderData(tabModel->fieldIndex("Province"), Qt::Horizontal,
                          "省份");
  tabModel->setHeaderData(tabModel->fieldIndex("City"), Qt::Horizontal, "城市");
  tabModel->setHeaderData(tabModel->fieldIndex("Department"), Qt::Horizontal,
                          "部门");
  tabModel->setHeaderData(tabModel->fieldIndex("Education"), Qt::Horizontal,
                          "学历");
  tabModel->setHeaderData(tabModel->fieldIndex("Salary"), Qt::Horizontal,
                          "工资");
  tabModel->setHeaderData(tabModel->fieldIndex("Memo"), Qt::Horizontal, "备注");
  tabModel->setHeaderData(tabModel->fieldIndex("Photo"), Qt::Horizontal,
                          "照片");

  theSelection = new QItemSelectionModel(tabModel);
  connect(theSelection, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this,
          SLOT(on_currentChanged(QModelIndex, QModelIndex)));
  connect(theSelection, SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
          this, SLOT(on_currentRowChanged(QModelIndex, QModelIndex)));

  ui->tableView->setModel(tabModel);
  ui->tableView->setSelectionModel(theSelection);
  ui->tableView->setColumnHidden(tabModel->fieldIndex("Memo"), true);
  ui->tableView->setColumnHidden(tabModel->fieldIndex("Photo"), true);

  QStringList strList;
  strList << "男"
          << "女";
  bool isEditable = false;
  delegateSex.setItems(strList, isEditable);
  ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("Gender"),
                                          &delegateSex);

  strList.clear();
  strList << "销售部"
          << "技术部"
          << "生产部"
          << "行政部";
  isEditable = true;
  delegateDepart.setItems(strList, isEditable);
  ui->tableView->setItemDelegateForColumn(tabModel->fieldIndex("Department"),
                                          &delegateDepart);

  dataMappler = new QDataWidgetMapper();
  dataMappler->setModel(tabModel);
  dataMappler->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
  dataMappler->addMapping(ui->dbSpinEmpNo, tabModel->fieldIndex("EmpNo"));
  dataMappler->addMapping(ui->dbEditName, tabModel->fieldIndex("Name"));
  dataMappler->addMapping(ui->dbComboSex, tabModel->fieldIndex("Gender"));
  dataMappler->addMapping(ui->dbSpinHeight, tabModel->fieldIndex("Height"));
  dataMappler->addMapping(ui->dbEditBirth, tabModel->fieldIndex("Birthday"));
  dataMappler->addMapping(ui->dbEditMobile, tabModel->fieldIndex("Mobile"));
  dataMappler->addMapping(ui->dbComboProvince,
                          tabModel->fieldIndex("Province"));
  dataMappler->addMapping(ui->dbEditCity, tabModel->fieldIndex("City"));
  dataMappler->addMapping(ui->dbComboDep, tabModel->fieldIndex("Department"));
  dataMappler->addMapping(ui->dbComboEdu, tabModel->fieldIndex("Education"));
  dataMappler->addMapping(ui->dbSpinSalary, tabModel->fieldIndex("Salary"));
  dataMappler->addMapping(ui->dbEditMemo, tabModel->fieldIndex("Memo"));
  dataMappler->toFirst();

  getFieldNames();

  ui->actOpenDB->setEnabled(false);
  ui->actRecAppend->setEnabled(true);
  ui->actRecInsert->setEnabled(true);
  ui->actRecDelete->setEnabled(true);
  ui->actScan->setEnabled(true);
  ui->groupBoxSort->setEnabled(true);
  ui->groupBoxFilter->setEnabled(true);
}

void MainWindow::getFieldNames() {
  QSqlRecord emptyRec = tabModel->record();
  for (int i = 0; i < emptyRec.count(); i++)
    ui->comboFields->addItem(emptyRec.fieldName(i));
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  this->setCentralWidget(ui->splitter);

  // tableview
  ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
  ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tableView->setAlternatingRowColors(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_currentChanged(const QModelIndex &current,
                                   const QModelIndex &previous) {
  Q_UNUSED(current);
  Q_UNUSED(previous);

  ui->actSubmit->setEnabled(tabModel->isDirty());
  ui->actRevert->setEnabled(tabModel->isDirty());
}

void MainWindow::on_currentRowChanged(const QModelIndex &current,
                                      const QModelIndex &previous) {
  Q_UNUSED(previous);
  ui->actRecDelete->setEnabled(current.isValid());
  ui->actPhoto->setEnabled(current.isValid());
  ui->actPhotoClear->setEnabled(current.isValid());

  if (!current.isValid()) {
    ui->dbLabPhoto->clear();
    return;
  }

  dataMappler->setCurrentIndex(current.row());
  int curRecNo = current.row();
  QSqlRecord curRec = tabModel->record(curRecNo);
  if (curRec.isNull("Photo"))
    ui->dbLabPhoto->clear();
  else {
    QByteArray data = curRec.value("Photo").toByteArray();
    QPixmap pic;
    pic.loadFromData(data);
    ui->dbLabPhoto->setPixmap(
        pic.scaledToWidth(ui->dbLabPhoto->size().width()));
  }
}

void MainWindow::on_actOpenDB_triggered() {
  QString aFile = QFileDialog::getOpenFileName(this, "选择数据库文件", "",
                                               "SQLite数据库(*.db *.db3)");
  if (aFile.isEmpty()) return;

  DB = QSqlDatabase::addDatabase("QSQLITE");
  DB.setDatabaseName(aFile);
  if (!DB.open()) {
    QMessageBox::warning(this, "错误", "打开数据库失败", QMessageBox::Ok,
                         QMessageBox::NoButton);
  }
  openTable();
}

void MainWindow::on_actRecAppend_triggered() {
  tabModel->insertRow(tabModel->rowCount(), QModelIndex());
  QModelIndex curIndex = tabModel->index(tabModel->rowCount() - 1, 1);
  theSelection->clearSelection();
  theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
  int currow = curIndex.row();
  tabModel->setData(tabModel->index(currow, 0), 2000 + tabModel->rowCount());
  tabModel->setData(tabModel->index(currow, 2), "男");
}

void MainWindow::on_actRecInsert_triggered() {
  QModelIndex curIndex = ui->tableView->currentIndex();
  tabModel->insertRow(curIndex.row(), QModelIndex());
  theSelection->clearSelection();
  theSelection->setCurrentIndex(curIndex, QItemSelectionModel::Select);
}

void MainWindow::on_actRecDelete_triggered() {
  QModelIndex curIndex = theSelection->currentIndex();
  tabModel->removeRow(curIndex.row());
  ui->actSubmit->setEnabled(tabModel->isDirty());
  ui->actRevert->setEnabled(tabModel->isDirty());
}

void MainWindow::on_actSubmit_triggered() {
  bool res = tabModel->submitAll();
  if (!res)
    QMessageBox::information(
        this, "消息",
        "数据表保存错误,错误信息\n" + (tabModel->lastError().text()),
        QMessageBox::Ok, QMessageBox::NoButton);
  else {
    ui->actSubmit->setEnabled(false);
    ui->actRevert->setEnabled(false);
  }
}

void MainWindow::on_actRevert_triggered() {
  tabModel->revertAll();
  ui->actSubmit->setEnabled(false);
  ui->actRevert->setEnabled(false);
}

void MainWindow::on_actPhoto_triggered() {
  QString aFile =
      QFileDialog::getOpenFileName(this, "选择图片", "", "照片(*.png *.jpg)");
  if (aFile.isEmpty()) return;

  QByteArray data;
  QFile *file = new QFile(aFile);
  file->open(QIODevice::ReadOnly);
  data = file->readAll();
  file->close();

  int curRecNo = theSelection->currentIndex().row();
  QSqlRecord curRec = tabModel->record(curRecNo);
  curRec.setValue("Photo", data);
  tabModel->setRecord(curRecNo, curRec);
  QPixmap pic;
  pic.load(aFile);
  ui->dbLabPhoto->setPixmap(pic.scaledToWidth(ui->dbLabPhoto->width()));
}

void MainWindow::on_actPhotoClear_triggered() {
  int curRecNo = theSelection->currentIndex().row();
  QSqlRecord curRec = tabModel->record(curRecNo);
  curRec.setNull("Photo");
  tabModel->setRecord(curRecNo, curRec);
  ui->dbLabPhoto->clear();
}

void MainWindow::on_actScan_triggered() {
  if (tabModel->rowCount() == 0) return;
  for (int i = 0; i < tabModel->rowCount(); i++) {
    QSqlRecord aRec = tabModel->record(i);
    float salary = aRec.value("Salary").toFloat();
    salary = salary * 1.1;
    aRec.setValue("Salary", salary);
    tabModel->setRecord(i, aRec);
  }
  if (tabModel->submitAll())
    QMessageBox::information(this, "消息", "涨工资计算完毕", QMessageBox::Ok,
                             QMessageBox::NoButton);
}

void MainWindow::on_comboFields_currentIndexChanged(int index) {
  if (ui->radioBtnAscend->isChecked())
    tabModel->setSort(index, Qt::AscendingOrder);
  else
    tabModel->setSort(index, Qt::DescendingOrder);
  tabModel->select();
}

void MainWindow::on_radioBtnAscend_clicked() {
  tabModel->setSort(ui->comboFields->currentIndex(), Qt::AscendingOrder);
  tabModel->select();
}

void MainWindow::on_radioBtnDescend_clicked() {
  tabModel->setSort(ui->comboFields->currentIndex(), Qt::DescendingOrder);
  tabModel->select();
}

void MainWindow::on_radioBtnMan_clicked() {
  tabModel->setFilter("Gender='男'");
}

void MainWindow::on_radioBtnWoman_clicked() {
  tabModel->setFilter("Gender='女'");
}

void MainWindow::on_radioBtnBoth_clicked() { tabModel->setFilter(""); }
