#include <iostream>
#include <bits/stdc++.h>

using namespace std;
int N;
int Q;

vector<int> ResultVector;
int main()
{

    cin >> N >> Q;
    vector<int> players(N);
    vector<int> originPlayers(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> players[i];
    }
    originPlayers = players;
    for (int q = 0; q < Q; q++)
    {
        players = originPlayers;
        int k, newPlayer;
        cin >> k >> newPlayer;
        players.push_back(newPlayer);
        vector<vector<int>> result;
        result.resize(N + 1);

        sort(players.begin(), players.end());

        result[0].push_back(1);
        result[0].push_back(2);
        result[1].push_back(0);
        result[2].push_back(0);
        if(N+1 >= 3)
        {
            result[N].push_back(N - 1);
            result[N].push_back(N - 2);
            result[N - 1].push_back(N);
            result[N - 2].push_back(N);
        }
        
       


        for (int i = 0; i < N + 1; i++)
        {
            vector<int> neighbors;

            for (int j = -2; j < 3; j++)
            {
                if (j == 0)
                    continue;
                if (i + j >= 0 && i + j < N + 1)
                {
                    neighbors.push_back(i + j);
                }
            }
            sort(neighbors.begin(), neighbors.end(), [&](int a, int b)
                 {
                     int diffA = abs(players[i] - players[a]);
                     int diffB = abs(players[i] - players[b]);

                     if (diffA != diffB)
                     {
                         return diffA < diffB; // ���̰� ���� �� �켱
                     }
                     return result[a].size() < result[b].size(); // result size ���� �� �켱
                 });

            int idx = 0;
            while (result[i].size() < 2 && idx < neighbors.size())
            {
                if (result[neighbors[idx]].size() < 2)
                {
                    if (!result[i].empty())
                    {
                        if (result[i].front() == neighbors[idx])
                        {
                            idx++;
                        }
                    }
                    result[i].push_back(neighbors[idx]);
                    result[neighbors[idx]].push_back(i);
                }
                else
                {
                }

                idx++;
            }
        }
        long long resultValue = 0;
        for (int i = 0; i < N + 1; i++)
        {

            if (!result[i].empty())
            {

                //cout << "Index " << i << ": Min Indices = (" << result[i][0] << ", " << result[i][1] << ")" << endl;
                resultValue += abs(players[i] - players[result[i][0]]);
                resultValue += abs(players[i] - players[result[i][1]]);

                //printf("%d���� ���� 1�� %d�� %d�� �������� %d�� ���մϴ�.\n" , i, players[i] , players[result[i][0]] , abs(players[i]-players[result[i][0]]));
                //printf("%d���� ���� 2�� %d�� %d�� �������� %d�� ���մϴ�.\n\n" , i, players[i] , players[result[i][1]] , abs(players[i]-players[result[i][1]]));
            }
        }

        printf("%lld\n", resultValue / 2);
        //ResultVector.push_back(resultValue / 2);
        players.pop_back();
    }

}