#include<bits/stdc++.h>

using namespace std;


int main(void)
{
	int N, K;
	
	cin>>N>>K;
	
	
	int count = 0;
	while(true)
	{
		/*
		if(N % K != 0)
		{
			N--;
			count++;
		}
		
		else
		{
			N/=K;
			count++;
		}
		*/
		
		count += (N- ((int)(N/K) * K));
		
		N/=K;
		count++;
			
		
		
		if(N == 1)
		{
			break;
		}
	
	}
	
	printf("%d \n", count);
	
	
}