#include <bits/stdc++.h>

using namespace std;


#define MAX 101
int graph[MAX+1][MAX+1];
int floodingLand[MAX+1][MAX+1];
bool visited[MAX+1][MAX+1];
queue<pair<int, int>> q;
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

int  N;

int temp;
int numberOfLand = 0;

void bfs(int x, int y )
{
	
	
	
	q.push({x,y});
	
	visited[x][y] = true;
	
	while(!q.empty())
	{
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
	
		
		for(int i = 0; i<4; i++)
		{
			int next_x = x + dx[i];
			int next_y = y + dy[i];
			
		
			if(next_x < 0 || next_x >= N || next_y <0 || next_y >= N)
			{
				continue;
			}
			if(floodingLand[next_x][next_y] && !visited[next_x][next_y])
			{
				visited[next_x][next_y] = true;
				//graph[next_x][next_y] = graph[x][y] + 1;
				q.push({next_x, next_y});	
			}
		}
	}
}



int main(void)
{
	
	int maxWaterLevel = -1;
	cin>>N;
	
	for(int i =0; i< N; i++)
	{
		for(int j =0; j<N; j++)
		{
			//scanf("%1d" , &graph[i][j]);
			//1d로 하면 10 이상의 값이 들어올때 오류가 난다^^..
			// -> cin>>graph[i][j];
			cin>>graph[i][j];
			maxWaterLevel = max(graph[i][j], maxWaterLevel);
		}
	}
	
	
	for(int h = 0; h <= maxWaterLevel; h++)
	{
		for (int i = 0; i < N; i++) 
		{
            for (int j = 0; j < N; j++) 
			{
                if (graph[i][j] < h) 
				{
                    floodingLand[i][j] = 0;
                }
                else 
				{
                    floodingLand[i][j] = 1;
                }
            }
        }
		
		
		
		
		
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < N; j++) 
			{
				if(floodingLand[i][j] && !visited[i][j])
				{
					bfs(i,j);
					temp++;
				}
			}
		}	
		
		if(temp > numberOfLand)
		{
			numberOfLand = temp;
		}
		
		temp = 0;
		
		
		memset(floodingLand, 0, sizeof(floodingLand));
		memset(visited, 0, sizeof(visited));
		
			
	}
		
	cout<<numberOfLand<<'\n';
	
	
	
}
