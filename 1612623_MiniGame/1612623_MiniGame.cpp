// 1612623_MiniGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1612623_MiniGame.h"
#include <windowsx.h>


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnDestroy(HWND hwnd);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnPaint(HWND hwnd);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1612623MINIGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1612623MINIGAME));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1612623MINIGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_BTNFACE+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1612623MINIGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   300, 200, 600, 400, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
	case WM_TIMER:
		switch (wParam)
		{
		case ID_10SECONDS:

		
			break;
		case ID_1SECONDS:
			CountDownTimer--;
			WCHAR *temp;
			temp = new WCHAR[5];
			swprintf(temp, 5, L"%d", CountDownTimer);
			SetWindowText(Timer, temp);
			if (CountDownTimer == 0)
				LoadNewQuestion(hWnd);
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	isTrueAnswer = false;
	Score = 0;
	CurrentQuestion = 0;
	
	ReadIniFile();
	RandomPlayerImage();
	Random_Answer(CurrentQuestion);

	GetCurrentDirectory(BUFFERSIZE_260, curPath);
	wsprintf(curPath, L"%s\\players\\%d%s", curPath, Player_Result[CurrentQuestion],L".bmp");

	// Lấy font hệ thống
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	pFont = CreateFont(-15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	mFont = CreateFont(-25, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
	bigFont = CreateFont(25, 25, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");

	//Tạo ra Score
	ScoreWord = CreateWindowEx(0, L"STATIC", L"Point", WS_CHILD | WS_VISIBLE | SS_CENTER, 400, 30, 100, 40, hwnd, NULL, hInst, NULL);
	SendMessage(hwnd, WM_SETFONT, WPARAM(pFont), TRUE);
	Scores = CreateWindowEx(0, L"STATIC", L"0", WS_CHILD | WS_VISIBLE | SS_CENTER, 420, 70, 100, 40, hwnd, NULL, hInst, NULL);
	SendMessage(Scores, WM_SETFONT, WPARAM(pFont), TRUE);
	
	// Tạo ra hình ảnh
	PlayerBitmap = (HBITMAP)::LoadImage(NULL, curPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	PlayerImage = CreateWindowEx(0, L"STATIC", L"Point", WS_CHILD | WS_VISIBLE | SS_BITMAP, 220, 60, 400, 200, hwnd, NULL, hInst, NULL);
	SendMessage(PlayerImage, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)PlayerBitmap);

	// Tạo ra các câu trả lời
	FirstAnswerButton = CreateWindowEx(NULL, L"BUTTON", PlayerNames[firstAnswer],
		WS_CHILD | WS_VISIBLE,
		50, 230, 100, 50, hwnd,
		(HMENU)IDC_BTN_FIRSTPLAYER, lpCreateStruct->hInstance, NULL);
	SetWindowFont(FirstAnswerButton, pFont, TRUE);

	SecondAnswerButton = CreateWindowEx(NULL, L"BUTTON", PlayerNames[secondAnswer],
		WS_CHILD | WS_VISIBLE,
		400, 230, 100, 50, hwnd,
		(HMENU)IDC_BTN_SECONDPLAYER, lpCreateStruct->hInstance, NULL);
	SetWindowFont(SecondAnswerButton, pFont, TRUE);

	// Tạo ra timer đếm ngược
	CreateWindowEx(0, L"STATIC", L"Timer", WS_CHILD | WS_VISIBLE | SS_LEFT, 275, 220, 50, 60, hwnd, NULL, hInst, NULL);
	SetWindowFont(Timer, WM_SETFONT, WPARAM(mFont), TRUE);
	Timer = CreateWindowEx(0, L"STATIC", L"10", WS_CHILD | WS_VISIBLE | SS_LEFT, 280, 250, 50, 60, hwnd, NULL, hInst, NULL);
	SetWindowFont(Timer, WM_SETFONT, WPARAM(mFont), TRUE);

	TimmerID1s = SetTimer(hwnd, ID_1SECONDS, 1 * 1000, NULL);

	// Tạo text câu hỏi
	HWND Text = CreateWindowEx(NULL, L"STATIC", L"Chọn tên cầu thủ?",
		WS_CHILD | WS_VISIBLE,
		200, 10, 200, 70, hwnd,
		NULL, lpCreateStruct->hInstance, NULL);
	SetWindowFont(Text, bigFont, TRUE);

	HWND Question = CreateWindowEx(NULL, L"STATIC", L"Câu số",
		WS_CHILD | WS_VISIBLE,
		50, 10, 50, 70, hwnd,
		NULL, lpCreateStruct->hInstance, NULL);
	SetWindowFont(Question, pFont, TRUE);

	QuestionNumber = CreateWindowEx(NULL, L"STATIC", L"1",
		WS_CHILD | WS_VISIBLE,
		70, 40, 50, 70, hwnd,
		NULL, lpCreateStruct->hInstance, NULL);
	SetWindowFont(QuestionNumber, bigFont, TRUE);

	return TRUE;
}


void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}


void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id)
	{
	case IDM_ABOUT:
		DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, About);
		break;
	case IDM_EXIT:
		DestroyWindow(hwnd);
		break;
	case IDC_BTN_FIRSTPLAYER:
		if (random_result == 0)
		{
			isTrueAnswer = true;
			UpdatePoint();
			MessageBox(hwnd, L"Bạn đã trả lời đúng", L"Chúc mừng", 0);
		}
		else
		{
			isTrueAnswer = false;
			MessageBox(hwnd, L"Bạn đã trả lời sai", L"Rất tiếc", 0);
		}
		LoadNewQuestion(hwnd);
		break;
	case IDC_BTN_SECONDPLAYER:
		if (random_result == 1)
		{
			isTrueAnswer = true;
			UpdatePoint();
			MessageBox(hwnd, L"Bạn đã trả lời đúng", L"Chúc mừng", 0);
		}
		else
		{
			isTrueAnswer = false;
			MessageBox(hwnd, L"Bạn đã trả lời sai", L"Rất tiếc", 0);
		}
		
		LoadNewQuestion(hwnd);
		break;
	}

}

void UpdateQuestionNumber(HWND hwnd)
{
	WCHAR buffer_number[5];
	swprintf(buffer_number, 5, L"%d", CurrentQuestion + 1);
	SetWindowText(QuestionNumber, buffer_number);
}

void UpdatePoint()
{
	Score += ScoreStep;
	WCHAR buffer_point[5];
	swprintf(buffer_point, 5, L"%d", Score);
	SetWindowText(Scores, buffer_point);
}

void LoadNewQuestion(HWND hwnd)
{
	CurrentQuestion++;
	if (CurrentQuestion < NUMBER_OF_PLAYERS)
	{
		GetCurrentDirectory(BUFFERSIZE_260, curPath);
		wsprintf(curPath, L"%s\\players\\%d%s", curPath, Player_Result[CurrentQuestion], L".bmp");

		PlayerBitmap = (HBITMAP)::LoadImage(NULL, curPath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		DestroyWindow(PlayerImage);
		PlayerImage = CreateWindowEx(0, L"STATIC", L"Point", WS_CHILD | WS_VISIBLE | SS_BITMAP, 220, 60, 400, 200, hwnd, NULL, hInst, NULL);
		SendMessage(PlayerImage, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)PlayerBitmap);
		Random_Answer(CurrentQuestion);
		DestroyWindow(FirstAnswerButton);
		DestroyWindow(SecondAnswerButton);

		FirstAnswerButton = CreateWindowEx(NULL, L"BUTTON", PlayerNames[firstAnswer],
			WS_CHILD | WS_VISIBLE,
			50, 230, 100, 50, hwnd,
			(HMENU)IDC_BTN_FIRSTPLAYER, hInst, NULL);
		SetWindowFont(FirstAnswerButton, pFont, TRUE);

		SecondAnswerButton = CreateWindowEx(NULL, L"BUTTON", PlayerNames[secondAnswer],
			WS_CHILD | WS_VISIBLE,
			400, 230, 100, 50, hwnd,
			(HMENU)IDC_BTN_SECONDPLAYER, hInst, NULL);
		SetWindowFont(SecondAnswerButton, pFont, TRUE);

		UpdateTimer(hwnd);
		UpdateQuestionNumber(hwnd);
	}
	else
	{
		
		wchar_t buffer[BUFFERSIZE_256];
		wsprintf(buffer, L"Comeplete !!!\nScore: %d", Score);
		//wsprintf(notify, L"%s: %d", notify, Score);
	
		MessageBox(NULL, buffer,
			(LPCWSTR)L"Congratulation",
			MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2);

		KillTimer(hwnd, TimmerID1s);
		DestroyWindow(Timer);
		FirstAnswerButton->unused = true;
		SecondAnswerButton->unused = true;
	}
}


void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	ULONG_PTR gdiplusToken;
	HDC hdc = BeginPaint(hwnd, &ps);

	EndPaint(hwnd, &ps);
}

void ReadIniFile()
{
	WCHAR buffer[BUFFERSIZE_260];
	WCHAR curPath[BUFFERSIZE_260];
	WCHAR configPath[BUFFERSIZE_260];
	WCHAR PlayerKeyBuffer[BUFFERSIZE_260];

	// Tạo đường dẫn tuyệt đối tới file config
	GetCurrentDirectory(BUFFERSIZE_260, curPath);
	wsprintf(configPath, L"%s\\config.ini", curPath);
	GetPrivateProfileString(L"app", L"Number_Of_Players", L"Default value", buffer, BUFFERSIZE_260, configPath);
	NUMBER_OF_PLAYERS = _wtoi(buffer);
	
	for (int pos = 0; pos < NUMBER_OF_PLAYERS; pos++)
	{
		PlayerNames[pos] = new WCHAR[NAME_LENGTH];

		swprintf(PlayerKeyBuffer, 15,L"player_name%d", pos);
		GetPrivateProfileString(L"app", PlayerKeyBuffer, L"Default value", buffer, BUFFERSIZE_260, configPath);
		
		wcscpy_s(PlayerNames[pos], NAME_LENGTH,buffer);
	}
}

void DestroyAllHWNDOnScreen()
{
	DestroyWindow(FirstAnswerButton);
	DestroyWindow(SecondAnswerButton);
	DestroyWindow(PlayerImage);
	DestroyWindow(Scores);
}

void RandomPlayerImage()
{
	srand(time(NULL));
	int index = rand() % NUMBER_OF_PLAYERS;
	vector<int> generatedValues;
	generatedValues.push_back(index);
	Player_Result[0] = index;

	for (int i = 1; i < NUMBER_OF_PLAYERS; i++)
	{
		int count = 0;
		while (Contains(generatedValues, index))
		{
			index = rand() % NUMBER_OF_PLAYERS;
			count++;
			if (count == NUMBER_OF_PLAYERS )
				break;
		}
		
		generatedValues.push_back(index);
		Player_Result[i] = index;
		if (count == NUMBER_OF_PLAYERS)
			break;
	}
}

bool Contains(const std::vector<int> &list, int x)
{
	return std::find(list.begin(), list.end(), x) != list.end();
}

void Random_Answer(int currentQuestionIndex)
{
	srand(time(NULL));
	random_result = rand() % 2;
	switch (random_result)
	{
	case 0:
		firstAnswer = Player_Result[currentQuestionIndex];
		Random_False_Answer(secondAnswer, firstAnswer);
		break;
	case 1:
		secondAnswer = Player_Result[currentQuestionIndex];
		Random_False_Answer(firstAnswer, secondAnswer);
		break;
	}
}

void Random_False_Answer(int &Answer, int result)
{
	Answer = rand() % NUMBER_OF_PLAYERS;
	while (Answer == result)
	{
		Answer = rand() % NUMBER_OF_PLAYERS;
	}
}

void UpdateTimer(HWND hwnd)
{
	KillTimer(hwnd, TimmerID10s);
	KillTimer(hwnd, TimmerID1s);
	CountDownTimer = 10;
	TimmerID10s = SetTimer(hwnd, ID_10SECONDS, 10 * 1000, NULL);
	TimmerID1s = SetTimer(hwnd, ID_1SECONDS, 1 * 1000, NULL);
}