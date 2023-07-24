#include<iostream>
#include<cstdio>

using namespace std;
string frame;
string keyinf1;
string keyinf2_1;
string keyinf2_2;
string keyinf2_5;
string keyinf3;
string framebottom;
string frameup;
string frameside;
int sizex,sizey;
bool setScreen(int x,int y)
{
    sizex = x;
    sizey = y;
    if(x<5||y<5)
    {
        cout<<"zbyt maly rozmiar okna\n";
        return 0;
    }

    keyinf1+=176;
    keyinf1+=177;
    keyinf1+=178;
    keyinf1+=" W kieszeni masz ";

    keyinf2_1=" klucz ";
    keyinf2_2=" klucze ";
    keyinf2_5=" kluczy ";

    keyinf3+=178;
    keyinf3+=177;
    keyinf3+=176;
    keyinf3+="    ";
    //s=201;
    cout<<frame<<endl;
    frame+=201;
    frameup+=201;
    for(int i=0;i<x-2;i++)
    {
        frame+=205;
        frameup+=205;
    }
    frame+=187;
    frameup+=187;
    frame+="\n";
    frameside=186;
    for(int i=0;i<y-2;i++)
    {
        frame+=186;
        for(int u=0;u<x-2;u++)
        {
            frame+=" ";
        }
        frame+=186;
        frame+="\n";
    }
    frame+=200;
    framebottom+=200;
    for(int i=0;i<x-2;i++)
    {
        frame+=205;
        framebottom+=205;
    }
    framebottom+=188;
    frame+=188;
    return 1;
}
void showFrame(int y,char line[]=0,int keys=0)
{
    if(y==1)
        cout<<frameup<<endl;
    else if(y==sizey)
        {
            cout<<framebottom<<endl;
            cout<<keyinf1<<keys;
            switch (keys)
            {
            case 1:
                cout<<keyinf2_1;
                break;
            case 2:
                cout<<keyinf2_2;
                break;
            case 3:
                cout<<keyinf2_2;
                break;
            case 4:
                cout<<keyinf2_2;
                break;
            default:
                cout<<keyinf2_5;
                break;

            }
            cout<<keyinf3<<endl;
        }
    else
    {
        cout<<frameside<<line<<frameside<<endl;
    }
}
