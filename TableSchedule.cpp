#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "Schedule.h"
#include "Setcolor.h"

using namespace std;


static void drawTable(int rows, int cols, int start_x, int start_y) {
    const int cellWidth = 10;  // Độ rộng mỗi ô
    const int cellHeight = 3;  // Chiều cao mỗi ô

    // Tên các ngày trong tuần
    const char* daysOfWeek[] = { "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun" };

    // Vẽ hàng tiêu đề cho các thứ trong tuần
    for (int j = 0; j < cols; ++j) {
        gotoxy(start_x + j * (cellWidth + 1) + cellWidth / 2 - 1, start_y); 
        cout << setw(3) << daysOfWeek[j % 7]; 
    }
    Setcolor(14);

    // Tăng start_y để các hàng tiếp theo không đè lên hàng tiêu đề
    start_y += 1;

    // Vẽ bảng lịch (bắt đầu từ hàng dưới hàng tiêu đề)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            gotoxy(start_x + j * (cellWidth + 1), start_y + i * (cellHeight + 1));  
            cout << "+";
            for (int k = 0; k < cellWidth; ++k) cout << "-";
        }
        cout << "+\n";

        // Vẽ các hàng với chiều cao mỗi ô
        for (int h = 0; h < cellHeight; ++h) {
            for (int j = 0; j < cols; ++j) {
                gotoxy(start_x + j * (cellWidth + 1), start_y + i * (cellHeight + 1) + h + 1);  
                cout << "|";
                for (int k = 0; k < cellWidth; ++k) cout << " ";
            }
            cout << "|\n";
        }
    }

    // Vẽ đường kẻ ngang cuối cùng
    for (int j = 0; j < cols; ++j) {
        gotoxy(start_x + j * (cellWidth + 1), start_y + rows * (cellHeight + 1));  // Điều chỉnh vị trí
        cout << "+";
        for (int k = 0; k < cellWidth; ++k) cout << "-";
    }
    cout << "+\n";
    Setcolor(15);
}

static void fillContent(int rows, int cols, int start_x, int start_y, const string& monthYear,Doctor& doctor) {
    Schedule schedule;
    int num = 0;  // Số ngày trong tháng
    int nums = 1;  // Biến để điền ngày vào bảng
    int col_start = 0;
    string dayofweek;

    //lay ngay lam viec
    int arr[40] = { 0 };
    schedule.DayworkOfDoctor(arr, monthYear, doctor);


    if (!schedule.isValidMonth(monthYear, num, dayofweek)) {
        cout << "Invalid month/year format.\n";
        return;
    }

    static const string daysOfWeek[] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday","Sunday" };
    for (int i = 0; i < 7; i++) {
        if (daysOfWeek[i] == dayofweek) {
            col_start = i;
            break;
        }
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; ++j) {
            if (nums <= num) {
                if (i == 0 && j < col_start) {
                    gotoxy(start_x + j * (10 + 1) + 10 / 2 , start_y + 3 + i * 4);
                    Setcolor(10);
                    cout << " X";
                    Setcolor(15);
                }
                else {
                    gotoxy(start_x + j * (10 + 1) + 10 / 2 , start_y + 3 + i * 4);
                    if (arr[nums] == 1) {
                        Setcolor(12);
                        cout << setw(2) << nums;
                        Setcolor(15);
                    }
                    else {
                        cout << setw(2) << nums;
                    }
                    nums++;
                }
            }
            else {
                gotoxy(start_x + j * (10 + 1) + 10 / 2 , start_y + 3 + i * 4);
                Setcolor(10);
                cout << " X";
                Setcolor(15);
            }
        }
    }
}


