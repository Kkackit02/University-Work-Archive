#include <bits/stdc++.h>

using namespace std;


vector<int> res_dfs;

bool visited[26];

int graph[26][26];
int result = 0;
int cnt = 0;

int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
int N;
void dfs(int x, int y)
{
	
	for(int i = 0; i<4; i++)
	{
		int next_x = x + dx[i];
		int next_y = y + dy[i];
		
		if(next_x < 0 || next_x >= N || next_y <0 || next_y >= N)
		{
			continue;
		}
		if(graph[next_x][next_y] == 1)
		{
			cnt++;
			graph[next_x][next_y] = 2;
			dfs(next_x, next_y);
		}
	}
}




int main(void)
{
	
	
	string input;
	
	cin>>N;
	
	
	int i = 0;
	for(i = 0; i < N; i++)
	{
		cin>>input;
		
		for(int j =0; j<N; j++)
		{
			graph[i][j] = input[j] - '0';
		}
	}
	

	
	for(int i =0; i<N; i++)
	{
		for(int j = 0; j<N; j++)
		{
			if(graph[i][j] == 1)
			{
				cnt = 1;
				graph[i][j] = 2;
				dfs(i,j);
				res_dfs.push_back(cnt);
			}
		}
	}
	
	cout<<res_dfs.size()<<'\n';
	sort(res_dfs.begin(), res_dfs.end());
	
	for(int i = 0; i< res_dfs.size(); i++)
	{
		cout<<res_dfs[i]<<'\n';
	}
	
}
