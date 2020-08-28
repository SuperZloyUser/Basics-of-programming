#ifndef SPISOK_H
#define SPISOK_H

#include <QString>

class Spisok
{
private:
    struct list
    {
        QString isp;
        QString name;
        int pos;
        int month;
        int year;
        list *Prev, *Next;
    };

    list *Head, *Tail;


public:
    Spisok();
    ~Spisok();
    int count = 0;
    void addMuz(QString ispStr, QString nameStr, int posInt, int monthInt, int yearInt);
    list* showEl(int num);
    void deleteEl(int num);
    void editEl(int num, int field, QString change);
    void swapLinks(list *temp1, list *temp2);
    void sortMass(int rule);
};

#endif // SPISOK_H
