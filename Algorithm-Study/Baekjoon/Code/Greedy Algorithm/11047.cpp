#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	
	int N = 0;
	int K = 0;
	int count = 0;
	cin>>N;
	cin>>K;
	vector<int> coinList;
	
	
	int temp = 0;
	for(int i =0; i<N; i++)
	{
		cin>>temp;
		coinList.push_back(temp);
	}
		
	vector<int>::iterator iter = coinList.end();
	iter--;
	for(int i = 0; i<N; i++)
	{
		count += K / *iter;

		K %= *iter;
		iter--;
		
	}
	
	cout<<count<<"\n";
	
}
