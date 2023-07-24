#include <iostream>
#include<cstdio>
#include<cstdlib>
#include<windows.h>
using namespace std;

struct field
{
    char fieldType;
    int val;
    int x;
    int y;
    field *next;
    field();
};
field::field()
{
    next = 0;
}
struct gamemap
{
    field *first;
    field *last;
    int height;
    void addField(char type, int nr,int fieldX,int fieldY);
    void getLine(char line[],int x, int y, int lenght);
    field getField(int,int);
    field getField(char Type);
    field getField(int value);
    void deleteField(field*);
    void delete_List(gamemap* listtoDel, field* Pointer);

    gamemap();
};
gamemap::gamemap()
{
    first = 0;
    last = 0;
    height = 0;
}
void gamemap::addField(char type, int nr=0, int fieldX=-5,int fieldY=-5)
{
    field *newField = new field;
    newField -> fieldType = type;
    newField -> val = nr;
    newField -> x = fieldX;
    newField -> y = fieldY;
    if(first == 0)
    {
        first = newField;
        last = newField;
    }
    else
    {
        last -> next = newField;
        last = last -> next;
        newField -> next = 0;
        if(newField -> fieldType == 'x')++height;
    }
}

void gamemap::getLine(char line[],int x, int y, int lenght)
{

    int posX=x;
    int posY=y;

    if(y<1||y>height)
    for(int i=0;i<lenght;++i)
    {
        line[i]=' ';

    }
    else
    {
        int i=0;
        while(posX<1)
        {
            line[i++]=' ';
            ++posX;
        }
        field *temp = new field;

        *temp = *first;
        *temp = getField(posX,posY);
        while(temp->fieldType!='x')
        {
            ++posX;
            if(temp->fieldType==' ')
                line[i++]=' ';
            else
            if(temp->fieldType=='#')
                line[i++]='#';
            else
            if(temp->fieldType=='k')
                line[i++]='k';
            else
            if(temp->fieldType=='d')
                line[i++]='d';
            else
            if(temp->fieldType=='B')
                line[i++]='B';
            else
            if(temp->fieldType=='E')
                line[i++]='E';
                if(i>=lenght)break;
            temp=temp->next;
        }
        while(i<lenght)
        {
            line[i++]=' ';
        }
    }
    line[lenght]='\0';
}


field gamemap::getField(int posX,int posY)
{
    field *temp = first;
    while(temp->next)
    {
        if(temp->y==posY)
            if(temp->x==posX)
                break;
        temp=temp->next;
    }
    return *temp;
}
field gamemap::getField(char Type)
{
    field *temp = first;
    if(Type=='F')
        return *temp;
    while(temp->next)
    {
        if(temp->fieldType==Type)
        {
            break;
        }
        temp=temp->next;
    }
    return *temp;
}
field gamemap::getField(int value)
{
    field *temp = first;
    while(temp->next)
    {
        if(temp->val==value)
            break;
        temp=temp->next;
    }
    return *temp;
}

void gamemap::deleteField(field *temp)
{
    field *temp2= new field;

    *temp2= *temp;
    temp= first;
    if(temp2->val==first->val)
    {
        if(!first->next)
        {
            delete temp;
            return;
        }
        first=temp->next;
        delete temp2;
        return;
    }

    while(temp->next)
    {
        if(temp->next->val==temp2->val)
        {
            temp->next=temp2->next;
            delete temp2;
            break;
        }
        temp=temp->next;
    }
}
void gamemap::delete_List(gamemap* listtoDel, field* Pointer)
{
    do
    {
        *Pointer=listtoDel->getField('F');
        listtoDel->deleteField(Pointer);

    }while(Pointer->next);

    delete Pointer;
    delete (listtoDel);
}
