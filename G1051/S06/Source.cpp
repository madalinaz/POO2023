#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

class ExceptieExistentaPreturi {
	string mesaj;
	static int nrExceptiiGenerate;
public:
	ExceptieExistentaPreturi(string mesaj) :mesaj(mesaj) { ExceptieExistentaPreturi::nrExceptiiGenerate++; }

	string getMesaj() { return this->mesaj; }
};
int ExceptieExistentaPreturi::nrExceptiiGenerate = 0;

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
		if (this->nrZile > 0 && p.nrZile > 0) {
			if (this->preturi[this->nrZile - 1] > p.preturi[p.nrZile - 1])
				return true;
			return false;
		}
		else
			throw new exception("unele obj nu au preturi inca");//apel constructor cu 1 param
	}

	void setPreturi(float* preturi, int nrZile)
	{
		if (nrZile > 0 && preturi != nullptr)
		{
			this->nrZile = nrZile;
			this->preturi = new float[this->nrZile];
			for (int i = 0; i < this->nrZile; i++)
				this->preturi[i] = preturi[i];
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

	friend bool operator>(float pret, Produs p) {
		return pret > p.preturi[p.nrZile - 1];
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
	Produs p1("Paine", 10);
	p1.afisare();
	Produs p2 = p1;
	p2.afisare();
	p2.adaugaPret(100);
	p2.adaugaPret(100);
	p2.adaugaPret(120);
	p2.afisare();

	Produs p3(nullptr, 0);
	p3.afisare();
	p3 = p2;
	p3.afisare();
	p1 = p3 = p2;//apel in cascada / compunere de operatori
	//p1.operator=(p3.operator=(p2));
	p1.afisare();

	p1 = p1;//auto asignare
	p1.afisare();
	p1.adaugaPret(150);

	Produs p4("Carne", 100);
	try {
		if (p1 > p4)
			cout << "\nP1 are un pret mai mare ca p4";
		else
			cout << "\nInvers p1 vs p4";
	}
	catch (exception* ex) {
		cout << ex->what();
		delete ex;
	}

	//if(p1.operator>(p2))
	try {
		if (p1 > p2)
			cout << "\nP1 are un pret mai mare ca p2";
		else
			cout << "\nInvers p1 vs p2";
	}
	catch (exception* ex) {
		cout << ex->what();
		delete ex;
	}

	if (120 > p2)
		cout << "\np2 are un pret < ca 120";
	else
		cout << "\nInvers";

	cout << p2 << p1;

	return 0;
}