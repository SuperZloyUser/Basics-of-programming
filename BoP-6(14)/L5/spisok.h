#ifndef SPISOK_H
#define SPISOK_H

#include <QString>
#include <QVector>

class Spisok
{
private:
    struct list;

    struct val
    {
        QString pole1;
        QString pole2;
        QString pole3;
        QVector<list*> a;
    };

    struct list
    {
        val val;
        list *Prev, *Next;
    };

    list *Head1, *Tail1, *Head2, *Tail2;

public:
    struct ret
    {
        QString str1;
        QString str2;
        QString str3;
    };

public:
    Spisok();
    ~Spisok();    
    int count1 = 0;
    int count2 = 0;
    void addAvt(QString pole1Str, QString pole2Str, QString pole3Str);
    void addVld(QString pole1Str, QString pole2Str, QString pole3Str);
    void sortS1(int rule);
    void sortS2(int rule);
    void setLinks(int first, int second);
    list* retElS1(int num);
    list* retElS2(int num);
    void sortMassS1(int rule);
    void sortMassS2(int rule);
    void swapEl(list* temp1, list* temp2);
    QVector<ret> retListForLinks(int num);
};

#endif // SPISOK_H
