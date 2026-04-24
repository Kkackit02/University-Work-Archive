#include <bits/stdc++.h>

using namespace std;

int r,c,result; 

void Z(int x, int y, int n)
{
	if(x == r && y == c)
	{
		cout<<result<<endl;
		return;
	}
	
	if(r >= x && r < x+n && c >= y && c < y+n)
	{
		Z(x,y, n/2);
		Z(x,y+n/2, n/2);
		Z(x+n/2 , y, n/2);
		Z(x+n/2 , y+n/2 , n/2);
	}
	//해당 안된 영역이라면
	else
	{
		result += n*n;
	}
	
	
	
}

int main(void)
{
	int N = 0;
	cin>>N;
	
	cin>>r>>c;
	
	
	
	
	Z(0,0,pow(2,N));
	
}
