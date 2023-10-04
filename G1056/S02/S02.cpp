#include<iostream>
using namespace std;

void dubleazaValMax_vectorStatic(int* v, int& n) {
	int max = v[0];
	for (int i = 1; i < n; i++) {
		if (v[i] > max) {
			max = v[i];
		}
	}
	int aux[100];
	int k = 0;
	for (int i = 0; i < n; i++) {
		aux[k++] = v[i];
		if (v[i] == max)
			aux[k++] = v[i];
	}
	n = k;
	for (int i = 0; i < n; i++)
		v[i] = aux[i];
}

void dubleazaValMax(int*& v, int& n) {
	//p1.aflare noua dimensiune
	int max = v[0];
	int nrApMax = 1;
	for (int i = 1; i < n; i++) {
		if (v[i] > max) {
			max = v[i];
			nrApMax = 1;
		}
		else if (v[i] == max) {
			nrApMax++;
		}
	}
	int dimensiuneNoua = n + nrApMax;
	//p2.folosire vector auxiliar alocat cu noua dimensiune
	int* aux = new int[dimensiuneNoua];
	//p3.copiere in vector nou a tot ce vrem
	int k = 0;
	for (int i = 0; i < n; i++) {
		aux[k++] = v[i];
		if (v[i] == max)
			aux[k++] = v[i];
	}
	//p4.dezalocare vector vechi
	delete[] v;
	//p5.vector vechi pointeaza spre vector nou
	v = aux;
	//p6.actualizare noua dimensiune vector vechi
	n = dimensiuneNoua;
}

int main() {
	int* v1;
	int v2[100];
	int n = 10;
	// v1 = (int*)malloc(n * sizeof(int));
	//free(v1);
	v1 = new int[n];
	for (int i = 0; i < n; i++)
		v1[i] = 10 + i % 2 * 2 + i / 2;
	cout << "\nAfisare valori inainte: ";
	for (int i = 0; i < n; i++)
		cout << v1[i] << " ";
	dubleazaValMax(v1, n);
	cout << "\nAfisare valori dupa: ";
	for (int i = 0; i < n; i++)
		cout << v1[i] << " ";
	delete[] v1;

	int* pInt = new int(10);//pointeaza spre o adresa la care regasim o valoare int initializata cu 10
	delete pInt;


	return 0;
}