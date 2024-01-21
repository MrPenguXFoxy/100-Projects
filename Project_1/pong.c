// Starting at 9:56 - End it at ideally 11:56 - Completed at 11:41 - With Bugs ofc 

//Adding Raylib into our project
#include "raylib.h"
#include "stdio.h"
int main(void)
{
    //Define the screen size
    const int width = 800;
    const int height = 450;
    
    //Initatizing the screen
    InitWindow(width, height, "Pong Game Made in RayLib");
    
    SetTargetFPS(60);
    
    
    //Record of a Ball, with its properites, such as position in space (x,y), radius from its center, and the change in the position.
    struct Ball
    {
        int x;
        int y;
        float radius;
        int x_change;
        int y_change;
        Vector2 center;
    };
    
    struct Player
    {
        int x;
        int y;
        int y_change;
        int width;
        int height;
        int score;
    };
    
    //Initializing the ball dimesions
    struct Ball ball;
    ball.x = width/2;
    ball.y = height/2;
    ball.x_change = 2;
    ball.y_change = 2;
    ball.radius = 15.0f;
    ball.center = (Vector2){ball.x, ball.y};
    
    //Initiaizing the player dimesions 
    struct Player leftPlayer;
    leftPlayer.width = 16;
    leftPlayer.height = 80;
    leftPlayer.x = 5;
    leftPlayer.y = (height/2) - (leftPlayer.height/2);
    leftPlayer.y_change = 10;
    leftPlayer.score = 0;
        
    struct Player rightPlayer;
    rightPlayer.width = leftPlayer.width;
    rightPlayer.height = leftPlayer.height;
    rightPlayer.x = width - (leftPlayer.x + rightPlayer.width);
    rightPlayer.y = leftPlayer.y;
    rightPlayer.y_change = 10;
    rightPlayer.score = 0;
    
    int gameRunning = 1; 
    
    while(!WindowShouldClose() && gameRunning == 1)
    {
        
        
        //Start Drawing the stuff on screen
        BeginDrawing();
        
        //Making a ball on screen
        DrawCircle(ball.x, ball.y, ball.radius, BLACK);
        
        //Making the ball move
        ball.x += ball.x_change;
        ball.y += ball.y_change;
        ball.center = (Vector2){ball.x,ball.y};
        
        
        //Moving the left player using WASD
        //moving the player up
        if (IsKeyDown(KEY_W))
        {
            if (leftPlayer.y <= 10)
            {
                leftPlayer.y = leftPlayer.y;
            }
            else
            {
            leftPlayer.y -= leftPlayer.y_change;
            }
        }

        //Moving the player down
        if (IsKeyDown(KEY_S))
        {
            if (leftPlayer.y >= height - 10 - leftPlayer.height)
            {
                leftPlayer.y = leftPlayer.y;
            }
            else
            {
            leftPlayer.y += leftPlayer.y_change;    
            }
            
        }
        
        
        
        //Moving the right player using ARROW KEYS
        //moving the player up
        if (IsKeyDown(KEY_UP))
        {
            if (rightPlayer.y <= 10)
            {
                rightPlayer.y = rightPlayer.y;
            }
            else
            {
            rightPlayer.y -= rightPlayer.y_change;
            }
        }

        //Moving the player down
        if (IsKeyDown(KEY_DOWN))
        {
            if (rightPlayer.y >= height - 10 - rightPlayer.height)
            {
                rightPlayer.y = rightPlayer.y;
            }
            else
            {
            rightPlayer.y += rightPlayer.y_change;    
            }
            
        }
        //Making the leftPlayer
        struct Rectangle rightPlayerRec =
        {
            rightPlayer.x,
            rightPlayer.y,
            rightPlayer.width,
            rightPlayer.height,
        };
        DrawRectangleRec(rightPlayerRec, RAYWHITE);
        //Making the rightPlayer
        struct Rectangle leftPlayerRec =
        {
            leftPlayer.x,
            leftPlayer.y,
            leftPlayer.width,
            leftPlayer.height,
        };
        DrawRectangleRec(leftPlayerRec, RAYWHITE); 
        
        //Collision with players
        if (CheckCollisionCircleRec(ball.center, ball.radius, rightPlayerRec))
        {
            ball.x_change *= -1;
            rightPlayer.score += 1;
        }
        if (CheckCollisionCircleRec(ball.center, ball.radius, leftPlayerRec))
        {
            ball.x_change *= -1;
            leftPlayer.score += 1;
        }        
        //Check for the collision of the ball with the walls of the window, to change its direction
        if ( (ball.x + ball.radius) >= width)
        {
            gameRunning = 2;
        }

        if ((ball.x - ball.radius) <= 0)
        {
            gameRunning = 2;
        }            
        
        if ( (ball.y - ball.radius) <= 0 || (ball.y + ball.radius) >= height)
        {
            ball.y_change *= -1;
        }
        
        //Display the score
        //Left Player
        DrawText(TextFormat("Score: %d", leftPlayer.score), width/4 -50, 30, 30, BLACK);
        //Right Player
        DrawText(TextFormat("Score: %d", rightPlayer.score), width*3/4 -50, 30, 30 , BLACK);
        DrawLine(width/2,0,width/2,height,BLACK);
        
        EndDrawing();
        ClearBackground(GRAY);
    }
    if (leftPlayer.score > rightPlayer.score)
    {
        printf("Left Player won \n");
    }
    else if (rightPlayer.score > leftPlayer.score)
    {
        printf("Right Player won \n");
    }
    else
    {
        printf("Tie \n");
    }
    printf("");
    CloseWindow();
    return 0;
}