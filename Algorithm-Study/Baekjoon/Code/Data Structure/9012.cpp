#include<iostream>
#include<string>
#include<stack>
#include<deque> 
#include<queue>

using namespace std;



int main(void)
{
	int T;
	
	
	
	string Result[10000];
	
	
	cin>>T;
	getchar();
	for(int i = 0; i<T; i++)
	{
		
		stack<char> stack;
		while(true)
		{
			char key;
			key = getchar();
			if(key == '(')
			{
				stack.push(key);
			}
			
			else if(key == ')')
			{
				if(stack.empty())
				{
					cout<<"NO"<<'\n';
					while(key != '\n')
						key = getchar();
						break;
				}
				stack.pop();
			}
			
			else if(key == '\n')
			{
				if(stack.empty())
				{
					cout<<"YES"<<'\n';
					break;
				}
				else
				{
					cout<<"NO"<<'\n';
					break;
				}
			}
			
			
		}
		
	}
	
	
	
    return 0;
	
}
