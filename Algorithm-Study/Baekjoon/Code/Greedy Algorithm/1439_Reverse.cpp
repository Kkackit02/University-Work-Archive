#include<bits/stdc++.h>

using namespace std;
//처음 글자와 다른 글자가 나왔을때 그 묶음씩 없애주면 된다.
//다른거 건들필요없이 전부 다 묶음 처리 한 다음
//묶음을 하나하나 뒤집으면 된다.
//이때 더 적은 묶음으로 해야하나 싶었는데
//그냥 어떤걸 하던 상관없음

//맨 처음과 맨 끝이 같은 경우의 글자가 더 많은 묶음을 가짐(무조건) 
// 더 적은 묶음을 기준으로 한다고 하면 내 방식처럼 그냥 앞에서부터 다른거 나올때마다 더하면된다.
// 더 많은 묶음을 기준으로 하려면 앞에서부터가 아니라 가운데부터 다 뒤집고 맨처음과 맨 끝을 뒤집으면 됨
// 근데 결국 이 둘다 답이 같게 나오므로..

int main(void)
{
	string s;
	cin>>s;
	
	int s_len = s.length();
	
	char flag = s[0];
	
	int result = 0;
	int i =0;
	while(true)
	{
		
		if(s[i] != flag)
		{
			while(s[i] != flag && i != s_len-1)
			{
				i++;
			}
			
			result++;
		}
		
		i++;
		if(i == s_len)
		{
			break;
		}
		
	}
	
	
	cout<<result<<endl;
	
	
}