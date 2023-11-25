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

	bool operator>(Produs p) {
		if (this->preturi != nullptr && p.preturi != nullptr) {
			if (this->preturi[this->nrZile - 1] > p.preturi[p.nrZile - 1])
				return true;
			return false;
		}
		else {
			throw exception("nu ambele obj au preturi");
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

	bool operator==(string denumire) {
		return this->denumire == denumire;
	}

	friend ostream& operator<<(ostream& out, const Produs& p) {
		out << "\n------<<-------";
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

	//pre-incrementare
	Produs& operator++() {
		this->stoc++;
		return *this;//returneaza obj de dupa incrementare
	}

	//post-incrementare
	Produs operator++(int) {
		Produs copie = *this;
		this->stoc++;
		return copie;//returneaza obj de dinainte de incrementare
	}

	float operator[](int pozitie) {
		if (pozitie >= 0 && pozitie < this->nrZile) {
			if (this->preturi != nullptr) {
				return this->preturi[pozitie];
			}
		}
	}

	bool operator()(int stocMinim) {
		if (stocMinim > 0) {
			return this->stoc >= stocMinim;
		}
	}

	bool operator!() {
		return !this->stoc;
	}

	explicit operator int() {
		return this->stoc;
	}

	friend istream& operator>>(istream& in, Produs& p) {
		delete[] p.denumire;
		p.denumire = nullptr;
		delete[] p.preturi;
		p.preturi = nullptr;

		cout << "\nIntroduceti denumirea: ";
		//char buffer[100];
		//in >> buffer;
		//p.denumire = new char[strlen(buffer) + 1];
		//strcpy(p.denumire, buffer);

		string buffer;
		in >> buffer;
		p.denumire = new char[buffer.size() + 1];
		strcpy(p.denumire, buffer.data());

		cout << "Introduceti stoc: ";
		in >> p.stoc;
		if (p.stoc < 0)
			p.stoc = 0;
		cout << "Introduceti nr zile analiza preturi: ";
		in >> p.nrZile;
		if (p.nrZile <= 0) {
			p.nrZile = 0;
			p.preturi = nullptr;
		}
		else {
			p.preturi = new float[p.nrZile];
			for (int i = 0; i < p.nrZile; i++) {
				cout << "pret[" << i << "]=";
				in >> p.preturi[i];
			}
		}
		return in;
	}
};

bool operator==(string denumire, Produs p) {
	return p == denumire;
}


class Cadou {
private:
	string denumire = "Anonim";
	float pret = 0;

public:
	Cadou()
	{
	}

	Cadou(string denumire, float pret)
	{
		this->denumire = denumire;
		this->pret = pret;
	}

	Cadou(const Cadou& c)
	{
		this->denumire = c.denumire;
		this->pret = c.pret;
	}

	Cadou& operator=(const Cadou& c)
	{
		this->denumire = c.denumire;
		this->pret = c.pret;
		return *this;
	}

	friend ostream& operator<<(ostream& out, const Cadou& c)
	{
		out << "\nDenumire: " << c.denumire << ", pret: " << c.pret;
		return out;
	}

	friend istream& operator>>(istream& in, Cadou& c)
	{
		cout << "Introduceti denumire: ";
		in >> c.denumire;
		cout << "Introduceti pret: ";
		in >> c.pret;
		return in;
	}
};

class WishList1 {
	string detinator;
	Cadou listaCadouri[100];
	int nrCadouri;
};

class WishList2 {
	string detinator;
	Cadou* listaCadouri[100];
	int nrCadouri;
};

class WishList3 {
	string detinator;
	Cadou* listaCadouri;
	int nrCadouri;
};

class WishList {
	string detinator = "Anonim";
	Cadou** listaCadouri = nullptr;
	int nrCadouri = 0;

public:
	WishList() { }

	WishList(string detinator, Cadou** listaCadouri, int nrCadouri) {
		this->detinator = detinator;
		if (nrCadouri > 0 && listaCadouri != nullptr) {
			this->nrCadouri = nrCadouri;
			//this->listaCadouri = listaCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++) {
				//this->listaCadouri[i] = listaCadouri[i];
				this->listaCadouri[i] = new Cadou(*listaCadouri[i]);
			}
		}
	}

	WishList(const WishList& w) {
		this->detinator = w.detinator;
		if (w.nrCadouri > 0 && w.listaCadouri != nullptr) {
			this->nrCadouri = w.nrCadouri;
			//this->listaCadouri = w.listaCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++) {
				//this->listaCadouri[i] = w.listaCadouri[i];
				this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);
			}
		}
	}

	WishList& operator=(const WishList& w) {
		if (this != &w) {
			for (int i = 0; i < this->nrCadouri; i++) {
				delete this->listaCadouri[i];
				this->listaCadouri[i] = nullptr;
			}
			delete[] this->listaCadouri;
			this->listaCadouri = nullptr;

			this->detinator = w.detinator;
			if (w.nrCadouri > 0 && w.listaCadouri != nullptr) {
				this->nrCadouri = w.nrCadouri;
				//this->listaCadouri = w.listaCadouri;
				this->listaCadouri = new Cadou * [this->nrCadouri];
				for (int i = 0; i < this->nrCadouri; i++) {
					//this->listaCadouri[i] = w.listaCadouri[i];
					this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);
				}
			}
			else {
				this->nrCadouri = 0;
				this->listaCadouri = nullptr;
			}
		}
		return *this;
	}

	~WishList() {
		for (int i = 0; i < this->nrCadouri; i++) {
			delete this->listaCadouri[i];
			this->listaCadouri[i] = nullptr;
		}
		delete[] this->listaCadouri;
		this->listaCadouri = nullptr;
	}

	friend ostream& operator<<(ostream& out, const WishList& w) {
		out << "\nDetinator: " << w.detinator;
		out << "\nNr cadouri: " << w.nrCadouri;
		out << "\nLista cadouri: ";
		for (int i = 0; i < w.nrCadouri; i++)
			out << *w.listaCadouri[i];
		return out;
	}
};

class WishList4 {
	string detinator;
	Cadou* cadouSpecial;
};

class WishList5 {
	string detinator;
	int nrPrieteni;
	int* nrCadouriPrieteni;
	Cadou** listaCadouri;
};

class WishList6 {
	string detinator;
	int nrCadouriZi[24];
	Cadou** listaCadouri[24];
};

int main()
{
	/*Produs p("Stilou", 10);
	cin >> p;
	cout << p;*/
	Cadou c1("Stilou", 1000);
	Cadou c2("Carte", 250);
	Cadou c3("Papusa", 200);
	Cadou* lista[] = { &c1,&c2,&c3 };
	WishList w("DZM", lista, 3);
	cout << w;

	WishList w2 = w;
	cout << w2;
	WishList w3;
	w3 = w2;
	cout << w3;

	//float pretMinim = w[0];

	//Cadou cadouPretMinim = w;

	return 0;
}