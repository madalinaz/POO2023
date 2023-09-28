#include<stdio.h>
#include<string>

void f1(int a, int b) {
	int aux = a;
	a = b;
	b = aux;
}

int test2(int& a) {
	int b = a++;
	return b;
}

int test(const int& a) {
	int b = a + 1;
	return b;
}

void f2(int& a, int& b) {
	int aux = a;
	a = b;
	b = aux;
}

void f3(int* a, int* b) {
	int* aux = a;
	a = b;
	b = aux;
}

void f4(int* a, int* b) {
	int aux = *a;
	*a = *b;
	*b = aux;
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

	char s[31];
	strcpy_s(s, "Gigel invata POO");
	printf("\n%s", s);
	return 0;
}