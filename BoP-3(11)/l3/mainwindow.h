#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QProcess>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    int p = 0;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void addTrack();
    void deleteTrack();
    void editYear(QString);
    void editMonth(QString);
    void editItem(QTableWidgetItem*);
    void DBOpen();
    void DBSave();
    void DBEdit();
    void showError();
    void report();
    void DBshow();
    void line6edited(QString);
    int returncountDB();
    void setspin2();
};

#endif // MAINWINDOW_H
