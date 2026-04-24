#include<bits/stdc++.h>


using namespace std;




long long func(long long A, long long B)
{
    return (A+B)*(A-B);
}


int main(void)
{
    long long a,b;

    cin>>a>>b;

    cout<<func(a,b)<<'\n';
}