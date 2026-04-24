#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int T = 0;
	cin>>T;
	list<int> numberStream;
	
	stack<int> tempStack;
	
	int value;
	int result = -1;
	for(int i = 0; i<T; i++)
	{
		cin>>value;	
		numberStream.push_back(value);
	}
	
	
	
	list<int>::iterator iter = numberStream.begin();
	
	for(int i = 0; i<numberStream.size(); i++)
	{
		cout<<*iter;
		iter++;
	}
	
	cout<<"\n";
	for(int i = 0; i<numberStream.size(); i++)
	{
		iter = numberStream.begin();
		result = -1;
		for(int j = numberStream.size() - i ; j < numberStream.size(); j++)
		{
			iter++; 
		}   
		iter = numberStream.begin();
		for(int j = i; j<numberStream.size(); j++)
		{
			tempStack.push(*iter);
			iter++;
		}
		iter = numberStream.begin();
		for(int j = i; j < numberStream.size(); j++)
		{
			if(*iter < tempStack.top())
			{
				result = tempStack.top();
				tempStack.pop();
			}
			iter++;
		} 
		
		cout<<result<<' ';
	}
	cout<<'\n';
	 
}
