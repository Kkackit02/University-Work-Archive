#include<bits/stdc++.h>

using namespace std;

int main(void)
{
    bool v[31];


    for (int i = 1; i < 31; i++)
    {
        v[i] = true;
    }



    int n = 0;

    for(int i = 1; i < 29; i++)
    {
        cin>>n;
        v[n] = false;

    }


    for(int i = 1; i < 31; i++)
    {
        if(v[i] == true)
        {
            cout<<i<<"\n";
        }
    }


}