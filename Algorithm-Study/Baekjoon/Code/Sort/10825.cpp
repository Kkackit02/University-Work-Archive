#include <bits/stdc++.h>
using namespace std;

struct Member {
    int korean;
    int english;
    int math;
    string name;
};

bool compare(const Member &a, const Member &b) {
    if (a.korean == b.korean) 
    {
        if(a.english == b.english)
        {
            if(a.math == b.math)
            {
                return a.name < b.name;
            }
            return a.math > b.math;
        }
        return a.english < b.english; 
    }
    return a.korean > b.korean;
}

int main() {
    int N;
    cin >> N;

    vector<Member> members(N);

    for (int i = 0; i < N; i++) 
    {
        cin >> members[i].name;
        cin >> members[i].korean;
        cin >> members[i].english;
        cin >> members[i].math;
    }

    stable_sort(members.begin(), members.end(), compare);

    for(int i =0; i < N; i++)
    {
        cout<<members[i].name<<"\n";
    }

    return 0;
}
