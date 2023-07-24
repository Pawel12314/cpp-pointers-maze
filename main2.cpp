#include "list.h"
#include "window.h"
#include<conio.h>
#include <iostream>
#include <fstream>
#include<windows.h>
void chooseDir(int &movX,int &movY, char dir)
{
    switch(dir)
        {
        case 'w':
            movY=-1;
            movX=0;
            break;
        case 's':
            movY=1;
            movX=0;
            break;
        case 'd':
            movY=0;
            movX=1;
            break;
        case 'a':
            movY=0;
            movX=-1;
            break;
        default:
            movY=0;
            movX=0;
            break;
        }
}
void movePlayer(int &playerX,int &playerY,int movX,int movY,field *pointer,field *Dpointer)
{
        switch (pointer->fieldType)
        {
        case ' ':
            switch (Dpointer->fieldType)
            {
                case 'x':
                playerX+=movX;
                playerY+=movY;
                default:
                break;
            }
            break;
        case '#':
            break;
        case 'B':
            playerX+=movX;
            playerY+=movY;
            break;
        case 'E':
            playerX+=movX;
            playerY+=movY;
            break;
        }
}
void readKey(char &key)
{
    while(true)
        {
            key=getch();
            switch(key)
            {
            case 'w':
                return;
            case 's':
                return;
            case 'a':
                return;
            case 'd':
                return;
            case 'p':
                return;
            }
        }
}
bool readmap( char mapfile[], gamemap* map1, gamemap* keysOnFloor, gamemap* lockedDoors,int &keysonmap,int &doorsonmap)
{
    char type;
    int nr;
    int x=0,y=1;
    fstream in;
    in.open(mapfile);
    if(in.good()==false)
    {
        cout<<"otwarcie pliku z mapa nie powiodlo sie\n";
        return 0;
    }
    keysOnFloor->addField('x',-5,-5,-5);
    lockedDoors->addField('x',-5,-5,-5);
    map1->addField(x,0,-5,-5);
    while(!in.eof())
    {
        type=in.get();
        switch(type)
        {
        case 'x':
            x=-1;
            ++y;
            break;
        default:
            ++x;
        }
    //////////
        if(type=='f')
        {
            break;
        }
        switch(type)
        {
        case 'k':
            in>>nr;
            map1->addField(' ',0,x,y);
            keysOnFloor->addField(type,nr,x,y);
            ++keysonmap;
            break;
        case 'd':
            in>>nr;
            map1->addField(' ',0,x,y);
            lockedDoors->addField(type,nr,x,y);
            ++doorsonmap;
            break;
        default:
            map1->addField(type,0,x,y);
        }
    }
    keysOnFloor->addField('x',-5,-5,-5);
    lockedDoors->addField('x',-5,-5,-5);
    in.close();
    return 1;
}
void pickKey(gamemap* keysOnFloor, int &keysinpocket,field *keypointer)
{
    //cout<<keypointer->val<<endl;
    keysOnFloor->deleteField(keypointer);
    ++keysinpocket;
    *keypointer=keysOnFloor->getField('x');
}
void openTheDoor(gamemap* lockedDoors,int &keysinpocket,field *doorpointer)
{
    lockedDoors->deleteField(doorpointer);
    --keysinpocket;
    *doorpointer=lockedDoors->getField('x');
}
void showmap(int x1, int y1, int playerX,int playerY, field *keypointer, field *doorpointer,gamemap *map1, gamemap *keysOnFloor, gamemap *lockedDoors,int keysinpocket)
{



    x1-=2;
    y1-=2;
    char gameline[200];
    //char *gameline = new char[x1];

        showFrame(1);
        for(int i=0;i<y1;++i)
        {
            map1->getLine(gameline,playerX-x1/2,playerY-(y1/2)+i,x1);
            for(int u=playerX-x1/2;u<playerX+x1/2;++u)
            {
                *keypointer=keysOnFloor->getField(u,playerY-(y1/2)+i);
                if(keypointer->fieldType!='x')
                    //cout<<keypointer->x<<" "<<keypointer->y<<endl;
                    gameline[x1/2+u-playerX]='k';
                else
                {
                    *doorpointer=lockedDoors->getField(u,playerY-(y1/2)+i);
                    if(doorpointer->fieldType!='x')
                        gameline[x1/2+u-playerX]='d';
                }
            }
            if(i==y1/2)gameline[x1/2]='X';
            //cout<<gameline<<endl;
            showFrame(i+2,gameline);
        }
            showFrame(y1+2,gameline,keysinpocket);

        //delete [] gameline;
}
int main()
{
    COORD coord;
    coord.X=0;
    coord.Y=0;
    int keysonmap=0;
    int keysinpocket=0;
    int doorsonmap=0;
    char mapfile[100];
    mapfile[0]='\0';
    gamemap *map1 = new gamemap;
    gamemap *keysOnFloor = new gamemap;
    gamemap *lockedDoors = new gamemap;
    field *playerpointer = new field;
    field *keypointer = new field;
    field *doorpointer = new field;
    int playerX,playerY,movX,movY;
    int screenx,screeny;
    string scX,scY;
    char ifok;
     while(true)
    {
        ifok='\0';
        system("cls");
        cout<<"podaj nazwe pliku z mapa:\n";
        cin>>mapfile;
        if(readmap(mapfile,map1,keysOnFloor,lockedDoors,keysonmap,doorsonmap)==0)
        {
            cout<<"wczytywanie nie powiodlo sie\nsprobowac ponownie? y/n\n";
            bool loop=true;
            while(loop)
            {
                cin>>ifok;
                switch(ifok)
                {
                case 'y':
                    loop=false;
                    break;
                case 'n':
                    goto ENDofGAME;
                default:
                    break;
                }
            }
        }
        else
        {
            screenx=40;
            screeny=screenx/2;
            setScreen(screenx,screeny);
            break;
        }
    }

    *playerpointer=map1->getField('B');
    playerX=playerpointer->x;
    playerY=playerpointer->y;
    char direction;
    system("cls");
    while(true)
    {
        Sleep(100);
        showmap(screenx,screeny,playerX,playerY,keypointer,doorpointer,map1,keysOnFloor,lockedDoors,keysinpocket);
        readKey(direction);
        SetConsoleCursorPosition(GetStdHandle( STD_OUTPUT_HANDLE ) ,coord);
        if(direction=='p')goto ENDofGAME;
        chooseDir(movX,movY,direction);
        if(!(movX==0&&movY==0))
        {
            *playerpointer=map1->getField(playerX+movX,playerY+movY);

            if(playerpointer->fieldType==' ')
                {
                    *keypointer=keysOnFloor->getField(playerX+movX,playerY+movY);
                    *doorpointer=lockedDoors->getField(playerX+movX,playerY+movY);
                    if(keypointer->val!=-5)
                    {
                        pickKey(keysOnFloor,keysinpocket,keypointer);
                    }else
                    if(doorpointer->val!=-5)
                    {
                        *keypointer=keysOnFloor->getField(doorpointer->val);
                        if(keypointer->val==-5)
                        {
                            openTheDoor(lockedDoors,keysinpocket,doorpointer);
                        }
                    }
                }
                else if(playerpointer->fieldType=='E')
                {
                    system("cls");
                    cout<<"\n\n\nWyszedles z labiryntu\n\nWcisnij klawisz 'p' by zakonczyc dzialanie gry\n";
                    while(direction!='p')
                    {
                    readKey(direction);
                    }
                    system("cls");
                    goto ENDofGAME;
                    break;
                }
            *doorpointer=lockedDoors->getField(playerX+movX,playerY+movY);
            movePlayer(playerX,playerY,movX,movY,playerpointer,doorpointer);

        }
    }
    ENDofGAME:

    system("cls");
    map1->delete_List(map1,playerpointer);
    keysOnFloor->delete_List(keysOnFloor,keypointer);
    lockedDoors->delete_List(lockedDoors,doorpointer);
    return 0;
}
