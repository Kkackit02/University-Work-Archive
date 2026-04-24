#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int A = 0;
	int B = 0;
	
	int array[1000];
	
	cin>>A;
	cin>>B;
	int result =0;
	
	int count = 0;
	for(int i = 0; i < 1000; i++)
	{
		for(int j = 0; j<i; j++)
		{
			array[count] = i; 
			count++;
			if(count >= 1000)
			{
				break;
			}
		}
		if(count >= 1000)
		{
			break;
		}	
	}
	

	for(int i = A-1; i<B; i++)
	{
		result+=array[i];
	}
	
	cout<<result<<endl;
}
