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

	//forma de pre-incrementare
	Produs& operator++() {
		this->stoc++;
		return *this;//returneaza obj de dupa modificare
	}

	//post-incrementare
	Produs operator++(int) {
		Produs copie = *this;
		this->stoc++;
		return copie;//returneaza obj de dinainte de modificare
	}

	float& operator[](int pozitie) {
		if (pozitie >= 0 && pozitie < this->nrZile)
			return this->preturi[pozitie];
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

	//cast la string
	operator string() {
		return this->denumire;
	}

	//cast la int
	explicit operator int() {
		return this->stoc;
	}
};



int main()
{
	Produs p1("Pix", 100);
	p1.adaugaPret(10);
	p1.adaugaPret(12);
	p1.adaugaPret(15);

	Produs p2("Stilou", 10);
	p2.adaugaPret(670);
	p2.adaugaPret(700);

	Produs p3("Carte", 50);

	p3 = p1 + 10;
	p3.operator=(p1.operator+(10));
	cout << p3;

	p1 = p3 += 20;
	cout << p3;

	p2 = ++p3;
	cout << p2 << p3;

	p2 = p3++;
	cout << p2 << p3;

	float pret = p3[0];
	cout << endl << pret;

	//p3[1] = 12.5f;

	bool gasit = p3(12);
	cout << endl << gasit;

	/*Produs v[10];
	bool gasit2 = p3(v);*/

	//float pretMediu = p3;
	string denumire = p3;
	cout << endl << denumire;

	if ((int)p1 != (int)p2)
		cout << "\nStocurile sunt diferite";
	return 0;
}