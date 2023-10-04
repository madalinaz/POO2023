#include<iostream>
using namespace std;

void dublareValMax(int*& v, int& n) {
	//p1. se calc noua dimensiune
	int ctMax = 1;
	int max = v[0];
	for (int i = 1; i < n; i++)
		if (v[i] > max) {
			max = v[i];
			ctMax = 1;
		}
		else if (v[i] == max) {
			ctMax++;
		}
	int dimensiuneNoua = n + ctMax;
	//p2. se aloca zm pentru un vector nou de dim de la p1
	int* aux = new int[dimensiuneNoua];
	//p3. copiem in vector nou din vector vechi ce ne trebuie
	int k = 0;
	for (int i = 0; i < n; i++) {
		aux[k++] = v[i];
		if (v[i] == max)
			aux[k++] = v[i];
	}
	//p4. dezalocam vector vechi
	delete[] v;
	//p5. vector vechi pointeaza spre vector nou
	v = aux;
	//p6.actualizare dim vector
	n = dimensiuneNoua;
}

int main() {
	int* v;
	int n = 5;
	//v = (int*)malloc(n * sizeof(int));
	//free(v);
	v = new int[n];
	for (int i = 0; i < n; i++)
		v[i] = 10 + i / 3;
	cout << "\nVector inainte: ";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	dublareValMax(v, n);
	cout << "\nVector dupa: ";
	for (int i = 0; i < n; i++)
		cout << v[i] << " ";
	delete[] v;
	return 0;
}