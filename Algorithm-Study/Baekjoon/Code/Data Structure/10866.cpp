#include<iostream>
#include<string>
#include<deque>

using namespace std;

int main(void)
{
	int T;
	int value;
	deque<int> deque;
	string func;
	cin>>T;
	
	for(int i = 0; i < T; i++)
	{
		cin>>func;
		if(func.compare("push_back") == 0)
		{
			cin>>value;
			deque.push_back(value);
		}
		else if(func.compare("push_front") == 0)
		{
			cin>>value;
			deque.push_front(value);
		}
		else if(func.compare("front") == 0)
		{
			if(deque.empty())
			{
				cout<<"-1"<<'\n';
			}
			else
			{
				cout<<deque.front()<<'\n';
			}
			
		}
		else if(func.compare("back") == 0)
		{
			if(deque.empty())
			{
				cout<<"-1"<<'\n';
			}
			else
			{
				cout<<deque.back()<<'\n';
			}
			
		}
		else if(func.compare("size") == 0)
		{
			cout<<deque.size()<<'\n'; 
		}
		else if(func.compare("empty") == 0)
		{
			if(deque.empty())
			{
				cout<<"1"<<'\n';
			}
			else
			{
				cout<<"0"<<'\n';
			}
		}
		else if(func.compare("pop_front") == 0)
		{
			if(deque.empty())
			{
				cout<<"-1"<<'\n';
			}
			else
			{
				cout<<deque.front()<<'\n';
				deque.pop_front();	
			}
		}
		else if(func.compare("pop_back") == 0)
		{
			if(deque.empty())
			{
				cout<<"-1"<<'\n';
			}
			else
			{
				cout<<deque.back()<<'\n';
				deque.pop_back();	
			}
		}
	}
	
    return 0;
	
}
