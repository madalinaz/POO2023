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

	Produs operator-(int stocDeRedus) {
		if (stocDeRedus > 0) {
			if (this->stoc - stocDeRedus > 0) {
				Produs rez = *this;
				rez.stoc -= stocDeRedus;
				return rez;
			}
		}
	}

	Produs& operator+=(int stocSuplimentar) {
		if (stocSuplimentar > 0) {
			this->stoc += stocSuplimentar;
			return *this;
		}
	}

	//pre-incrementare
	Produs& operator++() {
		this->stoc++;
		return *this;//returneaza stare obj de dupa modif
	}

	//post-incrementare
	Produs operator++(int) {
		Produs copie = *this;
		this->stoc++;
		return copie;//returneaza starea obj de dinainte de modif
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

	bool operator!() {
		if (this->nrZile == 0)
			return true;
		else
			return false;

		//return !this->nrZile;
	}

	operator string() {
		string rez = "";
		rez += "\n--------------------";
		if (this->denumire != nullptr) {
			rez += "\nDenumire: ";
			rez += this->denumire;
		}
		else {
			rez += "\nDenumire: -";
		}
		rez += "\nStoc: "; rez += this->stoc;
		rez += "\nNr zile: "; rez += this->nrZile;
		rez += "\nIstoric preturi: ";
		if (this->nrZile > 0) {
			for (int i = 0; i < this->nrZile; i++)
				rez += this->preturi[i]; rez += " ";
		}
		else {
			rez += "-";
		}
		rez += "\n--------------------";
		return rez;
	}

	explicit operator int() {
		return this->stoc;
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

	p3 = p1 - 10;
	cout << p3 << p1;

	p1 = p3 += 10;
	cout << p3;

	p1 = ++p3;
	cout << p1 << p3;
	p1 = p3++;
	p1 = p3.operator++(2);
	cout << p1 << p3;

	float pret = p3[1];
	//p3[0] = 14.0f;
	cout << endl << pret;

	//float pretMediu = p3(1, 3);
	bool exista = p3(12);
	//Produs vp[10];
	//bool exista2 = p3(vp);
	//float pretMediu2 = p3();
	cout << endl << exista;

	int x = 5;
	if (!x)
		cout << "\nx este zero";
	else
		cout << "\nx NU este zero";
	cout << endl << x;
	int y = 10;
	y = !x;
	cout << endl << y << " " << x;

	if (!p3)
		cout << "\nP3 nu are preturi";
	else
		cout << "\nP3 are preturi";

	string descriereProdus = p3;
	cout << descriereProdus;

	int stoc = (int)p3;
	cout << endl << stoc;

	//int stoc = p3 * 2;
	return 0;
}