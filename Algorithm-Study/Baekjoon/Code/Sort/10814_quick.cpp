#include <bits/stdc++.h>

using namespace std;

int age = 0;
int ageArray[100001];
string nameArray[100001];
string name = "";

int N = 0;

int DataSwap(int *data , int a, int b)
{
    int temp;
    string tempName;

    tempName = nameArray[a];
    nameArray[a] = nameArray[b];
    nameArray[b] = tempName;

    temp = data[a];
    data[a] = data[b];
    data[b] = temp;
}
void quickSort(int *data, int start, int end)
{
    if (start >= end)
        return;
    int pivot = start; // 기준 값
    int i = start + 1;
    int j = end;

    while (i <= j)
    {
        while (data[i] <=
               data[pivot]) // 키 값보다 큰 값 만날때까지 오른쪽으로 이동
            i++;
        while (data[j] >= data[pivot] &&
               j > start) // 키 값보다 작은 값 만날 때까지 왼쪽으로 이동
            j--;
        if (i > j) // 현재 엇갈린 상태면 pivot 값 교체
        {
            DataSwap(data, j, pivot);
        }
        else if (i < j)
        {
            DataSwap(data, j, i);
        }
        // 재귀 호출
        quickSort(data, start, j - 1);
        quickSort(data, j + 1, end);
    }
}

int main()
{
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> age;
        cin >> name;

        ageArray[i] = age;
        nameArray[i] = name;
    }

    quickSort(ageArray, 0, N);


    for(int i = 1; i < N+1; i++)
    {
        cout<<ageArray[i]<<" "<<nameArray[i]<<"\n";
    }
}

