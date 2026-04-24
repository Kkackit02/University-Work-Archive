#include <bits/stdc++.h>

using namespace std;



int graph[301][301];

bool visited[301][301];
int dx[] = {-2,-2,-1,-1,1,1,2,2};
int dy[] = {1,-1,2,-2,2,-2,1,-1};

int N;

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
	cin>>T;
	
	int now_a,now_b;
	for(int t = 0; t < T; t++)
	{
		
		memset(graph,0,sizeof(graph));
		memset(visited, false, sizeof(visited));	
		cin>>N;
		cin>>now_a>>now_b;
		cin>>target_a>>target_b;
		cout<<bfs(now_a, now_b)<<'\n';
	}

		
	

	
	
}
