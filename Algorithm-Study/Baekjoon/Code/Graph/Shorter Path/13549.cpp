#include <bits/stdc++.h>

using namespace std;


priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> PQ;
#define MAX 100001

int dist[MAX];
int visited[MAX];
vector<pair<int, int>> Vertex[MAX];

int main(void)
{
	int start , end;
	cin>>start>>end;
    // make node & edge
	for(int i =0; i< MAX; i++)
	{
		visited[i] = false;
        //node Dist reset;
	}
	
	//우선순위 Q에 시작 노드 설정
	PQ.push(make_pair(0, start));
	visited[start] = true;
	
	while(PQ.empty() == 0) //우선순위 큐가 빌때까지 반복할 건데..
	{
		int cost = PQ.top().first;
		int cur = PQ.top().second;
		//우선 순위 큐에서 첫번쨰 값은 지금까지 든 비용, cur은 지금 주소

		if(cur == end)
		{
			break;
		}
		PQ.pop();
		if(cur < MAX && !visited[cur*2])
		{
			visited[cur*2] = true;
			PQ.push(make_pair(cost, 2*cur));
		}
		if(cur+1 < MAX && !visited[cur+1])
		{
			visited[cur+1] = true;
			PQ.push(make_pair(cost+1, cur+1));
		}
		if(cur -1 >= 0 && !visited[cur-1])
		{
			visited[cur-1] = true;
			PQ.push(make_pair(cost+1, cur-1));
		}
		

	}
    cout<<PQ.top().first<<"\n";
}