#include <httplib.h>
#include <iostream>
#include <iomanip>
using namespace std;
using namespace httplib;

int main()
{
    char nobat,t,winner;
    bool flag=true;//recognize when game start
    int choose;
    Client cli("localhost",8080);
    auto res=cli.Get("/start");
    string b=res->body;
    cout<<b<<endl;
    while(flag)
    {
        auto wait=cli.Get("/wait");
        string w=wait->body;
        if(w.substr(0,3)=="The"){flag=false;nobat=w[(w.length())-1];}
    }
    cout<<"you are player "<<nobat<<endl;
    bool win=true;
    while(win)
    {
        auto turn=cli.Get("/turn");
        string c=turn->body;
        t=c[12];
        if(t==nobat)
        {  
            auto mahal=cli.Get("/1");
            cout<<mahal->body<<endl;
            cout<<"what do you want to do?( just enter the number)\n";
            cout<<"1-move\n2-place wall\n3-show map\n:";
            cin>>choose;
            if(choose==1)
            {
                string jahat;
                cout<<"Up(U) or Down(D) or Right(R) or Left(L):";
                cin>>jahat;
                string aa;
                if(jahat[0]=='U'){
                    auto move=cli.Get("/up");
                    aa=move->body; 
                    } 
                else if(jahat[0]=='D'){
                    auto move=cli.Get("/down");
                    aa=move->body;
                    }
                else if(jahat[0]=='R'){
                    auto move=cli.Get("/right");
                    aa=move->body;
                    }
                else if(jahat[0]=='L'){
                    auto move=cli.Get("/left");
                    aa=move->body;
                    }
                if(aa.substr(0,2)=="fa")
                {
                    cout<<aa.substr(3,(aa.length()-3))<<endl;
                    continue;
                }
                else
                {
                    cout<<aa.substr(3,(aa.length()-3))<<endl;
                    auto barande=cli.Get("/5");
                    string bb=barande->body;
                    if(bb.substr(0,2)=="tr")
                    {
                        win=false;
                        cout<<bb.substr(3,(bb.length()-3))<<"congratulations!!!!\n";
                    }
                    auto done=cli.Get("/done");
                    cout<<done->body<<endl;
                }
            }
            else if(choose==2)
            {
                int i,j;
                string jahat,cc="";
                cout<<"where do you want place the wall?\ni:";
                cin>>i;
                while((i<0) || (i>10))
                {
                    cout<<"i should be equal or greater than 0 and smaller than 11. try again\ni:";
                    cin>>i;
                }
                cout<<"j:";
                cin>>j;
                while((j<0) || (j>10))
                {
                    cout<<"j should be equal or greater than 0 and smaller than 11. try again\nj:";
                    cin>>j;
                }
                cout<<"Horizontal(H) or Vertical(V):";
                cin>>jahat;
                for(int x=0;x<i;x++){cli.Get("/i");}
                for(int y=0;y<j;y++){cli.Get("/j");}
                if(jahat[0]=='H'){
                    auto wall=cli.Get("/horizontal");
                    cc=wall->body;
                }
                else if(jahat[0]=='V'){
                    auto wall=cli.Get("/vertical");
                    cc=wall->body;
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
            else if(choose==3)
            {
                string map;
                auto mmap=cli.Get("/4");
                map=mmap->body;
                cout<<map;
                continue;
            }
        }
    }
}