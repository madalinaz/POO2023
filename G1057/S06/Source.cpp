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
};

bool operator!=(string denumire, const Produs& p) {
	if (p.denumire != nullptr) {
		return denumire != p.denumire;
		//return p != denumire;
	}
	else
		throw new ExceptieExistentaDenumire("Nu exista denumire!");
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

	//p3 = p2 = p1;//apel in cascada op =
	//p3.afisare();

	p1 = p1;//auto asignare
	p1.afisare();

	try {
		if (p1 != p2) //p1.operator!=(p2) SAU operator!=(p1,p2)
			cout << "\nProdusele p1 si p2 au preturile curente diferite";
		else
			cout << "\nInvers";
		cout << "\nCod care se poate executa dupa apel meth cu throw";
	}
	catch (exception ex) {
		cout << ex.what();
	}

	try {
		if (p1 != p3)
			cout << "\nProdusele p1 si p3 au preturile curente diferite";
		else
			cout << "\nInvers";
		cout << "\nCod care se poate executa dupa apel meth cu throw";
	}
	catch (exception ex) {
		cout << ex.what();
	}

	try {
		if ("stilou" != p3)
			cout << "\nP2 nu are denumirea stilou";
		else
			cout << "\nP2 are denumirea stilou";
	}
	catch (ExceptieExistentaDenumire* ex) {
		cout << endl << ex->getMesaj();
		delete ex;
	}

	cout << 2 << p2 << 3;
	return 0;
}