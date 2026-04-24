#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int hour = 0;
	int min = 0;
	int second = 0;
	
	int hourLimit;
	int minLimit;
	int secondLimit;
	
	
	scanf("%d: %d: %d" , &hour, &min, &second);
	
	scanf("%d: %d: %d" , &hourLimit, &minLimit, &secondLimit);
	
	int startTime = hour * 3600 + min * 60 + second;
	int limitTime = hourLimit * 3600 + minLimit * 60 + secondLimit;
	
	if(startTime < limitTime)
	{
		int temp = limitTime - startTime;
		hour = temp/3600;
		temp%=3600;
		min = temp/60;
		second = temp % 60;
		
		printf("%02d:%02d:%02d\n", hour , min, second );
	}
	else
	{
		int temp = 86400 - startTime + limitTime;
		hour = temp/3600;
		temp%=3600;
		min = temp/60;
		second = temp % 60;
		
		printf("%02d:%02d:%02d\n", hour , min, second );
		
	}
	
}
