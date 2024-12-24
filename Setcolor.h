#pragma once
#ifndef SETCOLOR_H
#define SETCOLOR_H
#include <iostream>
#include "Schedule.h"
#include "windows.h"
using namespace std;
//============== dịch con trỏ hiện tại đến điểm có tọa độ (x,y) ==========
static void gotoxy(int x, int y) {
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { (SHORT)x, (SHORT)y }; // Đảm bảo kiểu dữ liệu đúng
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	if (SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos) == FALSE) {
		// Xử lý lỗi nếu không thể đặt vị trí con trỏ
		DWORD dwError = GetLastError();
		printf("ERROR: Unable to set cursor position. Error code: %lu\n", dwError);
	}
}
//============= đặt màu cho chữ =========
static void Setcolor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
//============== làm ẩn trỏ chuột ===========
static void Showcur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}
static void drawTree(int x, int y) {
	Setcolor(10);
	gotoxy(x, y);         std::cout << "*";
	gotoxy(x - 1, y + 1); std::cout << "***";
	gotoxy(x - 2, y + 2); std::cout << "*****";
	gotoxy(x - 3, y + 3); std::cout << "*******";
	Setcolor(12);
	gotoxy(x, y + 4);     std::cout << "|";
	Setcolor(15);
}
#endif 