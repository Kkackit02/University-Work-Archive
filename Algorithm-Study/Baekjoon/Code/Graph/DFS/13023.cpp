#include <bits/stdc++.h>
// 이분 그래프 문제
using namespace std;
//반례모음 https://www.acmicpc.net/board/view/77198

vector<int> vec[2001];
int visited[2001];

int  V, E;

bool result = false;
void dfs(int depth , int cnt)
{
	
	if(depth == 4)
	{
		result = true;
		return;
	}
	
	visited[cnt] = true;
	
	for(int i = 0; i< vec[cnt].size(); i++)
	{
		if(visited[vec[cnt][i]] == false && result == false)
		{
			dfs(depth+1 , cnt);
		}		
	}
	
	visited[cnt] = false; 
	
}



int main(void)
{
	int a,b;
	
	cin>>V>>E;
	for(int j = 0; j < E; j++)
	{
		cin>>a>>b;
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
		
	for(int j = 0; j < V; j++)
	{
		visited[j] = true;
		dfs(0, j);
		visited[j] = false;
		
		if(result == true)
		{
			break;
		}
	}
	
	cout<<result<<'\n';
	
	
	return 0;
	
}