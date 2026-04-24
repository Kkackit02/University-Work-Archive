#include <bits/stdc++.h>

using namespace std;

//2748 피보나치 수 2
// 90의 결과는 
// 2880067194370816120이므로
// int의 범위를 넘어서니 long을 사용하자

//그리고 동적계획법을 쓰자!
//연산 회수가 엄청 차이난다~
long memo[100] {};


long Fibonaci(long n)
{
	
	
	if(n<=1)
	{
		return n;
	}

	
	if(memo[n] != 0)
	{
		return memo[n];
	}
	else
	{
		memo[n] = Fibonaci(n-1) + Fibonaci(n-2);
	}
	
	return memo[n];

}


int main(void)
{
	int n = 0;
	cin>>n;
	for(int i = 0; i< 100; i++)
	{
		memo[i] = 0;
	}
	cout<<Fibonaci(n)<<'\n';
}

