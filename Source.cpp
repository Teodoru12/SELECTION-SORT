#include <windows.h>
#include <CommCtrl.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define ID_BEEP 1
#define ID_QUIT 20
#define ID_EDIT 10
#define ID_BUTTON 2
#define ID_vectori 101
#define ID_LSI 102
#define ID_LDI 103


typedef struct nodS{
	int numar;
	nodS *urmator;
};

nodS *head=NULL,*end=NULL;

typedef struct nodD{
	int numar;
	nodD *urmator,*precedent;
};

nodD *prim=NULL,*ultim=NULL;

void createS(int x)
{
	nodS *p;
	p=(nodS*)malloc(sizeof(nodS));
	p->numar=x;
	p->urmator=NULL;
	if(head==NULL)
	{
		head=end=p;
	}
		end->urmator=p;
		end=p;
}


void createD(int x)
{
	nodD *p;
	p=(nodD*)malloc(sizeof(nodD));
	p->numar=x;
	if(prim==NULL)
	{
		prim=ultim=p;
		p->urmator=NULL;
		p->precedent=NULL;
		return;
	}
	else
	{
		ultim->urmator=p;
		p->precedent=ultim;
		p->urmator=NULL;
		ultim=p;
	}



}

void afisareS()
{
	nodS *p;
	p=head;
	while(p!=NULL)
	{
//		printf("%d ",p->numar);
		p=p->urmator;
	}
//	printf("\n");
}

void sortare_lista_simpla(nodS *first)
{
	nodS *x;
	nodS *p=first;
	nodS *poz,*j;
	poz=(nodS*)malloc(sizeof(nodS));
	j=(nodS*)malloc(sizeof(nodS));
	x=(nodS*)malloc(sizeof(nodS));
	for(p=first;p!=end;p=p->urmator)
	{
		x=p;
		for(j=p->urmator;j!=NULL;j=j->urmator)
			if(j->numar<x->numar)
			{
				x=j;
			}
			if(x!=p)
			{
				int aux;
				aux=x->numar;
				x->numar=p->numar;
				p->numar=aux;
			}
	}
	first=p;
}

void sortare_lista_dubla(nodD *first)
{
	nodD *x;
	nodD *p=first;
	nodD *poz,*j;
	poz=(nodD*)malloc(sizeof(nodD));
	j=(nodD*)malloc(sizeof(nodD));
	x=(nodD*)malloc(sizeof(nodD));
	for(p=first;p!=ultim;p=p->urmator)
	{
		x=p;
		for(j=p->urmator;j!=NULL;j=j->urmator)
			if(j->numar<x->numar)
			{
				x=j;
			}
			if(x!=p)
			{
				int aux;
				aux=x->numar;
				x->numar=p->numar;
				p->numar=aux;
			}
	}
	first=p;
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


//void CreateControls(HWND hwnd);
//void UpdateLabel(void);

HWND hTrack;
HWND hlbl;
HWND numar;





int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR lpCmdLine, int nCmdShow) {

    MSG  msg;    
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"Static image";
    wc.hInstance     = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0,IDC_ARROW);
	wc.lpszClassName = L"Edit control";
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
	wc.lpszClassName = L"Trackbar";

  
    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Selection Sort!",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  350, 250, 530, 370, 0, 0, hInstance, 0);

	/*RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Trackbar", 
        WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 350, 180, 0, 0, hInstance, 0);*/
    while (GetMessage(&msg, NULL, 0, 0)) {
    
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

  return (int) msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, 
    WPARAM wParam, LPARAM lParam) {
    
	static wchar_t *mesaj =  L"Introduceti numarul de elemente ce doriti sa fie sortate!";
	static wchar_t *mesaj1 = L"Introduceti numerele ce doriti sa fie sortate!";
	static wchar_t *mesaj2 = L"Vectorul ordonat";
	static wchar_t *mesaj3 = L"Lista simplu inlantuita ordonata:";
	static wchar_t *mesaj4 = L"Lista dublu inlantuita ordonata:";
	HDC hdc;
    PAINTSTRUCT ps;

    POINT points[4] = { 0, 40, 40, 0 };
	static HWND hwndEdit;
    HWND hwndButton,hwndButton1,hwndButton2,hwndButton3;

    switch(msg) {

        case WM_CREATE:
    

			CreateWindowW(L"Static", mesaj, 
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                40, 20, 300, 230, 
                hwnd, (HMENU) 1, NULL, NULL);

			/*hwndEdit = CreateWindowW(L"Edit", NULL, 
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				 50, 50, 150, 20, hwnd, (HMENU) ID_EDIT,
				NULL, NULL);*/

			numar=CreateWindowEx(WS_EX_CLIENTEDGE,"Edit", " ", WS_CHILD | WS_VISIBLE | ES_NUMBER,50,50,150,20,hwnd,NULL,NULL,NULL);
       
			hwndButton = CreateWindowW(L"button", L"OK",
                WS_VISIBLE | WS_CHILD, 50, 100, 80, 25,
                hwnd, (HMENU) ID_BUTTON, NULL, NULL);

			CreateWindowW(L"Button", L"Quit",
                WS_VISIBLE | WS_CHILD ,
                150, 100, 80, 25, hwnd, (HMENU) ID_QUIT, NULL, NULL);
            break;

            break;
			

		/*case WM_HSCROLL:{
			UpdateLabel();
			break;
			}*/


		case WM_COMMAND:
			switch(LOWORD(wParam))
            {
				case ID_BUTTON:
				{
					ShowWindow(hwndButton,SW_HIDE);

					CreateWindowW(L"Static", mesaj1, 
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                20, 20, 300, 230, 
                hwnd, (HMENU) 1, NULL, NULL);

					hwndButton1 = CreateWindowW(L"button", L"Vectori",
                WS_VISIBLE | WS_CHILD, 15, 150, 80, 25,
                hwnd, (HMENU) ID_vectori, NULL, NULL);

					hwndButton2 = CreateWindowW(L"button", L"LSI",
                WS_VISIBLE | WS_CHILD, 125, 150, 80, 25,
                hwnd, (HMENU) ID_LSI, NULL, NULL);

					hwndButton3 = CreateWindowW(L"button", L"LDI",
                WS_VISIBLE | WS_CHILD, 235, 150, 80, 25,
                hwnd, (HMENU) ID_LDI, NULL, NULL);

					hwndEdit = CreateWindowW(L"Edit", NULL, 
				WS_CHILD | WS_VISIBLE | WS_BORDER,
				 50, 50, 150, 20, hwnd, (HMENU) ID_EDIT,
				NULL, NULL);
				}
				break;

				case ID_QUIT:{
					MessageBox(hwnd,"Mesaj de iesire!",NULL,NULL);
					PostQuitMessage(0);
					break;
				}

				case ID_vectori:{
					CreateWindowW(L"Static", mesaj2, 
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                20, 20, 300, 230, 
                hwnd, (HMENU) 1, NULL, NULL);

					
					case WM_PAINT:

					hdc = BeginPaint(hwnd, &ps);

					PolyBezier(hdc, points, 4);

					EndPaint(hwnd, &ps);
            break;

				/*MessageBox( NULL,
                "Welcome to Win32 Application Development\n"
                "You will learn about functions, classes, "
                "communication, and other cool stuff\n"
                "Are you ready to rumble!!!!!!!!!!!!!!",
                NULL,
                MB_YESNOCANCEL | MB_ICONQUESTION);*/
					//CreateControls(hwnd);
					break;
					
				}

				case ID_LSI:{
					//sortare_lista_dubla(p);
					CreateWindowW(L"Static", mesaj3, 
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                20, 20, 300, 230, 
                hwnd, (HMENU) 1, NULL, NULL);
				
				//	CreateControls(hwnd);
					 break;
				
				}

				case ID_LDI:{
					CreateWindowW(L"Static", mesaj4, 
                WS_CHILD | WS_VISIBLE | SS_LEFT,
                20, 20, 300, 230, 
                hwnd, (HMENU) 1, NULL, NULL);
			
					//CreateControls(hwnd);
					  break;

				}


			}
			break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
		break;
	}

	return DefWindowProc(hwnd,msg,wParam,lParam);
}


