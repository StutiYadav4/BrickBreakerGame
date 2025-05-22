#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define PADDLE_SPEED 6
#define BALL_SPEED_X 1
#define BALL_SPEED_Y 1
#define BRICK_SCORE 10

enum Difficulty 
{ 
    EASY = 1, 
    NORMAL = 2, 
    HARD = 3
};

void setDifficulty(enum Difficulty difficulty, int *ballVelX, int *ballVelY) 
{
    switch (difficulty) 
    {
        case EASY:
            *ballVelX = 1;
            *ballVelY = 1;
           
            Sleep(150);
            break;
        case NORMAL:
            *ballVelX = 4;
            *ballVelY = 4;
            
            Sleep(150);
            break;
        case HARD:
            *ballVelX = 8;
            *ballVelY = 8;
            
            Sleep(150);
            break;
    }
}

// Function to hide the cursor
void hideCursor() {
    printf("\e[?25l");  // Hide cursor
}

// Function to show the cursor
void showCursor() {
    printf("\e[?25h");  // Show cursor
}

void movePaddle(char direction, int *paddleX, int column) 
{
    // Update paddle position based on direction
    if(direction == 'a' && *paddleX > 1) 
    {
        *paddleX -= PADDLE_SPEED;
    } 
    else if(direction == 'd' && *paddleX < column - 4)
    { // adjusted paddle size
        *paddleX += PADDLE_SPEED;
    }
}

void drawBrick(int x, int y) 
{
    // Move cursor to position (x, y) and print brick character
    printf("\033[38;5;208m");
    printf("\033[%d;%dH", y, x);
    
    printf("-");
    printf("\033[0m");
}

void drawPaddle(int x, int y) 
{
    // Move cursor to position (x, y) and print paddle character
    printf("\033[%d;%dH", y, x);
    printf("=");
}

void drawBall(int x, int y) 
{
    // Move cursor to position (x, y) and print ball character
    printf("\033[%d;%dH", y, x);
    printf("0");
}

void clearBrick(int x, int y) 
{
    // Move cursor to position (x, y) and clear brick character
    printf("\033[%d;%dH", y, x);
    printf(" ");
}

void clearPaddle(int x, int y) 
{
    // Move cursor to position (x, y) and clear paddle character
    printf("\033[%d;%dH", y, x);
    printf(" ");
}

void clearBall(int x, int y) 
{
    // Move cursor to position (x, y) and clear ball character
    printf("\033[%d;%dH", y, x);
    printf(" ");
}

// Define a structure to hold the game state
struct GameState 
{
    int score;
    int lives;
    time_t startTime;
    // Add more game state variables as needed
};

// Function to print the current score, lives, and time taken
void printGameInfo(struct GameState* gameState) 
{
    // Calculate the time taken by subtracting the start time from the current time
    time_t currentTime;
    time(&currentTime);
    int timeTaken = (int)difftime(currentTime, gameState->startTime);

    printf("Score: %d\tLives: %d\tTime taken: %d seconds\n", gameState->score, gameState->lives, timeTaken);
}

// Function to simulate hitting a brick (increments score by 10)
void hitBrick(struct GameState* gameState) 
{
    gameState->score += 10;
}

// Function to initialize the game state
void initializeGame(struct GameState* gameState, int numberOfBalls) 
{
    gameState->score = 0;
    gameState->lives = (numberOfBalls == 1) ? 3 : 3; // Start with 3 lives regardless of the number of balls
    time(&gameState->startTime);
}

void printenter(const char *line) 
{
    printf("%s", line);
    printf("PRESS ENTER TO CONTINUE...\n");
    while (getchar() != '\n');
    system("cls"); // Clear the screen
}

int main() 
{
    int difficultyChoice;
     // ANSI escape code for yellow color
    printf("\033[0;32m");

    // ANSI escape code for increasing font size (may not work on all terminals)
    printf("\033[5m");

    // Print "The Brick Breaker Game"
    printf("\t                                          #######  ######  #  ######  #    #         #######  ######  ######     #      #   #  #######  #######             \n");
    printf("\t                                          #     #  #    #  #  #       #   #          #     #  #    #  #         # #     #  #   #        #     #             \n");
    printf("\t                                          #     #  #    #  #  #       #  #           #     #  #    #  #        #   #    # #    #        #     #             \n");
    printf("\t                                          #######  ######  #  #       ##             #######  ######  ####    #     #   ##     #####    #######           \n");
    printf("\t                                          #     #  # #     #  #       # #            #     #  # #     #      #########  # #    #        # #              \n");
    printf("\t                                          #     #  #  #    #  #       #   #          #     #  #  #    #      #       #  #  #   #        #   #             \n");
    printf("\t                                          #######  #    #  #  ######  #    #         #######  #    #  ###### #       #  #   #  #######  #     #           \n");

    // ANSI escape code to reset color and font size
    printf("\033[0m");
    printf("\n\n\n\n");



    //printenter("WELCOME TO BRICK BREAKER WORLD\n\n");
    printf("\033[0;33m");
    printenter("Brick Breaker is a classic arcade game where you have to control a paddle at the bottom of the screen, moving it horizontally to bounce a ball towards a wall of bricks at the top. Your goal is to breakall the bricks by hitting them with the ball, while preventing the ball from falling off the bottom of the screen.\n\n\n\n");
    printf("\033[0m");
    printf("\033[0;34m");
    printf("\033[6;1m"); 
    printf("\t\t\t\t                                                ~ INSTRUCTIONS FOR THE GAME ~\n\n\n\n");
    printf("\033[0m");
    printf("\033[0;34m");
    printf("\t\t\t\t                                     1. 'a' or 'A' - moves the paddle to the left\n\n");
    printf("\t\t\t\t                                     2. 'd' or 'D' - moves the paddle to the right\n\n");
    printf("\t\t\t\t                                     3.  You have 3 lives to survive.\n\n");
    printf("\t\t\t\t                                     4.  As you break one brick your score updates by 10.\n\n");
    printf("\t\t\t\t                                     5.  You can also choose to play with either one or two balls simultaneously.\n\n");
    printenter("\t\t\t\t                                     6. There are 3 levels of difficulties in the game-EASY, MEDIUM and HARD.\n\n\n\n\n");
    printf("\033[0m");

    // ANSI escape code to reset color and font size
    printf("\n\n");
    printf("\033[0;34m");
    printf("\033[6;1m"); 
    printf("\t\t\t\t\t\t\t\t           ~ CHOOSE DIFFICULTY LEVEL ~\n\n\n");
    printf("\033[0m");
    printf("\033[0;34m");
    printf("\t\t\t\t\t\t\t\t                1 - Easy\n");
    printf("\t\t\t\t\t\t\t\t                2 - Medium\n");
    printf("\t\t\t\t\t\t\t\t                3 - Hard\n\n\n\n");
    printf("Select Difficulty Level : ");
    printf("\033[0m");
    scanf("%d", &difficultyChoice);
    printf("\n");
    int ballVelX = BALL_SPEED_X, ballVelY = BALL_SPEED_Y;
    
    enum Difficulty difficulty = (enum Difficulty)difficultyChoice;
    setDifficulty(difficulty, &ballVelX, &ballVelY);
    printf("Press any key to continue");
    Sleep(1000);
    getch();
    system("cls");

    /*int numberOfBalls;
    printf("\033[0;34m");
    printf("\033[6;1m"); 
    printf("\t\t\t\t\t\t\t\t     Enter number of balls (1 or 2): ");
    printf("\033[0m");
    scanf("%d", &numberOfBalls);
    printf("\n");*/

    int i, j, rows, columns;
    char input;

    // Input number of rows and columns from user
    printf("\033[0;34m");
    printf("\033[6;1m"); 
    printf("\t\t\t\t\t\t\t\t        Enter number of rows: ");
    printf("\033[0m");
    scanf("%d", &rows);
    printf("\033[0;34m");
    printf("\033[6;1m"); 
    printf("\t\t\t\t\t\t\t\t       Enter number of columns: ");
    printf("\033[0m");
    scanf("%d", &columns);
    system("cls");
    int paddleX = columns / 2;
    int ballX = columns / 2, ballY = rows - 5;
    

    
    
    int score = 0; // Initialize player's score

    // Initialize the bricks
    int bricks[rows][columns];
    for(i = 0; i < rows; i++) 
    {
        for(j = 0; j < columns; j++) 
        {
            if(i == 2 || i == 3 || i == 4 || i == 5) 
            {
                bricks[i][j] = 1; // Bricks present
            } 
            else 
            {
                bricks[i][j] = 0; // Empty space
            }
        }
    }

    hideCursor(); // Hide the cursor before starting the game loop

    struct GameState gameState;
    initializeGame(&gameState, 1); // Initialize the game state with 1 ball
    while (gameState.lives>0) 
    {
        // Draw the game screen
        for(i = 0; i < rows; i++) 
        {
            for(j = 0; j < columns; j++) 
            {
                //if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
                   // printf("*");
                
                if(bricks[i][j] == 1) 
                {
                    drawBrick(j, i);
                } 
                else if(i == rows - 4 && j >= paddleX && j <= paddleX + 3) 
                { // adjusted paddle size
                    drawPaddle(j, i);
                } 
                else if((i == ballY && j == ballX)) 
                { // Draw both balls
                    drawBall(j, i);
                } 
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }

        // Move the balls automatically
        ballX += ballVelX;
        ballY += ballVelY;
        

        // Handle ball collisions with screen edges for both balls
        if(ballX <= 1 || ballX >= columns - 2) 
        {
            ballVelX = -ballVelX; // Reverse horizontal velocity
        }
        if(ballY <= 0) 
        {
            ballVelY = -ballVelY; // Reverse vertical velocity
        }
        
        // Handle ball collisions with paddle for both balls
        if(ballY >= rows - 4 && ballX >= paddleX && ballX <= paddleX + 3) 
        { // adjusted paddle size
            ballVelY = -ballVelY; // Reverse vertical velocity
        }
        

        // Handle ball collisions with bricks for both balls
        if(ballY >= 2 && ballY <= 5) 
        {
            if(bricks[ballY][ballX] == 1) 
            {
                bricks[ballY][ballX] = 0; // Remove the brick
                ballVelY = -ballVelY; // Reverse vertical velocity
                score += BRICK_SCORE; // Increase score
                clearBrick(ballX, ballY); // Clear the brick after collision
            }
        }
        

        // Update paddle position based on user input
        if(_kbhit()) 
        {
            input = _getch();
            if(input == 'q' || input == 'Q') 
            {
                break;
            } 
            else if(input == 'a' || input == 'A') 
            {
                movePaddle(input, &paddleX, columns);
                clearPaddle(paddleX + 4, rows - 4); // Clear previous paddle position
            } 
            else if(input == 'd' || input == 'D') 
            {
                movePaddle(input, &paddleX, columns);
                clearPaddle(paddleX - 1, rows - 4); // Clear previous paddle position
            }
        }

        // Check if the ball misses the paddle and exit the game
        if(ballY >= rows - 1 ) 
        {
            gameState.lives--; //reduces lives
            if(gameState.lives ==0)
            {
                time_t endTime;
                time(&endTime);
                
                printf("\033[%d;%dH", rows + 1, 0); // Move cursor to a new line
                printf("\033[1;31m");
                printf("\033[6;1m"); 
                printf("\t\t\t\t Oops Game Over!\n\n");
                printf("\033[0m");
                printf("\033[0;34m");
                printf("\033[6;1m"); 
                printf("\t Your Score: %d\t\t", score);
                printf("Total time played: %d seconds\n\n\n\n\n", (int)difftime(endTime, gameState.startTime));
                printf("\033[0m");
                break;

            }
            else
            {
                //reset the ball position
                ballX=columns/2;
                ballY=rows-5;

                

                paddleX=columns/2;

                ballVelX=BALL_SPEED_X;
                ballVelY=-BALL_SPEED_Y;
                
                Sleep(1000);

            }
            
        }

        // Delay to control frame rate (adjust the value to slow down or speed up the game)
        Sleep(100); // 100 milliseconds
    }

    showCursor(); // Show the cursor after the game loop ends

    return 0;
}
