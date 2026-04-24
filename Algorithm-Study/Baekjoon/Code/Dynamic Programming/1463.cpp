#include <bits/stdc++.h>

using namespace std;

//2748 피보나치 수 2
// 90의 결과는 
// 2880067194370816120이므로
// int의 범위를 넘어서니 long을 사용하자

//그리고 동적계획법을 쓰자!
//연산 회수가 엄청 차이난다~

int main(void)
{
	int N = 0;
	cin>>N;
	
	vector<int> memo(N+1);
	
	memo[1] = 0;
	for(int i = 2; i<= N; i++)
	{
		memo[i] = memo[i-1] +1;
		if(!(i%3))
		{
			memo[i] = min(memo[i] , memo[i/3] + 1);
		}
		if(!(i%2))
		{
			memo[i] = min(memo[i] , memo[i/2] + 1);
		}
		
	}
	
	cout<<memo[N]<<"\n";
	
	
}

