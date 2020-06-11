//解决VS对scanf不安全函数报警问题
#define _CRT_SECURE_NO_WARNINGS

/***************************************************
 * 文件名：GameLib.c
 * 描  述：GameLib.h的  实现文件
 * 创建人：andi
 * 日  期：2019-10-25
 * 版  本：1.0
 *
 **************************************************/
#include <stdio.h>
//#include <unistd.h>
#include <string.h>
#include "GameLib.h"



void SetTitle(char* title)
{
    SetConsoleTitle(title);
}

void SetColor(int ForeColor, int BackGroundColor)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);                    //获取当前窗口句柄
    SetConsoleTextAttribute(handle, ForeColor + BackGroundColor * 0x10);//设置颜色
}
void SetConsoleWindowSize(int width, int height)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    //设置控制台窗口的缓冲区大小
    COORD size = { width, height };
    SetConsoleScreenBufferSize(handle, size);
    //设置控制台窗口大小,最大坐标是缓冲区大小-1
    SMALL_RECT rect = { 0, 0, width - 1, height - 1 };
    SetConsoleWindowInfo(handle, 1, &rect);
}
void SetPosition(int x, int y)
{
    COORD cursorPosition;   //光标的坐标
    HANDLE handle;          //当前窗口句柄
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    cursorPosition.X = x;   //设置x、y坐标
    cursorPosition.Y = y;
    SetConsoleCursorPosition(handle, cursorPosition);
}
void PrintString(const char* msgString)
{
    int length = strlen(msgString);
    int i = 0;
    for (; i < length; i++)
    {
        char tempChar = msgString[i];
        printf("%c", tempChar);
        Sleep(1000 * 20);//20毫秒
        fflush(stdout);
    }
}
void Read(char* Buffer, int BufferSize)
{
    DWORD Read;
    HANDLE handle;          //当前窗口句柄
    handle = GetStdHandle(STD_INPUT_HANDLE);
    ReadConsole(handle, Buffer, BufferSize, &Read, NULL);
}

int GetKey()

{
    HANDLE handle;          //当前窗口句柄
    handle = GetStdHandle(STD_INPUT_HANDLE);
    DWORD Read;
    INPUT_RECORD Event;
    //得到控制台的输入
    ReadConsoleInput(handle, &Event, 1, &Read);
    //如果输入事件是一个键盘事件，就进行判断，返回按下键的虚拟键码
    if (Event.EventType == KEY_EVENT)
    {
        if (Event.Event.KeyEvent.bKeyDown)//返回值为true，表示有键被按下
        {
            return Event.Event.KeyEvent.wVirtualKeyCode;//返回按下键的虚拟键码
        }
    }
    return 0;
}
char* GetGameTime()
{

    time_t rawtime;
    struct tm* timeinfo;
    static char buffer[128];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return buffer;
}
void Clear(int X, int Y)
{
    DWORD written;
    COORD start;    //开始坐标
    HANDLE handle;  //当前窗口句柄
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    start.X = X;
    start.Y = Y;
    FillConsoleOutputAttribute(handle, 15, 80 * 25, start, &written);
    FillConsoleOutputCharacter(handle, ' ', 80 * 25, start, &written);
    SetConsoleCursorPosition(handle, start);
}
void ClearMessage()
{
    //清空信息显示区
    COORD coordStart = { 0, 12 };
    DWORD written;
    HANDLE handle;  //当前窗口句柄
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    FillConsoleOutputAttribute(handle, 15, 120 * 7, coordStart, &written);
    FillConsoleOutputCharacter(handle, ' ', 120 * 7, coordStart, &written);
    SetConsoleCursorPosition(handle, coordStart);
}














