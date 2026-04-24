#include <bits/stdc++.h>

using namespace std;



int graph[100002];


bool visited[100002];

int dx[] = {-1,1};
int cnt = 0;
int N , K;

int bfs(int x)
{
	
	queue<int> q;
	
	q.push(x);
	int next_x = 0;
	visited[x] = true;
	
	
	
	while(!q.empty())
	{
		int sz=q.size(); // 깊이를 재기 위한 변수
		
		for(int z = 0; z < sz; z++)
		{
			int x = q.front();
			q.pop();

			for(int i = 0; i<3; i++)
			{

				if(i < 2)
				{
					next_x = x + dx[i];
				}
				else
				{
					next_x = x * 2;
				}

				//cout<<"nextX = "<<next_x<<endl;

				if(next_x < 0 || next_x > 100002 )
				{
					continue;
				}
				//cout<<"?"<<next_x<<":"<<graph[next_x]<<endl;
				if(next_x == K)
				{
					cnt++;
					return cnt;
				}

				if(!visited[next_x])
				{
					q.push(next_x);

					visited[next_x] = true;
				}

			}
		}
		cnt++;
		
		
		
	}
	return -1;
}


int main(void)
{
	
	
	cin>>N>>K;
	if(N == K)
	{
		cout<<0<<endl;
		return 0;
	}
	memset(graph, 0, sizeof(graph));
	memset(visited, false, sizeof(visited));
	graph[K] = 1;

	

	cout<<bfs(N)<<'\n';
	
}
