#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBox->setRange(0, 0);
    ui->spinBox_2->setRange(0, 0);
    ui->spinBox_3->setRange(0, 0);
    ui->spinBox_4->setRange(0, 0);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(AddAvt()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(AddVld()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(showAllS1()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(showAllS2()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(showLinksS1()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(showLinksS2()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(makeLinks()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(saveSB1()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(openSB1()));
    connect(ui->pushButton_10, SIGNAL(clicked()), this, SLOT(saveSB2()));
    connect(ui->pushButton_11, SIGNAL(clicked()), this, SLOT(openSB2()));
    connect(ui->pushButton_12, SIGNAL(clicked()), this, SLOT(saveST1()));
    connect(ui->pushButton_13, SIGNAL(clicked()), this, SLOT(openST1()));
    connect(ui->pushButton_14, SIGNAL(clicked()), this, SLOT(saveST2()));
    connect(ui->pushButton_15, SIGNAL(clicked()), this, SLOT(openST2()));

    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(sortS1()));
    connect(ui->comboBox_2, SIGNAL(currentIndexChanged(QString)), this, SLOT(sortS2()));
}

void MainWindow::AddAvt()
{
    combo.addAvt(ui->lineEdit->text(), ui->lineEdit_2->text(), ui->lineEdit_3->text());

    ui->tableWidget->setRowCount(combo.count1);
    ui->tableWidget->setItem(combo.count1 - 1, 0, new QTableWidgetItem(ui->lineEdit->text()));
    ui->tableWidget->setItem(combo.count1 - 1, 1, new QTableWidgetItem(ui->lineEdit_2->text()));
    ui->tableWidget->setItem(combo.count1 - 1, 2, new QTableWidgetItem(ui->lineEdit_3->text()));

    ui->spinBox_4->setRange(1, combo.count1);
    ui->spinBox_2->setRange(1, combo.count1);
}

void MainWindow::AddVld()
{
    combo.addVld(ui->lineEdit_4->text(), ui->lineEdit_5->text(), ui->lineEdit_6->text());

    ui->tableWidget_2->setRowCount(combo.count2);
    ui->tableWidget_2->setItem(combo.count2 - 1, 0, new QTableWidgetItem(ui->lineEdit_4->text()));
    ui->tableWidget_2->setItem(combo.count2 - 1, 1, new QTableWidgetItem(ui->lineEdit_5->text()));
    ui->tableWidget_2->setItem(combo.count2 - 1, 2, new QTableWidgetItem(ui->lineEdit_6->text()));

    ui->spinBox_3->setRange(1, combo.count2);
    ui->spinBox->setRange(1, combo.count2);
}

void MainWindow::showAllS1()
{
    ui->tableWidget->setRowCount(0);

    ui->tableWidget->setRowCount(combo.count1);
    for(int i = 0; i < combo.count1; i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(combo.retElS1(i + 1)->val.pole1));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(combo.retElS1(i + 1)->val.pole2));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(combo.retElS1(i + 1)->val.pole3));
    }
}

void MainWindow::showAllS2()
{
    ui->tableWidget_2->setRowCount(0);

    ui->tableWidget_2->setRowCount(combo.count2);
    for(int i = 0; i < combo.count2; i++)
    {
        ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(combo.retElS2(i + 1)->val.pole1));
        ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(combo.retElS2(i + 1)->val.pole2));
        ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(combo.retElS2(i + 1)->val.pole3));
    }
}

void MainWindow::showLinksS1()
{
    if(ui->spinBox->value() == 0) return;
    int k = 0;
    ui->tableWidget->setRowCount(k);

    QVector<Spisok::ret> temp;
    Spisok::ret tempR;
    for(int i = 0; i < combo.count1; i++)
    {
        tempR.str1 = combo.retElS1(i + 1)->val.pole1;
        tempR.str2 = combo.retElS1(i + 1)->val.pole2;
        tempR.str3 = combo.retElS1(i + 1)->val.pole3;
        temp.push_back(tempR);
    }

    for(auto i : combo.retElS2(ui->spinBox->value())->val.a)
    {
        ui->tableWidget->setRowCount(k+1);
        ui->tableWidget->setItem(k, 0, new QTableWidgetItem(i->val.pole1));
        ui->tableWidget->setItem(k, 1, new QTableWidgetItem(i->val.pole2));
        ui->tableWidget->setItem(k, 2, new QTableWidgetItem(i->val.pole3));
        k++;
    }

    for(int i = 0; i < combo.count1; i++)
    {
        combo.retElS1(i + 1)->val.pole1 = temp[i].str1;
        combo.retElS1(i + 1)->val.pole2 = temp[i].str2;
        combo.retElS1(i + 1)->val.pole3 = temp[i].str3;
    }
}

void MainWindow::showLinksS2()
{
    if(ui->spinBox->value() == 0) return;
    int k = 0;
    ui->tableWidget_2->setRowCount(k);

    QVector<Spisok::ret> temp;
    Spisok::ret tempR;
    for(int i = 0; i < combo.count2; i++)
    {
        tempR.str1 = combo.retElS2(i + 1)->val.pole1;
        tempR.str2 = combo.retElS2(i + 1)->val.pole2;
        tempR.str3 = combo.retElS2(i + 1)->val.pole3;
        temp.push_back(tempR);
    }

    for(auto i : combo.retElS1(ui->spinBox->value())->val.a)
    {
        ui->tableWidget_2->setRowCount(k+1);
        ui->tableWidget_2->setItem(k, 0, new QTableWidgetItem(i->val.pole1));
        ui->tableWidget_2->setItem(k, 1, new QTableWidgetItem(i->val.pole2));
        ui->tableWidget_2->setItem(k, 2, new QTableWidgetItem(i->val.pole3));
        k++;
    }

    for(int i = 0; i < combo.count2; i++)
    {
        combo.retElS2(i + 1)->val.pole1 = temp[i].str1;
        combo.retElS2(i + 1)->val.pole2 = temp[i].str2;
        combo.retElS2(i + 1)->val.pole3 = temp[i].str3;
    }
}

void MainWindow::sortS1()
{
    combo.sortMassS1(ui->comboBox->currentIndex());
    ui->tableWidget->setRowCount(combo.count1);

    for(int i = 0; i < combo.count1; i++)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(combo.retElS1(i + 1)->val.pole1));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(combo.retElS1(i + 1)->val.pole2));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(combo.retElS1(i + 1)->val.pole3));
    }
}

void MainWindow::sortS2()
{
    combo.sortMassS2(ui->comboBox_2->currentIndex());
    ui->tableWidget_2->setRowCount(combo.count2);

    for(int i = 0; i < combo.count2; i++)
    {
        ui->tableWidget_2->setItem(i, 0, new QTableWidgetItem(combo.retElS2(i + 1)->val.pole1));
        ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(combo.retElS2(i + 1)->val.pole2));
        ui->tableWidget_2->setItem(i, 2, new QTableWidgetItem(combo.retElS2(i + 1)->val.pole3));
    }
}

void MainWindow::makeLinks()
{
    if(ui->spinBox_2->value() == 0 || ui->spinBox_3->value() == 0) return;
    combo.setLinks(ui->spinBox_2->value(), ui->spinBox_3->value());
}

void MainWindow::saveSB1()
{
    QFile file(QFileDialog::getSaveFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-5(13)\\1", "*.dat"));

    showAllS1();

    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);

        for(int i = 0; i < combo.count1; i++)
        {
            for(int j = 0; j < 3; j++)
                out << ui->tableWidget->item(i, j)->text();
        }
    }
}

void MainWindow::openSB1()
{
    QFile file(QFileDialog::getOpenFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-5(13)", "*.dat"));
    int temp = combo.count1;
    int temptemp = combo.count1;
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);

        while(!in.atEnd())
        {
            ui->tableWidget->setRowCount(temp + 1);
            QString s = nullptr;

            for(int i = 0; i < 3; i++)
            {
                in >> s;
                ui->tableWidget->setItem(temp, i, new QTableWidgetItem(s));
            }
            temp++;
        }
        file.close();
    }

    for(int i = temptemp; i < temp; i++)
        combo.addAvt(ui->tableWidget->item(i, 0)->text(), ui->tableWidget->item(i, 1)->text(), ui->tableWidget->item(i, 2)->text());

    ui->spinBox_4->setRange(1, combo.count1);
    ui->spinBox_2->setRange(1, combo.count1);

}

void MainWindow::saveSB2()
{
    QFile file(QFileDialog::getSaveFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-5(13)\\2", "*.dat"));

    showAllS2();

    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);

        for(int i = 0; i < combo.count2; i++)
        {
            for(int j = 0; j < 3; j++)
                out << ui->tableWidget_2->item(i, j)->text();
        }
    }
}

void MainWindow::openSB2()
{
    QFile file(QFileDialog::getOpenFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-5(13)", "*.dat"));
    int temp = combo.count2;
    int temptemp = combo.count2;
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream in(&file);

        while(!in.atEnd())
        {
            ui->tableWidget_2->setRowCount(temp + 1);
            QString s = nullptr;

            for(int i = 0; i < 3; i++)
            {
                in >> s;
                ui->tableWidget_2->setItem(temp, i, new QTableWidgetItem(s));
            }
            temp++;
        }
        file.close();
    }

    for(int i = temptemp; i < temp; i++)
        combo.addVld(ui->tableWidget_2->item(i, 0)->text(), ui->tableWidget_2->item(i, 1)->text(), ui->tableWidget_2->item(i, 2)->text());

    ui->spinBox->setRange(1, combo.count2);
    ui->spinBox_3->setRange(1, combo.count2);
}

void MainWindow::saveST1()
{
    QFile file(QFileDialog::getSaveFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-7(15)\\L7\\1", "*.txt"));

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        for(int i = 0; i < combo.count1; i++)
        {
            for(int j = 0; j < 3; j++)
                out << ui->tableWidget->item(i, j)->text() << "$";
            out << "\n";
        }
    }
}

void MainWindow::openST1()
{
    QFile file(QFileDialog::getOpenFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-7(15)\\L7", "*.txt"));
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            ui->tableWidget->setRowCount(combo.count1 + 1);
            QString s = in.readLine();

            QString s1 = s.section('$', 0, 0);
            QTableWidgetItem *str1 = new QTableWidgetItem;
            str1->setData(0, s1);
            ui->tableWidget->setItem(combo.count1, 0, str1);

            QString s2 = s.section('$', 1, 1);
            QTableWidgetItem *str2 = new QTableWidgetItem;
            str2->setData(0, s2);
            ui->tableWidget->setItem(combo.count1, 1, str2);

            QString s3 = s.section('$', 2, 2);
            QTableWidgetItem *str3 = new QTableWidgetItem;
            str3->setData(0, s3);
            ui->tableWidget->setItem(combo.count1, 2, str3);
            combo.count1++;
        }
    file.close();

    ui->spinBox_4->setRange(1, combo.count1);
    ui->spinBox_2->setRange(1, combo.count1);
    }

}

void MainWindow::saveST2()
{
    QFile file(QFileDialog::getSaveFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-7(15)\\L7\\2", "*.txt"));

    if(file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);

        for(int i = 0; i < combo.count2; i++)
        {
            for(int j = 0; j < 3; j++)
                out << ui->tableWidget_2->item(i, j)->text() << "$";
            out << "\n";
        }
    }
}

void MainWindow::openST2()
{
    QFile file(QFileDialog::getOpenFileName(nullptr, "Выберите файл", "A:\\progi\\BoP-7(15)\\L7", "*.txt"));
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        while(!in.atEnd())
        {
            ui->tableWidget_2->setRowCount(combo.count2 + 1);
            QString s = in.readLine();

            QString s1 = s.section('$', 0, 0);
            QTableWidgetItem *str1 = new QTableWidgetItem;
            str1->setData(0, s1);
            ui->tableWidget_2->setItem(combo.count2, 0, str1);

            QString s2 = s.section('$', 1, 1);
            QTableWidgetItem *str2 = new QTableWidgetItem;
            str2->setData(0, s2);
            ui->tableWidget_2->setItem(combo.count2, 1, str2);

            QString s3 = s.section('$', 2, 2);
            QTableWidgetItem *str3 = new QTableWidgetItem;
            str3->setData(0, s3);
            ui->tableWidget_2->setItem(combo.count2, 2, str3);
            combo.count2++;
        }
    file.close();

    ui->spinBox->setRange(1, combo.count2);
    ui->spinBox_3->setRange(1, combo.count2);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
