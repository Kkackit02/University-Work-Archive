#include<bits/stdc++.h>

using namespace std;

map<string, int> m; // 번호가 주어졌을때를 위한 map
string s[1000000]; // 이름이 주어졌을때를 위한 배열
int main(void) 
{
    
    ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

    int N,M;
    
    cin>>N>>M;
 
    string str;
    for(int i = 1; i <= N; i++)
    {
        cin>>str;
        s[i] = str;
        m[str] = i;
    }
    for(int i = 1; i<=M; i++)
    {
        cin>>str;
        if(isdigit(str[0])) // 입력이 숫자라면
        {
            cout<<s[stoi(str)]<<'\n';
        }
        else 
        {
            cout<<m[str]<<'\n';
        }
    }
}  