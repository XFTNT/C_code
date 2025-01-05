#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define ROW 9
#define COL 9
#define ROWS 11
#define COLS 11
#define MINE 10
void displayboard(char board[ROWS][COLS], int row, int col);
void tap(char game[ROWS][COLS]);
void boom(char mine[ROWS][COLS], char game[ROWS][COLS], int x, int y, int* win, char visited[ROWS][COLS]);


 
void menu()
{
    printf("*********************************\n");
    printf("*********  1. play game  ********\n");
    printf("*********  0. exit       ********\n");
    printf("*********************************\n");
}

void initboard(char board[ROWS][COLS], int rows, int cols, char symbol)
{
    int x = 0;
    int y = 0;
    for (x = 0; x < rows; x++)
    {
        for (y = 0; y < cols; y++)
        {
            board[x][y] = symbol;
        }
    }

}
void setmine(char mine[ROWS][COLS], int fx, int fy)
{
    int n = 1;
    while(n <= MINE)
    {
        int x = rand() % 9 + 1;
        int y = rand() % 9 + 1;
        if (mine[x][y] == '0' && !(x == fx && y == fy))
        {
            mine[x][y] = '1';
            n++;
        }

    }
    //displayboard(mine, ROW, COL);


}

void displayboard(char board[ROWS][COLS], int row, int col)
{
    int x = 1;
    int y = 1;
    printf("0 1 2 3 4 5 6 7 8 9\n");
    for (x = 1; x <= row; x++)
    {
        printf("%d ", x);
        for (y = 1; y <= col; y++)
        {
           printf("%c ", board[x][y]);
        }
        printf("\n");
    }
}
void play(char mine[ROWS][COLS], char game[ROWS][COLS], char visited[ROWS][COLS])
{
    int x;
    int y;
    int num = 0;
    int win= 0;
    int fx;
    int fy;
    while(1)
    {
        printf("please enter x y:>");
        scanf("%d %d", &fx, &fy);

        if (fx > 0 && fx <= 9 && fy > 0 && fy <= 9 && game[fx][fy] == '*')
            {
                setmine(mine, fx, fy);//设置雷 
                num = 0;                    
                if (mine[fx-1][fy-1] == '1')
                    num++;
                if (mine[fx-1][fy] == '1')
                    num++;
                if (mine[fx][fy-1] == '1')
                    num++;
                if (mine[fx+1][fy] == '1')
                    num++;
                if (mine[fx+1][fy+1] == '1')
                    num++;
                if (mine[fx][fy+1] == '1')
                    num++;
                if (mine[fx-1][fy+1] == '1')
                    num++;
                if (mine[fx+1][fy-1] == '1')
                    num++;
                if (num == 0)
                    {
                        game[fx][fy] = ' ';
                        win++;
                        boom(mine, game, fx, fy, &win, visited);
                        displayboard(game, ROW, COL);
                        tap(game);
                        break;
                    }
                else
                {
                    game[fx][fy] = num + '0';
                    win++;
                    displayboard(game, ROW, COL);
                    tap(game);
                    break;
                }
            }
    }
    while (1)
    {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);

        printf("please enter x y:>");
        scanf("%d %d", &x, &y);
        if (x > 0 && x <= 9 && y > 0 && y <= 9 && game[x][y] == '*')
        {
            if (mine[x][y] == '1')
            {
                printf("you are loser.\n");
                displayboard(mine, ROW, COL);
                displayboard(game, ROW, COL);
                break;
            }
            else
            {
                num = 0;
                if (mine[x-1][y-1] == '1')
                    num++;
                if (mine[x-1][y] == '1')
                    num++;
                if (mine[x][y-1] == '1')
                    num++;
                if (mine[x+1][y] == '1')
                    num++;
                if (mine[x+1][y+1] == '1')
                    num++;
                if (mine[x][y+1] == '1')
                    num++;
                if (mine[x-1][y+1] == '1')
                    num++;
                if (mine[x+1][y-1] == '1')
                    num++;
                if (num == 0)
                {
                    game[x][y] = ' ';
                    win++;
                    if (win == 81 - MINE)
                        {
                            printf("you are winner!!!\n");
                            displayboard(mine, ROW, COL);
                            break;
                        }
                    boom(mine, game, x, y, &win, visited);
                    //displayboard(mine, ROW, COL);
                    printf("\n");
                    displayboard(game, ROW, COL);
                    tap(game);                   
                }
                else
                {
                    game[x][y] = num + '0';
                    win++;

                    //displayboard(mine, ROW, COL);
                    displayboard(game, ROW, COL);
                    if (win == 81 - MINE)
                        {
                            printf("you are winner!!!\n");
                            displayboard(mine, ROW, COL);
                            break;
                        }
                    tap(game);
                }
                
                
            }
        }
        else 
        {
            printf("please enter a number between 1 and 9\n");
        }

    }

}
void tap(char game[ROWS][COLS])
{
    int x;
    int y;
    char choice[10];
    printf("tap??? yes or no:>");
    scanf("%s", choice);
    if (strcmp(choice, "yes") == 0)
    {
        while (1)
        {
            printf("please enter x y or 0 0:>");
            scanf("%d %d", &x, &y);
            if (x > 0 && x <= 9 && y > 0 && y <= 9 && game[x][y] == '*')
            {
                game[x][y] = '$';
                printf("\n");
                displayboard(game, ROW, COL);
            }
            else 
            {
                break;
            }
        }   
    }
}

void boom (char mine[ROWS][COLS], char game[ROWS][COLS], int x, int y, int* win, char visited[ROWS][COLS])
{
    int num = 0;
    int m;
    int n;
    for (m = x - 1; m <= x + 1; m++)
    {
        for (n = y -1; n <= y + 1; n++)
        {
            if (!(x == m && y == n) && m > 0 && n > 0 && m < 10 && n < 10 && visited[m][n] != '1')
            {
                num = 0;
                if (mine[m-1][n-1] == '1')
                    num++;
                if (mine[m-1][n] == '1')
                    num++;
                if (mine[m][n-1] == '1')
                    num++;
                if (mine[m+1][n] == '1')
                    num++;
                if (mine[m+1][n+1] == '1')
                    num++;
                if (mine[m][n+1] == '1')
                    num++;
                if (mine[m-1][n+1] == '1')
                    num++;
                if (mine[m+1][n-1] == '1')
                    num++;
                if (num == 0)
                {
                    game[m][n] = ' ';
                    (*win)++;
                    visited[m][n] = '1';
                    boom(mine, game, m, n, win, visited);
                }
                else
                {
                    game[m][n] = num + '0';
                    visited[m][n] = '1';
                    (*win)++;

                }


            }
        }
    }

}
int main()
{
    srand((unsigned int)time(NULL));
    int p;
    char mine[ROWS][COLS] = {0};
    char game[ROWS][COLS] = {0};
 
    

    do
    {
        char visited[ROWS][COLS] = {0};
        int r;
        int c;
        for (r = 0; r < ROWS; r++)
        {
            for (c = 0; c < COLS; c++)
            {
                visited[r][c] = '0';
            }
        }
        menu();
        printf("please choice:>");
        scanf("%d", &p);
        if (p == 1)
        {
            initboard(mine, ROWS, COLS, '0');//初始化棋盘
            initboard(game, ROWS, COLS, '*');//初始化棋盘

            //displayboard(mine, ROW, COL);//打印mine棋盘
            displayboard(game, ROW, COL);//打印棋盘
            play(mine, game, visited);
        }
        else if (p == 0)
        {
            break;
        }
        else
        {
            printf("please enter again!\n");
        }
    } while (p);



    getchar();
    getchar();
    getchar();
    return 0;
}  