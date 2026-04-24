#include <bits/stdc++.h>

using namespace std;



int graph[101];
int ladderAndSnake[101];
queue<int> q;
bool visited[101];
int dx[] = {1,2,3,4,5,6};

int N, M;

void bfs()
{
	
	while(!q.empty())
	{
		int x = q.front();
		q.pop();
		visited[x] = true;
		for(int i = 0; i<6; i++)
		{
			int next_x = x + dx[i];

			if(next_x < 1 || next_x > 100)
			{
				continue;
			}
			while(ladderAndSnake[next_x] != 0)
			{
				next_x = ladderAndSnake[next_x];
			}
			if(visited[next_x] == false)
			{
				visited[next_x] = true;
				graph[next_x] = graph[x] + 1;
				q.push(next_x);
			}
		
			
		}
	}
	
}



int main(void)
{
	cin>>N>>M;
	int A, B;
	
	memset(ladderAndSnake, 0, sizeof(ladderAndSnake));
	
	for(int i = 1; i<N+1; i++)
	{
		cin>>A;
		cin>>B;
		ladderAndSnake[A] = B;
	}
	
	for(int i = 1; i<M+1; i++)
	{
		cin>>A;
		cin>>B;
		ladderAndSnake[A] = B;
	}
	
	memset(visited, false, sizeof(visited));
	
	
	q.push(1);
	graph[1] = 0;
	
	bfs();
	
	int result = 0;
	
	result = graph[100];
	
	
	cout<<result<<'\n';

	
	
}
