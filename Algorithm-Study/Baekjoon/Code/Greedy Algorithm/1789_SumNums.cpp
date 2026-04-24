#include<bits/stdc++.h>

using namespace std;


int main(void)
{
	
	long S;
	cin>>S;
	
	long Sum = 0;
	int N = 0;
	for(long i = 1; i <= S; i++)
	{
		Sum+=i;
		
		if(Sum + (i+1) < S)
		{	
			N++;
		}
		else if(Sum + (i+1) > S)
		{
			Sum -= i;
			Sum += S - Sum;
			N++;
		}
		else if(Sum + (i+1) == S)
		{
			Sum += i+1;
			N+=2;
		}
		
		if(Sum == S)
		{
			break;
		}
	}
	
	cout<<N<<endl;
	
	
}