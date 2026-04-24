#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	stack<int> stack;
	
	int K = 0;
	cin>>K;
	
	int temp;
	for(int i =0; i<K; i++)
	{
		cin>>temp;
		if(temp == 0)
		{
			stack.pop();
		}
		else
		{
			stack.push(temp);	
		}
		
	}
	
	int result = 0;
	
	while(!stack.empty())
	{
		result+=stack.top();
		stack.pop();
	}
	
	cout<<result<<'\n';
	
}
