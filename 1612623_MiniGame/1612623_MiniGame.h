#pragma once

#include "resource.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

const int BUFFERSIZE_260 = 260;
const int BUFFERSIZE_256 = 256;
const WCHAR* PLAYER_NAME = L"player_name";
const int NAME_LENGTH = 40;
const int ScoreStep = 10;

int CountDownTimer = 10;
int NUMBER_OF_PLAYERS;
int Player_Result[256];
int firstAnswer, secondAnswer, random_result;
bool isTrueAnswer;
int Score;
int CurrentQuestion;

WCHAR* PlayerNames[BUFFERSIZE_256];
WCHAR curPath[BUFFERSIZE_260];

HBITMAP PlayerBitmap;

UINT TimmerID10s = 0;
UINT TimmerID1s = 1;

//Khai báo font variable
HFONT pFont, hFont, mFont, bigFont;

//Declare HWND menu
HWND PlayerImage, FirstAnswerButton, SecondAnswerButton;
HWND ScoreWord, Scores, Timer, QuestionNumber;

// Đọc file và ghi player name vào mảng Player_Names và tính số lượng cầu thủ vào NUMBER_OF_PLAYERS.
void ReadIniFile();

// Hủy các button, image.
void DestroyAllHWNDOnScreen();

// Kiểm tra trong danh sách có phần tử x hay chưa
bool Contains(const std::vector<int> &list, int x);

// Random hình ảnh cầu thủ: random thứ tự hình ảnh xuất hiện.
void RandomPlayerImage();

//Random câu trả lời đúng và sai
void Random_Answer(int currentQuestionIndex);

// Random câu trả lời sai
void Random_False_Answer(int &Answer, int result);

// Cập nhật điểm
void UpdatePoint();

// Load câu hỏi mới
void LoadNewQuestion(HWND hwnd);

// Update timer
void UpdateTimer(HWND hwnd);

// Cập nhật câu hỏi
void UpdateQuestionNumber(HWND hwnd);