#include<bits/stdc++.h>


using namespace std;

int main(void)
{
    char matrix[51][51];
    int N,M;

    cin>>N>>M;


    char WB[8][8]
    {
       'W','B','W','B','W','B','W','B',
        'B','W','B','W','B','W','B','W',
        'W','B','W','B','W','B','W','B',
        'B','W','B','W','B','W','B','W',
        'W','B','W','B','W','B','W','B',
        'B','W','B','W','B','W','B','W',
        'W','B','W','B','W','B','W','B',
        'B','W','B','W','B','W','B','W'
    };

    char BW[8][8]
    {
        'B','W','B','W','B','W','B','W',
        'W','B','W','B','W','B','W','B',
        'B','W','B','W','B','W','B','W',
        'W','B','W','B','W','B','W','B',
        'B','W','B','W','B','W','B','W',
        'W','B','W','B','W','B','W','B',
        'B','W','B','W','B','W','B','W',
        'W','B','W','B','W','B','W','B'
    };

    int BWresult[51][51];
    int WBresult[51][51];
    char k;
    for(int i = 0; i< N; i++)
    {
        for(int j = 0; j<M; j++)
        {
            cin>>matrix[i][j];   
            BWresult[i][j] = 0;
            WBresult[i][j] = 0;
        }
    }


  

    for(int i = 0; i+8 <= N; i++)
    {
        for(int j = 0; j+8 <= M; j++)
        {
            for(int k = 0; k < 8; k++)
            {
                for(int l = 0; l < 8; l++)
                {
                    if(matrix[i+k][j+l] != BW[k][l])
                    {
                        BWresult[i][j]++;
                    }
                    if(matrix[i+k][j+l] != WB[k][l])
                    {
                        WBresult[i][j]++;
                    }
                }
            }

        }
    }

    int result = 1111;
    for(int i =0; i<=N-8; i++)
    {
        for(int j = 0; j<=M-8; j++)
        {
            result = min(result, min(BWresult[i][j],WBresult[i][j]));
        }
    }

    cout<<result<<'\n';

}