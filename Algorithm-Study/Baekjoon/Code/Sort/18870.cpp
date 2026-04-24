#include <bits/stdc++.h>
using namespace std;

bool compare(const int &a, const int &b) {
    
    return a < b;
}

int main() {
    int N;
    cin >> N;

    vector<int> X(N);

    for (int i = 0; i < N; i++) {
        cin >> X[i];
    }

    
    vector<int> CalX(N);
    CalX = X;
    
    stable_sort(CalX.begin(), CalX.end(), compare);
    CalX.erase(unique(CalX.begin(), CalX.end()) , CalX.end());

    for(int i =0; i < N; i++)
    {
        cout<<lower_bound(CalX.begin(), CalX.end(), X[i]) - CalX.begin()<<" ";
        //lower_bound : 이진탐색기반이어서 성능이 (logN), 찾는 값보다 크거나 같은 값이 제일 처음 등장하는 곳 위치를 return.
    }
    cout<<"\n";

    return 0;
}
