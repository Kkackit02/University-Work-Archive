#include<iostream>
#include<string>
#include<stack>

using namespace std;



int main(void)
{
	int T;
	stack<char> stack;
	
	string Result[10000];
	cin>>T;
	cin.ignore();
	for (int i = 0; i < T; i++)
	{
		
		string TestCase;
		getline(cin, TestCase);
		Result[i] = (TestCase+=' ');
		//cout<<"Text : "<<Result[i]<<'\n';
		//Result[i].append("\n");
		
		
	}
	
	for(int i = 0; i<T; i++)
	{
		//cout<<"Size : " << Result[i].size() << endl;
		for (int j = 0; j<Result[i].size(); j++)
		{
			if(Result[i][j] != ' ')
			{
				stack.push(Result[i][j]);
				
				//cout<<"flag1 : "<< Result[i][j] << endl;
			}
			else
			{
				while(!stack.empty())
				{
					cout<<(stack.top());
					stack.pop();
					//cout<<"flag2" << endl;
				}
				
				if(j!=Result[i].size()-1)
				{
					cout<<' ';
				}
				
			}
		}
		cout<<"\n";
		
		
	}
	
	
	
    return 0;
	
}

/*
https://www.acmicpc.net/board/view/22716
https://dbstndi6316.tistory.com/33
vector<string> s;
string str;
while (getline(cin, str))
	s.push_back(str);
*/