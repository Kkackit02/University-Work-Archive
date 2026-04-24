#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	
	ios::sync_with_stdio(false);

	cin.tie(NULL);

	cout.tie(NULL);
	
	int M,N;
	int A,B;
	
	cin>>N>>M;
	
	int subtotal[100001];
	subtotal[0] = 0;
	for(int i = 1; i<N+1; i++)
	{
		cin>>subtotal[i];
		
		subtotal[i] = subtotal[i-1] + subtotal[i];
		
	}

	
	
	
	
	for(int i = 1; i<M+1; i++)
	{
		cin>>A>>B;
		
		cout<<subtotal[B] - subtotal[A-1]<<'\n';
	}
	
}
