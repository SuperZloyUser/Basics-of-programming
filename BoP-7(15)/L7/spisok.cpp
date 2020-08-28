#include "spisok.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

Spisok::Spisok():Head1(nullptr), Tail1(nullptr), Head2(nullptr), Tail2(nullptr)
{

};

Spisok::~Spisok()
{
    while(Head1)
    {
        Tail1 = Head1->Next;
        delete Head1;
        Head1 = Tail1;
    }

    while(Head2)
    {
        Tail2 = Head2->Next;
        delete Head1;
        Head2 = Tail2;
    }
};

Spisok::list* Spisok::retElS1(int num)
{
    list *temp = new list;
    temp = Head1;

    for(int i = 1; i < num; i++)
    {
        temp = temp->Next;
    }

    return temp;
}

Spisok::list* Spisok::retElS2(int num)
{
    list *temp = new list;
    temp = Head2;

    for(int i = 1; i < num; i++)
    {
        temp = temp->Next;
    }

    return temp;
}


void Spisok::addAvt(QString pole1Str, QString pole2Str, QString pole3Str)
{
    list *temp = new list;
    temp->Next = nullptr;
    temp->Prev = nullptr;
    temp->val.pole1 = pole1Str;
    temp->val.pole2 = pole2Str;
    temp->val.pole3 = pole3Str;

    if(Head1 != nullptr)
    {
        temp->Prev = Tail1;
        Tail1->Next = temp;
        Tail1 = temp;
    } else
    {
        temp->Prev = nullptr;
        Head1 = Tail1 = temp;
    }

    count1++;
}

void Spisok::addVld(QString pole1Str, QString pole2Str, QString pole3Str)
{
    list *temp = new list;
    temp->Next = nullptr;
    temp->Prev = nullptr;
    temp->val.pole1 = pole1Str;
    temp->val.pole2 = pole2Str;
    temp->val.pole3 = pole3Str;

    if(Head2 != nullptr)
    {
        temp->Prev = Tail2;
        Tail2->Next = temp;
        Tail2 = temp;
    } else
    {
        temp->Prev = nullptr;
        Head2 = Tail2 = temp;
    }

    count2++;
}

void Spisok::setLinks(int first, int second)
{

    list *temp1 = retElS1(first);
    list *temp2 = retElS2(second);

    /*for(auto i : temp1->val.a)
       if(i == second) return;

    temp1->val.a.push_back(second);
    temp2->val.a.push_back(first);*/

    for(auto i : temp1->val.a)
    {
        if(i->val.pole1 == temp2->val.pole1 && i->val.pole2 == temp2->val.pole2 && i->val.pole3 == temp2->val.pole3) return;
    }

    temp1->val.a.push_back(temp2);
    temp2->val.a.push_back(temp1);
}

QVector<Spisok::ret> Spisok::retListForLinks(int num)
{

    list *now = Head2;

    QVector<ret> values;

    int i = 1;

    while (now != nullptr)
    {
        if(i == num)
        {
            for (auto j : now->val.a)
            {
                ret temp;
                temp.str1 = j->val.pole1;
                temp.str2 = j->val.pole2;
                temp.str3 = j->val.pole3;
                values.push_back(temp);
            }
            break;
        }
        now = now->Next;
        i++;
    }

    return values;
}

void Spisok::swapEl(list *temp1, list *temp2)
{
    ret temp;
    temp.str1 = temp1->val.pole1;
    temp.str2 = temp1->val.pole2;
    temp.str3 = temp1->val.pole3;

    temp1->val.pole1 = temp2->val.pole1;
    temp1->val.pole2 = temp2->val.pole2;
    temp1->val.pole3 = temp2->val.pole3;

    temp2->val.pole1 = temp.str1;
    temp2->val.pole2 = temp.str2;
    temp2->val.pole3 = temp.str3;

    std::swap(temp1->val.a, temp2->val.a);
}

void Spisok::sortMassS1(int rule)
{
    list *temp1 = Head1;
    list *temp2 = Head1->Next;

    if(rule == 0)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole1 > temp2->val.pole1) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 1)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole1 < temp2->val.pole1) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 2)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole2 > temp2->val.pole2) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 3)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole2 < temp2->val.pole2) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 4)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole3 > temp2->val.pole3) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 5)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole3 < temp2->val.pole3) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }
}

void Spisok::sortMassS2(int rule)
{
    list *temp1 = Head2;
    list *temp2 = Head2->Next;

    if(rule == 0)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole1 > temp2->val.pole1) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 1)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole1 < temp2->val.pole1) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 2)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole2 > temp2->val.pole2) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 3)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole2 < temp2->val.pole2) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 4)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole3 > temp2->val.pole3) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

    if(rule == 5)
    {
        for(int i = 1; i < count1; i++)
        {
            for(int j = i; j < count1; j++)
            {
                if(temp1->val.pole3 < temp2->val.pole3) swapEl(temp1, temp2);
                temp2 = temp2->Next;
            }
            if(i == count1 - 1) continue;

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }
}

/*
void Spisok::addMuz(QString pole1Str, QString pole2Str, int pole3Int)
{
    list *temp = new list;
    temp->Next = nullptr;
    temp->Prev = nullptr;
    temp->val.pole1 = pole1Str;
    temp->val.pole2 = pole2Str;
    temp->val.pole3 = pole3Int;

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
        temp->val.pole1 = change;
    }

    if(field == 2)
    {
        for(int i = 1; i < num; i++)
            temp = temp->Next;
        temp->val.pole2 = change;
    }

    if(field == 3)
    {
        for(int i = 1; i < num; i++)
            temp = temp->Next;
        temp->val.pole3 = change.toInt();
    }

    if(field == 4)
    {
        for(int i = 1; i < num; i++)
            temp = temp->Next;
        temp->val.month = change.toInt();
    }

    if(field == 5)
    {
        for(int i = 1; i < num; i++)
            temp = temp->Next;
        temp->val.year = change.toInt();
    }

}

void Spisok::swapLinks(list *temp1, list *temp2)
{

    QString swapperStr = nullptr;
    int swapperInt = 0;

    swapperStr = temp1->val.pole1;
    temp1->val.pole1 = temp2->val.pole1;
    temp2->val.pole1 = swapperStr;

    swapperStr = nullptr;
    swapperStr = temp1->val.pole2;
    temp1->val.pole2 = temp2->val.pole2;
    temp2->val.pole2 = swapperStr;

    swapperInt = temp1->val.pole3;
    temp1->val.pole3 = temp2->val.pole3;
    temp2->val.pole3 = swapperInt;

    swapperInt = 0;
    swapperInt = temp1->val.month;
    temp1->val.month = temp2->val.month;
    temp2->val.month = swapperInt;

    swapperInt = 0;
    swapperInt = temp1->val.year;
    temp1->val.year = temp2->val.year;
    temp2->val.year = swapperInt;

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
                if(temp1->val.pole1 > temp2->val.pole1) swapLinks(temp1, temp2);
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
                if(temp1->val.pole1 < temp2->val.pole1) swapLinks(temp1, temp2);
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
                if(temp1->val.pole2 > temp2->val.pole2) swapLinks(temp1, temp2);
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
                if(temp1->val.pole2 < temp2->val.pole2) swapLinks(temp1, temp2);
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
                if(temp1->val.pole3 > temp2->val.pole3) swapLinks(temp1, temp2);
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
                if(temp1->val.pole3 < temp2->val.pole3) swapLinks(temp1, temp2);
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
                if(temp1->val.month > temp2->val.month) swapLinks(temp1, temp2);
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
                if(temp1->val.month < temp2->val.month) swapLinks(temp1, temp2);
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
                if(temp1->val.year > temp2->val.year) swapLinks(temp1, temp2);
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
                if(temp1->val.year < temp2->val.year) swapLinks(temp1, temp2);
                temp2 = temp2->Next;
            }

            temp1 = temp1->Next;
            temp2 = temp1->Next;
        }
    }

}*/
