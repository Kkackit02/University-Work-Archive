#include <bits/stdc++.h>

using namespace std;



int graph[101][101][101];
queue<tuple<int, int,int>> q;
bool visited[101][101][101];
int dx[] = {0,0,0,0,-1,1};
int dy[] = {0,0,1,-1,0,0};
int dz[] = {1,-1,0,0,0,0}; 
int N, M, H;

void bfs()
{
	while(!q.empty())
	{
		int x = get<0>(q.front());
		int y = get<1>(q.front());
		int z = get<2>(q.front());
		q.pop();
		visited[x][y][z] = true;
		for(int i = 0; i<6; i++)
		{
			int next_x = x + dx[i];
			int next_y = y + dy[i];
			int next_z = z + dz[i];
			
			if(next_x < 0 || next_x >= N || next_y <0 || next_y >= M || next_z < 0 || next_z >= H)
			{
				continue;
			}
			if(graph[next_x][next_y][next_z] == 0 && visited[next_x][next_y][next_z] == false)
			{
				graph[next_x][next_y][next_z] = graph[x][y][z] + 1;
				q.push(make_tuple(next_x, next_y , next_z));
				//cout<<next_x<<":"<<next_y<<'\n';
				visited[next_x][next_y][next_z] = true;
			}
			
		}
	}
	
}



int main(void)
{
	cin>>M>>N>>H;
	memset(visited, false, sizeof(visited));
	memset(graph,0,sizeof(graph));
	
	
	for(int h = 0; h< H; h++)
	{
		for(int i =0; i< N; i++)
		{
			for(int j =0; j<M; j++)
			{
				cin>>graph[i][j][h];
				if(graph[i][j][h] == 1)
				{
					q.push(make_tuple(i,j,h));
				}
				if(graph[i][j][h] == -1)
				{
					visited[i][j][h] == true;
				}
			}
		}
	}
	
	bfs();
	
	
	int result = 0;
	

	
	for(int h = 0; h< H; h++)
	{
		for(int i =0; i< N; i++)
		{
			for(int j =0; j<M; j++)
			{
				if(graph[i][j][h] == 0)
				{
					result = -1;
					cout<<result<<'\n';
					return 0;
				}
				else
				{
					if(result < graph[i][j][h])
					{
						result = graph[i][j][h];
					}
				}
			}
		}
	}
	
	
	cout<<result-1<<'\n';

	
	
}
