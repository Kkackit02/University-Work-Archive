#include <bits/stdc++.h>

using namespace std;
// compare 같은 함수 쓰는 법을 좀 공부하자.

vector<int> vec[100002];

int visited[100002];
int idx = 1;
void bfs(int value)
{
	queue<int> queue;
	
	queue.push(value);
	visited[value] = idx;
	idx++;
	while(!queue.empty())
	{
		int x = queue.front();
		queue.pop();
		
		for(int i = 0; i< vec[x].size(); i++)
		{
			if(!visited[vec[x][i]])
			{
				queue.push(vec[x][i]);
				visited[vec[x][i]] = idx++;
			}
		}
	}
}


bool compare(int a, int b)
{
	return a>b;
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

	bfs(R);
	
	
	
	for(int i =1; i< N+1; i++)
	{
		cout<<visited[i]<<'\n';
	}
	
	
}
