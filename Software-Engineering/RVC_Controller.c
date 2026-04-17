#include<stdio.h>
   

typedef int bool;
#define false 0
#define true 1
    

bool F = false; // Front Sensor Interface
bool L = false; // Left Sensor Interface
bool R = false; // Right Sensor Interface
bool D = false; // Dust Sensor Interface

bool isCleanerActive = false;
bool isPowerUpActive = false;




int Det_OL()
{
    if (!F) 
    {

        // Stimulus 2: count < 100 && !F && !D
        // Functional requirement 2.1
        return 1;
    } 
    else if (F && !L) 
    {
        // Stimulus 4: count < 100 && F && !L
        // Functional requirement 4.1
        return 2;
    } 
    else if (F && L && !R) 
    {
        // Stimulus 5: count < 100 && F && L && !R
        // Functional requirement 5.1
        return 3;
    } 
    else if (F && L && R) 
    {
        // Stimulus 6: count < 100 && F && L && R
        // Functional requirement 6.1
        
        return 4;
    } 
    else 
    {
        // Default case
    }
    return -1;
}



bool Det_DE()
{
    if(D)
    {
        return true;
    }
    
    return false;
    

}
void Terminate()
{
    printf("Terminate!\n");
}




int main(void)
{

    int obstacle_Location;
    // 0 : Not Work
    // 1 : Move Forward(Clean)
    // 2 : Turn Left
    // 3 : Turn Right
    // 4 : Turn Backward

    bool dust_Existence;
    
    int turnCount = 0;
    char input;


    while(1)
    {
        F = false;
        L = false;
        R = false;
        D = false;
         char input[50]; // 최대 50자까지 입력 가능
    int i;

    printf("Enter commands (e.g., WADP): ");
    fgets(input, sizeof(input), stdin); // 문자열로 입력받음

    // 입력 문자열 처리
    for (i = 0; input[i] != '\0' && input[i] != '\n'; i++) {
        if (input[i] == 'W') 
        {
            F = true; // 전방 장애물
        } 
        else if (input[i] == 'A') 
        {
            L = true; // 왼쪽 장애물
        } 
        else if (input[i] == 'D') 
        {
            R = true; // 오른쪽 장애물
        } 
        else if (input[i] == 'P') 
        {
            D = true; // 먼지 감지
        } 
        else if (input[i] == 'M') {
            printf("System OFF\n");
            return 0; // 프로그램 종료
        }
    }

        obstacle_Location = Det_OL();
        dust_Existence = Det_DE();


        if(turnCount >= 100)
        {
            
        // Stimulus 1: count >= 100, 
        // Functional requirement 1.1
            Terminate();
            break;
        }
        else
        {
            if(obstacle_Location == 1)
            {
                //move forward
                isCleanerActive = true;
                printf("RVC is Moving Forward\n");
                if(dust_Existence)
                {
                    isPowerUpActive = true;
                    printf("Dust Detected , Cleaner Power UP ON\n");
                    
                    // Stimulus 3:  count < 100 && !F && D,
                    // Functional requirement 1.3
                }
                else //Dust not Existence , dust_exitence == false
                {
                    isPowerUpActive = false;
                    printf("Cleaner ON\n");
                    // Stimulus 2: count < 100 && !F && !D,,
                    // Functional requirement 1.3
                }
            }
            else
            {
                printf("Cleaner OFF\n");
                isCleanerActive = false;
                if(obstacle_Location == 2)
                {
                    // turn left
                    // Stimulus 4: count < 100 && F && !L
                    // Functional requirement 4.1
                    printf("RVC is Turning Left\n");
                }
                else if(obstacle_Location == 3)
                {
                    // turn right
                    // Stimulus 5: count < 100 && F && L && !R
                    // Functional requirement 5.1
                    printf("RVC is Turning Right\n");
                }
                else if(obstacle_Location == 4)
                {
                    //turn backward
                    // Stimulus 6: count < 100 && F && L && R
                    // Functional requirement 6.1
                    printf("RVC is Turning BackWard\n");
                }
            }
            
            
        }


        
        //wait(200);
    }

}
