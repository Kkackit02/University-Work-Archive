#include <bits/stdc++.h>

using namespace std;
// compare 같은 함수 쓰는 법을 좀 공부하자.

vector<int> vec[100002];

int visited[100002];
int idx = 1;
void dfs(int value)
{
	
	visited[value] = idx;
	idx++;
	
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
	int R;
	
	cin>>N>>M>>R;
	
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
	
	memset(visited, 0, sizeof(visited));

	dfs(R);
	
	
	
	for(int i =1; i< N+1; i++)
	{
		cout<<visited[i]<<'\n';
	}
	
	
}
