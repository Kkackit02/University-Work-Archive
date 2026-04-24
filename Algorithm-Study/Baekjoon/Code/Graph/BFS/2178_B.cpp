#include <bits/stdc++.h>

using namespace std;



int graph[101][101];


int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

int M , N, K;
int bfs(int x, int y)
{
	
	queue<pair<int, int>> q;
	
	q.push({x,y});
	
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
			if(graph[next_x][next_y] == 0)
			{
				continue;
			}
			if(graph[next_x][next_y] == 1)
			{
				graph[next_x][next_y] = graph[x][y] + 1;
				q.push({next_x, next_y});	
			}
		}
	}
	
	return graph[N-1][M-1];
	
}



int main(void)
{
	
	
	cin>>N>>M;
	
	for(int i =0; i< N; i++)
	{
		for(int j =0; j<M; j++)
		{
			scanf("%1d" , &graph[i][j]);
		}
	}

	
		
		
	cout<<bfs(0,0)<<'\n';

	
	
}
