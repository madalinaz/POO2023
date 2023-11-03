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
};





int main()
{
	Produs p1("Stilou", 10);
	p1.afisare();
	Produs p2 = p1;
	p2.afisare();
	p2.adaugaPret(100);
	p2.adaugaPret(100);
	p2.adaugaPret(120);
	p2.afisare();

	Produs p3("Pix", 1000);
	p3.adaugaPret(12);

	p3.afisare();
	p1 = p2 = p3;
	p3.afisare();

	p3 = p3; //auto asignare
	p3.afisare();
	p1.adaugaPret(1000);
	//if(operator<=(p1,p2))
	try {
		if (p1 <= p2) //if(p1.operator<=(p2))
			cout << "\nP1 are un pret mai <= ca p2";
		else
			cout << "\nInvers comparatie p1 cu p2";
		cout << "\nExista cod dupa meth care arunca exceptie in bloc try";
	}
	catch (exception ex) {
		cout << ex.what();
	}

	Produs p4("Carte", 2);
	try {
		if (p1 <= p4)
			cout << "\nP1 are un pret mai <= ca p4";
		else
			cout << "\nInvers comparatie p1 cu p4";
		cout << "\nExista cod dupa meth care arunca exceptie in bloc try";
	}
	catch (exception ex) {
		cout << endl << ex.what();
	}

	Produs p5(nullptr, 0);
	try {
		if ("Stilou" == p5)
			cout << "\ndenumirea lui p5 este stilou";
		else
			cout << "\nInvers";
	}
	catch (ExceptieExistentaDenumire* ex) {
		cout << endl << ex->getMesaj();
		delete ex;
	}

	cout << p1 << p2;
	return 0;
}