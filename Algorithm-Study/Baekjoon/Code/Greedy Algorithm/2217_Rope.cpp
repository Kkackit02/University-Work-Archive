#include<bits/stdc++.h>

using namespace std;

bool compare(int i , int j)
{
	return j<i;
}


int main(void)
{
	int N;
	cin>>N;
	
	vector<int> v;
	int maxMass = 0;
	
	int a;
	for(int i = 0; i < N; i++)
	{
		cin>>a;
		v.push_back(a);
	}
	
	sort(v.begin() , v.end());
	
	for(int i = 0; i < N; i++)
	{
		if(maxMass < (N-i) * v[i])
		{
			maxMass = (N-i)*v[i];
		}
	}
	
	printf("%d\n" , maxMass);

}

/*
로프를 가장 많이 쓰는게 이득이라고 생각했다.

최악의 경우는 로프의 총 개수* 최소 강도 로프의 값이
특정 로프 1개의 강도보다 낮은 경우이다.

이 경우 계산하는 경우가 최대 100,000이므로 제한 시간인 2초안엔 무조건 가능.

그냥 완전탐색으로 계산했다.

그래서 로프를 가장 많이 잡아놓고, 최솟값을 순서대로 하나하나 뺴가면서 계산해봤다.
*/
