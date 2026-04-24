#include <bits/stdc++.h>
using namespace std;


struct solution {
    int absFeat;
    int feat;
};


bool compare(const solution &a, const solution &b) {
    
    return a.absFeat < b.absFeat;
}

int main() {
    int N;
    cin >> N;

    vector<solution> X(N);

    for (int i = 0; i < N; i++) {
        cin >> X[i].feat;
        X[i].absFeat = abs(X[i].feat);
    }
    
    stable_sort(X.begin(), X.end(), compare);

    int temp;
    int minIdx = 0;
    for(int i = 0; i < N-1; i++)
    {
        if(abs(X[minIdx].feat + X[minIdx+1].feat) > abs(X[i].feat + X[i+1].feat))
        {
            minIdx = i;
        }
        if(X[minIdx].feat + X[minIdx+1].feat == 0)
        {
            break;
        }
    }
    
    if(X[minIdx].feat > X[minIdx+1].feat)
    {
        cout<<X[minIdx+1].feat<<" "<<X[minIdx].feat<<"\n";
    }
    else
    {
        cout<<X[minIdx].feat<<" "<<X[minIdx+1].feat<<"\n";
    
    }


    return 0;
}
