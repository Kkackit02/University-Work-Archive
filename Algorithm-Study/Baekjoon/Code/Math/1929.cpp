#include<iostream>
#include<string>
#include<stack>
#include<cmath>
using namespace std;



int main(void)
{
	int M;
	int N;
	cin>>M;
	cin>>N;
	
	int primeN_Table[1000001];
	for(int i = 0; i<= N; i++)
	{
		primeN_Table[i] = i;
	}
	primeN_Table[1] = 0;
	
	
	for(int i = 2; i<=N; i++)
	{

		if(primeN_Table[i] != 0)
		{
			for(int j = 2; j <= (N/i); j++)
			{
				primeN_Table[i*j] = 0;
			}
		}
		
	}
	for(int i = M; i<= N; i++)
	{

		if(primeN_Table[i] != 0)
		{
			printf("%d\n" , primeN_Table[i]);
		}
		
	}
	
	
    return 0;
	
}
