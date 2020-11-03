#include <windows.h>
#include <conio.h>
#include <iostream>
#include <iomanip>
using namespace std;
int plansza[42][22];
bool* visited;
int BFSpath[800];
int ilosc_przejsc=0;
int path[800];
int path_length = 0;
int pktA, pktB;

struct slist
{
    slist* next;
    int v;
};
slist** vertex;
int licznik = 1;
int v1, v2;
slist* p, * r;
int segmentA[5][5] = {{0,0,1,0,0},
                      {0,1,1,0,0},
                      {1,1,0,1,1},
                      {0,1,1,1,0},
                      {0,0,1,0,0}};
int segmentB[5][5] = {{0,0,1,1,0},
                     {1,0,0,1,0},
                     {1,1,1,1,1},
                     {0,1,1,1,0},
                     {0,0,1,1,0}};
int segmentC[5][5] = {{1,1,1,1,1},
                     {1,1,0,1,1},
                     {1,1,0,0,1},
                     {0,1,0,0,0},
                     {0,1,1,1,1}};
int segmentD[5][5] = {{0,0,1,1,1},
                     {0,1,1,0,1},
                     {1,1,0,1,1},
                     {1,0,1,1,0},
                     {0,1,1,0,0}};
int segmentE[5][5] = {{1,1,1,0,0},
                     {0,1,1,1,0},
                     {1,1,0,1,1},
                     {1,1,0,1,1},
                     {1,1,1,1,0}};
int segmentF[5][5] = {{0,0,1,0,0},
                     {0,0,1,0,0},
                     {1,1,1,1,1},
                     {0,0,1,0,0},
                     {0,0,1,0,0}};

void plansza_animacja()
{
    system("cls");
    Sleep(500);
    COORD zero;
    zero.X = 0;
    zero.Y = 0;
    bool found = false;
    for (int k = path_length - 1; k >= 0; k--)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), zero);
        Sleep(700);
        for (int i = 0; i < 42; i++)
        {
            for (int j = 0; j < 22; j++)
            {
                found = false;
                for (int z = path_length - 1; z >= k; z--)
                {
                    if (path[z] == plansza[i][j])
                    {

                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
                        cout << setw(5) << plansza[i][j];
                        found = true;
                    }
                }

                if (plansza[i][j] == 0)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    cout << setw(5) << " ";
                }
                else if (plansza[i][j] == pktA || plansza[i][j] == pktB)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                    cout << setw(5) << plansza[i][j];
                }
                else if(!found)
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    cout << setw(5) << plansza[i][j];

                }

            }
            cout << endl;
        }
        cout << endl;
        for (int z = path_length - 1; z >= k; z--)
        cout << setw(5) << path[z];
    }
    cout << endl;
}

void BFS(int v, int z)
{
    bool flagowa = true;
    slist* p, * q, * head, * tail; // Kolejka
    ilosc_przejsc = 0;
    q = new slist;      // W kolejce umieszczamy v
    q->next = NULL;
    q->v = v;
    head = tail = q;

    visited[v] = true; // Wierzchołek v oznaczamy jako odwiedzony
    cout << "Punkty z przejscia po BFS: ";
    do
    {
        v = head->v;        // Odczytujemy v z kolejki

        q = head;           // Usuwamy z kolejki odczytane v
        head = head->next;
        if (!head) tail = NULL;
        delete q;

        cout << setw(5) << v;
        BFSpath[ilosc_przejsc] = v; // 
        ilosc_przejsc++;

        if (v == z)
            flagowa = false;

        for (p = vertex[v]; p; p = p->next)
        {

            if (!visited[p->v])
            {
                q = new slist; // W kolejce umieszczamy nieodwiedzonych sąsiadów
                q->next = NULL;
                q->v = p->v;
                if (!tail)
                    head = q;
                else
                    tail->next = q;
                tail = q;
                visited[p->v] = true; // i oznaczamy ich jako odwiedzonych
            }
        }
    } 
    while (head && flagowa);
    cout << endl << endl;
}

void wypisywanie_list()
{
    cout << "Kolejne wierzcholki i ich \"sasiedzi\" ";
    cout << endl;
    
    for (int i = 1; i < licznik ; i++)
    {
        cout << "A [ " << i << " ] =";
        p = vertex[i];

        while (p)
        {
            cout << setw(5) << p->v;
            p = p->next;
        }
        cout << endl;
    }
    cout << endl << endl;
    
}
void wstawianiesegm(int segment[5][5], int i, int j)
{
    for (int x = 0; x < 5; x++)
        for (int y = 0; y < 5; y++)
            plansza[x + i][y + j] = segment[x][y];
}

void generowaniemapy()
{
    for (int i = 1; i < 41; i += 5)
        for (int j = 1; j < 21; j += 5)
        {
            int losowa = 1 + rand() % 6;
            switch (losowa) {
            case 1:
            {
                wstawianiesegm(segmentA, i, j);
                break;
            }
            case 2:
            {
                wstawianiesegm(segmentB, i, j);
                break;
            }
            case 3:
            {
                wstawianiesegm(segmentC, i, j);
                break;
            }
            case 4:
            {
                wstawianiesegm(segmentD, i, j);
                break;
            }
            case 5:
            {
                wstawianiesegm(segmentE, i, j);
                break;
            }
            case 6:
            {
                wstawianiesegm(segmentF, i, j);
                break;
            }
            }
        }
}
void wypisywanie_planszy()
{
    cout << "Plansza z zaznaczonymi puntami A i B: " << endl;
    for (int i = 0; i < 42; i++)
    {
        for (int j = 0; j < 22; j++)
        {
            if (plansza[i][j] == 0)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << setw(5) << " ";
            }
            else if (plansza[i][j] == pktA || plansza[i][j] == pktB)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                cout << setw(5) << plansza[i][j];
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                cout << setw(5) << plansza[i][j];

            }
        }
        cout << endl;
    }
}
int main()
{
    srand(time(NULL));

    generowaniemapy();

    for (int i = 1; i < 41; i++) // nadawanie liczb dla kolejnych wierzchołków grafu/ numerowanie pól planszy
        for (int j = 1; j < 21; j++)
        {
            if (plansza[i][j] == 1)
            {
                plansza[i][j] = licznik;
                licznik++;
            }
        }
     

    pktA = 1 + rand() % licznik;
    pktB = 1 + rand() % licznik;
    cout << "Punkt A: " << pktA << "  Punkt B: " << pktB << endl;

    vertex = new slist * [licznik];
    visited = new bool[licznik];

    for (int i = 1; i < licznik; i++) // zerowanie tablicy list
    {
        vertex[i] = NULL;
        visited[i] = false;
    }
     // tworzenie dynamicznych list
    for (int i = 1; i < 41; i++)
        for (int j = 1; j < 21; j++)
        {
            if (plansza[i][j] != 0)
            {
                v1 = plansza[i][j];

                if (plansza[i - 1][j] != 0)
                {
                    v2 = plansza[i - 1][j];
                    p = new slist;
                    p->v = v2;
                    p->next = vertex[v1];
                    vertex[v1] = p;
                }
                if (plansza[i + 1][j] != 0)
                {
                    v2 = plansza[i + 1][j];
                    p = new slist;
                    p->v = v2;
                    p->next = vertex[v1];
                    vertex[v1] = p;
                }
                if (plansza[i][j - 1] != 0)
                {
                    v2 = plansza[i][j - 1];
                    p = new slist;
                    p->v = v2;
                    p->next = vertex[v1];
                    vertex[v1] = p;
                }
                if (plansza[i][j + 1] != 0)
                {
                    v2 = plansza[i][j + 1];
                    p = new slist;
                    p->v = v2;
                    p->next = vertex[v1];
                    vertex[v1] = p;
                }
            }
        }

    wypisywanie_planszy();

    BFS(pktA,pktB); // BFS puszczony przez dwa punkty

	wypisywanie_list();
    // Dajemy punkt koncowy
    // Szukamy jego sąsiadów
    // Jeśli znajdziemy jednego z jego sąsiadów w tablicy z punktami BFS to wypisujemy go i skracamy listę do tego momentu
    // Powtarzarzamy to samo ale ze znalezionym sąsiadem
    // Powtarzamy do momentu znalezienia punktu A

    p = vertex[pktB];

    int list_length = ilosc_przejsc - 1; // zmienna przekazująca dlugosc tablicy z punktami BFS, "skraca się" przy kolejnych przejsciach
    bool to_end = true; // w przypadku znalezienia punkty

    while (p)
    { 
        to_end = true;
        while (p && to_end)
        {
            for (int i = list_length; i > 0; i--) 
            {
                if (p->v == BFSpath[i])
                {
                    path[path_length] = BFSpath[i];
                    path_length++;
                    list_length = i;
                    p = vertex[BFSpath[i]];
                    to_end = false;
                    break;
                }
            }
            if (to_end)
                p = p->next;
        }
     }
             
    // Usuwamy tablicę list sąsiedztwa
    for (int i = 1; i < licznik; i++)
    {
        p = vertex[i];
        while (p)
        {
            r = p;
            p = p->next;
            delete r;
        }
    }
    
    delete[] vertex;
    delete[] visited;

    cout << "Sciezka przejscia robota: " << endl;
    for (int i = path_length-1; i >= 0; i--)
    {
        cout << path[i] << endl;
    }

    string yon;
    cout << endl;
    cout << "Czy chcesz wyswietlic droge?  T/N ";
    cin >> yon;
    if (yon == "T")
        plansza_animacja();
    return 0;
}

