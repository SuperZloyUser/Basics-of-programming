#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QProcess>
#include "spisok.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Spisok combo;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void AddAvt();
    void AddVld();
    void showAllS1();
    void showAllS2();
    void showLinksS1();
    void showLinksS2();
    void makeLinks();
    void sortS1();
    void sortS2();
    void saveSB1();
    void saveSB2();
    void openSB1();
    void openSB2();
    void saveST1();
    void saveST2();
    void openST1();
    void openST2();
};

#endif // MAINWINDOW_H
