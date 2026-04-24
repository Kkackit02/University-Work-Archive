#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int N;
	cin>>N;
	
	vector<int> v;
	int a;
	int result = 0;
	for(int i = 0; i < N; i++)
	{
		cin>>a;
		v.push_back(a);
	}

	//sort(v.begin(), v.end());
	
	for(int i = N-2; i >= 0; i--)
	{
		//printf(":%d : %d : %d \n" , v[i+1] , v[i] , v[i-1]);
		while(v[i+1] <= v[i])
		{
			v[i]--;
			result++;
		}
		//printf("::%d : %d : %d \n" , v[i+1] , v[i] , v[i-1]);
	}
	
	cout<<result<<endl;


}