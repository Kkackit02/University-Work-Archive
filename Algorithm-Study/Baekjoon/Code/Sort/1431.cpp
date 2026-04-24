#include <bits/stdc++.h>
using namespace std;


bool compare(const string &a, const string &b) {
    if (a.length() == b.length()) {
        int aValue = 0;
        int bValue = 0;
        for(int i = 0; i < a.length(); i++)
        {
            if(isdigit(a[i]))
                aValue+=(int)a[i] - 48;
        }

        for(int i = 0; i < b.length(); i++)
        {
            if(isdigit(b[i]))
                bValue+=(int)b[i] - 48;
        }

        if(aValue == bValue)
        {
            return a < b;
        }
        return aValue < bValue; 
    }
    return a.length() < b.length();
}

int main() {
    int N;
    cin >> N;

    vector<string> serialNumber(N);

    for (int i = 0; i < N; i++) 
    {
        cin>>serialNumber[i];
    }

    stable_sort(serialNumber.begin(), serialNumber.end(), compare);
    serialNumber.erase(unique(serialNumber.begin(), serialNumber.end()), serialNumber.end());
    for(int i =0; i < N; i++)
    {
        cout<<serialNumber[i]<<"\n";
    }

    return 0;
}
