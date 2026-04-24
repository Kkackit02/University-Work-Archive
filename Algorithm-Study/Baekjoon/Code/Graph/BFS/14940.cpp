#include <bits/stdc++.h>

using namespace std;



int graph[1001][1001];
queue<pair<int, int>> q;
int visited[1001][1001];
int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};

int N, M;

void bfs(int start_x, int start_y)
{

	q.push({start_x, start_y});
	visited[start_x][start_y] = 0;
	while(!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		for(int i = 0; i<4; i++)
		{
			int next_x = x + dx[i];
			int next_y = y + dy[i];

			if(next_x < 0 || next_x >= N || next_y <0 || next_y >= M)
			{
				continue;
			}
			if(graph[next_x][next_y] == 1 && visited[next_x][next_y] == -1)
			{
				q.push({next_x, next_y});
				
				//cout<<next_x<<":"<<next_y<<'\n';
				visited[next_x][next_y] = visited[x][y]+1;
			}
			
		}
	}
	
}



int main(void)
{
	cin>>N>>M;
	memset(visited, -1, sizeof(visited));
	memset(graph,0,sizeof(graph));
	
	int start_x;
	int start_y;
	for(int i =0; i< N; i++)
	{
		for(int j =0; j<M; j++)
		{
			cin>>graph[i][j];
			if(graph[i][j] == 2)
			{
				start_x = i;
				start_y = j;
			}
			if(graph[i][j] == 0)
			{
				visited[i][j] = 0;
			}
		}
	}
	
	
	bfs(start_x,start_y);
	
	for(int i =0; i< N; i++)
	{
		for(int j =0; j<M; j++)
		{
			cout<<visited[i][j]<<' ';
			
		}
		cout<<endl;
	}
	

	
	
}
