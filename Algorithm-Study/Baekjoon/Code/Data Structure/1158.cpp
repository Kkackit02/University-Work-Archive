#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	queue<int> q;
	int N = 0;
	cin>>N;
	int K = 0;
	cin>>K;
	
	
	
	for(int i = 1; i<N+1; i++)
	{
		q.push(i);
	}
	
	cout<<'<';
	
	int temp=0;
	for(int i = 0; i < N; i++)
	{
		for(int j= 0; j<K-1;j++)
		{
			temp = q.front();
			q.push(temp);
			q.pop();
			
		}
		
		if((!q.empty()))
		{
			cout<<q.front();
			q.pop();
		}
		
		
		if(!q.empty())
		{
			cout<<", ";
		}
	}
	
	cout<<'>'<<'\n';
}
