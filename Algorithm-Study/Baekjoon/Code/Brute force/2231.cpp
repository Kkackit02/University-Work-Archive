#include<bits/stdc++.h>

using namespace std;


int main(void)
{   
    int N;

    cin>>N;

    int minConstructor = 1000001;
    int sum;
    int temp;
    for(int i = N; i > 0; i--)
    {
        sum = i;
        temp = i;
        while(temp != 0)
        {
            sum += temp%10;
            temp/=10;
        }


        if(N == sum)
        {

            if(minConstructor > i)
            {
                minConstructor = i;
            }
        }
    }


    if(minConstructor != 1000001)
    {
        cout<<minConstructor<<"\n";
    }
    else
    {
        cout<<0<<"\n";
    }

    return 0;
}