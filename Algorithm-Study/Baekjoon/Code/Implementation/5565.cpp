#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int totalMoney = 0;
	cin>>totalMoney;
	
	int temp = 0;
	int readMoney = 0;
	for(int i =0; i< 9; i++)
	{
		cin>>temp;
		readMoney+=temp;
	}
	
	cout<<totalMoney-readMoney<<endl;
	
}
