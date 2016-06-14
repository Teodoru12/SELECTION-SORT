#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include<commctrl.h>
#include<time.h>
#include<math.h>


#define ID_BEEP 1
#define ID_QUIT 20
#define ID_EDIT 10
#define ID_BUTTON 2
#define ID_vectori 101
#define ID_LSI 102
#define ID_LDI 103
#define ID_GRAFIC1 123
#define ID_GRAFIC2 124
#define ID_GRAFIC3 125
#define ID_INAPOI 126
#define ID_QUIT2 21
#define IDM_FILE_HELP 1010
#define IDM_FILE_QUIT 1011


char c[100];
int v[100];
int timp1,timp2,timp3;
HWND vectori_result,listeS_result,listeD_result;
clock_t start1,start2,start3;
double t1,t2,t3;

void AddMenus(HWND hwnd) {

    HMENU hMenubar;
    HMENU hMenu;

    hMenubar = CreateMenu();
    hMenu = CreateMenu();

    AppendMenuW(hMenu, MF_STRING, IDM_FILE_HELP, L"&Indicatii");
    AppendMenuW(hMenu, MF_SEPARATOR, 0, NULL);
    AppendMenuW(hMenu, MF_STRING, IDM_FILE_QUIT, L"&Iesire");

    AppendMenuW(hMenubar, MF_POPUP, (UINT_PTR) hMenu, L"&HELP");
    SetMenu(hwnd, hMenubar);
}


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

void stergereS()
{
	nodS *p=head;
	while(head!=0)
	{
		head=p;
		head=head->urmator;
		free(p);
	}
	end=0;
}

void stergereD()
{
	nodD *p=prim;
	while(head!=0)
	{
		prim=p;
		prim=prim->urmator;
		free(p);
	}
	ultim=0;
}


void schimbare(int **a, char ***c, int n)
{
	for (int i = 0; i<n; i++)
	{
		(*c)[i] = (char*)malloc(10);
		_itoa((*a)[i], (*c)[i], 10);
	}
}

int searchS(int key)
{
	nodS *p=head;
	while(p!=NULL)
	{
		if(p->numar==key)
			return 1;
		p=p->urmator;
	}
	return 0;

}

void createS(int x)
{
	nodS *p;
	p=(nodS*)malloc(sizeof(nodS));
	p->numar=x;
	p->urmator=NULL;
	if(searchS(x)==1)
		return;
	if(head==NULL)
	{
	head=end=p;
	return;
	}
	end->urmator=p;
	end=p;
}

int searchD(int key)
{
	nodD *p=prim;
	while(p!=NULL)
	{
		if(p->numar==key)
			return 1;
		p=p->urmator;
	}
	return 0;

}

void createD(int x)
{
nodD *p;
p=(nodD*)malloc(sizeof(nodD));
p->numar=x;
if(searchD(x)==1)
	return;
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

	listeS_result = CreateWindow("Static", TEXT(string), WS_CHILD | WS_VISIBLE | SS_LEFT, 20, 70, 600, 30, hwnd, NULL, NULL, NULL);

	SendMessage(listeS_result,     /*HWND*/        /*Label*/
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

	listeD_result = CreateWindow("Static", TEXT(string), WS_CHILD | WS_VISIBLE | SS_LEFT, 20, 70, 600, 30, hwnd, NULL, NULL, NULL);

	SendMessage(listeD_result,     /*HWND*/        /*Label*/
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



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



HWND hTrack;
HWND hlbl;
HWND numar;

HDC hdc;
PAINTSTRUCT ps;
RECT rcClient;
HWND hwndButton, hwndButton1, hwndButton2, hwndButton3, hwndQuit,hwndGrafic1,hwndGrafic2,hwndGrafic3,hwndInapoi;
HWND hwndEdit, hwndEdit2,hwndQuit2;
HWND mesash, mesash1,mesajj2,mesajj3,mesajj4;
HWND vec,lis,lid;




int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PWSTR lpCmdLine, int nCmdShow) {


		HBRUSH hh=CreateSolidBrush(RGB(255,255,102));
	
	MSG  msg;
	WNDCLASSW wc = { 0 };
	wc.lpszClassName = L"Static image";
	wc.hInstance = hInstance;
	wc.hbrBackground = hh;
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.lpszClassName = L"Edit control";
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

	return (int)msg.wParam;
}





LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
	WPARAM wParam, LPARAM lParam) {

	static wchar_t *mesaj = L"\n\n\n        Bine ati venit! Aplicatia va arata eficienta algoritmului de selection sort pentru vectori, liste simple si dublu inlantuite.           Pentru a continua apasati OK!";
	static wchar_t *mesaj1 = L"Introduceti numerele ce doriti sa fie sortate!";
	static wchar_t *mesaj2 = L"Vectorul ordonat:";
	static wchar_t *mesaj3 = L"Lista simplu inlantuita ordonata:";
	static wchar_t *mesaj4 = L"Lista dublu inlantuita ordonata:";
	static wchar_t *vectori= L"Vectori";
	static wchar_t *LSI = L"LSI";
	static wchar_t *LDI = L"LDI";


	switch (msg) {

	case WM_CREATE:
	{

		AddMenus(hwnd);

		mesash = CreateWindowW(L"Static", mesaj,
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			40, 20, 400, 230,
			hwnd, (HMENU)1, NULL, NULL);

		
		hwndButton = CreateWindow("BUTTON", "OK",
			WS_VISIBLE | WS_CHILD, 130, 190, 80, 25,
			hwnd, (HMENU)ID_BUTTON, NULL, NULL);

		hwndQuit = CreateWindow("Button", "Quit",
			WS_VISIBLE | WS_CHILD,
			270, 190, 80, 25, hwnd, (HMENU)ID_QUIT, NULL, NULL);

		hwndButton1 = CreateWindow("button", "Sortati VECTORUL",  
			WS_VISIBLE | WS_CHILD, 15, 150, 145, 25,
			hwnd, (HMENU)ID_vectori, NULL, NULL);

		hwndButton2 = CreateWindow("button", "Sortati lista SIMPLA",
			WS_VISIBLE | WS_CHILD, 175, 150, 145, 25,
			hwnd, (HMENU)ID_LSI, NULL, NULL);

		hwndButton3 = CreateWindow("button", "Sortati lista DUBLA",
			WS_VISIBLE | WS_CHILD, 335, 150, 145, 25,
			hwnd, (HMENU)ID_LDI, NULL, NULL);

		hwndEdit2 = CreateWindow("Edit", "",
			WS_BORDER | WS_CHILD | WS_VISIBLE,
			20, 50, 470, 25, hwnd, NULL,
			NULL, NULL);

		hwndGrafic1=CreateWindow("button", "VeziGraficEFIECIENTA",
			WS_VISIBLE | WS_CHILD, 165, 200, 155, 35,
			hwnd, (HMENU)ID_GRAFIC1, NULL, NULL);

		hwndInapoi=CreateWindow("button", "Inapoi",
			WS_VISIBLE | WS_CHILD, 50, 270, 80, 25,
			hwnd, (HMENU)ID_INAPOI, NULL, NULL);

		hwndQuit2=CreateWindow("Button", "Iesire",
			WS_VISIBLE | WS_CHILD,
			355, 270, 80, 25, hwnd, (HMENU)ID_QUIT2, NULL, NULL);

		mesash1 = CreateWindowW(L"Static", mesaj1,
				WS_CHILD | WS_VISIBLE | SS_LEFT,
				20, 20, 300, 23,
				hwnd, NULL, NULL, NULL);

		vec=CreateWindowW(L"Static", vectori,
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			40, 14, 48, 15,
			hwnd, NULL, NULL, NULL);
		lis=CreateWindowW(L"Static", LSI,
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			40, 34, 33, 15,
			hwnd, NULL, NULL, NULL);
		lid=CreateWindowW(L"Static", LDI,
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			40, 54, 33, 15,
			hwnd, NULL, NULL, NULL);
		

		ShowWindow(hwndButton1, SW_HIDE);
		ShowWindow(hwndButton2, SW_HIDE);
		ShowWindow(hwndButton3, SW_HIDE);
		ShowWindow(hwndEdit2, SW_HIDE);
		ShowWindow(hwndGrafic1, SW_HIDE);
		ShowWindow(hwndInapoi, SW_HIDE);
		ShowWindow(hwndQuit2, SW_HIDE);
		ShowWindow(mesash1, SW_HIDE);
		ShowWindow(vec, SW_HIDE);
		ShowWindow(lis, SW_HIDE);
		ShowWindow(lid, SW_HIDE);
		

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
			ShowWindow(hwndGrafic1, SW_SHOW);
			ShowWindow(mesash1, SW_SHOW);
			ShowWindow(hwndQuit2, SW_SHOW);
			ShowWindow(vec, SW_HIDE);
			ShowWindow(lis, SW_HIDE);
			ShowWindow(lid, SW_HIDE);
			

		};
		break; 

		case IDM_FILE_HELP:{

				LPCTSTR Caption = "Application Programming Interface";

							MessageBox( NULL,
                "In primul rand pentru a continua apasati OK!\n"
                "Dupa ce apasati OK introduceti numerele ce doriti sa fie sortate.\n "
                "Odata ce le-ati introdus apasati pe rand pe butoanele destinate sortarii fiecarei categorii de structuri.\n"
                "Butonul VeziGraficEFICIENTA va genera un grafic ce va arata eficacitatea SelectionSORT pentru fiecare categorie de structuri!",
                Caption,
                MB_OK);

					return 0;
						   }


		case IDM_FILE_QUIT:
              
                SendMessage(hwnd, WM_CLOSE, 0, 0);
                  break;

		case ID_QUIT: {
			PostQuitMessage(0);
		}; break;

		case ID_QUIT2:{
			PostQuitMessage(0);
					  }; break;

		case ID_vectori: {

			if(GetWindowTextLength(hwndEdit2)==0)
				MessageBox(hwnd,"Introduceti elemente spre sortare!!!",NULL,NULL);
			else
			{

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
			t1=double(clock()-start1);

			

			ShowWindow(hwndEdit2, SW_HIDE);
			ShowWindow(hwndButton1, SW_HIDE);
			ShowWindow(hwndButton2, SW_HIDE);
			ShowWindow(hwndButton3, SW_HIDE);
			ShowWindow(mesash1, SW_HIDE);
			ShowWindow(hwndGrafic1, SW_HIDE);
			ShowWindow(hwndInapoi, SW_SHOW);
			ShowWindow(mesash1, SW_HIDE);
			ShowWindow(hwndQuit2, SW_SHOW);
			ShowWindow(vec, SW_HIDE);
			ShowWindow(lis, SW_HIDE);
			ShowWindow(lid, SW_HIDE);
			


			

			mesajj2=CreateWindowW(L"Static", mesaj2,
				WS_CHILD | WS_VISIBLE | SS_LEFT,
				30, 20, 100, 30,
				hwnd, NULL, NULL, NULL);
			}
			


		}; break;



		case ID_LSI: {

			if(GetWindowTextLength(hwndEdit2)==0)
				MessageBox(hwnd,"Introduceti elemente spre sortare!!!",NULL,NULL);
			else
			{
			
			ShowWindow(hwndEdit2, SW_HIDE);
			ShowWindow(hwndButton1, SW_HIDE);
			ShowWindow(hwndButton2, SW_HIDE);
			ShowWindow(hwndButton3, SW_HIDE);
			ShowWindow(hwndGrafic1, SW_HIDE);
			ShowWindow(mesash1, SW_HIDE);
			ShowWindow(hwndInapoi, SW_SHOW);
			ShowWindow(mesash1, SW_HIDE);
			ShowWindow(hwndQuit2, SW_SHOW);
			ShowWindow(vec, SW_HIDE);
			ShowWindow(lis, SW_HIDE);
			ShowWindow(lid, SW_HIDE);
			
			

			mesajj3=CreateWindowW(L"Static", mesaj3,
				WS_CHILD | WS_VISIBLE | SS_LEFT,
				30, 20, 200, 30,
				hwnd, NULL, NULL, NULL);

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
			start2=clock();
			sortare_lista_simpla();
			t2=double(clock()-start2);
			
			afisareS(hwnd);
			}

			
		}; break;

		case ID_LDI: {

			if(GetWindowTextLength(hwndEdit2)==0)
				MessageBox(hwnd,"Introduceti elemente spre sortare!!!",NULL,NULL);
			else
			{

			ShowWindow(hwndEdit2, SW_HIDE);
			ShowWindow(hwndButton1, SW_HIDE);
			ShowWindow(hwndButton2, SW_HIDE);
			ShowWindow(hwndButton3, SW_HIDE);
			ShowWindow(mesash1, SW_HIDE);
			ShowWindow(hwndGrafic1, SW_HIDE);
			ShowWindow(hwndInapoi, SW_SHOW);
			ShowWindow(mesash1, SW_HIDE);
			ShowWindow(hwndQuit2, SW_SHOW);
			ShowWindow(vec, SW_HIDE);
			ShowWindow(lis, SW_HIDE);
			ShowWindow(lid, SW_HIDE);
			

			

			mesajj4=CreateWindowW(L"Static", mesaj4,
				WS_CHILD | WS_VISIBLE | SS_LEFT,
				20, 20, 200, 30,
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
				createD(atoi(p));
				p = strtok(NULL, " ");
			}
			
			start3=clock();
			sortare_lista_dubla();
			t3=double(clock()-start3);

			afisareD(hwnd);

			}

			
		}; break;


		case ID_GRAFIC1:{


			if(GetWindowTextLength(hwndEdit2)==0)
			{
				MessageBox(hwnd,"Introduceti elemente pentru sortare!!!", "Atentie!", NULL);
			}
			else
				if(vectori_result==NULL||listeS_result==NULL||listeD_result==NULL)
					MessageBox(hwnd,"Sortati cele trei structuri de date!!!", "Atentie!", NULL);
				
				else
			{



			ShowWindow(hwndEdit2, SW_HIDE);
			ShowWindow(hwndButton1, SW_HIDE);
			ShowWindow(hwndButton2, SW_HIDE);
			ShowWindow(hwndButton3, SW_HIDE);
			ShowWindow(hwndButton, SW_HIDE);
			ShowWindow(hwndEdit, SW_HIDE);
			ShowWindow(hwndQuit, SW_HIDE);
			ShowWindow(mesash, SW_HIDE);
			ShowWindow(mesash1, SW_HIDE);
			ShowWindow(mesajj2, SW_HIDE);
			ShowWindow(mesajj3, SW_HIDE);
			ShowWindow(mesajj4, SW_HIDE);
			ShowWindow(vectori_result, SW_HIDE);
			ShowWindow(mesash1, SW_HIDE);
			ShowWindow(hwndQuit2, SW_SHOW);
			ShowWindow(hwndGrafic1, SW_HIDE);
			ShowWindow(hwndInapoi, SW_SHOW);
			ShowWindow(vec, SW_SHOW);
			ShowWindow(lis, SW_SHOW);
			ShowWindow(lid, SW_SHOW);
			
	

            hdc = BeginPaint(hwnd, &ps);

			GetClientRect(hwnd, &rcClient);

			HPEN hPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
			HPEN holdPen = HPEN(SelectObject(hdc, HGDIOBJ(hPen)));
			HBRUSH hBrush1 = CreateSolidBrush(RGB(121, 90, 0));
			HBRUSH hBrush2 = CreateSolidBrush(RGB(240, 63, 19));
			HBRUSH hBrush3 = CreateSolidBrush(RGB(9, 189, 21));

			HBRUSH holdBrush = HBRUSH(SelectObject(hdc, hBrush1));


			int a,b,c;
			a=t1;
			b=t2;
			c=t3;
			int max=a;
			if(b>max)
				max=b;
			else
				if(c>max)
					max=c;

			float r;

			r=300.0/((float)max);


			Rectangle(hdc,100,50,130,150-floor(r*float(a)));
			SelectObject(hdc, hBrush2);
			Rectangle(hdc,200,50,230,150-floor(r*float(b)));
			SelectObject(hdc, hBrush3);
			Rectangle(hdc,300,50,330,150-floor(r*float(c)));
			

			SelectObject(hdc,hBrush1);
			Rectangle(hdc,30,20,35,25);
			SelectObject(hdc,hBrush2);
			Rectangle(hdc,30,40,35,45);
			SelectObject(hdc,hBrush3);
			Rectangle(hdc,30,60,35,65);

			SelectObject(hdc, holdPen);
			SelectObject(hdc, holdBrush);

			DeleteObject(hPen);
			DeleteObject(hBrush1);
			DeleteObject(hBrush2);
			DeleteObject(hBrush3);

            EndPaint(hwnd, &ps);

			}
           



						};break;

	

		case ID_INAPOI:{
				ShowWindow(hwndEdit2, SW_SHOW);
				ShowWindow(hwndButton1, SW_SHOW);
				ShowWindow(hwndButton2, SW_SHOW);
				ShowWindow(hwndButton3, SW_SHOW);
				ShowWindow(mesash, SW_HIDE);
			//	ShowWindow(mesash1, SW_HIDE);
				ShowWindow(hwndEdit,SW_HIDE);
				ShowWindow(vectori_result, SW_HIDE);
				ShowWindow(mesajj2, SW_HIDE);
				ShowWindow(mesajj3, SW_HIDE);
				ShowWindow(mesajj4, SW_HIDE);
				ShowWindow(hwndGrafic1, SW_SHOW);
				ShowWindow(hwndInapoi,SW_HIDE);
				ShowWindow(mesash1, SW_SHOW);
				ShowWindow(hwndQuit2, SW_SHOW);
				ShowWindow(listeD_result, SW_HIDE);
				ShowWindow(listeS_result, SW_HIDE);
				ShowWindow(vec, SW_HIDE);
				ShowWindow(lis, SW_HIDE);
				ShowWindow(lid, SW_HIDE);
			//	stergereS();
				//stergereD();
					   }


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