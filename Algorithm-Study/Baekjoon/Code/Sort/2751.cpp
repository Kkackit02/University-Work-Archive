#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int T = 0;
	int array[1000000];
	cin>>T;
	
	for(int i = 0; i<T; i++)
	{
		cin>>array[i];
	}
	
	sort(array, array + T);
	
	
	for(int i = 0; i<T; i++)
	{
		cout<<array[i]<<'\n';
	}
	
}
