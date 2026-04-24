#include <bits/stdc++.h>

using namespace std;



int graph[101][101];

bool visited[101][101];
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

int N,M,K;

int target_a, target_b;
int bfs(int x, int y)
{
	
	queue<pair<int, int>> q;
	
	q.push({x,y});
	visited[x][y] = true;
	
	while(!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		
		for(int i = 0; i<8; i++)
		{
			int next_x = x + dx[i];
			int next_y = y + dy[i];

			if(next_x < 0 || next_x >= N || next_y <0 || next_y >= N)
			{
				continue;
			}
			else if(visited[next_x][next_y] == false)
			{
				
				graph[next_x][next_y] = graph[x][y] + 1;
				q.push({next_x, next_y});
				cout<<next_x<<":"<<next_y<<'\n';
				visited[next_x][next_y] = true;
				
			}
			
		}
	}
	
	return graph[target_a][target_b];
	
}



int main(void)
{
	int T = 0;
	cin>>M;
	cin>>N;
	cin>>K;
	
	M--;
	N--;
	
	int now_a,now_b;
	int x1,x2,y1,y2;
	memset(graph,0,sizeof(graph));
	memset(visited, false, sizeof(visited));	
	
	for(int i = 0; i<K; i++)
	{
		cin>>x1>>y1>>x2>>y2;
		
		
		
		for(int k = y1; k < y2; k++)
		{
			for(int l = x1; l < x2; l++)
			{
				graph[l][k]++;
			}
		}
		
	}

	
	for(int i = 0; i< M; i++)
	{
		for(int j = 0; j < N; j++)
		{
			cout<<graph[j][i];
		}
		cout<<endl;
	}
	

	
	
}
