#include<iostream>
using namespace std;

void eliminaValoriPare(int*& v, int& n) {
	//p1. aflare dimensiune noua
	int nrPare = 0;
	for (int i = 0; i < n; i++)
		if (v[i] % 2 == 0)
			nrPare++;
	int dimensiuneNoua = n - nrPare;
	//p2.declare vector nou pe baza noii dimensiuni
	int* aux = new int[dimensiuneNoua];
	//p3.copiere in vector nou a valorilor dorite
	int k = 0;
	for (int i = 0; i < n; i++)
		if (v[i] % 2 != 0)
			aux[k++] = v[i];
	//p4.dezlocam vector vechi
	delete[] v;
	//p5.vector vechi pointeaza spre vector nou
	v = aux;
	//p6.setare dimensiune
	n = dimensiuneNoua;
}

int main() {
	int v1[100];
	int* v2;
	int n = 5;
	//v2 = (int*)malloc(n * sizeof(int));
	v2 = new int[5];
	for (int i = 0; i < n; i++)
		v2[i] = i + 10;
	cout << "\nValori inainte de eliminare: ";
	for (int i = 0; i < n; i++)
		cout << v2[i] << " ";
	eliminaValoriPare(v2, n);
	cout << "\nValori dupa eliminare: ";
	for (int i = 0; i < n; i++)
		cout << v2[i] << " ";

	//free(v2);
	delete[] v2;
	return 0;
}