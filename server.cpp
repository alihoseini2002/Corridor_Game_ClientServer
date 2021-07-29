#include <httplib.h>
#include <iostream>
#include <game.h>
using namespace std;
using namespace httplib;
bool aval(int f=0)
{
    static bool a=false;
    if(f==1){a=true;}
    return a;
}

int pl(int a)
{
    static int c=0;
    c+=a;
    return c;
}

int addi(int a)
{
    static int i=0;
    i+=a;
    return i;
}

int addj(int a)
{
    static int j=0;
    j+=a;
    return j;
}

int add(int a)
{
    static int t=0;
    t+=a;
    return t;
}

int numplayer()//give num to player
{
    static int g=0;
    g++;
    return g;
}

int turn(int a,int b)
{
    static int c=1;
    c+=a;
    if(c>b){c=1;}
    return c;
}

string gaming(int a,string jahat="")
{
    string f="";
    int nobat=turn(0,pl(0));
    static Map game(pl(0));
    if(a==1){f=game.whereismohre(nobat);}
    else if(a==2){f=game.move(nobat,jahat);}
    else if(a==3){f=game.placewall(addi(0),addj(0),jahat);}
    else if(a==4){f=game.showmap();}
    else if(a==5){f=game.iswin();}
    return f;
}

int main()
{
    Server svr;

    svr.Get("/ghablaval",[](const Request &req, Response &res){
        if(aval()){res.set_content("dont","text/plain");}
        else{res.set_content("ask","text/plain");}
    });

    svr.Get("/pl",[](const Request &req, Response &res){
        pl(addj(0));
        aval(1);
    });

    svr.Get("/start", [](const Request &req, Response &res) {
        int player=add(1);
        if(player<pl(0))
        {
            char l=(pl(0)-player)+48;
            string s="please wait for ";
            s+=l;
            s+=" other players";
            res.set_content(s, "text/plain");
        }
        else if(player==pl(0)){res.set_content("The game begins :)", "text/plain");}
        else{res.set_content("sorry you can't play :(", "text/plain");}
    });

    svr.Get("/wait", [](const Request &req, Response &res) {
        int player=add(0);
        if(player==pl(0))
        {
            string s="The game begins :) and you are player ";
            char r=(numplayer())+48;
            s=s+r;
            res.set_content(s, "text/plain");
        }
        else{res.set_content("true", "text/plain");}
    });

    svr.Get("/turn", [](const Request &req, Response &res) {
        char nobat=turn(0,pl(0))+48;
        string s="it's player ";
        s+=nobat;
        s+=" turn.";
        res.set_content(s, "text/plain");
    });

    svr.Get("/1", [](const Request &req, Response &res) {
        string f=gaming(1);
        res.set_content(f, "text/plain");
    });

    svr.Get("/up", [](const Request &req, Response &res) {
        string f=gaming(2,"up");
        res.set_content(f, "text/plain");
    });

    svr.Get("/down", [](const Request &req, Response &res) {
        string f=gaming(2,"down");
        res.set_content(f, "text/plain");
    });

    svr.Get("/right", [](const Request &req, Response &res) {
        string f=gaming(2,"right");
        res.set_content(f, "text/plain");
    });

    svr.Get("/left", [](const Request &req, Response &res) {
        string f=gaming(2,"left");
        res.set_content(f, "text/plain");
    });
   
    svr.Get("/4", [](const Request &req, Response &res) {
        string f=gaming(4);
        res.set_content(f, "text/plain");
    });
 
    svr.Get("/horizontal", [](const Request &req, Response &res) {
        string f=gaming(3,"horizontal");
        res.set_content(f, "text/plain");
    });
    
    svr.Get("/vertical", [](const Request &req, Response &res) {
        string f=gaming(3,"vertical");
        res.set_content(f, "text/plain");
    });
   
    svr.Get("/5", [](const Request &req, Response &res) {
        string f=gaming(5);
        res.set_content(f, "text/plain");
    });
   
    svr.Get("/done", [](const Request &req, Response &res) {
        turn(1,pl(0));
        res.set_content("next round", "text/plain");
    });

    svr.Get("/i", [](const Request &req, Response &res) {
        addi(1);
    });

    svr.Get("/j", [](const Request &req, Response &res) {
        addj(1);
    });

    svr.Get("/-i", [](const Request &req, Response &res) {
        addi(-1);
    });

    svr.Get("/-j", [](const Request &req, Response &res) {
        addj(-1);
    });

    svr.listen("localhost",8080);
}