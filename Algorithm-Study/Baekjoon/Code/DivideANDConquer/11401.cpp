//https://m.blog.naver.com/hongjg3229/221650178981





/*

( n! / k!(n-k)! ) % P != n!%P / k!(n-k)!%P

*/

#include<bits/stdc++.h>

using namespace std; 

long long P = 1000000007;

long long A = 1;
long long B = 1;

long long DAC(long long b, long long p)
{
	
	if(p == 0) // 
	{
		return 1;
	}
	
	if(p % 2 > 0) // P가 홀수라면..  그냥 n 한번 곱해버리고 P를 짝수로 만들어준 뒤 쪼개기 위해 보낸다.
	{
		return (DAC(b, p-1) * b) % P;
	}
	
	
	long long temp = DAC(b, p/2) % P;
	return (temp * temp) % P; // 쪼개기
	
	/*
	
	즉 2의 8승은 8번 계산해야하지만 
	(((2^2)^2)^2)라고 하면 3번만 계산하면 된다.
	
	*/
	
}

// A = n!
// B = k!(n-k)!
// 이라고 하면 우리가 구해야하는 식은 A*B^(-1) % P

// A*B^(-1) % P = A*B^(P-2)%P = (A%P)(B^(P-2)%P)%P



int main(void)
{
	int n, k;
	
	cin>>n>>k;
	
	for(int i = 1; i <= n; i++)
	{
		A *= i;
		A %= P;
	}
	for(int i = 1; i <= k; i++)
	{
		B *= i;
		B %= P;
	}
	for(int i = 1; i <= n-k; i++)
	{
		B *= i;
		B %= P;
	}
	
	long long temp = DAC(B, P-2);
	//B의 P-2승을 구하기 위한 분할정복
	
	long long result = (A*temp) % P;
	
	
	cout<<result<<"\n";
	
	return 0;
	
	
	
}
