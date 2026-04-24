#include<bits/stdc++.h>


using namespace std;



int main(void)
{
    string text;

    int T;

    cin>>T;
    for(int i = 0; i < T; i++)
    {
        cin>>text;

        cout<<text[0]<<text[text.length()-1]<<'\n';
    }
}