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
	printf("\nApel f1 (transfer prin valoare)");
	x = 5; y = 10;
	printf("\nInainte de apel x=%d y=%d", x, y);
	f1(x, y);
	printf("\nDupa apel x=%d y=%d", x, y);

	printf("\nApel f2 (transfer prin referinta)");
	x = 5; y = 10;
	printf("\nInainte de apel x=%d y=%d", x, y);
	f2(x, y);
	printf("\nDupa apel x=%d y=%d", x, y);

	printf("\nApel f3 (transfer prin pointeri I)");
	x = 5; y = 10;
	printf("\nInainte de apel x=%d y=%d", x, y);
	f3(&x, &y);
	printf("\nDupa apel x=%d y=%d", x, y);

	printf("\nApel f4 (transfer prin pointeri II)");
	x = 5; y = 10;
	printf("\nInainte de apel x=%d y=%d", x, y);
	f4(&x, &y);
	printf("\nDupa apel x=%d y=%d", x, y);

	printf("\nLucrul cu siruri de caractere\n");
	char sir[25];
	strcpy_s(sir, "Gigel Gigelus");
	sir[5] = 'b';
	printf("%s", sir);
	return 0;
}