#include <bits/stdc++.h>

using namespace std;

//https://www.acmicpc.net/board/view/27386
/*
1) 완전 탐색으로 모든 벽을 부수는 경우를 확인하기에는 시간이 부족함
2) 좌표뿐만 아니라 벽을 부쉈는지 안부쉈는지도 이제 저장을 해야한다.

아악 진짜 너무 어렵ㄴ다ㅏ아
*/
#define MAX 1000

int graph[MAX+1][MAX+1];
queue<pair<pair<int,int>,int>> q;
int visited[MAX+1][MAX+1][2];
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};

int N, M;

int bfs()
{
	
	while(!q.empty())
	{
		int x = q.front().first.first;
		int y = q.front().first.second;
		int block = q.front().second;
		
		q.pop();
		if(x == N && y == M)
		{
			return visited[x][y][block];
		}
		
		for(int i = 0; i<4; i++)
		{
			int next_x = x + dx[i];
			int next_y = y + dy[i];
			
			
			if(next_x < 1 || next_x > N || next_y < 1 || next_y > M)
			{
				continue;
			}
			
			if(graph[next_x][next_y] == 1 && block)
			{
				visited[next_x][next_y][block-1] = visited[x][y][block] + 1;
				
				q.push({{next_x,next_y} , block-1});
				
			}
			if(graph[next_x][next_y] == 0 && visited[next_x][next_y][block] == 0)
			{
				visited[next_x][next_y][block] = visited[x][y][block] + 1;
				q.push({{next_x,next_y} , block});
			}
			
			/*
			if(visited[next_x][next_y] == false && graph[next_x][next_y] == 0)
			{
				printf("!!");
				visited[next_x][next_y] = true;
				graph[next_x][next_y] = graph[x][y] + 1;
				q.push({next_x, next_y});
			}
			*/
		}
	}
	
	return -1;
}



int main(void)
{
	cin>>N>>M;
	int A, B;
	
	for(int i =1; i< N+1; i++)
	{
		for(int j =1; j<M+1; j++)
		{
			scanf("%1d" , &graph[i][j]);
	
			
		}
	}
	
	
	
	q.push({{1,1} , 1});
	visited[1][1][1] = 1;
	
	
	int result = bfs();

	
	
	cout<<result<<'\n';

	
	

	
	
}
