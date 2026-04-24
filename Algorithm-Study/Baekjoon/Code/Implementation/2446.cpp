#include <bits/stdc++.h>

using namespace std;


int main(void)
{
	int N;
	
	cin>>N;
	for(int i = 0; i< N; i++)
	{
		for(int k = 0; k < i; k++)
		{
			cout<<" ";
		}		
		for(int k = 0; k < 2*N-2*i -1; k++)
		{
			cout<<"*";
		}
		cout<<endl;
	}

	for(int i = 1; i< N; i++)
	{
		for(int k = 0; k < N-i-1; k++)
		{
			cout<<" ";
		}		
		for(int k = 0; k < 2*i+1; k++)
		{
			cout<<"*";
		}

		cout<<endl;
	}
}
