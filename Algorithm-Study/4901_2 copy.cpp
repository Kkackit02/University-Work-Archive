#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int N, Q;

int prefixDp[1000000];
int suffixDp[1000000];
int playerSkills[1000000];
int originPlayerSkill[1000000];
// Function to calculate minimum imbalance for a given array of skills
int calculatePrefixDP()
{

    int minV = INT_MAX;
    prefixDp[0] = 0; // Base case: 선수 0명을 선택했을 때 불균형은 0
    prefixDp[1] = INT_MAX;
    prefixDp[2] = INT_MAX;
    for (int i = 3; i < N; i++)
    { // i는 3부터 시작
        minV = INT_MAX;
        for (int j = 3; j <= 5; j++) // 3번쨰, 4번쨰, 5번쨰 : 2 3 4
        {
            if (i - j == 1 || i - j == 2)
            {
                continue;
            }

            int data = (prefixDp[i - j] + (2 * (playerSkills[i - 1] - playerSkills[i - j])));
            // printf("%d : %d : %d \n" , dp[i-j] , playerSkills[i] , playerSkills[i-j+1]);
            minV = min(minV, data);
            // 567일때
            //printf("dp[%d] is %d, data is %d \n", i, minV, data);
        }
        prefixDp[i] = minV;
        // printf("\n\n");
        //printf("\n\ndp[%d] is %d, dp[n] is %d \n" ,i, prefixDp[i] , prefixDp[N-1]);
    }
    return prefixDp[N + 1];
}

int calculateSuffixDP()
{
    printf("\n\n");
    int minV = INT_MAX;
    suffixDp[N + 1] = 0; // Base case: 선수 0명을 선택했을 때 불균형은 0
    for (int i = N-1; i >= 0; i--)
    { // i는 3부터 시작
        minV = INT_MAX;
        for (int j = 3; j <= 5; j++) // 3번쨰, 4번쨰, 5번쨰 : 2 3 4
        {
            if (i + j == N-2 || i + j == N - 1)
            {
                continue;
            }

            int data = (suffixDp[i + j] + (2 * abs(playerSkills[i - j] - playerSkills[i - 1])));
            // printf("%d : %d : %d \n" , dp[i-j] , playerSkills[i] , playerSkills[i-j+1]);
            minV = min(minV, data);
            // 567일때
            // printf("dp[%d] is %d, data is %d \n" ,i, minV , data);
        }
        suffixDp[i] = minV;
        
        //printf("\n\ndp[%d] is %d, dp[n] is %d \n" ,i, suffixDp[i] , suffixDp[N-1]);
    }
    return suffixDp[N + 1];
}

long long calculateResult(int newSkill)
{
    // 이분 탐색으로 삽입 위치 찾기
    auto it = lower_bound(playerSkills, playerSkills + N, newSkill);
    int index = it - playerSkills;
    printf("새로운 위치는 %d \n", index);
    // 새로운 기여 계산
    long long newContribution = 0;
    if (index > 0)
    {
        newContribution += 2LL * abs(newSkill - playerSkills[index - 1]); // 좌측 기여
    }
    if (index < N)
    {
        newContribution += 2LL * abs(newSkill - playerSkills[index]); // 우측 기여
    }

    // 최종 결과 계산
    long long result = 0;
    if (index > 0)
        result += prefixDp[index];
    if (index < N)
        result += suffixDp[index + 1];
    result += newContribution;

    return result;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> Q;

    for (int i = 0; i < N; i++)
    {
        cin >> playerSkills[i];
    }

    // sort(playerSkills, playerSkills + N);

    sort(playerSkills, playerSkills + N);
    calculatePrefixDP();
    calculateSuffixDP();
    for (int q = 0; q < Q; q++)
    {
        int k;
        int kSkill;
        cin >> k;
        cin >> kSkill;
        int result = calculateResult(kSkill);

        cout<<result<<endl;
    }

    return 0;
}