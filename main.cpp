#include <iostream>
#include <fstream>
#include <iomanip>
#include <conio.h>

using namespace std;

ifstream f("date.in");

const int DMAX = 1000; /// Dimensiunea maxima a marii

struct pozitie
{
    int x, y;
};

int M, N, L[DMAX + 2][DMAX + 2],A[DMAX + 2][DMAX + 2]; /// mareul

pozitie C[DMAX * DMAX + 1]; ///Coada
int p, u;

pozitie ps; ///pozitia barcii
pozitie pc; ///pozitia omului

int d[4][2] = {{0, -1}, { -1, 0}, {0, 1}, {1, 0}}; ///modalitati de deplasare in mare

bool bar=0,om=0;

char ch;

void bordare()
{
    for(int i = 0; i <= M + 1; i++)
    {
        L[i][0] = -1;
        L[i][N + 1] = -1;
    }
    for(int i = 0; i <= N + 1; i++)
    {
        L[0][i] = -1;
        L[M + 1][i] = -1;
    }
}
void Lee()
{
    pozitie vec, crt;
    p = u = 1;
    C[1] = ps; ///se pune in coada pozitia barcii
    while(p <= u && L[pc.x][pc.y] == 0) ///cat timp coada este nevida si nu s-a ajuns la om
    {
        crt = C[p++]; ///se extrage un element din coada
        for(int k = 0; k < 4; k++) ///se parcurg vecinii pozitiei curente
        {
            vec.x = crt.x + d[k][0]; ///coordonate vecin
            vec.y = crt.y + d[k][1];
            if(L[vec.x][vec.y] == 0) ///vecinul este culoar si e nevizitat
            {
                L[vec.x][vec.y] = L[crt.x][crt.y] + 1; /// marcam pozitia
                C[++u] = vec; ///adaugam vecin in coada
            }
        }
    }
}

void traseu1(int x, int y)
{
    int vx, vy;
    cout << x << ' ' << y << endl;
    if(L[x][y] > 1)
        for(int k = 0; k < 4; k++)
        {
            vx = x + d[k][0];
            vy = y + d[k][1];
            if(L[vx][vy] == L[x][y] - 1)
            {
                traseu1(vx, vy);
                break;
            }
        }
}

void traseu2(int x, int y)
{
    int vx, vy;
    if(L[x][y] > 1)
        for(int k = 0; k < 4; k++)
        {
            vx = x + d[k][0];
            vy = y + d[k][1];
            if(L[vx][vy] == L[x][y] - 1)
            {
                traseu2(vx, vy);
                break;
            }
        }
    A[x][y]=3;
    cout << x << ' ' << y << endl;
}

int main()
{
    inceput:
    cout<<"Introduceti latimea si lungimea luciului de apa, separate printr-un spatiu:";
    cin >> M >> N;
    cout<<"\n";
    cout<<"Introduceti matricea suprafetei apei codificata astfel:\n";
    cout<<"- '0' reprezinta apa\n";
    cout<<"- '-1' reprezinta obstacol\n";
    cout<<"- '1' pozitia de plecare a barcii\n";
    cout<<"- '2' omul care trebuie salvat\n";
    cout<<"Trebuie sa avem o singura barca si un singur om\n";
    cout<<"\n";
    cout<<"Un exemplu de date de intrare introduse corect pentru o matrice de dimensiuni 3 6:\n";
    cout<<"\n";
    cout<<"1  -1  0 -1 0 0\n";
    cout<<"0  -1 -1 -1 0 0\n";
    cout<<"0   0  0  2 0 0\n";
    cout<<"\n";
gresit3:
    bar=0;
    om=0;
    for(int i = 1; i <= M; i++)
    {
        for(int j = 1; j <= N; j++)
        {
gresit:
            ch=getch();
            if(ch=='0')
            {
                L[i][j]=0;
                cout<<" 0";
            }
            else if(ch=='1'&&bar!=1)
            {
                L[i][j]=1;
                cout<<" 1";
            }
            else if(ch=='2'&&om!=1)
            {
                L[i][j]=2;
                cout<<" 2";
            }
            else if(ch=='-')
            {
                cout<<'-';
gresit2:
                ch=getch();
                if(ch!='1')
                    goto gresit2;
                else
                {
                    cout<<'1';
                    L[i][j]=-1;
                }
            }
            else
                goto gresit;
            cout<<' ';
            A[i][j]=L[i][j];
            if(L[i][j] == 1)
            {
                ps.x = i;
                ps.y = j;
                bar=1;
            }
            if(L[i][j] == 2)
            {
                pc.x = i;
                pc.y = j;
                L[i][j] = 0;
                om=1;
            }
        }
        cout<<"\n";
    }
    if(bar==0||om==0)
    {
        cout<<"\nTrebuie introdusa macar o barca si macar un om\nIntrodu inca o data matricea\n\n";
        goto gresit3;
    }
    bordare();
    Lee();
    cout<<'\n'<<"----------------------------------"<<'\n'<<'\n';
    if(L[pc.x][pc.y] == 0)
        cout << "NU SE POATE AJUNGE LA OM!!!" << endl;
    else
    {
        cout << "SE POATE AJUNGE LA OM!!!" << endl;
        cout<<'\n'<<"----------------------------------"<<'\n'<<'\n';
        cout << "Numar minim de pasi= " << L[pc.x][pc.y] - 1 << endl;
        cout<<'\n'<<"----------------------------------"<<'\n'<<'\n'<<"Coordonatele traseului sunt :"<<'\n';
        traseu2(pc.x, pc.y);
    }
    cout<<'\n'<<"----------------------------------"<<'\n'<<'\n';
    for(int i = 1; i <= M; i++)
    {
        for(int j = 1; j <= N; j++)
            if(A[i][j]==3)
                cout << setw(3) << 'x' << ' ';
            else
                cout << setw(3) << A[i][j] << ' ';
        cout << endl;
    }
    cout<<'\n'<<"----------------------------------"<<'\n'<<'\n';
    cout<<"Vrei sa introduci inca o problema? (y/n)";
    cout<<'\n'<<'\n'<<"----------------------------------"<<'\n'<<'\n';
    gresit4:
        ch=getch();
    if(ch=='y')
    goto inceput;
    else if(ch=='n')
    return 0;
    else goto gresit4;
}
