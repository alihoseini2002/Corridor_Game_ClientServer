#include <iomanip>
#include <iostream>
using namespace std;

class Map
{
    public:
        Map(int);
        ~Map();
        string whereismohre(int);
        string move(int,string);
        string showmap();
        string placewall(int,int,string);
        string iswin();
    private:
        int** m;
        int size;
        int player;
        int** mohre;
};

Map::Map(int num)
{
    size=11;
    player=num;
    m=new int* [size];//start making map
    for(int i=0;i<size;i++){m[i]=new int [size];}
    for(int i=0;i<size;i++)
    {
        for(int j=0;j<size;j++)
        {
            m[i][j]=0;
        }
    }//end making map

    mohre=new int* [player];//place players
    for(int i=0;i<player;i++){mohre[i]=new int [2];}
    m[0][0]=1;
    mohre[0][0]=0;
    mohre[0][1]=0;
    m[size-1][size-1]=2;
    mohre[1][0]=size-1;
    mohre[1][1]=size-1;
    if(player==4)
    {
        m[size-1][0]=3;
        mohre[2][0]=size-1;
        mohre[2][1]=0;
        m[0][size-1]=4;
        mohre[3][0]=0;
        mohre[3][1]=size-1;
    }
}

Map::~Map()
{
    delete [] m;
    delete [] mohre;
}

string Map::iswin()
{
    string s="fa";
    for(int i=0;i<player;i++)
    {
        if((mohre[i][0]==5) && (mohre[i][1]==5))
        {
            s="tr player ";
            char t=i+49;
            s+=t;
            s+=" win the game!";
            return s;
        }
    }
    return s;
}

string Map::whereismohre(int i)
{
    string s="player ";
    char t=i+48;
    s+=t; 
    s+=" is in ( ";
    if(mohre[i-1][0]<10)
    {
        t=mohre[i-1][0]+48;
        s+=t;
    }
    else{s+="10";}
    s+=" , ";
    if(mohre[i-1][1]<10)
    {
        t=mohre[i-1][1]+48;
        s+=t;
    }
    else{s+="10";}
    s+=" )";
    return s;
}

string Map::move(int i,string jahat)
{
    string s="";
    if(i<=player)
    {
        if(jahat=="up")
        {
            if(((mohre[i-1][0])-1)>=0)
            {
                if(m[(mohre[i-1][0])-1][mohre[i-1][1]]==0)
                {
                    m[mohre[i-1][0]][mohre[i-1][1]]=0;
                    m[(mohre[i-1][0])-1][mohre[i-1][1]]=i;
                    mohre[i-1][0]=(mohre[i-1][0])-1;
                    s="tr done";
                    return s;
                }
                else
                {
                    s="fa sorry you can't go up beacause it isn't empty";
                    return s;
                }
            }
            else
            {
                s="fa sorry you can't go up.";
                return s;
            }
        }
        else if(jahat=="down")
        {
            if(((mohre[i-1][0])+1)<size)
            {
                if(m[(mohre[i-1][0])+1][mohre[i-1][1]]==0)
                {
                    m[mohre[i-1][0]][mohre[i-1][1]]=0;
                    m[(mohre[i-1][0])+1][mohre[i-1][1]]=i;
                    mohre[i-1][0]=(mohre[i-1][0])+1;
                    s="tr done";
                    return s;
                }
                else
                {
                    s="fa sorry you can't go down beacause it isn't empty";
                    return s;
                }
            }
            else
            {
                s="fa sorry you can't go down";
                return s;
            }
        }
        else if(jahat=="left")
        {
            if(((mohre[i-1][1])-1)>=0)
            {
                if(m[mohre[i-1][0]][(mohre[i-1][1])-1]==0)
                {
                    m[mohre[i-1][0]][mohre[i-1][1]]=0;
                    m[mohre[i-1][0]][(mohre[i-1][1])-1]=i;
                    mohre[i-1][1]=(mohre[i-1][1])-1;
                    s="tr done";
                    return s;
                }
                else
                {
                    s="fa sorry you can't go left beacause it isn't empty";
                    return s;
                }
            }
            else
            {
                s="fa sorry you can't go left";
                return s;
            }
        }
        else if(jahat=="right")
        {
            if(((mohre[i-1][1])+1)<size)
            {
                if(m[mohre[i-1][0]][(mohre[i-1][1])+1]==0)
                {
                    m[mohre[i-1][0]][mohre[i-1][1]]=0;
                    m[mohre[i-1][0]][(mohre[i-1][1])+1]=i;
                    mohre[i-1][1]=(mohre[i-1][1])+1;
                    s="tr done";
                    return s;
                }
                else
                {
                    s="fa sorry you can't go right beacause it isn't empty";
                    return s;
                }
            }
            else
            {
                s="fa sorry player you can't go right";
                return s;
            }
        }
    }
    return s;
}

string Map::showmap()
{
    string s="";
    s+="    0  1  2  3  4  5  6  7  8  9  10\n";
    s+="   ---------------------------------\n";
    for(int i=0;i<size;i++)
    {
        if(i<10)
        {
            char tt=i+48;
            s+=tt;
            s+="  |";
        }
        else{s+="10 |";}
        for(int j=0;j<size;j++)
        {
            char t=m[i][j]+48;
            if(i==5 && j==5)
            {
                t='*';
            }
            s+=t;
            s+="  ";
        }
        s+='\n';
    }
    return s;
}

string Map::placewall(int i,int j,string jahat)
{
    string s="";
    if(i<size && j<size)
    {
        if(!((i==5) && (j==5)))
        {
            if(jahat=="horizontal")
            {
                if(!(((i==5) && (j==4)) || ((i==5) && (j==6))))
                    if(((j-1)>=0) && ((j+1)<size))
                    {
                        if((m[i][j-1]==0) && (m[i][j]==0) && (m[i][j+1]==0))
                        {
                            m[i][j-1]=-1;
                            m[i][j]=-1;
                            m[i][j+1]=-1;
                            s="tr done";
                        }
                        else
                        {
                            s="fa The horizontal wall can't be placed here.";
                            return s;
                        }
                    }
                    else
                    {
                        s="fa The horizontal wall can't be placed here.";
                        return s;
                    }
                else
                {
                    s="wall can't be placed here.";
                    return s;
                }
            }
            else if(jahat=="vertical")
            {
                if(!(((j==5) && (i==4)) || ((j==5) && (i==6))))
                {
                    if(((i-1)>=0) && ((i+1)<size))
                    {
                        if((m[i-1][j]==0) && (m[i][j]==0) && (m[i+1][j]==0))
                        {
                            m[i-1][j]=-1;
                            m[i][j]=-1;
                            m[i+1][j]=-1;
                            s="tr done";
                            return s;
                        }
                        else
                        {
                            s="fa The vertical wall can't be placed here.";
                            return s;
                        }
                    }
                    else
                    {
                        s="fa The vertical wall can't be placed here.";
                        return s;
                    }
                }
                else
                {
                    s="wall can't be placed here.";
                    return s;
                }
            }
        }
        else
        {
            s="wall can't be placed here.";
            return s;
        }
    }
    else
    {
        s="fa i,j are out of range.";
        return s;
    }
    return s;
}