#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

long long calculateMinImbalance(const vector<int>& players) {
    int N = players.size();
    vector<long long> DP(N + 1, LLONG_MAX);

    // 초기 조건
    DP[0] = 0;

    // DP 계산
    for (int i = 3; i <= N; i++) {
        for (int j = 3; j <= 5 && i - j >= 0; ++j) {
            DP[i] = min(DP[i], DP[i - j] + 2 * (players[i - 1] - players[i - j]));
        }
    }

    return DP[N];
}

int main() {
    int N, Q;
    cin >> N >> Q;

    vector<int> players(N);
    for (int i = 0; i < N; ++i) {
        cin >> players[i];
    }

    // 정렬
    sort(players.begin(), players.end());

    for (int query = 0; query < Q; query) {
        int k, newPlayer;
        cin >> k >> newPlayer;

        // 새 선수 추가
        players.push_back(newPlayer);
        sort(players.begin(), players.end());

        // 최소 불균형 계산
        long long result = calculateMinImbalance(players);
        cout << result << "\n";

        // 새 선수 제거
        players.pop_back();
    }

    return 0;
}
