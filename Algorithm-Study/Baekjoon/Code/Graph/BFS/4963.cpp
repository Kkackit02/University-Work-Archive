#include <bits/stdc++.h>

using namespace std;



int graph[51][51];
queue<pair<int, int>> q;
bool visited[51][51];
int dx[] = {0,0,1,-1,1,1,-1,-1};
int dy[] = {1,-1,0,0,1,-1,1,-1};

int N = -1; 
int M = -1;
int result = 0;

void bfs()
{
	while(!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		visited[x][y] = true;
		for(int i = 0; i<8; i++)
		{
			int next_x = x + dx[i];
			int next_y = y + dy[i];

			if(next_x < 0 || next_x >= N || next_y <0 || next_y >= M)
			{
				continue;
			}
			if(graph[next_x][next_y] == 1 && visited[next_x][next_y] == false)
			{
				q.push({next_x, next_y});
				//cout<<next_x<<":"<<next_y<<'\n';
				visited[next_x][next_y] = true;
			}
			
		}
	}
	
	
}



int main(void)
{
	while(true)
	{
		result = 0;
		cin>>M>>N;
		if(M == 0 && N == 0)
		{
			break;
		}
		
		memset(visited, false, sizeof(visited));
		memset(graph,0,sizeof(graph));


		for(int i =0; i< N; i++)
		{
			for(int j =0; j<M; j++)
			{
				cin>>graph[i][j];

			}
		}
		
		

		for(int i =0; i< N; i++)
		{
			for(int j =0; j<M; j++)
			{
				if(visited[i][j] == false && graph[i][j] == 1)
				{
					result++;
					//cout<<" : "<<i<<' '<<j<<endl;
					q.push({i,j});
					bfs();
				}
			}
		}
	
		cout<<result<<'\n';
	}
	
	
	
}
