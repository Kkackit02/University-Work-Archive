#include <bits/stdc++.h>

using namespace std;
//2442 별찍기 5


int main(void)
{
	int N;
	
	cin>>N;
	
	for(int i = 1; i< N+1; i++)
	{
		for(int k = 0; k < (N-i); k++)
		{
			cout<<" ";
		}	
		for(int k = 0; k < (2*i - 1); k++)
		{
			cout<<"*";
		}

		cout<<'\n';
	}
	
}
