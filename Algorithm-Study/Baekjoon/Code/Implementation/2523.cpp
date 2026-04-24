#include <bits/stdc++.h>

using namespace std;


int main(void)
{
	int N;
	
	cin>>N;
	
	for(int i = 1; i< N; i++)
	{
		for(int k = 0; k < i; k++)
		{
			cout<<"*";
		}		
		cout<<endl;
	}
	
	for(int k = 0; k < N; k++)
	{
		cout<<"*";
	}
	cout<<endl;
	
	for(int i = 1; i< N; i++)
	{
		for(int k = 0; k < N-i; k++)
		{
			cout<<"*";
		}		

		cout<<endl;
	}
	cout<<endl;
}
