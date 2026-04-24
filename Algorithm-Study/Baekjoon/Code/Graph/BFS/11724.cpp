#include <bits/stdc++.h>

using namespace std;
//반례모음 https://www.acmicpc.net/board/view/77198

vector<int> vec[1001];
bool visited[1001];

int K , V, E;
int bfs(int value)
{
	queue<int> queue;
	queue.push(value);
	visited[value] = true;
	
	while(!queue.empty())
	{
		int x = queue.front();
		queue.pop();
	
		
		for(int i = 0; i< vec[x].size(); i++)
		{
			if(!visited[vec[x][i]])
			{
				queue.push(vec[x][i]);
				visited[vec[x][i]] = true;
				
			}
			
		}
		
	}
	
	return 0;
}
bool compare(int a, int b)
{
	return a>b;
}

int main(void)
{

	cin>>V>>E;
	int a, b;
	for(int j = 0; j < E; j++)
	{
		cin>>a>>b;
		vec[a].push_back(b);
		vec[b].push_back(a);
	}
	

	for (int i = 1; i <= V; i++)
	{			
		sort(vec[i].begin(), vec[i].end());
	}
		
	int cnt = 0;
	for(int j =1; j<= V; j++)
	{
		if(!visited[j])
		{
			bfs(j);
			cnt++;
		}	
	}	
		
	cout<<cnt<<endl;;
	
	
	
	
	return 0;
	
}