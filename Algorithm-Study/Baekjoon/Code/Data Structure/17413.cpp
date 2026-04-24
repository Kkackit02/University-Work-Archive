#include<iostream>
#include<string>
#include<stack>
#include<queue>

using namespace std;



int main(void)
{
	stack<char> stack;
	queue<char> queue;
	
	while(true)
	{
		char key;
		key = getchar();
		
		if(key == '<')
		{
			while(!stack.empty())
			{
				cout<<stack.top();
				stack.pop();
			}
			queue.push(key);
			while(true)
			{
				key = getchar();
				queue.push(key);
				if(key == '>')
				{
					while(!queue.empty())
					{
						cout<<queue.front();
						queue.pop();
					}
					break;
				}
			}
		}
		
		else if(key == '\n')
		{

			while(!stack.empty())
			{
				cout<<stack.top();
				stack.pop();
			}

			break;
		}
		
		else if(key == ' ')
		{
			while(!stack.empty())
			{
				cout<<stack.top();
				stack.pop();
			}
			cout<<' ';
		}		
		else
		{
			stack.push(key);
		}
		
		
	}

    return 0;
	
}
