#include<bits/stdc++.h>

using namespace std;


int main(void)
{
    int temp = 0;
    int tempLeast = 0;

    cin>>temp;

    if(temp == 8)
    {
        for(int i = 0; i < 7; i++)
        {
            cin>>tempLeast;
            if(tempLeast + 1 != temp)
            {
                cout<<"mixed"<<endl;
                return 0;
            }
            temp = tempLeast;
        }
        cout<<"descending"<<endl;
    }
    else if(temp == 1)
    {
        for(int i = 0; i < 7; i++)
        {
            cin>>tempLeast;
            if(tempLeast -1 != temp)
            {
                cout<<"mixed"<<endl;
                return 0;
            }
            
            temp = tempLeast;
        }
        
        cout<<"ascending"<<endl;
    }
    else
    {
        cout<<"mixed"<<endl;
    }

    
}