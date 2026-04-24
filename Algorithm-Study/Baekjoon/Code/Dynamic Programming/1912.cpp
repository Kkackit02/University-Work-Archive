#include <bits/stdc++.h>

using namespace std;

int input[100001];
int memo[100001];


// 아 쒯...................................... -를 먹고 다음 연속을 가져가야 이득인 경우가 있네........

int main(void)
{
	int T = 0;
	int result = -1001;
	int total = 0;
	cin>>T;
	
	for(int i = 0; i<T; i++)
	{
		cin>>input[i];
	}
	
	int count = 0;
	result = input[0];
	memo[0] = input[0];
	
	
	for(int i =1; i<T; i++)
	{
		
		memo[i] = max(memo[i-1] + input[i] , input[i]);
		result = max(memo[i] , result);
	}
	
	
	cout<<result<<endl;
	
	return 0;
}
