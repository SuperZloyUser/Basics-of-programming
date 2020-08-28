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
    ui->spinBox->setRange(1,p);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addTrack()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(deleteTrack()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(textSave()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(textOpen()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(binSave()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(binOpen()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(report()));


    connect(ui->lineEdit_4, SIGNAL(textEdited(QString)), this, SLOT(editMonth(QString)));
    connect(ui->lineEdit_5, SIGNAL(textEdited(QString)), this, SLOT(editYear(QString)));
    connect(ui->tableWidget, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(editItem(QTableWidgetItem*)));
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
    ui->spinBox->setRange(1,p);

}

void MainWindow::deleteTrack()
{

    if(p==0) return;

    ui->tableWidget->removeRow(ui->spinBox->value()-1);
    p--;
    ui->spinBox->setRange(1,p);

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

void MainWindow::showError()
{
        ui->tableWidget->removeRow(p);
        QMessageBox::warning(this, "ERROR","Файл некорретен");
}

void MainWindow::textOpen()
{

    QFile file(QFileDialog::getOpenFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-2(10)\\l2", "*.txt"));
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            ui->tableWidget->setRowCount(p+1);
            QString s = in.readLine();

            QString s1 = s.section('$', 0, 0);
            QTableWidgetItem *str1 = new QTableWidgetItem;
            str1->setData(0, s1);
            ui->tableWidget->setItem(p, 0, str1);

            QString s2 = s.section('$', 1, 1);
            QTableWidgetItem *str2 = new QTableWidgetItem;
            str2->setData(0, s2);
            ui->tableWidget->setItem(p, 1, str2);

            QString s3 = s.section('$', 2, 2);
            QTableWidgetItem *str3 = new QTableWidgetItem;
            str3->setData(0, s3.toInt());
            ui->tableWidget->setItem(p, 2, str3);

            QString s4 = s.section('$', 3, 3);
            QTableWidgetItem *str4 = new QTableWidgetItem;
            str4->setData(0, s4.toInt());
            ui->tableWidget->setItem(p, 3, str4);

            QString s5 = s.section('$', 4, 4);
            QTableWidgetItem *str5 = new QTableWidgetItem;
            str5->setData(0, s5.toInt());
            ui->tableWidget->setItem(p, 4, str5);
        p++;
    }
    file.close();
    }
}


void MainWindow::textSave()
{
    QFile file(QFileDialog::getSaveFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-2(10)\\l2\\1", "*.txt"));

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        for(int i = 0; i < p; i++)
        {
            for(int j = 0; j < 5; j++)
                out << ui->tableWidget->item(i, j)->text() << "$";
            out << "\n";
        }
    }
}

void MainWindow::binOpen()
{

    QFile file(QFileDialog::getOpenFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-2(10)\\l2", "*.dat"));
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);

        while(!in.atEnd())
        {
            ui->tableWidget->setRowCount(p+1);
            QString s = NULL;

            for(int i = 0; i < 5; i++)
            {
                in >> s;

                if(i < 3)
                {
                    ui->tableWidget->setItem(p, i, new QTableWidgetItem(s));
                } else {
                    QTableWidgetItem *item = new QTableWidgetItem;
                    item->setData(0, s.toUInt());
                    ui->tableWidget->setItem(p, i, item);
                }

            }
            p++;
        }
        file.close();
    }

}

void MainWindow::binSave()
{
    QFile file(QFileDialog::getSaveFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-2(10)\\l2\\1", "*.dat"));
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);

        for(int i = 0; i < p; i++)
        {
            for(int j = 0; j < 5; j++)
                out << ui->tableWidget->item(i, j)->text();
        }
    }
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
