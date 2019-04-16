// Tema2-Graf_orientat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

using namespace std;

class Matrice {

	int **a;
protected:
	int size;
	int bonds;

public:

	Matrice(int max) {

		size = max;
		a  = new int*[max + 1];
		for (int i = 0; i <= size + 1; i++) {
			a[i] = new int[max + 1];
			for (int j = 0; j <= size; j++)
				a[i][j] = 0;
		}

	} 
	Matrice(const Matrice & g) {

		for (int i = 1; i < size; i++)
			for (int j = 1; j < size; j++)
				a[i][j] = g.a[i][j];
	}
	/*~Matrice() {
		for (int i = 1; i <= size; i++)
			delete[] a[i];
	}*/

	friend istream &operator >> (istream & input, Matrice& g1);
	friend ostream &operator << (ostream & output, Matrice& g1);

	int getBonds() { return bonds; }
	int getSize() { return size; }
	int getElement(int x, int y) {
		return a[x][y];
	}

};

istream& operator >> (istream & input, Matrice& g1) {

	int i, j;

	input >> g1.size;
	input >> g1.bonds;

	for (int k = 1; k <= g1.bonds; k++) {
		input >> i;
		input >> j;
		g1.a[i][j] = 1;
	}
	return input;
}

ostream& operator << (ostream & output, Matrice& g1) {

	for (int i = 1; i <= g1.size; i++) {
		for (int j = 1; j <= g1.size; j++)
			output << g1.a[i][j] << ' ';
		output << endl;
	}
	return output;

}
 
class Graf {

	int *nr_noduri;

public:

	Graf( class Matrice & g ) {

		nr_noduri = new int;
		*nr_noduri = g.getSize();

	}

	~Graf() {
		delete nr_noduri;
	}

	virtual void BFS(int x, Matrice & g ) = 0;
	virtual void DFS(int x, Matrice & g, int *vis) = 0;
	virtual int Conex(int x, Matrice & g) = 0;

};


class Graf_complet : public Graf {

	int *nr_muchii;
	int *rezultat_complet;
public:

	Graf_complet(class Matrice &g) : Graf (g) {

		nr_muchii = new int;
		*nr_muchii = g.getBonds();

	}

	void BFS(int x, Matrice & g) override {

		int i, first = 0, last = 0, nr;
		nr = g.getSize();

		int *vis = new int [nr + 1];
		int *tail = new int[nr + 1];

		for (i = 1; i <= nr; i++) {
			vis[i] = 0;
			tail[i] = 0;
		}

		vis[x] = 1;
		tail[0] = x;
		while (first <= last) {
			x = tail[first++];
			for (i = 1; i <= nr; i++) {
				int k = g.getElement(x, i);
			//	cout << k << endl;
				if (k && vis[i] !=1) {
					vis[i] = 1;
					tail[++last] = i;
				}
			}
		}
		cout << "Rezultatul parcurgerii in latime este:";
		for (int i = 0; i <= last; i++)
			cout << tail[i] << ' ';
		cout << endl;
	}

	void DFS(int x, Matrice & g, int *vis = NULL) override {

		int i, nr;
		nr = *nr_muchii;

		if (vis == NULL) {

			vis = new int[nr + 1];
			for (i = 1; i <= nr; i++)
				vis[i] = 0;
		}
			vis[x] = 1;
			cout << x << " ";

			for (i = 1; i <= nr; i++) {
				int k = g.getElement(x, i);
				if (k == 1 && vis[i] == 0) DFS(i, g, vis);

			}
		
	}
	
	int Conex(int x, Matrice & g) override {

		int **matrix;
		rezultat_complet = new int;

		int k = g.getSize();
		matrix = new int*[k + 1];

		for (int i = 0; i <= k; i++) 
			matrix[i] = new int[k + 1];

		for (int i = 1; i <= k ; i++){
			for (int j = 0; j <= k; j++)
				if(g.getElement(i,j) == 1) matrix[j][i] = 1;
				else matrix[j][i] = 0;
		}
	
		for (int h = 1; h <= k; h++)
			for (int i = 1; i <= k; i++)
				for (int j = 1; j <= k; j++)
					if ( matrix[i][h] ==1  && matrix[h][j] ==1 )
							matrix [i][j] = 1;
			
		for (int i = 1; i <= k; i++)
			for (int j = 1; j <= k; j++)
				if (i != j && matrix[i][j] == 0) {
					cout << "Graful dat nu este tare-conex." << endl;
					*rezultat_complet = 0;
					return 0;
				}
		cout << "Graful dat este tare-conex." << endl;
		*rezultat_complet = 1;
		return 1;
	};
	
	int getRezComp() {
		return *rezultat_complet;
	}
};

class Graf_antisimetric : public Graf_complet{

int *nr_muchii;
int *rezultat_antisimetric;

public:

	Graf_antisimetric(Matrice &g) : Graf_complet(g) {
		nr_muchii = new int;
		rezultat_antisimetric = new int;
		*nr_muchii = g.getBonds();
	}

	virtual int Antisimetric( Matrice &g) {

		for (int i = 1; i <= g.getSize(); i++)
			for (int j = i + 1; j <= g.getSize(); j++)
				if (g.getElement(i, j) == 1 && g.getElement(j, i) == 0) {
					cout << "Graful dat este antisimetric!" << endl;
					*rezultat_antisimetric = 0;
				return 0;
				}

	cout << "Graful dat este simetric!" << endl;
	*rezultat_antisimetric = 1;
	return 1;
	};
	int getRezultat() {
		return *rezultat_antisimetric;
	}
	~Graf_antisimetric() {
		delete nr_muchii;
	}
};


//class Graf_turneu : public Graf_antisimetric, public Graf_complet {
//public:
//	Graf_turneu(Matrice  & g) :
//		Graf_antisimetric(g), Graf_complet(g) {};
//	virtual void Turneu() {
//		if (getRezultat() == 1 && getRezComp() == 1) cout << "Graful este Turneu";
//		else cout << "Graful nu este Turneu";
//	};
//};

int main()
{
	Matrice g1(10),g2(10);

	cin >> g1;
	cout << endl;
	cout << g1 << endl;

	g2 = g1;
	cout << g2;

	cout << g1.getBonds() << ' ' << g1.getSize() << endl;
	
	Graf_complet *graf = new Graf_complet(g1);
	graf->BFS(1, g1);
	cout << "Rezultatul parcurgerii in adancime este :";
	graf->DFS(1, g1);
	cout << endl;

	graf->Conex(1,g1);
	cout << endl;

	Graf_antisimetric *anti = new Graf_antisimetric(g1);
	anti->Antisimetric(g1);

	Graf_turneu *tur = new Graf_turneu(g1);
	//tur->Turneu();



	return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

