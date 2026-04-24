#include <bits/stdc++.h>

using namespace std;

int house[1001][3];

int main(void)
{
	int T = 0;
	cin>>T;
	
	int red,green,blue;
	house[0][0] = 0;
	house[0][1] = 0;
	house[0][2] = 0;
	
	for(int i = 1; i<T+1; i++)
	{
		cin>>red>>green>>blue;
		house[i][0] = min(house[i-1][1] , house[i-1][2]) + red;
		house[i][1] = min(house[i-1][0] , house[i-1][2]) + green;
		house[i][2] = min(house[i-1][1] , house[i-1][0]) + blue;
	}
	
	cout<<min(house[T][2] , min(house[T][1] , house[T][0]))<<"\n";
}

