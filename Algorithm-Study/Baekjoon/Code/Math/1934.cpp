#include<iostream>
using namespace std;

/*
유클리드 호제법.

gcd(A,B) A>B

A를 B로 나눴을떄 나머지가 0이 될때까지
A = B
B = A%B
대입을 반복한다
나머지가 0이 될때의 B가 gcd.
최소공배수는
lcm(A,B)
A*B / gcd이다.

정수 a, b의 최대공약수 G = gcd(a, b)에 대하여 아래의 식을 만족하는 정수 x와 y가 존재
a = Gx, b = Gy (단, x, y는 정수)
이 때 a b = GGxy 임을 알 수 있고, G는 두 수의 최대 공약수이며 x와 y는 서로소인 관계를 가집니다.
집합적으로 생각하면, a와 b의 합집합은 G, x, y이고 이 세 수를 곱한 Gxy가 최소공배수가 됨을 알 수 있습니다.

a b = GGxy
a b / G = GGxy / G (양변에 최소 공약수를 나누어 줌)
a b / G = Gx*y(최소공배수)
최소공배수 = a * b / G
그러므로 두 수의 최소공배수 L = lcm(a, b)은 L= lcm(a, b)= a * b / gcd(a, b)이 성립합니다.

*/

int main(void)
{
	
	int T;
	int A;
	int B;
	
	int A_origin;
	int B_origin;
	cin>>T;
	
	int result[1000];
	
	for(int i = 0; i < T; i++)
	{
		
		int gcd = 0;
		int lcm = 0;
		cin>>A;
		cin>>B;
		
		A_origin = A;
		B_origin = B;
		
		while(B > 0)
		{
			int temp = 0;
			if(A%B != 0)
			{
				temp = A%B;
				A = B;
				B = temp;
			}
			else
			{
				gcd = B;
				break;
			}
		}
		lcm = A_origin*B_origin/gcd;
		result[i] = lcm;
		
	}
	
	
	
	for(int i = 0; i < T; i++)
	{
	printf("%d\n" , result[i]);
	}
	

}
