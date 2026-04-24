#include <bits/stdc++.h>

using namespace std;
//반례모음 https://www.acmicpc.net/board/view/77198

vector<int> vec[200001];
int visited[200001];

int flag = 1;
int K , V, E;
int bfs(int value)
{
	queue<int> queue;
	queue.push(value);
	visited[value] = flag;
	
	while(!queue.empty())
	{
		int x = queue.front();
		queue.pop();
		//cout<<"1. x = "<<x<<": flag = "<<flag<<endl;
		
		if(visited[x] == 1)
		{
			flag = 2;
		}
		else if(visited[x] == 2)
		{
			flag = 1;
		}
		
		
		for(int i = 0; i< vec[x].size(); i++)
		{
			if(!visited[vec[x][i]])
			{
				queue.push(vec[x][i]);
				//cout<<"3. "<<"ADD vec[x][i] : "<<vec[x][i]<<endl;
				visited[vec[x][i]] = flag;
				
			}
			
		}
		
	}
	
	return 0;
}


bool isBiparitie()
{
	for(int i = 1; i<= V; i++)
	{
		for(int j = 0; j < vec[i].size(); j++)
		{
			if(visited[i] == visited[vec[i][j]])
			{
				return 0;
			}
		}
	}
	
	return 1;
}




int main(void)
{

	cin>>K;
	
	int a,b;
	for(int i = 1; i<=K; i++)
	{
		
		cin>>V>>E;
		
		for(int j = 0; j < E; j++)
		{
			cin>>a>>b;
			vec[a].push_back(b);
			vec[b].push_back(a);
		}
		
		for(int j =1; j<= V; j++)
		{
			if(!visited[j])
			{
				bfs(j);
			}
			
		}
		
		
		if(isBiparitie())
		{
			cout<<"YES"<<endl;
		}
		else
		{
			cout<<"NO"<<endl;
		}
		
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i <= V; i++) 
		{
            vec[i].clear();
        }
	}
	
	
	
	
	
	return 0;
	
}