#include<bits/stdc++.h>

using namespace std;



	


int main(void)
{
	int A, B;
	
	cin>>A>>B;
	
	bool flag = false;
	int temp = 0;
	int N = 0;
	while(true)
	{
		temp = B;
		while(temp > 9)
		{
			temp %= 10;
		}
		
		if(temp == 1)
		{
			N++;
			B /= 10;
		}
		else if(temp % 2 == 0)
		{
			N++;
			B /= 2;
		}
		else
		{
			break;
		}
		
		if(A>B)
		{
			break;
		}
		
		if(B == A)
		{
			flag = true;
			break;
		}
		
	}
	
	if(flag == false)
	{
		cout<<-1<<endl;
	}
	else
	{
		cout<<N+1<<endl;
	}
	
}