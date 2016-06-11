#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<commctrl.h>
#include<time.h>

#define ID_BEEP 1
#define ID_QUIT 20
#define ID_EDIT 10
#define ID_BUTTON 2
#define ID_vectori 101
#define ID_LSI 102
#define ID_LDI 103
#define ID_GRAFIC1 1001
#define ID_GRAFIC2 1002
#define ID_GRAFIC3 1003

char c[100];
int v[100];

HWND vectori_result;

typedef struct nodS{
int numar;
struct nodS *urmator;
};

nodS *head = NULL;
nodS *end = NULL;

typedef struct nodD {
	int numar;
	struct nodD *urmator, *precedent;
};

nodD *prim = NULL;
nodD *ultim = NULL;

void schimbare(int **a, char ***c, int n)
{
	for (int i = 0; i<n; i++)
	{
		(*c)[i] = (char*)malloc(10);
		_itoa((*a)[i], (*c)[i], 10);
	}
}


void createS(int x)
{
	nodS *p;
	p=(nodS*)malloc(sizeof(nodS));
	p->numar=x;
	p->urmator=NULL;
	if(head==NULL)
	{
	head=end=p;
	return;
	}
	end->urmator=p;
	end=p;
}


void createD(int x)
{
nodD *p;
p=(nodD*)malloc(sizeof(nodD));
p->numar=x;
if(prim == NULL)
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

void afisareS(HWND hwnd)
{
	nodS *p;
	p = head;
	int *a = NULL, k = 0;

	while(p)
	{
		a = (int *)realloc(a, (k + 1)*sizeof(int));
		a[k] = p->numar;
		k++;
		p = p->urmator;
	}

	char **s;
	s = (char**)malloc(sizeof(char*)*k);

	char string[1000];
	schimbare(&a, &s, k);
	strcpy(string, s[0]);
	strcat(string, " ");

	for (int i = 1; i < k; i++)
	{
		strcat(string, s[i]);
		strcat(string, " ");
	}

	vectori_result = CreateWindow("Static", TEXT(string), WS_CHILD | WS_VISIBLE | SS_LEFT, 20, 70, 600, 30, hwnd, NULL, NULL, NULL);

	SendMessage(vectori_result,     /*HWND*/        /*Label*/
		WM_SETTEXT,     /*UINT*/        /*Message*/
		NULL,           /*WPARAM*/      /*Unused*/
		(LPARAM)TEXT(string));  /*LPARAM*/      /*Text*/
}

void afisareD(HWND hwnd)
{
	nodD *p;
	p = prim;
	int *a = NULL, k = 0;

	while(p)
	{
		a = (int *)realloc(a, (k + 1)*sizeof(int));
		a[k] = p->numar;
		k++;
		p = p->urmator;
	}

	char **s;
	s = (char**)malloc(sizeof(char*)*k);

	char string[1000];
	schimbare(&a, &s, k);
	strcpy(string, s[0]);
	strcat(string, " ");

	for (int i = 1; i < k; i++)
	{
		strcat(string, s[i]);
		strcat(string, " ");
	}

	vectori_result = CreateWindow("Static", TEXT(string), WS_CHILD | WS_VISIBLE | SS_LEFT, 20, 70, 600, 30, hwnd, NULL, NULL, NULL);

	SendMessage(vectori_result,     /*HWND*/        /*Label*/
		WM_SETTEXT,     /*UINT*/        /*Message*/
		NULL,           /*WPARAM*/      /*Unused*/
		(LPARAM)TEXT(string));  /*LPARAM*/      /*Text*/
}


void sortare_lista_simpla()
{
	nodS *x;
	nodS *p=head;
	nodS *poz,*j;
	poz=(nodS*)malloc(sizeof(nodS));
	j=(nodS*)malloc(sizeof(nodS));
	x=(nodS*)malloc(sizeof(nodS));

	for(p=head;p!=end;p=p->urmator)
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
}

void sortare_lista_dubla()
{
	nodD *x;
	nodD *p=prim;
	nodD *poz,*j;
	poz=(nodD*)malloc(sizeof(nodD));
	j=(nodD*)malloc(sizeof(nodD));
	x=(nodD*)malloc(sizeof(nodD));
		for(p=prim;p!=ultim;p=p->urmator)
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
}


void sort_selectie(HWND hwnd, int n, int a[100])

{
	int i, j, poz;
	int x;

	char **s;
	s = (char**)malloc(sizeof(char*)*n);

	for (i = 0; i<n - 1; i++)
	{
		x = a[i]; poz = i;
		for (j = i + 1; j<n; j++)
			if (a[j]<x) {
				x = a[j];
				poz = j;
			}
		a[poz] = a[i]; a[i] = x;
	}

	
	char string[1000];
	schimbare(&a, &s, n);
	strcpy(string, s[0]);
	strcat(string, " ");
	
	for (int i = 1; i < n; i++)
	{
		strcat(string, s[i]);
		strcat(string, " ");
	}

	vectori_result = CreateWindow("Static", TEXT(string),	WS_CHILD | WS_VISIBLE | SS_LEFT,30, 70, 600, 30,hwnd, NULL, NULL, NULL);

	SendMessage(vectori_result,     /*HWND*/        /*Label*/
		WM_SETTEXT,     /*UINT*/        /*Message*/
		NULL,           /*WPARAM*/      /*Unused*/
		(LPARAM)TEXT(string));  /*LPARAM*/      /*Text*/
}

void DrawPixels(HWND hwnd) {

    PAINTSTRUCT ps;
    RECT r;

    GetClientRect(hwnd, &r);

    if (r.bottom == 0) {
    
        return;
    }

    HDC hdc = BeginPaint(hwnd, &ps);

    for (int i=0; i<1000; i++) {

        int x = rand() % r.right;
        int y = rand() % r.bottom;
        SetPixel(hdc, x, y, RGB(255, 0, 0));
    }

    EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



HWND hTrack;
HWND hlbl;
HWND numar;


HWND hwndButton, hwndButton1, hwndButton2, hwndButton3, hwndQuit,hwndGrafic1,hwndGrafic2,hwndGrafic3;
HWND hwndEdit, hwndEdit2;
HWND mesash, mesash1;

clock_t start1,start2,start3,end1,end2,end3;


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lpCmdLine, int nCmdShow) {

	MSG  msg;
	WNDCLASSW wc = { 0 };
	wc.lpszClassName = L"Static image";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.lpszClassName = L"Edit control";
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"Trackbar";

	RegisterClassW(&wc);
	CreateWindowW(wc.lpszClassName, L"Selection Sort!",
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,
		350, 250, 530, 370, 0, 0, hInstance, 0);

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	//srand(time(NULL));

	return (int)msg.wParam;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	static wchar_t *mesaj = L"Introduceti numarul de elemente ce doriti sa fie sortate!";
	static wchar_t *mesaj1 = L"Introduceti numerele ce doriti sa fie sortate!";
	static wchar_t *mesaj2 = L"Vectorul ordonat:";
	static wchar_t *mesaj3 = L"Lista simplu inlantuita ordonata:";
	static wchar_t *mesaj4 = L"Lista dublu inlantuita ordonata:";


	switch (msg) {

	case WM_CREATE:
	{

		mesash = CreateWindowW(L"Static", mesaj,
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			40, 20, 300, 230,
			hwnd, (HMENU)1, NULL, NULL);



		hwndEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "Edit", " ", WS_CHILD | WS_VISIBLE | ES_NUMBER, 40, 60, 150, 20, hwnd, NULL, NULL, NULL);

		hwndButton = CreateWindow("BUTTON", "OK",
			WS_VISIBLE | WS_CHILD, 40, 100, 80, 25,
			hwnd, (HMENU)ID_BUTTON, NULL, NULL);

		hwndQuit = CreateWindow("Button", "Quit",
			WS_VISIBLE | WS_CHILD,
			140, 100, 80, 25, hwnd, (HMENU)ID_QUIT, NULL, NULL);

		hwndButton1 = CreateWindow("button", "Vectori",   // de aici
			WS_VISIBLE | WS_CHILD, 15, 150, 80, 25,
			hwnd, (HMENU)ID_vectori, NULL, NULL);

		hwndButton2 = CreateWindow("button", "LSI",
			WS_VISIBLE | WS_CHILD, 125, 150, 80, 25,
			hwnd, (HMENU)ID_LSI, NULL, NULL);

		hwndButton3 = CreateWindow("button", "LDI",
			WS_VISIBLE | WS_CHILD, 235, 150, 80, 25,
			hwnd, (HMENU)ID_LDI, NULL, NULL);

		hwndEdit2 = CreateWindow("Edit", "",
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			20, 50, 350, 20, hwnd, NULL,
			NULL, NULL);

		

		ShowWindow(hwndButton1, SW_HIDE);
		ShowWindow(hwndButton2, SW_HIDE);
		ShowWindow(hwndButton3, SW_HIDE);
		ShowWindow(hwndEdit2, SW_HIDE);
		

	}; break;



	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
			
		case ID_BUTTON:
		{
			char replace[100];
			ShowWindow(hwndEdit2, SW_SHOW);
			ShowWindow(hwndButton1, SW_SHOW);
			ShowWindow(hwndButton2, SW_SHOW);
			ShowWindow(hwndButton3, SW_SHOW);
			ShowWindow(hwndButton, SW_HIDE);
			ShowWindow(hwndEdit, SW_HIDE);
			ShowWindow(hwndQuit, SW_HIDE);
			ShowWindow(mesash, SW_HIDE);

			int gwstat = 0;
			char textul[100];
			char *t = &textul[0];

			strcpy(textul, "");
			gwstat = GetWindowText(hwndEdit, t, 100);
			strcpy(replace, textul);

			// in replace ai continutul hwndEdit sub forma de string => convert cu 'atoi' probabil

			mesash1 = CreateWindowW(L"Static", mesaj1,
				WS_CHILD | WS_VISIBLE | SS_LEFT,
				20, 20, 300, 23,
				hwnd, NULL, NULL, NULL);


		};
		break; 

		case ID_QUIT: {
			PostQuitMessage(0);
		}; break;

		case ID_vectori: {

			char replace[100];
			int gwstat = 0;
			char textul[300];
			char *t = &textul[0];

			strcpy(textul, "");
			gwstat = GetWindowText(hwndEdit2, t, 300);
			strcpy(replace, textul);

			// in replace se afla sirul de numere sub forma de string

			int k = 0;
			char *p;
			p = strtok(replace, " ");
			while (p)
			{
				v[k] = atoi(p);
				k++;
				p = strtok(NULL, " ");
			}

			start1=clock();
			sort_selectie(hwnd, k, v);
			end1=clock();

			ShowWindow(hwndEdit2, SW_HIDE);
			ShowWindow(hwndButton1, SW_HIDE);
			ShowWindow(hwndButton2, SW_HIDE);
			ShowWindow(hwndButton3, SW_HIDE);
			ShowWindow(mesash1, SW_HIDE);

			hwndGrafic1=CreateWindow("button", "ArataGRAFIC",
			WS_VISIBLE | WS_CHILD, 20, 400, 80, 25,
			hwnd, (HMENU)ID_GRAFIC1, NULL, NULL);

			CreateWindowW(L"Static", mesaj2,
				WS_CHILD | WS_VISIBLE | SS_LEFT,
				30, 20, 100, 30,
				hwnd, NULL, NULL, NULL);

			PAINTSTRUCT ps;
			 RECT r;
			 int x=500,y=500;

			GetClientRect(hwnd, &r);

			if (r.bottom == 0) {
    
				return 0;
			  }

			HDC hdc = BeginPaint(hwnd, &ps);

		 for (int i=0; i<500; i++) {
	
				 
				  SetPixel(hdc, x, y, RGB(255, 0, 0));
				  x--;
				  y--;
				}

			 EndPaint(hwnd, &ps);


		}; break;



		case ID_LSI: {
			
			ShowWindow(hwndEdit2, SW_HIDE);
			ShowWindow(hwndButton1, SW_HIDE);
			ShowWindow(hwndButton2, SW_HIDE);
			ShowWindow(hwndButton3, SW_HIDE);
			ShowWindow(mesash1, SW_HIDE);

			hwndGrafic2=CreateWindow("button", "ArataGRAFIC",
			WS_VISIBLE | WS_CHILD, 20, 400, 80, 25,
			hwnd, (HMENU)ID_GRAFIC2, NULL, NULL);

			CreateWindowW(L"Static", mesaj3,
				WS_CHILD | WS_VISIBLE | SS_LEFT,
				20, 20, 100, 30,
				hwnd, (HMENU)1, NULL, NULL);

			char replace[100];
			int gwstat = 0;
			char textul[300];
			char *t = &textul[0];

			strcpy(textul, "");
			gwstat = GetWindowText(hwndEdit2, t, 300);
			strcpy(replace, textul);

			char *p;
			p = strtok(replace, " ");
			
			while (p)
			{
				createS(atoi(p));
				p = strtok(NULL, " ");
			}

			sortare_lista_simpla();

			afisareS(hwnd);
		}; break;

		case ID_LDI: {

			ShowWindow(hwndEdit2, SW_HIDE);
			ShowWindow(hwndButton1, SW_HIDE);
			ShowWindow(hwndButton2, SW_HIDE);
			ShowWindow(hwndButton3, SW_HIDE);
			ShowWindow(mesash1, SW_HIDE);

			CreateWindowW(L"Static", mesaj4,
				WS_CHILD | WS_VISIBLE | SS_LEFT,
				20, 20, 200, 30,
				hwnd, (HMENU)1, NULL, NULL);

			hwndGrafic3=CreateWindow("button", "ArataGRAFIC",
			WS_VISIBLE | WS_CHILD, 20, 400, 80, 25,
			hwnd, (HMENU)ID_GRAFIC3, NULL, NULL);

			char replace[100];
			int gwstat = 0;
			char textul[300];
			char *t = &textul[0];

			strcpy(textul, "");
			gwstat = GetWindowText(hwndEdit2, t, 300);
			strcpy(replace, textul);

			char *p;
			p = strtok(replace, " ");
			
			while (p)
			{
				createD(atoi(p));
				p = strtok(NULL, " ");
			}

			sortare_lista_dubla();

			afisareD(hwnd);

			
		}; break;


		case ID_GRAFIC1:{
			ShowWindow(hwndEdit2, SW_HIDE);
			ShowWindow(hwndButton1, SW_HIDE);
			ShowWindow(hwndButton2, SW_HIDE);
			ShowWindow(hwndButton3, SW_HIDE);
			ShowWindow(hwndButton, SW_HIDE);
			ShowWindow(hwndEdit, SW_HIDE);
			ShowWindow(hwndQuit, SW_HIDE);
			ShowWindow(mesash, SW_HIDE);
						}break;

		};
		break;
	}

	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	};
	break;

	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}