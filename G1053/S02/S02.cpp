#include<iostream>
using namespace std;

void dublareValoarePare_VectorStatic(int* v, int& n) {
	int aux[100];
	int k = 0;
	for (int i = 0; i < n; i++) {
		aux[k++] = v[i];
		if (v[i] % 2 == 0)
			aux[k++] = v[i];
	}
	n = k;
	for (int i = 0; i < n; i++)
		v[i] = aux[i];
}

void dublareValoarePare(int*& v, int& n) {
	//p1. se calc noua dimensiune
	int nrPare = 0;
	for (int i = 0; i < n; i++)
		if (v[i] % 2 == 0)
			nrPare++;
	int dimensiuneNoua = n + nrPare;
	//p2. se aloca zm pentru un nou vector cu noua dim de la p1
	int* aux = new int[dimensiuneNoua];
	//p3. se copiaza in noul vector ceea ce vrem
	int k = 0;
	for (int i = 0; i < n; i++) {
		aux[k++] = v[i];
		if (v[i] % 2 == 0)
			aux[k++] = v[i];
	}
	//p4. se dezaloca vectorul vechi
	delete[] v;
	//p5. vector vechi pointeaza spre vector nou
	v = aux;
	//p6. se actualizeaza dimensiunea vectorului vechi
	n = dimensiuneNoua;
}

int main() {
	int* v;
	int v2[100];
	int n = 5;
	//v = (int*)malloc(n * sizeof(int));
	//free(v);
	v = new int[n];
	for (int i = 0; i < n; i++)
		v[i] = i + 10;
	cout << "\nVector inainte: ";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	dublareValoarePare(v, n);
	cout << "\nVector dupa: ";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	delete[] v;

	int* pInt = new int(10);//pointeaza spre o zm care contine un int care a fost si initializat cu 10
	delete pInt;

	return 0;
}