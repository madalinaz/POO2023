#include<iostream>
using namespace std;

void dublareElementeImpare_Static(int* v, int& n) {
	int aux[1000]; int k = 0, i = 0;
	while (i < n) {
		aux[k++] = v[i];
		if (v[i] % 2 == 1) aux[k++] = v[i];
		i++;
	}
	n = k;
	for (int i = 0; i < n; i++)
		v[i] = aux[i];
}

void dublareElemImpare(int*& v, int& n) {
	//p1.aflare dim noua
	int ctImpar = 0;
	for (int i = 0; i < n; i++)
		if (v[i] % 2 != 0)
			ctImpar++;
	int dimensiuneNoua = n + ctImpar;
	//p2. alocare zm pentru un nou vector cu noua dimensiune de la p1
	int* aux = new int[dimensiuneNoua];
	//p3.se copiaza in noul vector ceea ce este necesar
	int k = 0;
	for (int i = 0; i < n; i++) {
		aux[k++] = v[i];
		if (v[i] % 2 != 0)
			aux[k++] = v[i];
	}
	//p4. dezaloc vectorul vechi
	delete[] v;
	//p5. vector vechi pointeaza spre vector nou
	v = aux;
	//p6. actualizare dimensiune noua
	n = dimensiuneNoua;
}

int main() {
	int* v;
	int n = 5;
	//v = (int*)malloc(n * sizeof(int));
	//free(v);
	v = new int[n];
	for (int i = 0; i < n; i++)
		v[i] = i + 10;
	cout << "\nVector inainte: ";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	dublareElemImpare(v, n);
	cout << "\nVector dupa: ";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	delete[] v;

	int* pInt = new int(5);
	delete pInt;
	int** a;

	return 0;
}