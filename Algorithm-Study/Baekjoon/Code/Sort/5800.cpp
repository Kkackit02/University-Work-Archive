#include <bits/stdc++.h>

using namespace std;



int main(void)
{
	int class_num = 0;
	int student_num = 0;
	
	int ScoreArray[50];
	int bestScoreArray[100];
	int worstScoreArray[100];
	int bestIntervalArray[100];
	cin>>class_num;
	
	
	
	
	int bestTemp = -1;
	int worstTemp = 101;
	int bestInterval = 0;
	for(int i = 0; i<class_num; i++)
	{

		bestTemp = -1;
		worstTemp = 101;
		bestInterval = 0;
		//memset(ScoreArray, 0, 50 * sizeof(int));
		for(int j = 0; j< 50; j++)
		{
			ScoreArray[j] = 0;
		}
		
		cin>>student_num;
		for(int j = 0; j < student_num; j++)
		{
			cin>>ScoreArray[j];

			if(ScoreArray[j] >= bestTemp)
			{
				bestTemp = ScoreArray[j];
			}
			
			if(ScoreArray[j]<=worstTemp)
			{
				worstTemp = ScoreArray[j];
			}
		}
		
		bestScoreArray[i] = bestTemp;
		worstScoreArray[i] = worstTemp;
		sort(ScoreArray , ScoreArray+student_num, greater<int>());
		
		for(int j = 0; j<student_num; j++)
		{
			if(j+1 != student_num)
			{
				if(bestInterval <= (ScoreArray[j] - ScoreArray[j+1]))
				{
					bestInterval = ScoreArray[j] - ScoreArray[j+1];
					bestIntervalArray[i] = bestInterval;
				}
			}
			
		}
	}
	
	for(int i = 0; i < class_num; i++)
	{
		cout<<"Class "<<i+1<<'\n';
		printf("Max %d, Min %d, Largest gap %d\n", 
			  bestScoreArray[i], worstScoreArray[i], bestIntervalArray[i]);
		
	}
}
