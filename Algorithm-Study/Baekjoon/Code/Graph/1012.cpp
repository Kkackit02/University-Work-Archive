#include <bits/stdc++.h>

using namespace std;


vector<int> res_dfs;


int graph[51][51];
int result = 0;
int cnt = 0;

int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
int M , N, K;
void dfs(int x, int y)
{
	
	for(int i = 0; i<4; i++)
	{
		int next_x = x + dx[i];
		int next_y = y + dy[i];
		
		if(next_x < 0 || next_x >= M || next_y <0 || next_y >=N)
		{
			continue;
		}
		if(graph[next_x][next_y] == 1)
		{
			cnt++;
			graph[next_x][next_y] = 2;
			dfs(next_x, next_y);
		}
	}
}




int main(void)
{
	
	
	string input;
	int T;
	cin>>T;
	
	for(int t = 0; t<T; t++)
	{
		memset(graph, 0, sizeof(graph));
		res_dfs.clear();
		cin>>M;
		cin>>N;
		cin>>K;


		int a, b;
		for(int i = 0; i < K; i++)
		{
			cin>>a>>b;
			
			graph[a][b] = 1;
			//cout<<"GET!"<<a<<":"<<b<<'\n';
			//cout<<"this!"<<graph[a][b]<<'~'<<a<<":"<<b<<'\n';
			
		}

	
		for(int i =0; i<M; i++)
		{
			for(int j = 0; j<N; j++)
			{
				if(graph[i][j] == 1)
				{
					cnt = 1;
					graph[i][j] = 2;
					dfs(i,j);
					res_dfs.push_back(cnt);
				}
			}
		}

		cout<<res_dfs.size()<<'\n';
		sort(res_dfs.begin(), res_dfs.end());


	}
	
	
}
