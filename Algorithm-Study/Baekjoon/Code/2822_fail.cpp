#include <bits/stdc++.h>

using namespace std;

//2822 점수 계산
//https://www.acmicpc.net/problem/2822
//참고한 블로그 https://jaimemin.tistory.com/843

//벡터를 쓰는 것에 익숙해져야겠다.
//

int main(void)
{
	
	vector<pair<int, int>> score(8);
	//{score, idx}
	
	for(int i =0; i< 8; i++)
	{
		cin>>score[i].first;
		score[i].second = i+1;
	}
	//입력을 받는데, 점수는 1번란에, 순서는 2번란에 가진 자료구조를 하나 만들었다.
	
	sort(score.begin(), score.end() , greater<pair<int, int>>());
	//정렬 한번 떄려주는데, 점수대로 정리한다.
	//근데 순번도 같이 따라감.
	//즉 
	//30 10 50 40 60
	//1  2  3  4  5
	//가
	//60 50 40 30 10
	//5  3  4  1  2
	//가 되었다는 뜻.
	
	int totalScore = 0;
	vector<int> idx;
	//순번을 출력하기 위해 저장할 벡터 하나 생성
	
	for(int i =0; i< 5; i++)
	{
		totalScore += score[i].first;
		idx.push_back(score[i].second);
	}
	//push_back -> vector에 요소를 추가하는 함수
	
	cout<<totalScore<<"\n";
	
	sort(idx.begin(), idx.end());
	// 오름차순으로 정렬.
	
	
	for(int i = 0; i< idx.size(); i++)
	{
		cout<<idx[i] << " ";
	}
	
	
	cout<<"\n";
	return 0;
}
