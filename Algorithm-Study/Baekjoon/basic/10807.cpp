#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	
    int T;

    cin>>T;

    vector<int> v;


    int A;
    for(int i = 0; i < T; i++)
    {
        cin>>A;
        v.push_back(A);
    }

    int V;

    cin>>V;
    int result = 0;
    for(int i = 0; i < T; i++)
    {
        if(v[i] == V)
        {
            result++;
        }
    }

    cout<<result<<"\n";
    
}
