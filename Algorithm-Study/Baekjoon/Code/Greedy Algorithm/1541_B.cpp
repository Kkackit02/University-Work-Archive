#include <bits/stdc++.h>
#include <sstream> 
using namespace std;


int main(void)
{
	
	string text;
	bool minusChecker = false;
	int result = 0;
	string temp = "";
	
	
	
	cin>>text;
	
	for(int i =0; i<= text.size(); i++)
	{
		if(text[i] == '+' || text[i] == '-' || text[i] == '\0')
		{
			if(minusChecker == true)
			{
				result -= stoi(temp);
			}
			else
			{
				result += stoi(temp);
			}
			
			temp = "";
			if(text[i] == '-')
			{
				minusChecker = true;
			}
		}
		else
		{
			temp += text[i];
		}
	}
	
	cout<<result<<endl;
}


