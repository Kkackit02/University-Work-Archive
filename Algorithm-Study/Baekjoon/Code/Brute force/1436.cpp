#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int N = 0;
	cin>>N;
	
	int i = 0;
	int copy_i = 0;
		
	int streak = 0;
	int count = 0;
	bool doomsNumber = false;
	while(true)
	{
		streak = 0;
		doomsNumber = false;
		
		copy_i = i;
		
		while(copy_i != 0)
		{
			if((copy_i % 10) == 6)
			{
				streak++;
				if(streak >= 3)
				{
					doomsNumber = true;
				}
			}
			else
			{
				streak = 0;	
			}
			
			copy_i /= 10;
		}
		if(doomsNumber == true)
		{
			count++;
		}
		
		if(count==N)
		{
			break;
		}
		i++;
	}
	
	cout<<i<<endl;
	
}
