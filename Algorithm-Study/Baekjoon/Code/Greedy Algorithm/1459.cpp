#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	long X ,Y,W,S;
	cin>>X>>Y>>W>>S;
	
	
	long time = 0;
	
	
	long temp1;
	long temp2;
	long temp3;
	
	temp1 = (X+Y) * W;//전부 평행 이동
	
	
	if((X + Y) % 2 == 0) // 전부 대각선 이동
	{
		temp2 = max(X,Y) * S;
	}
	else // 홀수라면 마지막만 평행이동
	{
		temp2 = (max(X,Y) - 1) * S + W; 
	}
	
	temp3 = min(X,Y) * S + (max(X,Y) - min(X,Y)) * W;
	//작은 수만큼 대각이동하고, 남은만큼 평행이동
	
	time = min(min(temp1, temp2), temp3);
	
	cout<<time<<'\n';
	
	
	
	
}
