#include<iostream>
using namespace std;



int main(void)
{
	
	int A;
	int B;
	
	int A_origin;
	int B_origin;
	cin>>A;
	cin>>B;
	
	A_origin = A;
	B_origin = B;
	int gcd = 0;
	int lcm = 0;
	
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
	
	printf("%d\n" , gcd);
	printf("%d\n" , lcm);
}
