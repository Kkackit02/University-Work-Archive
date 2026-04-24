#include <bits/stdc++.h>

using namespace std;


#define MAX 302
int graph[MAX+1][MAX+1];
int iceBerg[MAX+1][MAX+1];
bool visited[MAX+1][MAX+1];
queue<pair<int, int>> q;
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

int  N, M;

int temp;
int result = 0;

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
			
		
			if(next_x < 0 || next_x > N || next_y <0 || next_y > M)
			{
				continue;
			}
			if(graph[next_x][next_y] && !visited[next_x][next_y])
			{
				visited[next_x][next_y] = true;
				//graph[next_x][next_y] = graph[x][y] + 1;
				q.push({next_x, next_y});	
			}
			if(graph[next_x][next_y] == 0)
			{
				if(iceBerg[x][y] > 0)
				{
					iceBerg[x][y]--;
				}
			}
		}
	}
}



int main(void)
{

	cin>>N>>M;

	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{		
			if (i == 0 || i == N - 1 || j == 0 || j == M - 1) 
			{
				graph[i][j] = 0;
			}
			cin>>graph[i][j];			
		}			
	}
	
	
	
	copy(&graph[0][0], &graph[0][0] + (MAX*MAX), &iceBerg[0][0]);
	
	
	
	int year = 0;
	int checker = 0;
	while(true)
	{
		checker = 0;
		for (int i = 0; i < N; i++) 
		{
			for (int j = 0; j < M; j++) 
			{
				if(graph[i][j] > checker)
				{
					checker = graph[i][j];
				}
				if(graph[i][j] && !visited[i][j])
				{
					
					
					bfs(i,j);
					/*
					for(int i =0; i< N; i++)
					{
						for(int j =0; j<M; j++)
						{
							cout<<iceBerg[i][j];
						}
						cout<<endl;
					}
					cout<<endl;
					*/
					
					temp++;
					if(temp >= 2)
					{
						result = year;
						cout<<result<<endl;
						return 0;
					}
					
				}
			}
			
		}	
		copy(&iceBerg[0][0], &iceBerg[0][0] + (MAX*MAX), &graph[0][0]);
		temp = 0;
		
		memset(visited, 0, sizeof(visited));
		
		year++;
		if(checker == 0)
		{
			break;
		}
		
			
	}
		
	cout<<0<<'\n';
	
	
	
}
