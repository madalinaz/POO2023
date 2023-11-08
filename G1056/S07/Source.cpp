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

	bool operator<=(const Produs& p) {
		if (this->nrZile > 0 && p.nrZile > 0) {
			if (this->preturi[this->nrZile - 1] <= p.preturi[p.nrZile - 1])
				return true;
			return false;
		}
		else throw exception("nu toate obj au preturi");
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

	friend bool operator==(string denumire, const  Produs& p) {
		if (p.denumire != nullptr)
			return denumire == p.denumire;
		else throw new ExceptieExistentaDenumire("produsul nu are denumire");
	}

	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "\n---------OSTREAM-----------";
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
			this->stoc += stocSuplimentar;
			return *this;
		}
	}

	//forma pre-incrementare
	Produs& operator++() {
		this->stoc++;
		return *this;//returneaza starea obj de dupa incrementare
	}

	//forma post-incrementare
	Produs operator++(int) {
		Produs copie = *this;
		this->stoc++;
		return copie;//returneaza starea obj de dinainte de incrementare
	}

	float operator[](int pozitie) {
		if (pozitie >= 0 && pozitie < this->nrZile) {
			if (this->preturi != nullptr) {
				return this->preturi[pozitie];
			}
		}
	}

	bool operator()(float pret) {
		if (pret > 0) {
			if (this->preturi != nullptr) {
				for (int i = 0; i < this->nrZile; i++)
					if (this->preturi[i] == pret)
						return true;
				return false;
			}
		}
	}

	explicit operator int() {
		return this->stoc;
	}

	bool operator!() {
		if (this->preturi == nullptr)
			return true;
		return false;
	}
};


int main()
{
	Produs p1("Pix", 100);
	p1.adaugaPret(10);
	p1.adaugaPret(12);
	p1.adaugaPret(15);

	Produs p2("Stilou", 10);
	p2.adaugaPret(1000);

	Produs p3 = p2;

	p3 = p1 + 5;
	cout << p3 << p1;

	p1 = p3 += 10;
	cout << p3;

	p1 = ++p3;
	cout << p1 << p3;

	p1 = p3++;
	cout << p1 << p3;

	float pret = p3[0];
	cout << endl << pret;

	//p3[0] = 12.5;

	//float pretMediu = p3(1, 3);
	bool gasit = p3(12.0f);
	cout << endl << gasit;
	//Produs vp[10];
	//bool gasit2 = p3(vp);
	//float pret2 = p3();

	int stoc = (int)p3;
	//string denumire = p3;
	//float pretCurent = p3;
	cout << endl << stoc;

	//int x = p3 - 10.0f;

	int x = 10;
	if (!x)
		cout << "\nx-ul este zero";
	else
		cout << "\nx-ul NU este zero";
	cout << endl << x;

	int y = 5;
	y = !x;
	cout << endl << x << " " << y;

	if (!p3)
		cout << "\nP3 nu are preturi";
	else
		cout << "\nP3 are preturi";
	return 0;
}