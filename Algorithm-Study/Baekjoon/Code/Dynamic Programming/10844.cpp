#include <bits/stdc++.h>

using namespace std;

long long memo[10][100] {};

//https://velog.io/write?id=6b9edc6f-c28c-45ac-8e13-25115db424ed

/* 계단 아이디어 자체는 쉽게 떠올릴 수 있었다.
한 차원 한 차원 내리면서 위아래로 계단수가 있는지 조사하면 됐다.
그리고 어떤 값을 저장해서 다시 활용할지 생각해보니
결국 각 자릿 수가 자신의 아래로 가지는 계단 수는 정해져있더라.

결국은 재귀적으로 처리가 가능하다는 뜻.

그래서 재귀적으로 처리해줬다.

문제는 10억으로 나눈 나머지를 저장하게 하는데서 오류가 자주 나왔다.

마지막에 result를 구하는 과정에서 앞에선 전부 10억보다 낮은 값이지만,
마지막 result가 더해지고 더해지면서 10억을 초과해버려..
틀리는 경우가 만들어졌다.

마지막까지 긴장의 끈을 놓지 않아야한다.

자동 입력 테스터기를 하나 만들어봐야겠다는 생각을 했다.
https://ideone.com/n9K9id 이런 것 처럼?


*/


long long stairNumber(int n , int digit)
{
	if(digit<=1)
	{
		return 1;
	}
	
	if(memo[n][digit])
	{
		return memo[n][digit]% 1000000000;
	}
	else 
	{
		if(n-1 >= 0)
		{
			memo[n][digit] += stairNumber(n-1,digit-1) % 1000000000;
		}
		if(n+1 <= 9)
		{
			memo[n][digit] += stairNumber(n+1, digit-1) % 1000000000;
		}
		
	}
	return memo[n][digit] % 1000000000;

}


int main(void)
{
	int N = 0;
	cin>>N;
	
	long long result = 0;
	for(int i =1; i<10; i++)
	{
		result += stairNumber(i, N);	
		result %= 1000000000;
	}
	cout<<result<<'\n';
	
}

