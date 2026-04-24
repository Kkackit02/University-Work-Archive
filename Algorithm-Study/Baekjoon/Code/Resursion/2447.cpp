#include <bits/stdc++.h>

using namespace std;

void Draw_Star(int n)
{
	
	if(n%3==3)
	{
		pritnf("***");
	}
	else if(n%3==2)
	{
		printf("* *");
	}
	else if(n%3==1)
	{
		printf("***");
	}
	
	return Draw_Star(n-1);
	
}

int main(void)
{
	int T = 0;
	cin>>T;
	
	for(int i = 0; i<T; i++)
	{

	}
	
}
