#include <httplib.h>
#include <iostream>
#include <iomanip>
using namespace std;
using namespace httplib;

int main()
{
    char nobat,t,winner;
    bool flag=true;
    int choose,ff=1;
    Client cli("localhost",8080);
    auto aaval=cli.Get("/ghablaval");//retuen that should ask te number of player or no
    string aval=aaval->body;
    if(aval=="ask")
    {
        int pl;
        cout<<"how many players want to play ? (2 or 4) ";
        cin>>pl;
        while((pl!=2) && (pl!=4))
        {
            cout<<"players should be equal to 2 or 4.try again: ";
            cin>>pl;
        }
        for(int i=0;i<pl;i++){cli.Get("/j");}
        cli.Get("/pl");
        for(int i=0;i<pl;i++){cli.Get("/-j");}
    }
    auto res=cli.Get("/start");//conect to server
    bool win=true;
    string b=res->body;
    cout<<b<<endl;
    if(b.substr(0,5)=="sorry")//if number of conection > number of player go end of program
    {
        flag=false;
        win=false;
        ff=0;
    }
    
    while(flag)//ask can we start untill get yes and get his number 1,2,...
    {
        auto wait=cli.Get("/wait");
        string w=wait->body;
        if(w.substr(0,3)=="The"){flag=false;nobat=w[(w.length())-1];}
    }
    if(ff!=0){cout<<"you are player "<<nobat<<endl;}
    
    while(win)//the game start
    {
        auto turn=cli.Get("/turn");//always ask whose turn is it
        string c=turn->body;
        t=c[12];
        if(t==nobat)//if his turn he start
        {  
            auto mahal=cli.Get("/1");
            cout<<mahal->body<<endl;
            cout<<"what do you want to do? you can also see the map( just enter the number)\n";
            cout<<"1-move\n2-place wall\n3-show map\n:";
            cin>>choose;//recive the choice of player
            if(choose==1)//move player
            {
                string jahat,aa;
                cout<<"Up(U) or Down(D) or Right(R) or Left(L) to move or Sorry(S) to return to menu:";
                cin>>jahat;
                if((jahat[0]=='U') || (jahat[0]=='D') || (jahat[0]=='R') || (jahat[0]=='L') || (jahat[0]=='S'))
                {
                    if(jahat[0]=='U')
                    {
                        auto move=cli.Get("/up");
                        aa=move->body; 
                    } 
                    else if(jahat[0]=='D')
                    {
                        auto move=cli.Get("/down");
                        aa=move->body;
                    }
                    else if(jahat[0]=='R')
                    {
                        auto move=cli.Get("/right");
                        aa=move->body;
                    }
                    else if(jahat[0]=='L')
                    {
                        auto move=cli.Get("/left");
                        aa=move->body;
                    }
                    else if(jahat[0]=='S')
                    {
                        continue;
                    }
                    if(aa.substr(0,2)=="fa")//if player cant move
                    {
                        cout<<aa.substr(3,(aa.length()-3))<<endl;
                        continue;
                    }
                    else//if player can move ask that it win or not
                    {
                        cout<<aa.substr(3,(aa.length()-3))<<endl;
                        auto barande=cli.Get("/5");
                        string bb=barande->body;
                        if(bb.substr(0,2)=="tr")//if it win close the program and server
                        {
                            win=false;
                            cout<<bb.substr(3,(bb.length()-3))<<"congratulations!!!!\n";
                            cli.Get("/stop");
                            break;
                        }
                        auto done=cli.Get("/done");//if it does not win next player turn 
                        cout<<done->body<<endl;
                    }
                }
                else
                {
                    cout<<"wrong letter. choose again :)\n";
                    continue;
                }
            }
            else if(choose==2)//place wall
            {
                int i,j;
                string jahat,cc="";
                cout<<"where do you want place the wall?\nenter row to placewall or -1 to return to menu:";
                cin>>i;
                if(i==-1){continue;}
                while((i<0) || (i>10))
                {
                    cout<<"enter row should be equal or greater than 0 and smaller than 11. try again\nrow:";
                    cin>>i;
                }
                cout<<"enter column to placewall or -1 to return to menu:";
                cin>>j;
                if(j==-1){continue;}
                while((j<0) || (j>10))
                {
                    cout<<"enter column should be equal or greater than 0 and smaller than 11. try again\ncolumn:";
                    cin>>j;
                }
                cout<<"Horizontal(H) or Vertical(V) to place wall or Sorry(S) to return to menu:";
                cin>>jahat;
                if((jahat[0]=='H') || (jahat[0]=='V') || (jahat[0]=='S'))
                {
                    for(int x=0;x<i;x++){cli.Get("/i");}
                    for(int y=0;y<j;y++){cli.Get("/j");}
                    if(jahat[0]=='H')
                    {
                        auto wall=cli.Get("/horizontal");
                        cc=wall->body;
                    }
                    else if(jahat[0]=='V')
                    {
                        auto wall=cli.Get("/vertical");
                        cc=wall->body;
                    }
                    else if(jahat[0]=='S')
                    {
                        continue;
                    }
                    for(int x=0;x<i;x++){cli.Get("/-i");}
                    for(int y=0;y<j;y++){cli.Get("/-j");}
                    if(cc.substr(0,2)=="tr"){
                        cout<<cc.substr(3,(cc.length()-3))<<endl;
                        auto don=cli.Get("/done");
                        cout<<don->body<<endl;
                    }
                    else{
                        cout<<cc.substr(3,(cc.length()-3))<<endl;
                        continue;
                    }
                }
                else
                {
                    cout<<"wrong letter. choose again :)\n";
                    continue;
                }
            }
            else if(choose==3)//show map
            {
                string map;
                auto mmap=cli.Get("/4");
                map=mmap->body;
                cout<<map;
                continue;
            }
            else
            {
                cout<<"wrong number. choose again :)\n";
            }
        }
        else//if other player's turn it always ask it lose or not
        {
            auto llose=cli.Get("/barande");
            string lose=llose->body;
            if(lose=="lose")
            {
                cout<<"sorry you lost the game :(\n";
                cli.Get("/stop");
                break;
            }
        }
    }
}