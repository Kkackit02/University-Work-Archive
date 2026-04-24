#include<iostream>
#include<string>
#include<queue>

using namespace std;

int main(void)
{
	int T;
	int value;
	queue<int> queue;
	string func;
	cin>>T;
	
	for(int i = 0; i < T; i++)
	{
		cin>>func;
		if(func.compare("push") == 0)
		{
			cin>>value;
			queue.push(value);
		}
		else if(func.compare("front") == 0)
		{
			if(queue.empty())
			{
				cout<<"-1"<<'\n';
			}
			else
			{
				cout<<queue.front()<<'\n';
			}
			
		}
		else if(func.compare("back") == 0)
		{
			if(queue.empty())
			{
				cout<<"-1"<<'\n';
			}
			else
			{
				cout<<queue.back()<<'\n';
			}
			
		}
		else if(func.compare("size") == 0)
		{
			cout<<queue.size()<<'\n'; 
		}
		else if(func.compare("empty") == 0)
		{
			if(queue.empty())
			{
				cout<<"1"<<'\n';
			}
			else
			{
				cout<<"0"<<'\n';
			}
		}
		else if(func.compare("pop") == 0)
		{
			if(queue.empty())
			{
				cout<<"-1"<<'\n';
			}
			else
			{
				cout<<queue.front()<<'\n';
				queue.pop();	
			}
		}
	}
	
    return 0;
	
}
