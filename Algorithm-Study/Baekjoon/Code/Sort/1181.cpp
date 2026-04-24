#include <bits/stdc++.h>
using namespace std;

struct Member {
    int length;
    string word;  
    
    
    // 동등 비교 연산자 정의 (구조체의 == 조건 정의)
    bool operator==(const Member& other) const {
        return word == other.word;
    }
};

bool compare(const Member &a, const Member &b) {
    if (a.length == b.length) {
        return a.word < b.word; 
    }
    return a.length < b.length;
}

int main() {
    int N;
    cin >> N;

    vector<Member> members(N);

    for (int i = 0; i < N; i++) { 
        cin >> members[i].word;
        members[i].length = members[i].word.length();
    }
    
    stable_sort(members.begin(), members.end(), compare);
    members.erase(unique(members.begin(), members.end()), members.end());

    for(int i =0; i < members.size(); i++)
    {
        cout<<members[i].word<<"\n";
    }

    return 0;
}
