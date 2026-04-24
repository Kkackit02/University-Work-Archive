#include <bits/stdc++.h>

using namespace std;


vector<int> vec[1002];
vector<int> res_bfs;
vector<int> res_dfs;

bool visited[1002];



void bfs(int value)
{
	queue<int> queue;
	
	queue.push(value);
	visited[value] = true;
	while(!queue.empty())
	{
		int x = queue.front();
		queue.pop();
		res_bfs.push_back(x);
		
		for(int i = 0; i< vec[x].size(); i++)
		{
			if(!visited[vec[x][i]])
			{
				queue.push(vec[x][i]);
				visited[vec[x][i]] = true;
			}
		}
	}
}

void dfs(int value)
{
	
	visited[value] = true;
	res_dfs.push_back(value);
	
	for(int i = 0; i < vec[value].size(); i++)
	{
		if(!visited[vec[value][i]])
		{
			dfs(vec[value][i]);
		}
	}
}




int main(void)
{
	int N;
	int M;
	
	int V;
	
	cin>>N>>M>>V;
	
	int a,b;
	for(int i = 1; i<=M; i++)
	{
		cin>>a>>b;
		
		vec[a].push_back(b);
		vec[b].push_back(a);
	}

	for (int i = 1; i <= N; i++)
	{
        sort(vec[i].begin(), vec[i].end());
    }
	bfs(V);
	memset(visited, false, sizeof(visited));
	dfs(V);
	
	
	for(int i = 0; i < res_dfs.size(); i++)
	{
		cout<<res_dfs[i]<<' ';
	}
	cout<<'\n';
	for(int i = 0; i < res_bfs.size(); i++)
	{
		cout<<res_bfs[i]<<' ';
	}
	cout<<'\n';
	
	
}
