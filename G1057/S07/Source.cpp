#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class ExceptieExistentaDenumire {
	string mesaj;
public:
	ExceptieExistentaDenumire(string mesaj) :mesaj(mesaj) {}
	string getMesaj() { return this->mesaj; }
};

class Produs
{
	char* denumire = nullptr;
	int nrZile = 0;
	float* preturi = nullptr;
	int stoc = 0;

public:
	Produs(const char* denumire, int stoc)
	{
		if (denumire != nullptr) {
			this->denumire = new char[strlen(denumire) + 1];
			strcpy(this->denumire, denumire);
		}
		if (stoc > 0)
			this->stoc = stoc;
	}

	Produs(const Produs& p)
	{
		if (p.denumire != nullptr) {
			this->denumire = new char[strlen(p.denumire) + 1];
			strcpy(this->denumire, p.denumire);
		}
		this->stoc = p.stoc;
		this->nrZile = p.nrZile;
		this->preturi = new float[this->nrZile];
		for (int i = 0; i < this->nrZile; i++)
			this->preturi[i] = p.preturi[i];
	}

	Produs& operator=(const Produs& p)
	{
		if (this != &p) {
			delete[] this->denumire;
			this->denumire = nullptr;
			delete[] this->preturi;
			this->preturi = nullptr;
			if (p.denumire != nullptr) {
				this->denumire = new char[strlen(p.denumire) + 1];
				strcpy(this->denumire, p.denumire);
			}
			this->stoc = p.stoc;
			this->nrZile = p.nrZile;
			this->preturi = new float[this->nrZile];
			for (int i = 0; i < this->nrZile; i++)
				this->preturi[i] = p.preturi[i];
		}
		return *this;
	}

	bool operator!=(const Produs& p) {
		if (this->preturi != nullptr && p.preturi != nullptr) {
			if (this->preturi[this->nrZile - 1] != p.preturi[p.nrZile - 1])
				return true;
			return false;
		}
		else {
			throw exception("\nNu ambele produse au preturi");
		}
	}

	void adaugaPret(float pretNou)
	{
		if (pretNou > 0 && (this->nrZile == 0 || (pretNou != this->preturi[this->nrZile - 1]))) {
			Produs p = *this;
			delete[] this->preturi;
			this->nrZile++;
			this->preturi = new float[this->nrZile];
			for (int i = 0; i < p.nrZile; i++)
				this->preturi[i] = p.preturi[i];
			this->preturi[this->nrZile - 1] = pretNou;
		}
	}

	void afisare()
	{
		cout << "\n--------------------";
		if (this->denumire != nullptr) {
			cout << "\nDenumire: " << this->denumire;
		}
		else {
			cout << "\nDenumire: -";
		}
		cout << "\nStoc: " << this->stoc;
		cout << "\nNr zile: " << this->nrZile;
		cout << "\nIstoric preturi: ";
		if (this->nrZile > 0) {
			for (int i = 0; i < this->nrZile; i++)
				cout << this->preturi[i] << " ";
		}
		else {
			cout << "-";
		}
		cout << "\n--------------------";
	}

	~Produs()
	{
		delete[] this->denumire;
		this->denumire = nullptr;
		delete[] this->preturi;
		this->preturi = nullptr;
	}

	friend bool operator!=(string denumire, const Produs& p);

	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "\n--------<<---------";
		if (p.denumire != nullptr) {
			out << "\nDenumire: " << p.denumire;
		}
		else {
			out << "\nDenumire: -";
		}
		out << "\nStoc: " << p.stoc;
		out << "\nNr zile: " << p.nrZile;
		out << "\nIstoric preturi: ";
		if (p.nrZile > 0) {
			for (int i = 0; i < p.nrZile; i++)
				out << p.preturi[i] << " ";
		}
		else {
			out << "-";
		}
		out << "\n--------------------";
		return out;
	}

	Produs operator+(int stocSuplimentar) {
		if (stocSuplimentar > 0) {
			Produs rez = *this;
			rez.stoc += stocSuplimentar;
			return rez;
		}
	}

	Produs& operator+=(int stocSuplimentar) {
		if (stocSuplimentar > 0) {
			//*this = *this + stocSuplimentar;
			this->stoc += stocSuplimentar;
			return *this;
		}
	}

	//pre-incrementare
	Produs& operator++() {
		this->stoc++;
		return *this;//returneaza starea obj de dupa modif
	}

	//post-incrementare
	Produs operator++(int) {
		Produs copie = *this;
		this->stoc++;
		return copie;//returneaza stare obj de dinainte de modif
	}

	float operator[](int pozitie) {
		if (pozitie >= 0 && pozitie < this->nrZile) {
			if (this->preturi != nullptr) {
				return this->preturi[pozitie];
			}
		}
	}

	bool operator()(int stocNecesar) {
		if (stocNecesar > 0) {
			return this->stoc >= stocNecesar;
		}
	}

	bool operator!() {
		return !this->stoc;
	}

	//cast la int
	explicit operator int() {
		return this->stoc;
	}
};

bool operator!=(string denumire, const Produs& p) {
	if (p.denumire != nullptr) {
		return denumire != p.denumire;
		//return p != denumire;
	}
	else
		throw new ExceptieExistentaDenumire("Nu exista denumire!");
}

Produs operator+(int stocSuplimentar, Produs p) {
	return p + stocSuplimentar;
}

int main()
{
	Produs p1("Pix", 100);
	p1.adaugaPret(10);
	p1.adaugaPret(10);
	p1.adaugaPret(12);

	Produs p2("Stilou", 10);
	p2.adaugaPret(780);
	p2.adaugaPret(900);

	p1.afisare();
	p2.afisare();

	Produs p3(nullptr, 0);
	p3.afisare();

	p3 = p1 + 5;
	cout << p3 << p1;

	p3 = 5 + p1;

	p1 = p3 += 10;
	cout << p3;

	p1 = ++p3;
	//p3.operator++(); pre-incrementare
	cout << p3 << p1;
	p1 = p3++;
	//p3.operator++(2); post-incrementare
	cout << p3 << p1;

	float pret = p3[0];
	cout << endl << pret;

	//float pretMediu = p3(1, 5);
	bool existaStoc = p3(12);
	cout << endl << existaStoc;
	//Produs v[10];
	//bool gasit = p3(v, n);
	//float pretMediu = p3();
	//bool deCumparat = p3(3);
	//Produs p4 = p3(1, 5);

	int x = 10;
	if (!x)
		cout << "\nx este zero";
	else
		cout << "\nx NU este zero";
	cout << endl << x;
	int y = 6;
	y = !x;
	cout << endl << y << " " << x;

	if (!p3)
		cout << "\nP3 nu are stoc";
	else
		cout << "\nP3 are stoc";

	//string denumire = p3;
	int stoc = (int)p3;

	//int x = p3 / 2;
	return 0;
}