#include "spisok.h"

Spisok::Spisok():Head(nullptr), Tail(nullptr)
{

};

Spisok::~Spisok()
{
    while(Head)
    {
        Tail = Head->Next;
        delete Head;
        Head = Tail;
    }
};

void Spisok::addMuz(QString ispStr, QString nameStr, int posInt, int monthInt, int yearInt)
{
    list *temp = new list;
    temp->Next = nullptr;
    temp->Prev = nullptr;
    temp->isp = ispStr;
    temp->name = nameStr;
    temp->pos = posInt;
    temp->month = monthInt;
    temp->year = yearInt;

    if(Head != nullptr)
    {
        temp->Prev = Tail;
        Tail->Next = temp;
        Tail = temp;
    } else
    {
        temp->Prev = nullptr;
        Head = Tail = temp;
    }

    count++;
}

Spisok::list* Spisok::showEl(int num)
{
    list *temp = new list;
    temp = Head;

    for(int i = 1; i < num; i++)
    {
        temp = temp->Next;
    }

    return temp;
}

void Spisok::deleteEl(int num)
{

    list *temp = Head;

    if(num > count) return;

    if(num == 1)
    {
        Head = Head->Next;
        if(Head)
            Head->Prev = nullptr;
        else
            Tail = nullptr;
        delete temp;
        return;
    }

    if(num == count)
    {
        Tail = Tail->Prev;
        if(Tail)
            Tail->Next = nullptr;
        delete temp;
        return;
    }

    for(int i = 1; i < num; i++)
    {
        temp = temp->Next;
    }

    temp->Prev->Next = temp->Next;
    temp->Next->Prev = temp->Prev;
    count--;
    delete temp;
    return;

}

void Spisok::editEl(int num, int field, QString change)
{
    list *temp = Head;

    if(field == 1)
    {
        for(int i = 1; i < num; i++)
            temp = temp->Next;
        temp->isp = change;
    }

    if(field == 2)
    {
        for(int i = 1; i < num; i++)
            temp = temp->Next;
        temp->name = change;
    }

    if(field == 3)
    {
        for(int i = 1; i < num; i++)
            temp = temp->Next;
        temp->pos = change.toInt();
    }

    if(field == 4)
    {
        for(int i = 1; i < num; i++)
            temp = temp->Next;
        temp->month = change.toInt();
    }

    if(field == 5)
    {
        for(int i = 1; i < num; i++)
            temp = temp->Next;
        temp->year = change.toInt();
    }

}

void Spisok::swapLinks(list *temp1, list *temp2)
{

    QString swapperStr = nullptr;
    int swapperInt = 0;

    swapperStr = temp1->isp;
    temp1->isp = temp2->isp;
    temp2->isp = swapperStr;

    swapperStr = nullptr;
    swapperStr = temp1->name;
    temp1->name = temp2->name;
    temp2->name = swapperStr;

    swapperInt = temp1->pos;
    temp1->pos = temp2->pos;
    temp2->pos = swapperInt;

    swapperInt = 0;
    swapperInt = temp1->month;
    temp1->month = temp2->month;
    temp2->month = swapperInt;

    swapperInt = 0;
    swapperInt = temp1->year;
    temp1->year = temp2->year;
    temp2->year = swapperInt;

}

void Spisok::sortMass(int rule)
{
    list *temp1 = Head;
    list *temp2 = Head->Next;

    if(rule == 0)
    {
        for(int i = 1; i < count; i++)
        {
            for(int j = i; j < count; j++)
            {
                if(temp1->isp > temp2->isp) swapLinks(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 1)
    {
        for(int i = 1; i < count; i++)
        {
            for(int j = i; j < count; j++)
            {
                if(temp1->isp < temp2->isp) swapLinks(temp1, temp2);
                temp2 = temp2->Next;
            }

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 2)
    {
        for(int i = 1; i < count; i++)
        {
            for(int j = i; j < count; j++)
            {
                if(temp1->name > temp2->name) swapLinks(temp1, temp2);
                temp2 = temp2->Next;
            }

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 3)
    {
        for(int i = 1; i < count; i++)
        {
            for(int j = i; j < count; j++)
            {
                if(temp1->name < temp2->name) swapLinks(temp1, temp2);
                temp2 = temp2->Next;
            }

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 4)
    {
        for(int i = 1; i < count; i++)
        {
            for(int j = i; j < count; j++)
            {
                if(temp1->pos > temp2->pos) swapLinks(temp1, temp2);
                temp2 = temp2->Next;
            }

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 5)
    {
        for(int i = 1; i < count; i++)
        {
            for(int j = i; j < count; j++)
            {
                if(temp1->pos < temp2->pos) swapLinks(temp1, temp2);
                temp2 = temp2->Next;
            }

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 6)
    {
        for(int i = 1; i < count; i++)
        {
            for(int j = i; j < count; j++)
            {
                if(temp1->month > temp2->month) swapLinks(temp1, temp2);
                temp2 = temp2->Next;
            }

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 7)
    {
        for(int i = 1; i < count; i++)
        {
            for(int j = i; j < count; j++)
            {
                if(temp1->month < temp2->month) swapLinks(temp1, temp2);
                temp2 = temp2->Next;
            }

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 8)
    {
        for(int i = 1; i < count; i++)
        {
            for(int j = i; j < count; j++)
            {
                if(temp1->year > temp2->year) swapLinks(temp1, temp2);
                temp2 = temp2->Next;
            }

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 9)
    {
        for(int i = 1; i < count; i++)
        {
            for(int j = i; j < count; j++)
            {
                if(temp1->year < temp2->year) swapLinks(temp1, temp2);
                temp2 = temp2->Next;
            }

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

}
