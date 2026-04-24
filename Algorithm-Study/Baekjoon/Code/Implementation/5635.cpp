#include<iostream>
#include<string>
#include<stack>

using namespace std;


//5635 생일
//https://www.acmicpc.net/problem/5635


int main(void)
{
	int T;
	cin>>T;
	
	string name[100];
	int birthDay[100];
	
	int mostIdx = 0;
	int leastIdx = 0;

	
	
	for(int i = 0; i < T; i++)
	{
		int temp;
		birthDay[i] = 0;
		cin>>name[i];
		cin>>temp;//day
		birthDay[i] += temp;
		cin>>temp;//month;
		birthDay[i] += temp*100;
		cin>>temp;//year
		birthDay[i] += temp*10000;

	}
	
	for(int i = 1; i < T; i++)
	{
		if(birthDay[leastIdx] < birthDay[i])
		{
			leastIdx = i;
		}
		if(birthDay[mostIdx] > birthDay[i])
		{
			mostIdx = i;
		}
	}
	
	cout<<name[leastIdx]<<'\n';
	cout<<name[mostIdx]<<'\n';
	
	
    return 0;
	
}
