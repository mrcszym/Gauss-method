/*
autor: Szymon Marciniec
nr indeksu: 

Projekt zawiera punkty 1,2,5 z pdf, tj:
- wczytanie danych z pliku
- metod� eleminiacji Gaussa bez wyboru element�w
Wszystkie zadeklarowane metody maj� swoje cia�o po main().
*/
#include <iostream>
#include <windows.h>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <locale.h>
#include <cstdlib>

using namespace std;

void gaussMethod(int ch, double **tab, int msize);  //metoda eliminacji Gaussa bez wyboru elementu
double **loadData();        //wczytanie danych z pliku
void printMenu();       //wy�wietlenie menu w konsoli

int scale;  //rozmiar macierzy (zmienna globalna)

int main()
{
    setlocale(LC_CTYPE, "Polish");
    int choice, msize;   //choice - wyb�r u�ytkownika, msize - matrix size
    double **B;

    while(choice != 0)
    {
        printMenu();
        cin>>choice;

        switch(choice)
        {
        case 0:
        {
            cout<<"\nDo widzenia!"<<endl;
            return 0;
        }
        break;

        case 1:
        {
            B = loadData();     //metoda loadData() zape�nia tablic� B danymi z pliku
            gaussMethod(choice, B, msize);
        }
        break;

        case 2:
        {
            gaussMethod(choice, B, msize);  //tablica B na razie pozostaje pusta
        }
        break;

        default:
        {
            cout<<"\nNiepoprawny wyb�r!\n"<<endl;
            system("PAUSE");
            system("CLS");
        }
        break;
        }
    }

    delete []B; //alokacja pami�ci
    return 0;
}

void gaussMethod(int ch, double **tab, int msize)
{
    double **arr;

    if (ch == 1)     //tablica juz wype�niona danymi z pliku "dane.csv"
    {
        arr = new double*[scale]; //przydzielenie pami�ci

        for(int i=0; i<scale; i++)
        {
            arr[i] = new double [scale + 1];
            for(int j=0; j <= scale; j++)
            {
                arr[i][j] = tab[i][j];
            }
        }
    }

    else if (ch == 2) //tablica zostanie wypelniona danymi z klawiatury
    {
        cout<<"Prosz� poda� liczbe r�wna�: ";
        cin>>scale;
        cout<<"\nPodaj (oddzielajac spacj�) wsp�czynniki i wyrazy wolne (nowa linijka - enter):"<<endl;

        arr = new double*[scale];
        for(int i=0; i<scale; i++) //przypisanie ka�demu elementowi tablicy arr now� tablic� wska�nik�w (scale+1)
        {
            arr[i] = new double [scale + 1];
        }
        for(int j=0; j<scale; j++)  //r�czne wpisywanie znak�w do tablicy
        {
            for(int k=0; k <= scale; k++)
            {
                cin>>arr[j][k];
            }
        }

        cout<<"\nWpisana macierz:\n"<<endl;
        for(int i=0; i<scale; i++) //wy�wietlanie macierzy
        {
            for(int j=0; j <= scale; j++)
            {
                if(j == scale)
                {
                    cout<<setw(10)<<arr[i][j]; //wy�wietlenie w konsoli znak�w w okre�lonej odleg�o�ci dla przejrzysto�ci
                }
                else if(j == 0)
                {
                    cout<<setw(10)<<arr[i][j]<<"";
                }
                else
                {
                    cout<<setw(10)<<arr[i][j]<<"";
                }
            }
            cout<<endl;
        }
    }

    else cout<<"Wyst�pi� b��d na poziomie funkcji gaussMethod."<<endl;

    double p;   //wsp�czynnik(i)

    for(int i=0; i < scale-1; i++) //liczenie macierzy [A|B]
    {
        if(fabs(arr[i][i]) > 1e-7) //warunek dla a[i][i] != 0, fabs - warto�� bezwzgl�dna
        {
            for(int j = i+1; j < scale; j++)
            {
                p = arr[j][i] / arr[i][i];  //obliczanie wsp�czynnika ze wzoru

                for(int k=0; k <= scale; k++)
                {
                    arr[j][k] -= p * arr[i][k]; //przekszta�cenia kolejnych wierszy uk�adu wedle wzoru
                }
            }
        } //w przypadku nie spe�nienia warunku z if, ten element jest pomijany, program si� nie zamyka
    }

    cout<<"\nMacierz po eliminacji Gaussa:\n"<<endl;
    for(int i=0; i < scale; i++) //wy�wietlenie macierzy i wektora wyraz�w wolnych
    {
        for(int j=0; j <= scale; j++)
        {
            if(j == scale)
            {
                cout<<setw(10)<<arr[i][j];
            }
            else if(j == 0)
            {
                cout<<setw(10)<<arr[i][j]<<"";
            }
            else
            {
                cout<<setw(10)<<arr[i][j]<<"";
            }
        }
        cout<<endl; //nast�pny wiersz macierzy
    }

    double arrX[scale];     //tablica iks�w
    bool isPossible = true;     //bool przechowuje informacj� o mo�liwo�ci rozwi�zania

    for(int i=scale-1; i>=0; i--)
    {
        double X = arr[i][scale];
        if(fabs(arr[i][i])>1e-7)
        {
            for(int j=scale-1; j>i; j--)
            {
                X -= arr[i][j] * arrX[j];
            }
            arrX[i] = X / arr[i][i];
        }
        else
        {
            isPossible=false;
        }
    }
    if(isPossible == true)
    {
        cout<<"\nObliczone X:"<<endl;
        for(int i=0; i<scale; i++)
        {
            cout<<"x"<<i+1<<"= "<<arrX[i]<<endl;
        }
    }
    else if(isPossible == false)
    {
        cout<<"\nX nie mog� by� policzone."<<endl;
    }
    cout<<"\n=========================================================\n"<<endl;
    system("PAUSE");
    system("CLS");
    delete []arr;   //alokacja pami�ci
}

double **loadData()
{
    double** A;
    int matrix_size;    //rozmiar macierzy
    ifstream source_file("dane.csv");   //�cie�ka pliku z danymi
    if (!source_file.is_open())     //sprawdzenie czy plik zosta� poprawnie otwarty
    {
        cout<<"\nB��d wczytywania pliku! Program si� zako�czy.\n(Prawdopodobnie nale�y zmieni� �cie�k� pliku.)\n"<<endl;
        exit(1);    //program si� zamyka zamiast powrotu do menu - �eby zmieni� �cie�k� pliku
    }
    else
    {
        source_file >> matrix_size;
        A = new double*[matrix_size];
        for(int i = 0; i< matrix_size; i++)
        {
            A[i] = new double[matrix_size+1];
        }

        char semicolumn;
        for (int i = 0; i < matrix_size+1; i++)
            source_file >> semicolumn;

        for (int i = 0; i < matrix_size; i++)
        {
            for (int j = 0; j <=matrix_size; j++)
            {
                if(j==matrix_size)
                {
                    source_file >> semicolumn;
                    source_file >> A[i][j];
                }
                else
                {
                    source_file >> A[i][j];
                    source_file >> semicolumn;
                }
            }
        }
        source_file.close();

        cout<<"\nMacierz pomy�lnie za�adowana z pliku. Rozmiar: "<<matrix_size<<"x"<<matrix_size<<" (+ wektor)"<<endl;
        cout<<"\nWczytana macierz:\n"<<endl;
        for(int i=0; i<matrix_size; i++)
        {
            for(int j=0; j<=matrix_size; j++)
            {
                if(j == matrix_size)
                {
                    cout<<setw(10)<<A[i][j];
                }
                else if(j == 0)
                {
                    cout<<setw(10)<<A[i][j]<<"";
                }
                else
                {
                    cout<<setw(10)<<A[i][j]<<"";
                }
            }
            cout<<endl;
        }
    }
    scale = matrix_size;

    return A; //zwr�cenie macierzy (tablicy) A
}

void printMenu() //tylko szczeg�y wizualne menu
{
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<"\n======================== MENU PROGRAMU ========================\n"<<endl;
    cout<<setw(55)<<"Metoda eliminacji Gaussa bez wyboru elementu."<<endl;
    cout<<"\n---------------------------------------------------------------\n"<<endl;
    SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout<<"Opcje:"<<endl;
    cout<<"\n1 - wczytanie danych z pliku"<<endl;
    cout<<"2 - dane z klawiatury"<<endl;
    cout<<"\n0 - wyj�cie z programu"<<endl;
    cout<<"\nWyb�r: ";
}
