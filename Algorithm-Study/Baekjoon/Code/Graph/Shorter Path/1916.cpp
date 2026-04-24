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
	
	
	int u,v,w;

    // make node & edge
	for(int i =1; i<= V; i++)
	{
		Dist[i] = INF;
        //node Dist reset;
	}
	
	//edge 연결
	for(int i = 0; i <E; i++)
	{
        //출발번호 , 도착번호 , 비용
		cin>>u>>v>>w;
		Vertex[u].push_back(make_pair(v,w));
	}
	int start , end;
    cin>>start>>end;
	//우선순위 Q에 시작 노드 설정
	PQ.push(make_pair(0, start));
	Dist[start] = 0;
	
	while(PQ.empty() == 0) //우선순위 큐가 빌때까지 반복할 건데..
	{
		int cost = PQ.top().first;
		int cur = PQ.top().second;
		//우선 순위 큐에서 첫번쨰 값은 지금까지 든 비용, cur은 지금 주소

		PQ.pop();

        if(Dist[cur] < cost)
        {
            continue;
        }
		for (int i = 0; i < Vertex[cur].size(); i++) //지금 주소의 노드가 가진 edge의 개수만큼 반복
		{
			int next= Vertex[cur][i].first; // 다음 노드 위치
			int nextCost = Vertex[cur][i].second; // 다음 노드로 가는 비용
			
            //최초start 노드에서 next 노드 까지 가는데 필요한 cost의 최소를 Dist에 저장,
			//
            if(Dist[next] > cost + nextCost) 
			{
				Dist[next] = cost + nextCost;
				PQ.push(make_pair(Dist[next], next));
			}
		}
	}
    cout<<Dist[end]<<"\n";
}