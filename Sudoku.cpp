#include <bits/stdc++.h>
#include<thread>
using namespace std;
int M;
vector<vector<int>> grid;

//----------------Display part--------------------//
void display()
{
    cout<<"Output \n";
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<M; j++)
        {
            cout<<grid[i][j]<<" ";
        }
        cout<<'\n';
    }
}

//----------------Checker Part------------------//
void Existence_row_col(vector<int> &storage)
{
    for(int i=0; i<M; i++)
    {
        map<int, int> mp;
        for(int j=0; j<M; j++)
        {
            mp[grid[i][j]]=1;
            if(grid[i][j]>M || grid[i][j]<1)
            {
                storage[0]=false;
                return;
            }
        }
        if(mp.size()!=M)
        {
            storage[0]=false;
            return;
        }
    }
    storage[0]=true;
}


void Existence_box(vector<int> &storage)
{
    int tem= sqrt(M);
    int row=0, col=0;
    for(int k=0; k<M; k++)
    {
        col=k;
        int sr= row-(row%tem);
        int sc= col-(col%tem);
        map <int,int> mp;
        for(int i=0; i<tem; i++)
        {
            for(int j=0; j<tem; j++)
            {
                mp[grid[i+sr][j+sc]]=1;
                if(grid[i+sr][j+sc]>M || grid[i+sr][j+sc]<1)
                {
                    storage[1]=false;
                    return;
                }
            }
        }
        if(mp.size()!=M)
        {
            storage[1]=false;
            return;
        }
        row+=tem;
        row%=M;
    }
    storage[1]=true;
    return;
}


bool Existence()
{
    vector<int> storage(2);
    std::thread t1(Existence_box, ref(storage));
    std::thread t2(Existence_row_col, ref(storage));
    t1.join();
    t2.join();
    bool flag= storage[0]&storage[1];
    return flag;
}

//-------------------Solver part---------------------//
void check_row_col(int row,int col,int num, vector<int> &storage)
{
    for(int i=0; i<M; i++)
    {
        if(grid[i][col]==num){
            storage[0]=false;
            return;
        }

    }
    for(int i=0; i<M; i++)
    {
        if(grid[row][i]==num){
            storage[0]=false;
            return;
        }

    }
    storage[0]=true;
    return;
}


void check_box(int row, int col, int num, vector<int> &storage)
{
    int tem= sqrt(M);
    int sr= row-(row%tem);
    int sc= col-(col%tem);
    for(int i=0; i<tem; i++)
    {
        for(int j=0; j<tem; j++)
        {
            if(grid[i+sr][j+sc]==num){
                storage[1]=false;
                return;
            }
        }
    }
    storage[1]=true;
    return;
}


bool check(int row, int col, int num)
{   
    vector<int> storage(2);
    std::thread t1(check_box, row, col, num, ref(storage));
    std::thread t2(check_row_col, row, col, num, ref(storage));
    t1.join();
    t2.join();
    bool flag= storage[0]&storage[1];
    return flag;
}


bool Suduko(int row,int col)
{
    if (row == M-1 and col== M)
        return true;
    if (col == M)
        row+= 1,col = 0;
    if (grid[row][col] > 0)
        return Suduko(row, col + 1);
    for(int num=1; num<=M; num++)
        if (check(row, col, num))
        {
            grid[row][col] = num;
            if (Suduko(row, col + 1))
                return true;
            grid[row][col] = 0;
        }
    return false;
}

//-----------------Main function------------------//
int main()
{
    cout<<"Welcome to Sudoku Solver :)"<<'\n';
    cout<<"Enter grid size which is a perfect square:"<<" ";
    cin>>M;
    cout<<'\n';
    if(M<=0)
    {
        cout<<"INVALID INPUT"<<'\n';
        return 0;
    }
    int x= sqrt(M);
    if(M!=(x*x))
    {
        cout<<"INVALID INPUT"<<'\n';
        return 0;
    }
    grid.resize(M, vector<int>(M));
    for(int i=0; i<M; i++)
    {
        for(int j=0; j<M; j++)
        {
            cin>>grid[i][j];
        }
    }
    cout<<"Enter Operation to perform with the given grid"<<'\n'<<"1. Sudoku Solver"<<'\n'<<"2. Sudoku Checker"<<'\n';
    int y;
    cin>>y;
    if(y==1)
    {
        if(Suduko(0, 0))
            display();
        else
            cout<<"Solution does not exist:("<<'\n';
    }
    else if(y==2)
    {
        if(Existence())
            cout<<"YES... The given grid is valid solution :)"<<'\n';
        else
            cout<<"NO... The given grid is not a valid solution :("<<'\n';
    }
    else
    {
        cout<<"INVALID INPUT!!!"<<'\n';
    }
    int e;
    cout<<"To exit return 0"<<'\n';
    cin>>e;
    return(e);
}