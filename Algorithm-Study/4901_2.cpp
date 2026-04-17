#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int N, Q;

int playerSkills[1000000];
int originPlayerSkill[1000000];
// Function to calculate minimum imbalance for a given array of skills
int calculateMinImbalance() { 
     
    int dp[N+2];
    int minV = INT_MAX;
    dp[0] = 0;  // Base case: 선수 0명을 선택했을 때 불균형은 0
    dp[1] = INT_MAX;
    dp[2] = INT_MAX;
    for (int i = 3; i <= N+2; i++) 
    {  // i는 3부터 시작
        minV = INT_MAX;
        for (int j = 3; j <= 5; j++)  // 3번쨰, 4번쨰, 5번쨰 : 2 3 4 
        {
            if(i-j == 1 || i- j== 2)
            {
                continue;
            }
            
            
            int data = (dp[i - j] + (2 * (playerSkills[i-1] - playerSkills[i-j])));
            //printf("%d : %d : %d \n" , dp[i-j] , playerSkills[i] , playerSkills[i-j+1]);
            minV = min(minV, dp[i - j] + (2 * (playerSkills[i-1] - playerSkills[i-j])));
            //567일때
            //printf("dp[%d] is %d, data is %d \n" ,i, minV , data);
        }
        dp[i] = minV;
        //printf("\n\n");
        //printf("\n\ndp[%d] is %d, dp[n] is %d \n" ,i, dp[i] , dp[N]);
    }
    return dp[N+1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> Q;

    for (int i = 0; i < N; i++) {
        cin >> originPlayerSkill[i];
    }
    
    //sort(playerSkills, playerSkills + N);

    for (int q = 0; q < Q; q++) {
        int k;
        int kSkill;
        cin >> k;
        cin >> kSkill;
        memcpy(playerSkills, originPlayerSkill, sizeof(int) * N+1);
        playerSkills[N] = kSkill;
        
        sort(playerSkills, playerSkills + N+1);
        // Calculate and output the minimum imbalance
        cout << calculateMinImbalance() << '\n';
    }

    return 0;
}