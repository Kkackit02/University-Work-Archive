#include<bits/stdc++.h>


using namespace std;



int main(void)
{
    string text;


    cin>>text;


    for(int i = 0; i < text.length(); i++)
    {
        if(text[i] >= 97)
        {
            text[i] -= 32;
        }
        else
        {
            text[i] += 32;
        }
    }

    cout<<text<<endl;
}