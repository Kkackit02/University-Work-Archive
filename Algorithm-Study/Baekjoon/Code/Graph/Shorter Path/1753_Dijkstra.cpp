#include <bits/stdc++.h>

using namespace std;


priority_queue<pair<int, int>> PQ;
#define MAX 20001
#define INF 987654321

int V, E ,K;
int Dist[MAX];
vector<pair<int, int>> Vertex[MAX];

int main(void)
{
	cin>>V>>E;
	cin>>K;
	
	
	int u,v,w;
	
	for(int i = 0; i < E; i++)
	{
		cin>>u>>v>>w;
		Vertex[u].push_back(make_pair(v,w));
	}
	for(int i =1; i<= V; i++)
	{
		Dist[i] = INF;
	}
	
	
	
	PQ.push(make_pair(0, K));
	Dist[K] = 0;
	
	while(PQ.empty() == 0)
	{
		int cost = -PQ.top().first;
		int cur = PQ.top().second;
		
		PQ.pop();
		
		for (int i = 0; i < Vertex[cur].size(); i++)
		{
			int next= Vertex[cur][i].first;
			int nextCost = Vertex[cur][i].second;
			
			if(Dist[next] > cost + nextCost)
			{
				Dist[next] = cost + nextCost;
				PQ.push(make_pair(-Dist[next], next));
			}
		}
	}
	
	for( int i = 1; i<= V; i++)
	{
		if(Dist[i] == INF)
		{
			cout<<"INF"<<'\n';
		}
		else if( Dist[i] != INF)
		{
			cout<<Dist[i]<<'\n';
		}
	}

}