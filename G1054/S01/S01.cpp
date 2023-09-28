#include<stdio.h>
#include<string>

void f1(int a, int b) {
	int aux = a;
	a = b;
	b = aux;
}

void f2(int& a, int& b) {
	int aux = a;
	a = b;
	b = aux;
}

void f3(int* a, int* b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

void f4(int* a, int* b) {
	int* aux = a;
	a = b;
	b = aux;
}

int main() {
	int x, y;
	x = 5; y = 10;
	printf("\nApel transfer prin valoare");
	printf("\nInainte x=%d y=%d", x, y);
	f1(x, y);
	printf("\nDupa x=%d y=%d", x, y);

	x = 5; y = 10;
	printf("\nApel transfer prin referinta");
	printf("\nInainte x=%d y=%d", x, y);
	f2(x, y);
	printf("\nDupa x=%d y=%d", x, y);

	x = 5; y = 10;
	printf("\nApel transfer prin pointeri I");
	printf("\nInainte x=%d y=%d", x, y);
	f3(&x, &y);
	printf("\nDupa x=%d y=%d", x, y);

	x = 5; y = 10;
	printf("\nApel transfer prin pointeri II");
	printf("\nInainte x=%d y=%d", x, y);
	f4(&x, &y);
	printf("\nDupa x=%d y=%d", x, y);

	char sir[41];
	strcpy(sir, "Gigel si Costel invata programare");
	strcpy(sir + 6, sir + 15);
	printf("\n%s", sir);

	int* v;
	v = (int*)malloc(5 * sizeof(int));
	for (int i = 0; i < 5; i++)
		v[i] = i + 100;

	return 0;
}