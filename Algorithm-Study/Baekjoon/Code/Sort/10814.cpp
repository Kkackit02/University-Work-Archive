#include <bits/stdc++.h>
using namespace std;

struct Member {
    int order;
    int age;
    string name;
};

bool compare(const Member &a, const Member &b) {
    if (a.age == b.age) {
        return a.order < b.order; 
    }
    return a.age < b.age;
}

int main() {
    int N;
    cin >> N;

    vector<Member> members(N);

    for (int i = 0; i < N; i++) {
        members[i].order = i; 
        cin >> members[i].age;
        cin >> members[i].name;
    }

    stable_sort(members.begin(), members.end(), compare);

    for(int i =0; i < N; i++)
    {
        cout<<members[i].age<<" "<<members[i].name<<"\n";
    }

    return 0;
}
