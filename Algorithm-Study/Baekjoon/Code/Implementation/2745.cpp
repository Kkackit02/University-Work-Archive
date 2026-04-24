#include <bits/stdc++.h>

using namespace std;

//A = 65

int main(void)
{
	int T = 0;
	long result = 0;
	string str;
	
	
	cin>>str;
	cin>>T;
	
	
	int len = str.length();
	
	char* char_array = new char[len + 1];
	
	strcpy(char_array, str.c_str());
	
	for(int i = 0; i < len; i++)
	{
		if(char_array[i] >= 65)
		{
			//cout<<((long)char_array[i] - 55) * pow(10,len-1 - i)<<endl;
			result += ((long)char_array[i] - 55) * pow(T,len-1 - i);
		}
		else if(char_array[i] < 65)
		{
			//cout<<((long)char_array[i] - 48) * pow(10,len-1 - i)<<endl;
			result += ((long)char_array[i] - 48) * pow(T,len-1 - i);
		}
	}
	
	cout<<result<<endl;
	
}
