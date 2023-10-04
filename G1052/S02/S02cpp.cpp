#include<iostream>
using namespace std;

void eliminaValSubMedie_vectorStatic(int* v, int& n) {
	float ma;
	int suma = 0;
	for (int i = 0; i < n; i++)
		suma += v[i];
	ma = (float)suma / n;
	int aux[100];
	int k = 0;
	for (int i = 0; i < n; i++)
		if (v[i] >= ma)
			aux[k++] = v[i];
	n = k;
	for (int i = 0; i < n; i++)
		v[i] = aux[i];
}

void eliminaValSubMedie(int*& v, int& n) {
	//p1.aflare noua dimensiune
	float ma;
	int suma = 0;
	for (int i = 0; i < n; i++)
		suma += v[i];
	ma = (float)suma / n;
	int ctValSubMedie = 0;
	for (int i = 0; i < n; i++)
		if (v[i] < ma)
			ctValSubMedie++;
	int dimensiuneNoua = n - ctValSubMedie;
	//p2.folosire vector auxiliar alocat cu noua dimensiune
	int* aux = new int[dimensiuneNoua];
	//p3.copiere in vector nou a ce trebuie sa pastram
	int k = 0;
	for (int i = 0; i < n; i++)
		if (v[i] >= ma)
			aux[k++] = v[i];
	//p4.dezalocare vector vechi
	delete[] v;
	//p5.vector vechi pointeaza spre vector nou
	v = aux;
	//p6.actualizare dimensiune
	n = dimensiuneNoua;
}

int main() {
	int v1[100];
	int* v2;
	int** a;
	int n = 10;
	/*v2 = (int*)malloc(n * sizeof(int));
	free(v2);*/
	v2 = new int[n];
	for (int i = 0; i < n; i++)
		v2[i] = i * 3 + 10;
	cout << "\nValori inainte: ";
	for (int i = 0; i < n; i++)
		cout << v2[i] << " ";
	eliminaValSubMedie(v2, n);
	cout << "\nValori dupa: ";
	for (int i = 0; i < n; i++)
		cout << v2[i] << " ";
	int* v3;
	v3 = new int[n];
	for (int i = 0; i < n; i++)
		v3[i] = v2[i];

	v3 = v2;//shallow copy 
	delete[] v2;

	int* pInt = new int(20);//aloc zm pentru o singura variabila int si o si initializez
	delete pInt;

	const int x = 10;
	int const y = 20;
	return 0;
}