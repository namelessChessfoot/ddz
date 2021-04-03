#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include"ddz.h"
using namespace std;
int main()
{
    string help,rubbish;
    int i;
    Game mygame(1,3,100);
    i=mygame.LetsPlay(0);
    while(mygame.canPlay())
    {
        cout<<"是否继续游戏？（y or n）"<<endl;
        cin>>help;
        getline(cin,rubbish);
        for(char &c:help) c=toupper(c);
        while(help!="Y"&&help!="N")
        {
            cout<<"是否继续游戏？（y or n）"<<endl;
            cin>>help;
            getline(cin,rubbish);
            for(char &c:help) c=toupper(c);
        }
        if(help=="N") break;
        mygame.LetsPlay(i);
    }
    system("pause");
    return 0;
}
