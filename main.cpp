#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <tchar.h>
#include <windows.h>
#include <cstdio>
#include <commctrl.h>

#include "resources.h"

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[ ] = _T("TicTacToeVeselcraft");

HINSTANCE hInstance;

// network

const char szHost[] = "";

SOCKET Connection;

bool ConnectedServer = false;

bool ConnectedClient = false;

bool WhoIsOpponent = false; // true = first player, false = second player

int GameAreaNetwork[3][3] = {
{0,1,2},
{3,4,5},
{6,7,8}
};

char* ip[256];

// game itself

int GameArea[3][3] = {
{0,0,0},
{0,0,0},
{0,0,0}
};

HBITMAP xImage, oImage;

HWND BtnHwnd[3][3], StatusBarHwnd, hwnd;

HANDLE hndlClient, hndlServer, hndlClientListen, hndlServerListen;

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
    MSG messages;
    WNDCLASSEX wincl;
    hInstance = hThisInstance;

    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = 0;
    wincl.hIconSm = 0;
    //wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    //wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_WINDOW;

    if (!RegisterClassEx (&wincl))
        return -1;

    hwnd = CreateWindowEx (
           0,
           szClassName,
           _T("Tic-Tac-Toe"),
           WS_OVERLAPPED|WS_CAPTION|WS_MINIMIZEBOX|WS_SYSMENU|WS_EX_DLGMODALFRAME,
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

// About dialog

BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        SetTimer(hwndDlg, 2, 50, NULL);
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
        // TODO: GOVNOKOD, PEREDELAT'

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

//GUI

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

    HFONT hf;

    hf = CreateFont(15, 0, 0, 0, 0, FALSE, 0, 0, 0, 0, 0, 0, 0, "MS Shell Dlg");

    if(hf)
    {
        SendDlgItemMessage(hwnd, ID_STATUSBAR, WM_SETFONT, (WPARAM)hf, TRUE);
    }
}

void SetStatusBarText(LPCSTR text)
{
    SetWindowText(StatusBarHwnd, text);
}

void AddMenu(HWND hwnd){
    HMENU hMenu = CreateMenu();
    HMENU hGameMenu = CreateMenu();
    HMENU hHelpMenu = CreateMenu();

    AppendMenu(hGameMenu, MF_STRING, ID_NEW, "&New game");
    AppendMenu(hGameMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hGameMenu, MF_STRING, ID_STARTSERVER, "&Start server");
    AppendMenu(hGameMenu, MF_STRING, ID_CONNECT, "&Connect to server");
    AppendMenu(hGameMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hGameMenu, MF_STRING, ID_EXIT, "E&xit");

    AppendMenu(hHelpMenu, MF_STRING, ID_HELP, "&Contents");
    AppendMenu(hHelpMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hHelpMenu, MF_STRING, ID_ABOUT, "&About");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hGameMenu, "&Game");
    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hHelpMenu, "&Help");

    SetMenu(hwnd, hMenu);
}

void LoadImages()
{
    xImage = (HBITMAP)LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_XICON));
    oImage = (HBITMAP)LoadBitmap(hInstance,MAKEINTRESOURCE(IDB_OICON));
}

// GCC is retarded

void TerminateWinSOCK()
{
    ConnectedServer = false;
    ConnectedClient = false;
    closesocket(Connection);
    WSACleanup();

    TerminateThread (hndlClient, 0);
    TerminateThread (hndlClientListen, 0);
    TerminateThread (hndlServer, 0);
    TerminateThread (hndlServerListen, 0);

}

// Game

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
            GameEnded = true;
            if(ConnectedServer || ConnectedClient){
                TerminateWinSOCK();
            }
            MessageBox(hwnd, winner, "Tic-Tac-Toe", MB_OK | MB_ICONINFORMATION);
        }
    }
}

void SetMarkLowLevel(HWND hwnd, int y, int x){
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

void SetMark(HWND hwnd, int y, int x, bool c)
{

    char number[3];

    number[1] = '\r';
    number[2] = '\n';


    if(ConnectedServer || ConnectedClient){
        itoa(GameAreaNetwork[y][x]+1, number, 10);
        if(WhoPlays == false && WhoIsOpponent == false && c == true){
            SetMarkLowLevel(hwnd, y, x);
        }else if(WhoPlays == true && WhoIsOpponent == true && c == true){
            SetMarkLowLevel(hwnd, y, x);
        }else if(WhoPlays == true && WhoIsOpponent == false && c == false){
            send(Connection, number, sizeof(number), NULL);
            SetMarkLowLevel(hwnd, y, x);
        }else if(WhoPlays == false && WhoIsOpponent == true && c == false){
            send(Connection, number, sizeof(number), NULL);
            SetMarkLowLevel(hwnd, y, x);
        }
    }else{
        SetMarkLowLevel(hwnd, y, x);
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

// Server

void ListenClient()
{
    char msg[256];
    char protocolver[256] = "TTT20\r\n";
    bool opponentReady = false;
    while(true) {
        recv(Connection, msg, sizeof(msg)+1, NULL);
        printf(msg);
        if(opponentReady == false){
            if(strcmp(msg, protocolver) == 0)
            {
                if(WhoPlays == false)
                    send(Connection, "YOU\r\n", sizeof("YOU\r\n"), NULL); WhoIsOpponent = true;
                if(WhoPlays == true)
                    send(Connection, "ME\r\n", sizeof("ME\r\n"), NULL); WhoIsOpponent = false;

                ConnectedServer = true;
                opponentReady = true;
                GameEnded = false;
                WhoPlays ? SetStatusBarText("X player's turn.") : SetStatusBarText("O player's turn.");
            }
            else
            {
                send(Connection, "SORRYNOTSUPPORTED\r\n", sizeof("SORRYNOTSUPPORTED\r\n")-1, NULL);
                ConnectedServer = false;
                closesocket(Connection);
                MessageBoxA(hwnd, "Sorry, but your opponent need to update their version of Tic-Tac-Toe.", "Tic-Tac-Toe", MB_OK | MB_ICONERROR);
                return;
            }
        }else{
            int x[9] = {0, 1, 2, 0, 1, 2, 0, 1, 2};
            for (int i = 1; i < 10; i++)
            {
                if(atoi(msg) == i) {
                    SetMark(hwnd, (i-1)/3, x[i-1], true);
                }else if(atoi(msg) == 0)
                {
                    TerminateWinSOCK();
                    MessageBoxA(hwnd, "Your opponent has disconnected from the game.", "Tic-Tac-Toe", MB_OK | MB_ICONERROR);
                }
            }
        }
        ZeroMemory(msg, 256);
    }
}

void ServerStart(){
    ConnectedServer = true;
    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if(WSAStartup(DLLVersion, &wsaData) != 0)
    {
        MessageBoxA(hwnd, "Failed to run Winsock server (WSAStartup error)", "Error", MB_OK | MB_ICONERROR);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeofaddr);
    listen(sListen, 1);

    Connection = accept(sListen, (SOCKADDR*)&addr, &sizeofaddr);

    if(Connection == 0)
    {
        MessageBoxA(hwnd, "Client failed to connect", "Error", MB_OK | MB_ICONERROR);
    }
    else
    {
        char msg[64] = "HELLOWHOAREYOU\r\n";
        send(Connection, msg, sizeof(msg), NULL);
        SetStatusBarText("Opponent connected.");
        hndlServerListen = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ListenClient, NULL, NULL, NULL);
    }
}

// Client

void ListenServer()
{
    char msg[256];
    char welcomemsg[256] = "HELLOWHOAREYOU\r\n";
    char protocolver[256] = "TTT20\r\n";
    char memsg[256] = "ME\r\n";
    char youmsg[256] = "YOU\r\n";
    char notsupportedmsg[256] = "SORRYNOTSUPPORTED\r\n";
    bool opponentReady = false;
    while(true) {
        recv(Connection, msg, sizeof(msg)+1, NULL);
        printf(msg);
        if(opponentReady == false){
            if(strcmp(msg, welcomemsg) == 0)
            {
                send(Connection, protocolver, sizeof(protocolver), NULL);
            }
            else if(strcmp(msg, memsg) == 0)
            {
                ConnectedClient = true;
                opponentReady = true;
                WhoIsOpponent = true;
                WhoPlays = true;
                SetStatusBarText("Opponent's turn.");
            }
            else if(strcmp(msg, youmsg) == 0)
            {
                ConnectedClient = true;
                opponentReady = true;
                WhoIsOpponent = false;
                WhoPlays = true;
                SetStatusBarText("Your turn.");
            }
            else if(strcmp(msg, notsupportedmsg) == 0)
            {
                ConnectedClient = false;
                closesocket(Connection);
                MessageBoxA(hwnd, "Sorry, but your need to update Tic-Tac-Toe to actual version.", "Tic-Tac-Toe", MB_OK | MB_ICONERROR);
            }
        }

        if(opponentReady == true){
            int x[9] = {0, 1, 2, 0, 1, 2, 0, 1, 2};
            for (int i = 1; i < 10; i++)
            {
                if(strcmp(msg, memsg) != 0){
                    if(atoi(msg) == 0)
                    {
                        TerminateWinSOCK();
                        MessageBoxA(hwnd, "Client closed the connection. It means your opponent quit from the game.", "Tic-Tac-Toe", MB_OK | MB_ICONERROR);
                    }else if(atoi(msg) == i) {
                        SetMark(hwnd, (i-1)/3, x[i-1], true);
                    }
                }
            }
        }
        ZeroMemory(msg, 256);
    }
}

void ClientStart(){
    SetStatusBarText("Connecting...");
    ConnectedClient = true;

    WSAData wsaData;
    WORD DLLVersion = MAKEWORD(2, 1);
    if(WSAStartup(DLLVersion, &wsaData) != 0)
    {
        MessageBoxA(hwnd, "Failed to run Winsock client (WSAStartup error)", "Error", MB_OK | MB_ICONERROR);
        SetStatusBarText("Start a new game.");
        TerminateWinSOCK();
        return;
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_addr.s_addr = inet_addr(reinterpret_cast<const char*>(const_cast<char**>(ip)));
    addr.sin_port = htons(PORT);
    addr.sin_family = AF_INET;

    Connection = socket(AF_INET, SOCK_STREAM, NULL);

    if(connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0)
    {
        MessageBoxA(hwnd, "Client failed to connect", "Error", MB_OK | MB_ICONERROR);
        SetStatusBarText("Start a new game.");
        TerminateWinSOCK();
        return;
    }
    else
    {
        hndlClientListen = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ListenServer, NULL, NULL, NULL);
    }
}

BOOL CALLBACK ConnectDlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    GetWindowTextA(GetDlgItem(hwndDlg, DLG_ID_TEXTBOX), (LPSTR)(&ip), 256);
                    hndlClient = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientStart, NULL, NULL, NULL);
                case IDCANCEL:
                    EndDialog(hwndDlg, TRUE);
                    break;
            }
            break;
            return TRUE;

        case WM_CLOSE:
            EndDialog(hwndDlg, FALSE);
            break;
            return TRUE;
    }
    return FALSE;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
        case WM_INITDIALOG:
            return TRUE;
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
                    if(ConnectedServer || ConnectedClient){
                        TerminateWinSOCK();
                    }
                    break;
                case ID_ABOUT:
                    DialogBox(hInstance, MAKEINTRESOURCE(DLG_ABOUT), hwnd, (DLGPROC)DlgMain);
                    break;
                case ID_STARTSERVER:
                    if(ConnectedClient == true){
                        MessageBoxA(hwnd, "You are connected to client! Finish the game, please.", "Tic-Tac-Toe", MB_OK | MB_ICONERROR);
                    }else if(ConnectedServer == true){
                        MessageBoxA(hwnd, "You are a server already.", "Tic-Tac-Toe", MB_OK | MB_ICONERROR);
                    }else{
                        ClearGameArea();
                        hndlServer = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ServerStart, NULL, NULL, NULL);
                        GameEnded = true;
                        SetStatusBarText("Wait for opponent.");
                    }
                    break;
                case ID_CONNECT:
                    if(ConnectedClient == true){
                        MessageBoxA(hwnd, "You are connected to client! Finish the game, please.", "Tic-Tac-Toe", MB_OK | MB_ICONERROR);
                    }else if(ConnectedServer == true){
                        MessageBoxA(hwnd, "You are a server and you can't connect to the another server.", "Tic-Tac-Toe", MB_OK | MB_ICONERROR);
                    }else{
                        DialogBox(hInstance, MAKEINTRESOURCE(DLG_CONNECT), hwnd, (DLGPROC)ConnectDlgMain);
                    }
                    break;
                case ID_HELP:
                    ShellExecute(0, 0, "https://www.wikihow.com/Play-Tic-Tac-Toe", 0, 0 ,SW_SHOW);
                    break;
                case ID_11:
                    SetMark(hwnd, 0, 0, false);
                    break;
                case ID_12:
                    SetMark(hwnd, 0, 1, false);
                    break;
                case ID_13:
                    SetMark(hwnd, 0, 2, false);
                    break;
                case ID_21:
                    SetMark(hwnd, 1, 0, false);
                    break;
                case ID_22:
                    SetMark(hwnd, 1, 1, false);
                    break;
                case ID_23:
                    SetMark(hwnd, 1, 2, false);
                    break;
                case ID_31:
                    SetMark(hwnd, 2, 0, false);
                    break;
                case ID_32:
                    SetMark(hwnd, 2, 1, false);
                    break;
                case ID_33:
                    SetMark(hwnd, 2, 2, false);
                    break;
            }
            break;
        default:
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
