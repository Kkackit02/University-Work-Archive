#include <bits/stdc++.h>

using namespace std;



int graph[1001][1001];
queue<pair<int, int>> q;
bool visited[1001][1001];
int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};

int N, M, K;

void bfs()
{

	
	
	while(!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		visited[x][y] = true;
		for(int i = 0; i<4; i++)
		{
			int next_x = x + dx[i];
			int next_y = y + dy[i];

			if(next_x < 0 || next_x >= N || next_y <0 || next_y >= M)
			{
				continue;
			}
			if(graph[next_x][next_y] == 0 && visited[next_x][next_y] == false)
			{
				graph[next_x][next_y] = graph[x][y] + 1;
				q.push({next_x, next_y});
				//cout<<next_x<<":"<<next_y<<'\n';
				visited[next_x][next_y] = true;
			}
			
		}
	}
	
}



int main(void)
{
	cin>>M>>N>>K;
	memset(visited, false, sizeof(visited));
	memset(graph,0,sizeof(graph));
	
	int x1,x2,y1,y2;
	for(int i = 0; i < K; i++)
	{
		cin>>x1>>y1>>x2>>y2;
		
		for(int j = x1; j<x2; j++)
		{
			for(int k = y1; k<y2; k++)
			{
				graph[j][k]++;
				visited[j][k] = true;
			}
		}
	}
	
	
	
	
		
	int result = 0;
	
	for(int i =0; i<N;i++)
	{
		for(int j =0; j<M; j++)
		{
			if(visited[i][j] == false)
			{
				q.push({i,j});
				bfs();
				result++;
			}
		}
		cout<<endl;
	}

	
	for(int i =0; i<N;i++)
	{
		for(int j =0; j<M; j++)
		{
			cout<<graph[i][j];
		}
		cout<<endl;
	}
	
	
}
