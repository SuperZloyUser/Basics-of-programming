#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_3->setValidator(new QIntValidator(1, 1000));
    ui->lineEdit_4->setValidator(new QIntValidator(1, 100));
    ui->lineEdit_5->setValidator(new QIntValidator(1, 10000));
    ui->lineEdit_4->setText(QString::number(5));
    ui->lineEdit_5->setText(QString::number(2019));
    ui->spinBox->setValue(1);
    //ui->spinBox->setRange(1,p);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addTrack()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(deleteTrack()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(DBSave()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(DBOpen()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(report()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(DBEdit()));

    connect(ui->comboBox_3, SIGNAL(currentIndexChanged(QString)), this, SLOT(DBshow()));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(DBshow()));
    ui->spinBox_2->setValue(1);

    connect(ui->lineEdit_4, SIGNAL(textEdited(QString)), this, SLOT(editMonth(QString)));
    connect(ui->lineEdit_5, SIGNAL(textEdited(QString)), this, SLOT(editYear(QString)));
    connect(ui->lineEdit_6, SIGNAL(textEdited(QString)), this, SLOT(line6edited(QString)));
    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(editItem(QTableWidgetItem*)));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(setspin2()));
}

void MainWindow::addTrack()
{

    ui->tableWidget->setRowCount(p+1);
    ui->tableWidget->setItem(p, 0, new QTableWidgetItem(ui->lineEdit->text()));
    ui->tableWidget->setItem(p, 1, new QTableWidgetItem(ui->lineEdit_2->text()));

    QTableWidgetItem *pos = new QTableWidgetItem();
    pos->setData(0, ui->lineEdit_3->text().toInt());
    QTableWidgetItem *month = new QTableWidgetItem();
    month->setData(0, ui->lineEdit_4->text().toInt());
    QTableWidgetItem *year = new QTableWidgetItem();
    year->setData(0, ui->lineEdit_5->text().toInt());

    ui->tableWidget->setItem(p, 2, pos);
    ui->tableWidget->setItem(p, 3, month);
    ui->tableWidget->setItem(p, 4, year);

    p++;
    //ui->spinBox->setRange(1, p);

}

void MainWindow::deleteTrack()
{

    if(p==0) return;

    if(ui->radioButton_2->isChecked())
    {

        ui->tableWidget->removeRow(ui->spinBox->value()-1);
        p--;
        //ui->spinBox->setRange(1, p);
    }

    if(ui->radioButton->isChecked())
    {
        QSqlDatabase db;
        QString connection = QString(QSqlDatabase::defaultConnection);
        db = QSqlDatabase::addDatabase("QSQLITE", connection);
        db.setDatabaseName("A:\\progi\\BoP-3(11)\\test.db3");
        db.open();

        QSqlQuery query;
        query.prepare("DELETE FROM tracks WHERE ROWID = ?");
        query.addBindValue(ui->spinBox->text().toInt());
        query.exec();
        db.close();
    }


}

void MainWindow::editItem(QTableWidgetItem* change)
{

    int valueMonth = 0;
    int valueYear = 0;
    int valuePos = 0;

    QString cutstr = NULL;
    if(change->text().length() > 10)
    {
        cutstr = change->text().remove(10, change->text().length()-1);
        change->setData(0, cutstr);
    }


    if(change->column() == 3 || change->column() == 4) {
        QTableWidgetItem *item = ui->tableWidget->item(change->row(), 2);
        if(item != NULL)
        valuePos = item->text().toInt();
    }

    if(change->column() == 4 || change->column() == 2) {
        QTableWidgetItem *item2 = ui->tableWidget->item(change->row(), 3);
        if(item2 != NULL)
            valueMonth = item2->text().toInt();
    }

    if(change->column() == 3 || change->column() == 2) {
        QTableWidgetItem *item1 = ui->tableWidget->item(change->row(), 4);
        if(item1 != NULL)
            valueYear = item1->text().toInt();
    }

    if(change->column() == 3 && change->text().toInt() > 12) change->setData(0, 12);
    if(change->column() == 3 && change->text().toInt() > 5 && valueYear == 2019) change->setData(0, 5);
    if(change->column() == 3 && change->text().toInt() < 1) change->setData(0, 1);
    if(change->column() == 4 && change->text().toInt() > 2019) change->setData(0, 2019);
    if(change->column() == 4 && change->text().toInt() < 1) change->setData(0, 1);

    if(change->column() == 2 && valueYear == 2019 && valueMonth >= 2 && change->text().toInt() <= 20) ui->tableWidget->setItem(change->row(), 5, new QTableWidgetItem("Да"));
    if(change->column() == 2 && valueYear == 2019 && valueMonth >= 2 && change->text().toInt() > 20) ui->tableWidget->setItem(change->row(), 5, new QTableWidgetItem("Нет"));

    if(change->column() == 3 && valueYear == 2019 && change->text().toInt() >= 2 && valuePos <= 20) ui->tableWidget->setItem(change->row(), 5, new QTableWidgetItem("Да"));
    if(change->column() == 3 && change->text().toInt() < 2) ui->tableWidget->setItem(change->row(), 5, new QTableWidgetItem("Нет"));
    if(change->column() == 3 && valueYear != 2019) ui->tableWidget->setItem(change->row(), 5, new QTableWidgetItem("Нет"));

    if(change->column() == 4 && valueMonth >= 2 && change->text().toInt() == 2019 && valuePos <= 20) ui->tableWidget->setItem(change->row(), 5, new QTableWidgetItem("Да"));
    if(change->column() == 4 && valueMonth < 2) ui->tableWidget->setItem(change->row(), 5, new QTableWidgetItem("Нет"));
    if(change->column() == 4 && change->text().toInt() != 2019) ui->tableWidget->setItem(change->row(), 5, new QTableWidgetItem("Нет"));

}

void MainWindow::editMonth(QString change)
{

    int month = change.toInt();
    int year = ui->lineEdit_5->text().toInt();

    if(year == 2019 && month > 5) month = 5;
    if(month > 12) month = 12;
    //if(change == "") month = 5;

    ui->lineEdit_4->setText(QString::number(month));
}

void MainWindow::editYear(QString change)
{

    int year = change.toInt();
    if(year >= 2019) year = 2019;
    //if(change == "") year = 2019;
    ui->lineEdit_5->setText(QString::number(year));
}

void MainWindow::setspin2()
{
    ui->spinBox_2->setRange(1, returncountDB());
}

void MainWindow::showError()
{
        ui->tableWidget->removeRow(p);
        QMessageBox::warning(this, "ERROR","Файл некорретен");
}

void MainWindow::line6edited(QString change)
{
    if(ui->comboBox_3->currentIndex() == 3 && change.toInt() > 12) ui->lineEdit_6->setText(QString::number(12));
    if(ui->comboBox_3->currentIndex() == 4 && change.toInt() > 2019) ui->lineEdit_6->setText(QString::number(2019));
}

int MainWindow::returncountDB()
{
    QSqlDatabase db;
    QString connection = QString(QSqlDatabase::defaultConnection);
    db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName("A:\\progi\\BoP-3(11)\\test.db3");
    db.open();

    QSqlQuery query;
    QString s = "SELECT isp, name, pos, month, year FROM tracks";

    int a = 0;

    while (query.next())
    {
        a++;
    }

    return a;
}

void MainWindow::DBOpen()
{
    ui->tableWidget->setRowCount(0);
    p = 0;

    QSqlDatabase db;
    QString connection = QString(QSqlDatabase::defaultConnection);
    db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName("A:\\progi\\BoP-3(11)\\test.db3");
    db.open();

    QSqlQuery query;
    QString s = "SELECT isp, name, pos, month, year FROM tracks";

    if(ui->comboBox->currentIndex() != 0)
        s += " ORDER BY ";
    if(ui->comboBox->currentIndex() == 1)
        s += "isp";
    if(ui->comboBox->currentIndex() == 2)
        s += "name";
    if(ui->comboBox->currentIndex() == 3)
        s += "pos";
    if(ui->comboBox->currentIndex() == 4)
        s += "month";
    if(ui->comboBox->currentIndex() == 5)
        s += "year";

    if(ui->comboBox_2->currentIndex() == 1 && ui->comboBox->currentIndex() != 0) s += " DESC";

    query.exec(s);

    while (query.next())
    {
        QString isp = query.value(0).toString();
        QString name = query.value(1).toString();
        QString pos = query.value(2).toString();
        QString month = query.value(3).toString();
        QString year = query.value(4).toString();

        ui->tableWidget->setRowCount(p + 1);

        ui->tableWidget->setItem(p, 0, new QTableWidgetItem(isp));
        ui->tableWidget->setItem(p, 1, new QTableWidgetItem(name));

        QTableWidgetItem *in1 = new QTableWidgetItem;
        in1->setData(Qt::DisplayRole, pos.toUInt());
        ui->tableWidget->setItem(p, 2, in1);

        QTableWidgetItem *in2 = new QTableWidgetItem;
        in2->setData(Qt::DisplayRole, month.toUInt());
        ui->tableWidget->setItem(p, 3, in2);

        QTableWidgetItem *in3 = new QTableWidgetItem;
        in3->setData(Qt::DisplayRole, year.toUInt());
        ui->tableWidget->setItem(p, 4, in3);

        p++;
    }
    db.close();

    QMessageBox::information(this, "OK","БД успешно загружена");

}


void MainWindow::DBSave()
{
    QSqlDatabase db;
    QString connection = QString(QSqlDatabase::defaultConnection);
    db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName("A:\\progi\\BoP-3(11)\\test.db3");
    db.open();

    for(int i = 0; i < p; i++)
    {
        QString s1 = ui->tableWidget->item(i, 0)->text();
        QString s2 = ui->tableWidget->item(i, 1)->text();
        int s3 = ui->tableWidget->item(i, 2)->text().toInt();
        int s4 = ui->tableWidget->item(i, 3)->text().toInt();
        int s5 = ui->tableWidget->item(i, 4)->text().toInt();

        QSqlQuery query;
        query.prepare("INSERT INTO tracks(isp, name, pos, month, year) VALUES(:s1, :s2, :s3, :s4, :s5);");
        query.bindValue(":s1", s1);
        query.bindValue(":s2", s2);
        query.bindValue(":s3", s3);
        query.bindValue(":s4", s4);
        query.bindValue(":s5", s5);
        query.exec();
    }

    db.close();

    QMessageBox::information(this, "OK","БД успешно сохранена");
}

void MainWindow::DBEdit()
{

    QSqlDatabase db;
    QString connection = QString(QSqlDatabase::defaultConnection);
    db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName("A:\\progi\\BoP-3(11)\\test.db3");
    db.open();

    QSqlQuery query;
    QString s = "UPDATE tracks SET ";

    if(ui->comboBox_3->currentIndex() == 0)
        s += "isp";
    if(ui->comboBox_3->currentIndex() == 1)
        s += "name";
    if(ui->comboBox_3->currentIndex() == 2)
        s += "pos";
    if(ui->comboBox_3->currentIndex() == 3)
        s += "month";
    if(ui->comboBox_3->currentIndex() == 4)
        s += "year";

    QSqlQuery query1;
    query1.exec("SELECT ROWID FROM tracks");
    query1.seek(ui->spinBox_2->text().toInt()-1);

    QString rowid = query1.value(0).toString();

    query.prepare(s + " = '" + ui->lineEdit_6->text() + "' WHERE ROWID = ?");
    query.addBindValue(rowid);
    query.exec();

    QMessageBox::information(this, "OK","Запись успешно изменена");

}

void MainWindow::DBshow()
{

    QSqlDatabase db;
    QString connection = QString(QSqlDatabase::defaultConnection);
    db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName("A:\\progi\\BoP-3(11)\\test.db3");
    db.open();

    QSqlQuery query;
    QString s = "SELECT ";

    if(ui->comboBox_3->currentIndex() == 0)
    {
        s += "isp";
        ui->lineEdit_6->setValidator(nullptr);
    }

    if(ui->comboBox_3->currentIndex() == 1)
    {
        s += "name";
        ui->lineEdit_6->setValidator(nullptr);
    }

    if(ui->comboBox_3->currentIndex() == 2)
    {
        s += "pos";
        ui->lineEdit_6->setValidator(new QIntValidator(0, 9999));
    }

    if(ui->comboBox_3->currentIndex() == 3)
    {
        s += "month";
        ui->lineEdit_6->setValidator(new QIntValidator(0, 99));
    }

    if(ui->comboBox_3->currentIndex() == 4)
    {
        s += "year";
        ui->lineEdit_6->setValidator(new QIntValidator(0, 9999));
    }

    query.exec(s + " FROM tracks");
    query.seek(ui->spinBox_2->text().toInt()-1);

    ui->lineEdit_6->setText(query.value(0).toString());

}

void MainWindow::report()
{
    QString path = QFileDialog::getSaveFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-2(10)\\l2\\report", "*.txt");
    QFile file(path);

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        for(int i = 0; i < p; i++)
        {
            out.setFieldWidth(0);
            out << i+1 <<") ";
            for(int j = 0; j < 6; j++)
            {
                out.setFieldWidth(10);
                out << ui->tableWidget->item(i, j)->text();
                if(j != 3) out  <<" | ";
            }

            out <<"\r\n\r\n";
        }
    }
    file.close();

    QProcess* open = new QProcess(this);
    open->start("notepad", QStringList() << path);
}

MainWindow::~MainWindow()
{
    delete ui;
}
