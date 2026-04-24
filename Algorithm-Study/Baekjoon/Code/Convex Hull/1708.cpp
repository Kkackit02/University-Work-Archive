#include<bits/stdc++.h>

using namespace std;

/*
볼록껍질(Convex Hull)

점을 하나 잡고, 다른 모든 점에 대해서 선분을 걸어보고
다른 점을 r로 둬서, ccw 연산을 해본다
모든 점들이 다 같은 방향으로 회전하고있으면 OK!
CCW? : Counter - Clock - Wise

A(x1, y1), B(x2, y2), C(x3,y3)가 있을때
A,B,C의 방향 관계를 구하는 것으로

A,B,C 순서로 가는게 좌회전인지 우회전인지 확인하는 알고리즘
x1y2 + x2y3 + x3y1 - (x2y1 + x3y2 + x1y3) 

이 값이 양수이면 시계 반대(좌회전), 
0이면 평행, 
음수이면 시계(우회전)

graham scan
- 가장 y좌표가 낮은 값 고르기(같으면 x좌표가 가장 작은 값)
- 그 점을 기준으로 모든 점과의 극값을 구해서 오름차순으로 작업을 수행할 것.
- 스택에 집어넣는데, 2개를 넣고, 그 다음에 나오는 값은 방향을 검사해서, 좌회전이면(CCW) 스택에 집어넣어준다.
- 만약 스택이 아니라면 마지막에 넣었던 스택값을 빼낸다.이를 반복 수행해 모든 점을 검사하면 끝.
*/

pair<long long, long long> base;

double calculatePolarAngle(pair<long long, long long> base, pair<long long, long long> point ) 
{
    long long dx = point.first - base.first;
    long long dy = point.second - base.second;
    return atan2(dy, dx); // 라디안 단위의 극각 반환
}

bool compare(pair<long long, long long>&a,  pair<long long, long long>  &b) 
{
    
if(a.second == b.second)
{
    return a.first < b.first;
}

    return a.second < b.second;
}

bool polaCompare(pair<long long, long long>&a,  pair<long long, long long>&b) 
{
    double aP =  calculatePolarAngle(base,a);
    double bP = calculatePolarAngle(base,b);

    if(aP == bP)
    {
        return (a.first - base.first) * (a.first - base.first) +
               (a.second - base.second) * (a.second - base.second) <
               (b.first - base.first) * (b.first - base.first) +
               (b.second - base.second) * (b.second - base.second);
    }

    return aP<bP;
}


long long CCW(pair<long long,long long> p1 , pair<long long,long long> p2 , pair<long long,long long> p3)
{
    return p1.first*p2.second + p2.first*p3.second + p3.first*p1.second - (p2.first*p1.second + p3.first*p2.second + p1.first*p3.second);
}

int main(void)
{
    long long N;
    cin>>N;

    vector<pair<long long, long long>> data;

    stack<pair<long long, long long>> result;

    long long x, y;
    for(long long i = 0; i < N; i++)
    {
        cin>>x>>y;
        data.push_back(make_pair(x,y));
    }
    sort(data.begin(), data.end(), compare);
    base = data[0];
    sort(data.begin()+1, data.end() , polaCompare);


/*
    for(long long i = 0; i < N; i++)
    {
        cout<<data[i].first <<" "<<data[i].second<<endl;
    }
    cout<<endl;
*/
    pair<long long, long long> p1;
    pair<long long, long long> p2;


    result.push(data[0]);
    result.push(data[1]);

    long long size = 0;
    for(long long i = 2; i < N; i++)
    {
        while(result.size() >= 2)
        {
            p2 = result.top();
            result.pop();
            p1 = result.top();  
            



            //cout<<i <<" "<<CCW(p1, p2 , data[i])<<endl;

            if(CCW(p1, p2 , data[i]) > 0)
            {
                result.push(p2);
                break;
            }
            
        }
        result.push(data[i]);
        
        
    }

    
    cout<<result.size()<<endl;

}