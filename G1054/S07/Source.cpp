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

	bool operator>(const Produs& p) {
		if (this->preturi != nullptr && p.preturi != nullptr) {
			if (this->preturi[this->nrZile - 1] > p.preturi[p.nrZile - 1])
				return true;
			return false;
		}
		else {
			throw exception("Nu ambele obj au preturi");
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

	friend bool operator==(string denumire, const Produs& p) {
		if (p.denumire != nullptr)
			return denumire == p.denumire;
		throw new ExceptieExistentaDenumire("Produs fara denumire");
	}

	Produs& operator+=(int cantitate) {
		if (cantitate > 0) {
			this->stoc += cantitate;
		}
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "\n-------<<----------";
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

	friend Produs& operator+=(Produs& p, float pretNou) {
		p.adaugaPret(pretNou);
		return p;
	}

	Produs operator+(int stocSuplimentar) {
		if (stocSuplimentar > 0) {
			Produs rez = *this;
			rez.stoc += stocSuplimentar;
			return rez;
		}
	}

	//pre-incrementare
	Produs& operator++() {
		this->stoc++;
		return *this;//returnam starea obj de dupa modificare/incrementare
	}

	//post-incrementare
	Produs operator++(int) {
		Produs copie = *this;
		this->stoc++;
		return copie;//returnam starea obj de dinainte de modificare
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

	bool& test(bool p) {
		return p;
	}

	bool operator!() {
		return !this->stoc;
	}

	//cast la int
	explicit operator int() {
		return this->stoc;
	}
};



int main()
{
	Produs p1("Pix", 100);
	p1.adaugaPret(9);
	p1.adaugaPret(9);
	p1.adaugaPret(10);

	Produs p2("Stilou", 10);
	p2.adaugaPret(670);
	p2.adaugaPret(900);

	Produs p3(nullptr, 0);
	p1.afisare();
	p2.afisare();
	p3.afisare();

	p3 = p1 + 120;
	cout << p3 << p1;

	p1 = ++p3;
	//p1 = p3.operator++();
	cout << p3 << p1;

	p1 = p3++;
	//p1 = p3.operator++(10);
	cout << p3 << p1;

	float pret = p3[0];
	cout << endl << pret;

	//float pretMediu = p3(1, 4);
	bool existaStoc = p3(100);
	cout << endl << existaStoc;
	//Produs v[10];
	//bool gasit = p3(v, n);
	//float pretMediu = p3();
	//Produs p5 = p3(1, 4);
	//bool deCumparat = p3(3);

	int x = 10;
	if (!x)
		cout << "\nx este zero";
	else
		cout << "\nx NU este zero";
	cout << endl << x;
	int y = 19;
	y = !x;
	cout << endl << y << " " << x;
	if (!p3)
		cout << "\nP3 nu are stoc";
	else
		cout << "\nP3 are stoc";

	//string denumire = p3;
	int stoc = (int)p3;
	cout << endl << stoc;

	//int x = p2 / 2;
	return 0;
}