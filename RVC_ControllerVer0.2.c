#include <stdio.h>
#include <windows.h>
typedef int bool;
#define false 0
#define true 1
#define Stim2 1
#define Stim4 2
#define Stim5 3
#define Stim6 4

#define CleanerOff 0
#define CleanerOn 1
#define CleanerUp 2



bool F = false; // Front Sensor Interface
bool L = false; // Left Sensor Interface
bool R = false; // Right Sensor Interface
bool D = false; // Dust Sensor Interface
int turnCount = 0;
const int Threshold = 3;
bool isCleanerActive = false;
bool isPowerUpActive = false; // clean이랑 합쳐야함
int cleanerMode;
bool isFrontMotor = false;

int Det_OL()
{
    if (!F)
    {

        // Stimulus 2: count < 100 && !F && !D
        // Functional requirement 2.1
        return Stim2;
    }
    else if (F && !L)
    {
        // Stimulus 4: count < 100 && F && !L
        // Functional requirement 4.1
        return Stim4;
    }
    else if (F && L && !R)
    {
        // Stimulus 5: count < 100 && F && L && !R
        // Functional requirement 5.1
        return Stim5;
    }
    else if (F && L && R)
    {
        // Stimulus 6: count < 100 && F && L && R
        // Functional requirement 6.1

        return Stim6;
    }
    else
    {
        // Default case
    }
    return -1;
}

bool Det_DE()
{
    if (D)
    {
        return true;
    }

    return false;
}
void Terminate()
{
    printf("Terminate!\n");
}
void TurnLeft()
{
    printf("RVC is Turning Left\n");
    Sleep(500);
    turnCount++;
    printf("RVC Turned Left\n");
}
void TurnRight()
{
    printf("RVC is Turning Right\n");
    Sleep(500);
    turnCount++;
    printf("RVC Turned Right\n");
}
void TurnBackward()
{
    printf("RVC is Turning Backward\n");
    Sleep(1000);
    turnCount++;
    printf("RVC Turned Backward\n");
}

void GetInput()
{
    F = false;
    L = false;
    R = false;
    D = false;
    char input[50]; // 최대 50자까지 입력 가능
    for(int i = 0; i < 50; i++)
    {
        input[i] = 0;
    }
    int i;

    printf("Enter commands (e.g., WADP): ");
    fgets(input, sizeof(input), stdin); // 문자열로 입력받음

    // 입력 문자열 처리
    for (i = 0; input[i] != '\0' && input[i] != '\n'; i++)
    {
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
    }
    return;
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

    while (1)
    {
        obstacle_Location = Det_OL();
        if (turnCount >= Threshold)
        {
            // Stimulus 1: count >= 100,
            // Functional requirement 1.1
            Terminate();
            printf("System Terminate\n");
            break;
        }
        while (obstacle_Location == Stim2)
        {

            // move forward
            isFrontMotor = true;
            printf("RVC is Moving Forward\n");
            turnCount = 0;
            dust_Existence = Det_DE();
            if (dust_Existence)
            {
                cleanerMode = CleanerUp;
                printf("Dust Detected , Cleaner Power UP ON\n");

                // Stimulus 3:  count < 100 && !F && D,
                // Functional requirement 1.3
            }
            else // Dust not Existence , dust_exitence == false
            {
                cleanerMode = CleanerOn;
                printf("Cleaner ON\n");
                // Stimulus 2: count < 100 && !F && !D,,
                // Functional requirement 1.3
            }
            GetInput();
            obstacle_Location = Det_OL();
        }

        printf("Cleaner OFF\n");
        cleanerMode = CleanerOff;
        isFrontMotor = false;
        if (obstacle_Location == 2)
        {
            // turn left
            // Stimulus 4: count < 100 && F && !L
            // Functional requirement 4.1
            TurnLeft();
        }
        else if (obstacle_Location == 3)
        {
            // turn right
            // Stimulus 5: count < 100 && F && L && !R
            // Functional requirement 5.1
            TurnRight();
        }
        else if (obstacle_Location == 4)
        {
            // turn backward
            // Stimulus 6: count < 100 && F && L && R
            // Functional requirement 6.1
            TurnBackward();
        }
        GetInput();
        //wait(200);
    }
}
