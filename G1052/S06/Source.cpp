#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

//clasa tip custom exception
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
		else throw exception("nu ambele obj au preturi");
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
		if (p.denumire != nullptr) {
			return denumire == p.denumire;
			//return p == denumire; (dar cu p transferat prin valoare neconstant)
		}
		else {
			throw new ExceptieExistentaDenumire("obj produs nu are denumire");
		}
	}

	bool operator==(string denumire) {
		return this->denumire == denumire;
	}

	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "\n------OSTREAM-------";
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
		cout << "\n--------------------";
		return out;
	}
};



int main()
{
	Produs p1("Pix", 100);
	p1.adaugaPret(12);
	p1.adaugaPret(12);
	p1.adaugaPret(15);

	Produs p2("Stilou", 10);
	p2.adaugaPret(1200);
	p2.adaugaPret(1050);

	Produs p3(nullptr, 0);

	p3.afisare();
	//p3 = p2 = p1; //apel in cascada
	p3.afisare();

	p1.afisare();
	p1 = p1; //auto atribuire
	p1.afisare();

	try {
		if (p1 > p3) //p1.operator>(p2) sau operator>(p1,p2)
			cout << "\nP1 are un pret > ca p2";
		else
			cout << "\nInvers";
		cout << "\nAlte instructiuni dupa";
	}
	catch (exception ex) {
		cout << endl << ex.what();
	}

	try {
		if ("penar" == p3)
			cout << "\nDenumirea lui p3 e penar";
		else
			cout << "\nInvers";
	}
	catch (ExceptieExistentaDenumire* ex) {
		cout << endl << ex->getMesaj();
		delete ex;
	}

	cout << p1 << 2;

	return 0;
}