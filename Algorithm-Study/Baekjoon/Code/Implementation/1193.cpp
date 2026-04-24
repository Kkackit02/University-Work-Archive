#include <bits/stdc++.h>
using namespace std;

int main() {
    int N;
    cin>>N;

    int flag = 1;
    int i = 0;
    int cnt = 0;
    while(N != cnt)
    {
        
        i++;
        cnt++;
        
        if(flag == i)
        {
            flag++;
            i = 1;
        }
    }
    if(flag%2 == 0)
    {

        cout<<flag-i<<"/"<<i<<endl;
    }
    else
    {

        cout<<i<<"/"<<flag-i<<endl;
    }
}
