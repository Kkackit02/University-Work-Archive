#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> roads;
    vector<int> prices;

    int n;
    cin>>n; // 도로 개수

    for(int i = 1; i < n; i++) {
        int road;
        cin >> road;
        roads.push_back(road);
    }
    for(int i = 0; i < n; i++) {
        int price;
        cin >> price;
        prices.push_back(price);
    }

    long long totalCost = 0;
    int minPrice = prices[0];
    // 각 도로 구간에 대해 최소 비용 계산
    for (int i = 0; i < n - 1; i++) {
        if (prices[i] < minPrice) {
            minPrice = prices[i]; // 지금까지의 최소 주유소 가격 갱신
        }
        totalCost += (minPrice) * roads[i]; // 현재 구간의 비용 계산 및 총 비용에 추가
    }
 
    cout<< totalCost << endl;


    return 0;
}