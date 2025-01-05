#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void displayboard(char arr[3][3], int row, int col);



void board(char arr[3][3], int a, int b)
{
    arr[a][b] = '*';
    displayboard(arr, 3, 3);
}

void displayboard(char arr[3][3], int row, int col)
{
    int i = 0;
    for (i; i < row; i++)
    {
        printf(" %c | %c | %c \n", arr[i][0], arr[i][1], arr[i][2]);
        if (i < 2)
        {
            printf("---|---|---\n");
        }
    } 

}

void initboard(char arr[3][3], int row, int col)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < row; i++)
    {
        for (j = 0; j < col; j++)
        {
            arr[i][j] = ' ';
        }
    }
}

void computer(char arr[3][3], int row, int col)
{
    int x = 0;
    int y = 0;
    while (1)
    {
        x = rand() % row;
        y = rand() % col;
        if (arr[x][y] == ' ')
        {
            arr[x][y] = '#';
            displayboard(arr, 3, 3);
            break;
        }
    }
}
int condition(char arr[3][3], int row, int col)
{
    int x = 0;
    int y = 0;
    //判断每一行
    for (x = 0; x < row; x++)
    {
        if (arr[x][0] == arr[x][1] && arr[x][1] == arr[x][2] && arr[x][0] != ' ')
        {
            return 1;
        }
    }
    //判断列
    for (y = 0; y < row; y++)
    {
        if (arr[0][y] == arr[1][y] && arr[1][y] == arr[2][y] && arr[0][y] != ' ')
        {
            return 1;
        }
    }
    //判断对角线
    if (arr[0][0] == arr[1][1] && arr[1][1] == arr[2][2] && arr[0][0] != ' ')
    {
        return 1; // 当前玩家赢了
    }
    if (arr[0][2] == arr[1][1] && arr[1][1] == arr[2][0] && arr[0][2] != ' ')
    {
        return 1; // 当前玩家赢了
    }
    //判断平局
    for (x = 0; x < 3; x++)
    {
        for (y = 0; y < 3; y++)
        {
            if (arr[x][y] == ' ')
                return 0;
        }
    }
    return 2;

}



void game()
{
    char arr[3][3] = {0};
    initboard(arr, 3, 3);//初始化键盘
    displayboard(arr, 3, 3);//打印棋盘
    while (1)
    {

    
        printf("Player, please make your move\n");
        int n = 1;
        int ei;
        int ej;
        while (n)
        {
            printf("move:>");
            scanf("%d %d", &ei, &ej);
            if (ei <= 3 && ei > 0 && ej <= 3 && ej > 0 )
            {
                if (arr[ei - 1][ej - 1] == '#' || arr[ei - 1][ej - 1] == '*')
                {
                    printf("please input afresh!\n");
                    continue;
                }
                board(arr, ei - 1, ej - 1);
                n = 0;
            }
            else
            {
                printf("Please enter a number between 1 and 3\n");
            }
        }
        int ret = 0;
        ret = condition(arr, 3, 3);
        if (ret == 1)
        {
            printf("player win\n");
            break;
        }
        printf("computer\n");
        computer(arr, 3, 3);
        ret = condition(arr, 3, 3);
        if (ret == 1)
        {
            printf("player win\n");
            break;
        }
        if (ret == 2)
        {
            printf("draw\n");
            displayboard(arr, 3, 3);
            break;
        }
    }
}



int main()
{
    srand((unsigned)time(NULL));
    int row = 3;
    int col = 3;
    int start;
    do
    {
        printf("***********************************\n");
        printf("************1.  play   ************\n");
        printf("************0.  exit   ************\n");
        printf("***********************************\n");
        printf("pelase choose:>");
        scanf("%d", &start);

        switch (start)
        {
            case 1:
                printf("game start!\n");
                game();
                break;
            case 0:
                printf("game over!\n");
                break;
            default:
                printf("choose error\n");
                break;

        }

    } while (start);
    
    getchar();
    getchar();
    getchar();
    return 0; 
}