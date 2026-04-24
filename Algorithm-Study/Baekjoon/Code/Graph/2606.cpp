#include <bits/stdc++.h>

using namespace std;


vector<int> vec[102];
vector<int> res_dfs;

bool visited[102];

int result = 0;

void dfs(int value)
{
	
	visited[value] = true;
	result++;
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
	
	cin>>N>>M;
	
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
	
	memset(visited, false, sizeof(visited));
	dfs(1);
	
	result--;
	cout<<result;
	cout<<'\n';
	
	
}
