#include<bits/stdc++.h>


using namespace std;




long long func(long long A, long long B)
{
    return (A+B)*(A-B);
}


int main(void)
{
    int input;
    int result = 0;
    for(int i = 0; i < 5; i++)
    {
        cin>>input;
        result+=input*input;


    }

    cout<<result%10<<"\n";
}