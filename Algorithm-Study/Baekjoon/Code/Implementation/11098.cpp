#include<iostream>
#include<string>
#include<stack>
//11098 첼시를 도와줘!
//https://www.acmicpc.net/problem/11098

using namespace std;



int main(void)
{
	int n; // 테스트케이스
	int p; // 고려해야할 선수의 수
	
	string name[100];
	int cost[100];
	
	int bestIdx = 0;
	cin>>n;
	for(int i = 0; i<n; i++)
	{
		int bestCost = 0;
		cin>>p;
		for(int j = 0; j < p; j++)
		{
			cin>>cost[j];
			cin>>name[j];	
		}
		
		for(int j = 0; j < p; j++)
		{
			if(cost[j] > bestCost)
			{
				bestIdx = j;
				bestCost = cost[j];
			}
		}
		cout<<name[bestIdx]<<'\n';
		
		
	}
	
	stack<char> stack;
	
	
    return 0;
	
}
