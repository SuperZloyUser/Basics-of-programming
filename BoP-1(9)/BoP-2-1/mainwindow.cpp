#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void main228(char* g);

void MainWindow::on_pushButton_clicked()
{
    auto g = QFileDialog::getOpenFileName(nullptr, "Open Dialog", "A:\\progi\\BoP-1(9)", "*.*");

    if (QFile::exists(g))
    {
        main2(g.toLocal8Bit().data());
    }
}

int schitraz(char* gf)
{
    int x = 0;
    ifstream file(gf);
    char simbol;

    while (1)
    {
        simbol = file.get();
        if (file.eof() == 1) break;
        if(simbol == ' ' || simbol == '\n') x++;
    }

    file.close();

    x++;

    return x;
}


char* vvodstr()
{
    char *sf = new char[1];
    sf[0] = '\0';
    char simbol;

    while (1)
    {
        simbol = getch();
        printf("%c", simbol);

        if (simbol == 13)
            break;
        if (simbol == 8)
        {
            sf[strlen(sf)-1] = '\0';
            printf(" ");
            printf("%c", 8);
            continue;
        }

        char *news = new char[strlen(sf) + 2];

        strcpy(news, sf);
        news[strlen(sf)] = simbol;
        news[strlen(sf) + 1] = '\0';

        char* del = sf;
        delete[] del;

        sf = news;
    }

    return sf;
}

char* vvodstrf(char *gf, int k)
{
    ifstream file(gf);

    int n = 0;
    char *sf = new char[1];
    sf[0] = '\0';
    char simbol;

    while (1)
    {
        simbol = file.get();

        if ((simbol == ' ' || file.eof() == 1 || simbol == '\n') && k == n) break;
        if (simbol == ' ' || simbol == '\n')
        {
            n++;
            memset(sf, '\0', strlen(sf));
            continue;
        }

        if (simbol < 65 || simbol > 123) continue;

        char *news = new char[strlen(sf) + 2];

        strcpy(news, sf);
        news[strlen(sf)] = simbol;
        news[strlen(sf) + 1] = '\0';

        char* del = sf;
        delete[] del;

        sf = news;
    }

    file.close();

    return sf;
}

void readfile(int razf, char* gf, char** abf)
{
    for (int i = 0; i < razf; i++)
    {
        char* del = vvodstrf(gf, i);
        strcpy(abf[i], del);
        delete[] del;
    }
}

void vidmem(int razf, char* gf, char** abf)
{
    int i;

    for (i = 0; i < razf; i++)
    {
        char* del = vvodstrf(gf, i);
        abf[i] = new char[strlen(del) + 1];
        delete[] del;
    }

    return;
}

void MainWindow::obrabotka(int razf, char** abf)
{
    int i;
    QString s;

    for (i = 0; i < razf - 1; i++)
    {
        if (abf[i][0] == '\0') continue;
        s = s + "\"" + abf[i] + "\", "; //printf("\"%s\",", abf[i]);
    }
    s = s + "\"" + abf[razf-1] + "\""; //printf("\"%s\"\n", abf[razf-1]);

    ui->textBrowser->setText(s);

    QFile f("output.txt");

    if(f.open(QIODevice::WriteOnly | QIODevice::Text))
    {

        QTextStream writeStream(&f);

        writeStream << s;
    }

    return;
}

void MainWindow::main2(char* g) {
    int raz = 0;

    FILE *check = fopen(g, "r");

    while(check == NULL)
    {
        printf("\nВведите верный путь!\n");
        delete[] g;
        g = vvodstr();

        check = fopen(g, "r");
    }

    printf("\n\n");
    fclose(check);

    raz = schitraz(g);

    char **ab;
    ab = new char*[raz];

    vidmem(raz, g, ab);

    readfile(raz, g, ab);

    obrabotka(raz, ab);

    for (int i = 0; i < raz; i++)
        delete[] ab[i];
    delete[] ab;
    //delete[] g;

}
