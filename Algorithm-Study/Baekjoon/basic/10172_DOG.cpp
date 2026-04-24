#include <bits/stdc++.h>

using namespace std;

 

int main(void)
{
	string s1 =
	"|\\_/| \n"
	"|q p|   /}\n"
	"( 0 )\"\"\"\\\n"
	"|\"^\"`    |\n"
	"||_/=\\\\__|\n";

	copy(s1.begin(), s1.end(), std::ostream_iterator<char>(cout, ""));
    cout << endl;
}
