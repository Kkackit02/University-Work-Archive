#include<bits/stdc++.h>


using namespace std;


int main(void)
{
    string score;


    cin>>score;

    int result_1 = 0;
    int result_2 = 0;

    // switch(score[0]) 을 사용하면 더 편하겟찌?
    
    if(score[0] == 'A')
    {
        result_1 += 4;
    }
    else if(score[0] == 'B')
    {
        result_1 += 3;
    }
    else if(score[0] == 'C')
    {
        result_1 += 2;
    }
    else if(score[0] == 'D')
    {
        result_1 += 1;
    }
    else if(score[0] == 'F')
    {
        cout<<"0.0"<<'\n';
        return 0;
    }
    
    if(score[1] == '+')
    {
        result_2 += 3;
    }
    else if(score[1] == '0')
    {
        result_2 += 0;
    }
    else if(score[1] == '-')
    {
        result_2 += 7;
        result_1 -= 1;
    }



    printf("%d.%d\n", result_1, result_2);
    


}