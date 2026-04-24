#include<iostream>
#include<string>
#include<stack>

using namespace std;
//4월 22일 출석인데
//대체 웨 않대?
//?? 왜 스택에 푸시가 안되는거징????  모징??
//4월 23일
//stack에 아무것도 없을때 top가 접근하는 일이 생겨버렸던 것이었다....
// 바보~!

int main(void)
{
	int T;
	int value;
	stack<int> stack;
	string func;
	cin>>T;
	
	for(int i = 0; i < T; i++)
	{
		cin>>func;
		if(func.compare("push") == 0)
		{
			cin>>value;
			stack.push(value);
		}
		else if(func.compare("top") == 0)
		{
			if(stack.empty())
			{
				cout<<"-1"<<'\n';
			}
			else
			{
				cout<<stack.top()<<'\n';
			}
			
		}
		else if(func.compare("size") == 0)
		{
			cout<<stack.size()<<'\n'; 
		}
		else if(func.compare("empty") == 0)
		{
			if(stack.empty())
			{
				cout<<"1"<<'\n';
			}
			else
			{
				cout<<"0"<<'\n';
			}
		}
		else if(func.compare("pop") == 0)
		{
			if(stack.empty())
			{
				cout<<"-1"<<'\n';
			}
			else
			{
				cout<<stack.top()<<'\n';
				stack.pop();	
			}
		}
	}
	
    return 0;
	
}
