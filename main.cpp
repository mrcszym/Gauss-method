/*
autor: Szymon Marciniec
nr indeksu: 

Projekt zawiera punkty 1,2,5 z pdf, tj:
- wczytanie danych z pliku
- metodê eleminiacji Gaussa bez wyboru elementów
Wszystkie zadeklarowane metody maj¹ swoje cia³o po main().
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
void printMenu();       //wyœwietlenie menu w konsoli

int scale;  //rozmiar macierzy (zmienna globalna)

int main()
{
    setlocale(LC_CTYPE, "Polish");
    int choice, msize;   //choice - wybór u¿ytkownika, msize - matrix size
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
            B = loadData();     //metoda loadData() zape³nia tablicê B danymi z pliku
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
            cout<<"\nNiepoprawny wybór!\n"<<endl;
            system("PAUSE");
            system("CLS");
        }
        break;
        }
    }

    delete []B; //alokacja pamiêci
    return 0;
}

void gaussMethod(int ch, double **tab, int msize)
{
    double **arr;

    if (ch == 1)     //tablica juz wype³niona danymi z pliku "dane.csv"
    {
        arr = new double*[scale]; //przydzielenie pamiêci

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
        cout<<"Proszê podaæ liczbe równañ: ";
        cin>>scale;
        cout<<"\nPodaj (oddzielajac spacj¹) wspó³czynniki i wyrazy wolne (nowa linijka - enter):"<<endl;

        arr = new double*[scale];
        for(int i=0; i<scale; i++) //przypisanie ka¿demu elementowi tablicy arr now¹ tablicê wskaŸników (scale+1)
        {
            arr[i] = new double [scale + 1];
        }
        for(int j=0; j<scale; j++)  //rêczne wpisywanie znaków do tablicy
        {
            for(int k=0; k <= scale; k++)
            {
                cin>>arr[j][k];
            }
        }

        cout<<"\nWpisana macierz:\n"<<endl;
        for(int i=0; i<scale; i++) //wyœwietlanie macierzy
        {
            for(int j=0; j <= scale; j++)
            {
                if(j == scale)
                {
                    cout<<setw(10)<<arr[i][j]; //wyœwietlenie w konsoli znaków w okreœlonej odleg³oœci dla przejrzystoœci
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

    else cout<<"Wyst¹pi³ b³¹d na poziomie funkcji gaussMethod."<<endl;

    double p;   //wspó³czynnik(i)

    for(int i=0; i < scale-1; i++) //liczenie macierzy [A|B]
    {
        if(fabs(arr[i][i]) > 1e-7) //warunek dla a[i][i] != 0, fabs - wartoœæ bezwzglêdna
        {
            for(int j = i+1; j < scale; j++)
            {
                p = arr[j][i] / arr[i][i];  //obliczanie wspó³czynnika ze wzoru

                for(int k=0; k <= scale; k++)
                {
                    arr[j][k] -= p * arr[i][k]; //przekszta³cenia kolejnych wierszy uk³adu wedle wzoru
                }
            }
        } //w przypadku nie spe³nienia warunku z if, ten element jest pomijany, program siê nie zamyka
    }

    cout<<"\nMacierz po eliminacji Gaussa:\n"<<endl;
    for(int i=0; i < scale; i++) //wyœwietlenie macierzy i wektora wyrazów wolnych
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
        cout<<endl; //nastêpny wiersz macierzy
    }

    double arrX[scale];     //tablica iksów
    bool isPossible = true;     //bool przechowuje informacjê o mo¿liwoœci rozwi¹zania

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
        cout<<"\nX nie mog¹ byæ policzone."<<endl;
    }
    cout<<"\n=========================================================\n"<<endl;
    system("PAUSE");
    system("CLS");
    delete []arr;   //alokacja pamiêci
}

double **loadData()
{
    double** A;
    int matrix_size;    //rozmiar macierzy
    ifstream source_file("dane.csv");   //œcie¿ka pliku z danymi
    if (!source_file.is_open())     //sprawdzenie czy plik zosta³ poprawnie otwarty
    {
        cout<<"\nB³¹d wczytywania pliku! Program siê zakoñczy.\n(Prawdopodobnie nale¿y zmieniæ œcie¿kê pliku.)\n"<<endl;
        exit(1);    //program siê zamyka zamiast powrotu do menu - ¿eby zmieniæ œcie¿kê pliku
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

        cout<<"\nMacierz pomyœlnie za³adowana z pliku. Rozmiar: "<<matrix_size<<"x"<<matrix_size<<" (+ wektor)"<<endl;
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

    return A; //zwrócenie macierzy (tablicy) A
}

void printMenu() //tylko szczegó³y wizualne menu
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
    cout<<"\n0 - wyjœcie z programu"<<endl;
    cout<<"\nWybór: ";
}
