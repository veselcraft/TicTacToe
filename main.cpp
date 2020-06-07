#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <cstdio>
#include <commctrl.h>

#include "resources.h"

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[ ] = _T("TicTacToeVeselcraft");

HINSTANCE hInstance;

// game itself

int GameArea[3][3] = {
{0,0,0},
{0,0,0},
{0,0,0}
};

HBITMAP xImage, oImage;

HWND BtnHwnd[3][3], StatusBarHwnd;

DWORD str;

bool WhoPlays = true; // true = first player, false = second player
bool GameEnded = false;

//for animated about box

int XPos1 = 15;
int XPos2 = 18;
int XPos3 = 21;
int XPos4 = 24;

bool XPosR1 = false;
bool XPosR2 = false;
bool XPosR3 = false;
bool XPosR4 = false;

RECT Text1, Text2, Text3, Text4, Wndw;

int XPosClient1, XPosClient2, XPosClient3, XPosClient4;

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;
    hInstance = hThisInstance;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_APPWORKSPACE;

    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
           0,
           szClassName,
           _T("Tic-Tac-Toe"),
           WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU|DS_SHELLFONT,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           218,
           280,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );

    ShowWindow (hwnd, nCmdShow);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        SetTimer(hwndDlg, 2, 50, nullptr);
    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
            case 5:
            EndDialog(hwndDlg, 0);
                break;
        }
    }
    return TRUE;

    case WM_TIMER:
    {
        GetWindowRect(GetDlgItem(hwndDlg, 1), &Text1);
        GetWindowRect(GetDlgItem(hwndDlg, 2), &Text2);
        GetWindowRect(GetDlgItem(hwndDlg, 3), &Text3);
        GetWindowRect(GetDlgItem(hwndDlg, 4), &Text4);
        GetWindowRect(hwndDlg, &Wndw);
        XPosClient1 = Text1.left - Wndw.left;
        if(XPosClient1 > 35){
            XPosR1 = true;
        }else if(XPosClient1 < 25){
            XPosR1 = false;
        }

        if(XPosR1 == true){
            XPos1--;
        }else{
            XPos1++;
        }

        SetWindowPos(GetDlgItem(hwndDlg, 1), HWND_TOP, XPos1,20,120,16,SWP_SHOWWINDOW);

        XPosClient2 = Text2.left - Wndw.left;
        if(XPosClient2 > 35){
            XPosR2 = true;
        }else if(XPosClient2 < 25){
            XPosR2 = false;
        }

        if(XPosR2 == true){
            XPos2--;
        }else{
            XPos2++;
        }

        SetWindowPos(GetDlgItem(hwndDlg, 2), HWND_TOP, XPos2,20+15,120,16,SWP_SHOWWINDOW);

        XPosClient3 = Text3.left - Wndw.left;
        if(XPosClient3 > 35){
            XPosR3 = true;
        }else if(XPosClient3 < 25){
            XPosR3 = false;
        }

        if(XPosR3 == true){
            XPos3--;
        }else{
            XPos3++;
        }

        SetWindowPos(GetDlgItem(hwndDlg, 3), HWND_TOP, XPos3,20+15+15,120,16,SWP_SHOWWINDOW);

        XPosClient4 = Text4.left - Wndw.left;
        if(XPosClient4 > 35){
            XPosR4 = true;
        }else if(XPosClient4 < 25){
            XPosR4 = false;
        }

        if(XPosR4 == true){
            XPos4--;
        }else{
            XPos4++;
        }

        SetWindowPos(GetDlgItem(hwndDlg, 4), HWND_TOP, XPos4,20+15+15+15,120,16,SWP_SHOWWINDOW);
    }
    return TRUE;
    }
    return FALSE;
}

void CreateControls(HWND hwnd)
{
    BtnHwnd[0][0] = CreateWindowEx(NULL,"button","",WS_VISIBLE | WS_CHILD | BS_BITMAP,20             ,20             ,50,50,hwnd,(HMENU)ID_11,hInstance,NULL);
    BtnHwnd[0][1] = CreateWindowEx(NULL,"button","",WS_VISIBLE | WS_CHILD | BS_BITMAP,20+50+10       ,20             ,50,50,hwnd,(HMENU)ID_12,hInstance,NULL);
    BtnHwnd[0][2] = CreateWindowEx(NULL,"button","",WS_VISIBLE | WS_CHILD | BS_BITMAP,20+50+10+50+10 ,20             ,50,50,hwnd,(HMENU)ID_13,hInstance,NULL);
    BtnHwnd[1][0] = CreateWindowEx(NULL,"button","",WS_VISIBLE | WS_CHILD | BS_BITMAP,20             ,20+50+10       ,50,50,hwnd,(HMENU)ID_21,hInstance,NULL);
    BtnHwnd[1][1] = CreateWindowEx(NULL,"button","",WS_VISIBLE | WS_CHILD | BS_BITMAP,20+50+10       ,20+50+10       ,50,50,hwnd,(HMENU)ID_22,hInstance,NULL);
    BtnHwnd[1][2] = CreateWindowEx(NULL,"button","",WS_VISIBLE | WS_CHILD | BS_BITMAP,20+50+10+50+10 ,20+50+10       ,50,50,hwnd,(HMENU)ID_23,hInstance,NULL);
    BtnHwnd[2][0] = CreateWindowEx(NULL,"button","",WS_VISIBLE | WS_CHILD | BS_BITMAP,20             ,20+50+10+50+10 ,50,50,hwnd,(HMENU)ID_31,hInstance,NULL);
    BtnHwnd[2][1] = CreateWindowEx(NULL,"button","",WS_VISIBLE | WS_CHILD | BS_BITMAP,20+50+10       ,20+50+10+50+10 ,50,50,hwnd,(HMENU)ID_32,hInstance,NULL);
    BtnHwnd[2][2] = CreateWindowEx(NULL,"button","",WS_VISIBLE | WS_CHILD | BS_BITMAP,20+50+10+50+10 ,20+50+10+50+10 ,50,50,hwnd,(HMENU)ID_33,hInstance,NULL);
    StatusBarHwnd = CreateWindowEx(NULL,"static","X player's turn.",WS_VISIBLE | WS_CHILD,20 ,20+50+10+50+10+50+10,150,20,hwnd,(HMENU)ID_STATUSBAR,hInstance,NULL);
}

void SetStatusBarText(LPCSTR text)
{
    SetWindowText(StatusBarHwnd, text);
}

void AddMenu(HWND hwnd){
    HMENU hMenu = CreateMenu();
    HMENU hGameMenu = CreateMenu();
    HMENU hAboutMenu = CreateMenu();

    AppendMenu(hGameMenu, MF_STRING, ID_NEW, "New game");
    AppendMenu(hGameMenu, MF_STRING, ID_EXIT, "Exit");

    AppendMenu(hAboutMenu, MF_STRING, ID_ABOUT, "About");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hGameMenu, "Game");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hAboutMenu, "About");

    SetMenu(hwnd, hMenu);
}

void LoadImages()
{
    xImage = (HBITMAP)LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_XICON));
    oImage = (HBITMAP)LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_OICON));
}

void CheckForWinner(HWND hwnd)
{
    for(int i = 1; i <= 2; i++){
        if(GameArea[0][0] == i && GameArea[0][1] == i && GameArea[0][2] == i ||
           GameArea[1][0] == i && GameArea[1][1] == i && GameArea[1][2] == i ||
           GameArea[2][0] == i && GameArea[2][1] == i && GameArea[2][2] == i ||
           GameArea[0][0] == i && GameArea[1][1] == i && GameArea[2][2] == i ||
           GameArea[0][2] == i && GameArea[1][1] == i && GameArea[2][0] == i ||
           GameArea[0][0] == i && GameArea[1][0] == i && GameArea[2][0] == i ||
           GameArea[0][1] == i && GameArea[1][1] == i && GameArea[2][1] == i ||
           GameArea[0][2] == i && GameArea[1][2] == i && GameArea[2][2] == i){
            LPCTSTR winner;
            if (i == 1){
                winner = "X is the winner!";
            }else{
                winner = "O is the winner!";
            }
            SetStatusBarText("Start a new game.");
            MessageBox(hwnd, winner, "Tic-Tac-Toe", MB_OK | MB_ICONINFORMATION);
            GameEnded = true;
        }
    }
}

void SetMark(HWND hwnd, int y, int x){
    if(GameArea[y][x] == 0 && GameEnded == false){
        if(WhoPlays){
            GameArea[y][x] = 1;
            SendMessage(BtnHwnd[y][x],BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)xImage);
            SetStatusBarText("O player's turn.");
        }else{
            GameArea[y][x] = 2;
            SendMessage(BtnHwnd[y][x],BM_SETIMAGE,IMAGE_BITMAP,(LPARAM)oImage);
            SetStatusBarText("X player's turn.");
        }
        WhoPlays ? WhoPlays = false : WhoPlays = true;
        CheckForWinner(hwnd);
    }
}

void ClearGameArea()
{
    ZeroMemory(&GameArea, sizeof(GameArea));
    GameEnded = false;
    for(int i = 0; i <= 2; i++){
        for(int a = 0; a <= 2; a++){
            SendMessage(BtnHwnd[i][a],BM_SETIMAGE,NULL,NULL);
        }
    }
    WhoPlays ? SetStatusBarText("X player's turn.") : SetStatusBarText("O player's turn.");
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_DESTROY:
            PostQuitMessage (0);
            break;
        case WM_CREATE:
            CreateControls(hwnd);
            AddMenu(hwnd);
            LoadImages();
            break;
        case WM_COMMAND:
            switch(wParam){
                case ID_EXIT:
                    PostQuitMessage (0);
                    break;
                case ID_NEW:
                    ClearGameArea();
                    break;
                case ID_ABOUT:
                    DialogBox(hInstance, MAKEINTRESOURCE(DLG_ABOUT), hwnd, (DLGPROC)DlgMain);
                    break;
                case ID_11:
                    SetMark(hwnd, 0, 0);
                    break;
                case ID_12:
                    SetMark(hwnd, 0, 1);
                    break;
                case ID_13:
                    SetMark(hwnd, 0, 2);
                    break;
                case ID_21:
                    SetMark(hwnd, 1, 0);
                    break;
                case ID_22:
                    SetMark(hwnd, 1, 1);
                    break;
                case ID_23:
                    SetMark(hwnd, 1, 2);
                    break;
                case ID_31:
                    SetMark(hwnd, 2, 0);
                    break;
                case ID_32:
                    SetMark(hwnd, 2, 1);
                    break;
                case ID_33:
                    SetMark(hwnd, 2, 2);
                    break;
            }
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
