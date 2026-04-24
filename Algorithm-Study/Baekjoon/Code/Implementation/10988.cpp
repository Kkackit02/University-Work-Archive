#include<bits/stdc++.h>

using namespace std;

int main(void)
{
    string text;
    cin>>text;

    string reverseText = text;
    reverse(reverseText.begin(), reverseText.end());
    if(reverseText == text)
    {
        cout<<1<<endl;
    }
    else
    {
        cout<<0<<endl;
    }
}