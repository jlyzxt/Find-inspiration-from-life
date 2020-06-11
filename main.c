//解决VS对scanf不安全函数报警问题
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "GameLib.h"
#include "Game.h"

extern char Maps[8][8][10];
extern enum GameStatus CurrGameStatus;
extern Martial martials[20];
extern int X;
extern int Y;
int main()
{
    SetConsoleWindowSize(121, 31);
    int i = 0, j = 0;
    char key;   //用户按下的键
    SetTitle("笑傲江湖之精忠报国C语言版");
    SetColor(10, 0);
    SetPosition(MARGIN_X, 0);
    printf("-----------------------------------------------------------------------------\n");
    SetPosition(MARGIN_X, 1);
    printf("|\t\t\t欢迎来到《笑傲江湖之精忠报国》");
    SetPosition(MARGIN_X + 76, 1);
    printf("|");
    SetPosition(MARGIN_X, 2);
    printf("-----------------------------------------------------------------------------\n");
    InitializeGame();
    ShowMap();

    while (1) {
        //Clear(20, 2);
        SetPosition(MARGIN_X, 19);
        printf("-----------------------------------------------------------------------------\n");
        SetPosition(MARGIN_X, 20);
        printf("游戏菜单\n");
        SetPosition(MARGIN_X, 21);
        printf("1、自我欣赏\n");
        SetPosition(MARGIN_X, 22);
        printf("2、探查(打怪)\n");
        SetPosition(MARGIN_X, 23);
        printf("3、回总部\n");
        SetPosition(MARGIN_X, 24);
        printf("4、购买装备\n");
        SetPosition(MARGIN_X, 25);
        printf("5、(待完成)\n");
        SetPosition(MARGIN_X, 26);
        printf("6、(待完成)\n");
        SetPosition(MARGIN_X, 27);
        printf("7、退出游戏");
        SetPosition(MARGIN_X, 28);
        printf("请输入选择或四方向移动：");
        key = GetKey();//等待用户输入
        if (key == 38) {//上
            X--;
        }
        else if (key == 39) {//右
            Y++;
        }
        else if (key == 40) {//下
            X++;
        }
        else if (key == 37) {//左
            Y--;
        }
        else if (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || key == '6') {
            Process(key);
            continue;
        }
        else if (key == '7') {
            exit(0);
        }
        else
        {
            continue;
        }

        //getch();
        if (X > 7) X = 0;
        if (X < 0) X = 7;
        if (Y > 7) Y = 0;
        if (Y < 0) Y = 7;
        ShowMap();

    }
    SetColor(15, 0);
    //InitializeGame();
    //ShowPlayer();
    return 0;
}

