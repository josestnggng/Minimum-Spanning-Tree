/*
	Nama : Jose Alfredo Sitanggang
	NIM : 14116125
	Teknik Informatika 2016

	DESKRIPSI :
		Program ini meliputi 2 Algoritma untuk mencari
		Pohon merenggang minimum denganmenggunakan Algoritma
		Prims dan Kruskal	
 */


#include <iostream>
#include <fstream>
using namespace std;
#define SIZE 20
#define MAXEL 999
typedef struct 
{
	int elMatriks[SIZE][SIZE];
	int brEff;
	int koEff;
}MATRIKS;
/*
	MATRIKS M memiliki ukuran SIZE x SIZE
 */

/*
	Elmt(M,i,j) : Element matriks pada posisi[i][j]
	bEff(M)		: Baris Matriks M yang digunakan <=SIZE
	kEff(M)		: Kolom Matriks M yang digunakan <=SIZE
 */
#define Elmt(M,i,j) (M).elMatriks[i][j]
#define bEff(M)		(M).brEff
#define kEff(M)		(M).koEff

/*
	variabel-variabel global
 */
	 int parent[20];

/*
	Inisialisasi fungsi
 */
int FIND(int);
int UNION(int, int);

/*
	Membuat Matriks Persegi
 */
void BUAT_MATRIKS(MATRIKS *M,int size)
{
	bEff(*M)=kEff(*M)=size;
}
/*
	Menyalin data dari file text kedalam Matriks
	namaFile bertipe txt
 */
void INPUT_DARI_FILE(MATRIKS *M,string namaFile)
{
	ifstream input;
	int size;
	input.open(namaFile);
	input >> size;

	BUAT_MATRIKS(M,size);

	while(!input.eof())
	{
		for(int i = 1 ; i <= bEff(*M) ;i++)
		{
			for(int j = 1; j<= kEff(*M) ;j++)
			{
				input >> Elmt(*M,i,j);
				if(Elmt(*M,i,j)<=0)
				{
					/*
						Elmt M <=0 : tidak ada sisi
						Elmt M = nilai maksimal yg diasumsikan tidak muncul.
						mempermudah perbandingan dari nilai kecil -> besar
					 */
					Elmt(*M,i,j) = MAXEL;
				}
			}
		}
	}
	input.close();
}

char toChar(int a)
{	//Huruf hanya disesuaikan menurut soal
	//untuk menampilkan simpul dalam huruf
	char c;
	switch(a)
	{
		case 1 : c= 'A';break;
		case 2 : c= 'B';break;
		case 3 : c= 'C';break;
		case 4 : c= 'D';break;
		case 5 : c= 'E';break;
		case 6 : c= 'F';break;
		case 7 : c= 'G';break;
		case 8 : c= 'H';break;
		case 9 : c= 'I';break;
		default :c='@';break;
	}
	return c;
}

void PRIMS(MATRIKS M,bool CharNode)
{
	int i, j, k, a, b,edge = 1;
	int mincost = 0;
	int u = 0;
	int v = 1;
	int skip[SIZE] = {0};
	
	skip[1] =1;

	while(edge < bEff(M))
	{
		int min = Elmt(M,1,1);
		
		for (int i = 1; i <= bEff(M); i++)
		{
			for (int j = 1 ; j<=bEff(M) ; j++)
			{
				if(Elmt(M,i,j)< min)
				{
					if(skip[i]!=0)
					{
						min = Elmt(M,i,j);
						u = i;
						v = j;
					}
				}
			}

		}

		if(skip[u]==0 || skip[v]==0)
		{
			if(!CharNode){
 				cout <<edge++<<" ("<< (u) << " , " << (v) << ") = " << min << endl;
			}
			else
			{
				cout <<edge++<<" ("<< toChar(u) << " , " << toChar(v) << ") = " << min << endl;	
			}
			mincost += min;
			skip[v] = 1;
		}

		Elmt(M,u,v) = Elmt(M,v,u) = MAXEL+1;	
	}
	cout << "\nMinimum Spanning = " << mincost << endl;	
}

void KRUSKAL(MATRIKS Q,bool CharNode)
{
	int i, j, k, a, b, u, v, edge = 1 ;
	int mincost = 0;
	edge =1;

    while(edge< bEff(Q))
    {
        int min = MAXEL;
        for(i = 1; i <= bEff(Q); i++)
        {
            for(j = 1; j <= kEff(Q); j++)
            {
                if(Elmt(Q,i,j) < min)
                {
                    min = Elmt(Q,i,j);
                    a = u = i;
                    b = v = j;
                }
            }
        }
        u = FIND(u);
        v = FIND(v);
        if(UNION(u,v))
        {
            
 			if(!CharNode){
 				cout<<edge++<<"  ("<<(a)<<","<<(b)<<" ) = "<< min <<endl;
			}
			else
			{
				cout<<edge++<<"  ("<<toChar(a)<<","<<toChar(b)<<" ) = "<< min <<endl;	
			}
            mincost += min;
        }
        Elmt(Q,a,b) = MAXEL;
    }
    cout<<"\nMinimum Spanning =  "<<mincost<<endl;
}

int FIND(int i)
{
    while(parent[i])
    i = parent[i];
    return i;
}

int UNION(int i,int j)
{
    if(i!=j)
    {
        parent[j]=i;
        return 1;
    }
    return 0;
}

int main()
{
	MATRIKS M;
	string namaFile;
	int pilih;
	bool CharNode= false;
	cout<<"1. Graf 1 (6 Simpul)\n";
	cout<<"2. Graf 2 (9 Simpul)\n";
	cout<<"3. Graf 3 (12 Simpul)\n";
	cout<<"4. Graf 4 (5 Simpul)\n";
	cout<<" Pilih : ";
	cin>>pilih;

		switch(pilih){
			case 2: namaFile="Graf2.txt";CharNode=true;break;
			case 3: namaFile="Graf3.txt";break;
			case 4: namaFile="Graf4.txt";break;
			default: namaFile="Graf1.txt";break;
		}

	INPUT_DARI_FILE(&M,namaFile);
	cout<<" ALGORITMA PRIMS 	: \n";
	PRIMS(M,CharNode);
	cout<<" ALGORITMA KRUSKAL 	: \n";
	KRUSKAL(M,CharNode);
	return 0;


}