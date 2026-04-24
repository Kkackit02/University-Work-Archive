#include <bits/stdc++.h>

using namespace std;

long memo[100];

int cnt1 = 0;
int cnt2 = 0;

long Fibonaci(long n)
{
	
	
	if(n==1 || n==2)
	{
		cnt1++;
		return 1;
	}
	
	return Fibonaci(n-1) + Fibonaci(n-2);

}

long Fibonaci_dynamic(long n)
{
	

	if(n==1 || n==2)
	{
		return 1;
	}

	
	if(memo[n] != 0)
	{
		return memo[n];
	}
	else
	{
		cnt2++;
		memo[n] = Fibonaci_dynamic(n-1) + Fibonaci_dynamic(n-2);
	}
	
	return n;

}


int main(void)
{
	int n = 0;
	cin>>n;
	Fibonaci(n);
	Fibonaci_dynamic(n);
	cout<<cnt1<<' '<<cnt2<<endl;
}

