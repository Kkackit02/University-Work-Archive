#include<iostream>
#include<algorithm>

using namespace std;

//1427 소트인사이드
//https://www.acmicpc.net/problem/1427

int main(void)
{
	string str;
	
	cin>>str;
	sort(str.begin(), str.end() , greater<char>());
	//자동 오름차순 정렬,
	//greater<char>() 을 붙이면 내림차순이 된다.
	cout<<str;
	
}
