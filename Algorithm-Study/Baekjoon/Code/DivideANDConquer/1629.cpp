#include<bits/stdc++.h>

//지수법칙 : a^(n+m) = a^n * a^m
//모듈러 성질 : (a*b)%c = (a%c * b%c)%c
using namespace std;
int A,B,C;

int Multiple(int a, int b, int c)
{
	if(b>1)
	{
		long long result = Multiple(a, b/2, c);
		//f(10) = f(5)*f(5);
		
		if(b % 2 == 1)//짝수가 아니라 하나가 빈다면..
		{
			// ((f(5)*f(5)) % c * a) % c
			// ((f(5) % c) * (f(5) % c) * A) % c -> 즉 모듈러 성질 이용
			
			return ((result * result) % c * a) % c;
		}
		else
		{
			return (result * result) % c;
			
			// ((f(5)*f(5)) % c
			// (f(5) % c) * (f(5) % c)
		}
			
	}
	else if (b == 1) //f(1) = 1;
	{
		return a;
	}
	
	
}

int main(void)
{
	
	
	cin>>A>>B>>C;
	
	
	
	cout<<Multiple(A%C , B, C)<<"\n";
}