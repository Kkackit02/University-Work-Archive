#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int n = 0;
	cin>>n;
	stack<int> stack;
	queue<char> result;
	int T = 0;
	
	int count = 2;
	stack.push(1);
	result.push('+');
	for(int i = 0; i<n; i++)
	{
		cin>>T;
		while(true)
		{

			if(stack.empty() == false)
			{
				if(stack.top() == T)
				{
					stack.pop();
					result.push('-');
					continue;
				}
			}
			if(count <= T)
			{
				stack.push(count);
				count++;
				result.push('+');
			}
			else
			{
				break;
			}
			
		}
		
		
		
	}
	

	int len = result.size();
	
	if(!stack.empty())
	{
		cout<<"NO"<<'\n';
	}
	else
	{
		for(int i =0; i< len; i++)
		{
			cout<<result.front()<<'\n';
			result.pop();
		}
	}
	
}
