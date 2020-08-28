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

    int p = 0;
    Spisok spisok;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void addTrack();
    void deleteTrack();
    void editTrack();
    void editLine6(QString);
    void editCombo();
    void editIsp(QString);
    void editName(QString);
    void editYear(QString);
    void editMonth(QString);
    void editItem(QTableWidgetItem*);
    void binOpen();
    void binSave();
    void textOpen();
    void textSave();
    void sortByUser();
    void showError();
    void report();

};

#endif // MAINWINDOW_H
