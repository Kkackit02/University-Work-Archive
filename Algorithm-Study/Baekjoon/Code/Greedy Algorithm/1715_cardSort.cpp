#include<bits/stdc++.h>

using namespace std;


//https://zoosso.tistory.com/993
//우선순위 큐 사용법


/*
1) 큰 수의 사용을 최소화해야한다.
2) N을 우선순위 큐에 넣고 작은수부터 2개씩 뽑은 뒤 그 합을 다시 큐에 넣는다.
3) 큐에 남은 수가 하나가 될때까지 반복하며
2개씩 뽑을때마다 그 두 수의 합을 저장한다(비교 횟수 저장)

4) 출력!

*/
int main(void)
{
	int N;
	cin>>N;
	
	priority_queue<int, vector<int>, greater<int>> pq;
	// greater<int>를 삽입해 오름차순으로 변경
	
	
	
	int a;
	for(int i = 0; i < N; i++)
	{
		cin>>a;
		pq.push(a);
	}
	
	int sum = 0;
	
	int first;
	int second;
	while(pq.size() != 1)
	{
		first = pq.top();
		pq.pop();
		second = pq.top();
		pq.pop();
		
		sum += first+second;
		pq.push(first+second);
	}
	
	cout<<sum<<endl;
	
	
}