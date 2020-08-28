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
    ui->spinBox_2->setValue(1);
    ui->spinBox_2->setRange(1,p);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(addTrack()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(deleteTrack()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(textSave()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(textOpen()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(binSave()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(binOpen()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(report()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(editTrack()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(sortByUser()));

    connect(ui->lineEdit_6, SIGNAL(textEdited(QString)), this, SLOT(editLine6(QString)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(editCombo()));
    connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(editIsp(QString)));
    connect(ui->lineEdit_2, SIGNAL(textEdited(QString)), this, SLOT(editName(QString)));
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
    int posInt = 0;
    if(ui->lineEdit_3->text().toInt() == 0)
        posInt = 1;
    else
    {
        posInt = ui->lineEdit_3->text().toInt();
    }
    pos->setData(0, posInt);

    QTableWidgetItem *month = new QTableWidgetItem();
    month->setData(0, ui->lineEdit_4->text().toInt());

    QTableWidgetItem *year = new QTableWidgetItem();
    year->setData(0, ui->lineEdit_5->text().toInt());

    ui->tableWidget->setItem(p, 2, pos);
    ui->tableWidget->setItem(p, 3, month);
    ui->tableWidget->setItem(p, 4, year);

    spisok.addMuz(ui->lineEdit->text(), ui->lineEdit_2->text(), posInt, ui->lineEdit_4->text().toInt(), ui->lineEdit_5->text().toInt());

    p++;
    ui->spinBox->setRange(1,p);
    ui->spinBox_2->setRange(1,p);

}

void MainWindow::deleteTrack()
{

    if(p==0) return;

    spisok.deleteEl(ui->spinBox->value());

    ui->tableWidget->removeRow(ui->spinBox->value()-1);
    p--;
    ui->spinBox->setRange(1,p);
    ui->spinBox_2->setRange(1,p);

}

void MainWindow::editTrack()
{
    if(ui->spinBox_2->value() > spisok.count) return;

    if(ui->comboBox->currentIndex() == 3 && ui->lineEdit_6->text().toInt() == 0) ui->lineEdit_6->setText(QString::number(1));
    spisok.editEl(ui->spinBox_2->value(), ui->comboBox->currentIndex() + 1, ui->lineEdit_6->text());

    if(ui->comboBox->currentIndex() == 0)
    {
        ui->tableWidget->setItem(ui->spinBox_2->value()-1, 0, new QTableWidgetItem(spisok.showEl(ui->spinBox_2->value())->isp));
    }

    if(ui->comboBox->currentIndex() == 1)
    {
        ui->tableWidget->setItem(ui->spinBox_2->value()-1, 1, new QTableWidgetItem(spisok.showEl(ui->spinBox_2->value())->name));
    }

    if(ui->comboBox->currentIndex() == 2)
    {
        QTableWidgetItem *temp = new QTableWidgetItem();
        temp->setData(0, spisok.showEl(ui->spinBox_2->value())->pos);
        ui->tableWidget->setItem(ui->spinBox_2->value()-1, 2, temp);
    }

    if(ui->comboBox->currentIndex() == 3)
    {
        QTableWidgetItem *temp = new QTableWidgetItem();
        temp->setData(0, spisok.showEl(ui->spinBox_2->value())->month);
        ui->tableWidget->setItem(ui->spinBox_2->value()-1, 3, temp);
    }

    if(ui->comboBox->currentIndex() == 4)
    {
        QTableWidgetItem *temp = new QTableWidgetItem();
        temp->setData(0, spisok.showEl(ui->spinBox_2->value())->year);
        ui->tableWidget->setItem(ui->spinBox_2->value()-1, 4, temp);
    }
}


void MainWindow::editItem(QTableWidgetItem* change)
{
    int valueMonth = 0;
    int valueYear = 0;
    int valuePos = 0;

    QString cutstr = nullptr;
    if(change->text().length() > 12)
    {
        cutstr = change->text().remove(12, change->text().length());
        change->setData(0, cutstr);
    }

    if(change->column() == 3 || change->column() == 4) {
        QTableWidgetItem *item = ui->tableWidget->item(change->row(), 2);
        if(item != nullptr)
        valuePos = item->text().toInt();
    }

    if(change->column() == 4 || change->column() == 2) {
        QTableWidgetItem *item2 = ui->tableWidget->item(change->row(), 3);
        if(item2 != nullptr)
            valueMonth = item2->text().toInt();
    }

    if(change->column() == 3 || change->column() == 2) {
        QTableWidgetItem *item1 = ui->tableWidget->item(change->row(), 4);
        if(item1 != nullptr)
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

void MainWindow::editLine6(QString change)
{
    if(change.length() > 12)
    {
        QString cutstr = nullptr;
        cutstr = change.remove(12, change.length()-1);
        ui->lineEdit_6->setText(cutstr);
    }

    if(ui->comboBox->currentIndex() == 3)
    {
        if(change.toInt() > 12) ui->lineEdit_6->setText(QString::number(12));
        if(change.toInt() < 0) ui->lineEdit_6->setText(QString::number(1));
    }

    if(ui->comboBox->currentIndex() == 4)
    {
        if(change.toInt() > 2019) ui->lineEdit_6->setText(QString::number(2019));
        if(change.toInt() == 0) ui->lineEdit_6->setText(QString::number(1));
    }
}

void MainWindow::editCombo()
{
    if(ui->comboBox->currentIndex() == 0)
    {
        ui->lineEdit_6->setValidator(nullptr);
        ui->lineEdit_6->setText(spisok.showEl(ui->spinBox_2->value())->isp);
    }

    if(ui->comboBox->currentIndex() == 1)
    {
        ui->lineEdit_6->setValidator(nullptr);
        ui->lineEdit_6->setText(spisok.showEl(ui->spinBox_2->value())->name);
    }

    if(ui->comboBox->currentIndex() == 2)
    {
        ui->lineEdit_6->setValidator(new QIntValidator(1, 9999));
        ui->lineEdit_6->setText(QString::number(spisok.showEl(ui->spinBox_2->value())->pos));
    }

    if(ui->comboBox->currentIndex() == 3)
    {
        ui->lineEdit_6->setValidator(new QIntValidator(1, 99));
        ui->lineEdit_6->setText(QString::number(spisok.showEl(ui->spinBox_2->value())->month));
    }

    if(ui->comboBox->currentIndex() == 4)
    {
        ui->lineEdit_6->setValidator(new QIntValidator(1, 9999));
        ui->lineEdit_6->setText(QString::number(spisok.showEl(ui->spinBox_2->value())->year));
    }
}

void MainWindow::editIsp(QString change)
{
    QString temp = nullptr;
    if(change.length() > 12)
    {
        temp = change.remove(12, change.length());
        ui->lineEdit->setText(temp);
    }
}

void MainWindow::editName(QString change)
{
    QString temp = nullptr;
    if(change.length() > 12)
    {
        temp = change.remove(12, change.length());
        ui->lineEdit_2->setText(temp);
    }
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

void MainWindow::sortByUser()
{
    spisok.sortMass(ui->comboBox_2->currentIndex());

    for(int i = 0; i < spisok.count; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if(j == 0) ui->tableWidget->setItem(i, j, new QTableWidgetItem(spisok.showEl(i+1)->isp));
            if(j == 1) ui->tableWidget->setItem(i, j, new QTableWidgetItem(spisok.showEl(i+1)->name));
            if(j == 2)
            {
                QTableWidgetItem *temp = new QTableWidgetItem();
                temp->setData(0, spisok.showEl(i+1)->pos);
                ui->tableWidget->setItem(i, j, temp);
            }
            if(j == 3)
            {
                QTableWidgetItem *temp = new QTableWidgetItem();
                temp->setData(0, spisok.showEl(i+1)->month);
                ui->tableWidget->setItem(i, j, temp);
            }
            if(j == 4)
            {
                QTableWidgetItem *temp = new QTableWidgetItem();
                temp->setData(0, spisok.showEl(i+1)->year);
                ui->tableWidget->setItem(i, j, temp);
            }
        }
    }

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

    for(int i = 1; i <= spisok.count; i++)
        spisok.deleteEl(i);

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        spisok.addMuz(ui->tableWidget->item(i, 0)->text(), ui->tableWidget->item(i, 1)->text(), ui->tableWidget->item(i, 2)->text().toInt(), ui->tableWidget->item(i, 3)->text().toInt(), ui->tableWidget->item(i, 4)->text().toInt());

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
            QString s = nullptr;

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

    for(int i = 1; i <= spisok.count; i++)
        spisok.deleteEl(i);

    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        spisok.addMuz(ui->tableWidget->item(i, 0)->text(), ui->tableWidget->item(i, 1)->text(), ui->tableWidget->item(i, 2)->text().toInt(), ui->tableWidget->item(i, 3)->text().toInt(), ui->tableWidget->item(i, 4)->text().toInt());

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
