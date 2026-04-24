#include <bits/stdc++.h>

using namespace std;


int main(void)
{
	int N;
	
	cin>>N;
	for(int i = 1; i< N+1; i++)
	{
		for(int j = 0; j < N-i; j++)
		{
			cout<<" ";
		}
		for(int j = 0; j < 2*i-1; j++)
		{
			if(j%2 == 0)
			{
				cout<<"*";
			}
			else
			{
				cout<<" ";
			}
		}
		cout<<endl;
	}
	
	
}
