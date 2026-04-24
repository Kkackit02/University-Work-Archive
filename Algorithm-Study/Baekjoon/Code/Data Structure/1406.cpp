#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	list<char> text;
	char temp;
	
	while(true)
	{
		temp = getchar();
		
		if(temp == '\n')
		{
			break;
		}
		text.push_back(temp);
	}
	
	int T = 0;
	cin>>T;
	
	char Func;
	char val;
	list<char>::iterator iter = text.end();
	
	
	
	for(int i = 0; i<T; i++)
	{
		cin>>Func;
		if(Func == 'P')
		{
			cin>>val;
			text.insert(iter ,val);
			
		}
		else if(Func == 'L')
		{
			if(iter != text.begin())
			{
				iter--;
			}
		}
		else if(Func == 'D')
		{
			if(iter != text.end())
			{
				iter++;
			}
		}
		else if(Func == 'B')
		{
			if(iter != text.begin())
			{
				iter--;
				iter = text.erase(iter);
			}
			
		}
	}
	
	iter = text.begin();  
	for(int i = 0; i < text.size(); i++)
	{
     	 
		cout << *iter;
		iter++; 
    }    
	cout<<'\n';
}
