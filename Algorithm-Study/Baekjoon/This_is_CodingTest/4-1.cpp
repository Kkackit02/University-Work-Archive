#include<iostream>
#include<string>
#include<stack>
#include<cmath>
using namespace std;



int main(void)
{

    int N;
    int X = 1;
    int Y = 1;

    char inputText = ' ';

    for(int i = 0; i < N; i++)
    {
        cin>>inputText;
        if(inputText == 'L')
        {
            if(X > 1)
            {
                X--;
            }
        }
        else if(inputText == 'R')
        {
            if(X < N)
            {
                X++;
            }
        }
        else if(inputText == 'U')
        {
            if(Y < N)
            {
                Y++;
            }
        }
        else if(inputText == 'D')
        {
            if(Y > 1)
            {
                Y--;
            }
        }
    }

    cout<<X<<" "<<Y<<endl;
}