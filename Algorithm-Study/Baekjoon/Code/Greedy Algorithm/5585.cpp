#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int money = 0;
	int count = 0;
	cin>>money;
	
	money = 1000-money;
	int moneyList[6] = {500, 100, 50, 10, 5, 1};
	
	for(int i = 0; i < 6; i++)
	{
		count += money/moneyList[i];
		money %= moneyList[i];
		
	}	
	cout<<count<<"\n";
	
}
