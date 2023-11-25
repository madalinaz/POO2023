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

	friend istream& operator>>(istream& in, Produs& p) {
		delete[] p.preturi;
		p.preturi = nullptr;
		delete[] p.denumire;
		p.denumire = nullptr;

		cout << "\nIntroduceti denumirea: ";
		char buffer[100];
		in >> buffer;
		p.denumire = new char[strlen(buffer) + 1];
		strcpy(p.denumire, buffer);
		cout << "Introduceti stoc: ";
		in >> p.stoc;
		cout << "Introduceti nr zile analiza pret: ";
		in >> p.nrZile;
		if (p.nrZile <= 0) {
			p.nrZile = 0;
			p.preturi = nullptr;
		}
		else {
			p.preturi = new float[p.nrZile];
			cout << "Introduceti preturi:\n";
			for (int i = 0; i < p.nrZile; i++) {
				cout << "pret[" << i << "]=";
				in >> p.preturi[i];
			}
		}
		return in;
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

	bool operator!() {
		return !this->stoc;
	}
};


class Cadou {
private:
	string denumire = "Anonim";
	float pret = 0;
	const int cod;
	static int nrCadouri;

public:
	Cadou() :cod(Cadou::nrCadouri++)
	{

	}

	Cadou(string denumire, float pret) :cod(Cadou::nrCadouri++)
	{
		this->denumire = denumire;
		this->pret = pret;
	}

	Cadou(const Cadou& c) :cod(Cadou::nrCadouri++)
	{
		//Cadou::nrCadouri++;
		this->denumire = c.denumire;
		this->pret = c.pret;
	}

	Cadou& operator=(const Cadou& c)
	{
		this->denumire = c.denumire;
		this->pret = c.pret;
		return *this;
	}

	~Cadou() {
		//Cadou::nrCadouri--;
	}

	friend ostream& operator<<(ostream& out, const Cadou& c)
	{
		out << "\nCod: " << c.cod << ", denumire: " << c.denumire << ", pret: " << c.pret;
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

int Cadou::nrCadouri = 0;

class WishList1 {
	string posesorLista;
	int nrCadouri;
	Cadou listaCadouri[100];
};

class WishList2 {
	string posesorLista;
	int nrCadouri;
	Cadou* listaCadouri;
};

class WishList3 {
	string posesorLista;
	int nrCadouri;
	Cadou* listaCadouri[100];//vector static de pointeri la obj de tip Cadou
};

class WishList4 {
	string posesorLista = "Anonim";
	int nrCadouri = 0;
	Cadou** listaCadouri = nullptr;//vector dinamic de pointeri

public:
	WishList4() { }

	WishList4(string posesorLista, int nrCadouri, Cadou** listaCadouri) {
		this->posesorLista = posesorLista;
		if (nrCadouri > 0 && listaCadouri != nullptr) {
			this->nrCadouri = nrCadouri;
			this->listaCadouri = listaCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++)
				this->listaCadouri[i] = new Cadou(*listaCadouri[i]);
		}
	}

	WishList4(const WishList4& w) {
		this->posesorLista = w.posesorLista;
		if (w.nrCadouri > 0 && w.listaCadouri != nullptr) {
			this->nrCadouri = w.nrCadouri;
			this->listaCadouri = w.listaCadouri;
			this->listaCadouri = new Cadou * [this->nrCadouri];
			for (int i = 0; i < this->nrCadouri; i++)
				this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);
		}
	}

	WishList4& operator=(const WishList4& w) {
		if (this != &w) {
			for (int i = 0; i < this->nrCadouri; i++)
			{
				delete this->listaCadouri[i];
				this->listaCadouri[i] = nullptr;
			}
			delete[] this->listaCadouri;
			this->listaCadouri = nullptr;

			this->posesorLista = w.posesorLista;
			if (w.nrCadouri > 0 && w.listaCadouri != nullptr) {
				this->nrCadouri = w.nrCadouri;
				this->listaCadouri = w.listaCadouri;
				this->listaCadouri = new Cadou * [this->nrCadouri];
				for (int i = 0; i < this->nrCadouri; i++)
					this->listaCadouri[i] = new Cadou(*w.listaCadouri[i]);
			}
			else {
				this->nrCadouri = 0;
			}
		}
		return *this;
	}

	~WishList4() {
		for (int i = 0; i < this->nrCadouri; i++)
		{
			delete this->listaCadouri[i];
			this->listaCadouri[i] = nullptr;
		}
		delete[] this->listaCadouri;
		this->listaCadouri = nullptr;
	}
};

class WishList5 {
	string posesorLista;
	Cadou* cadou; //pointer la un obj de tip Cadou
};

class WishList6 {
	string posesorLista;
	int nrPrieteni;
	int* nrCadouriPrieteni;
	Cadou** listaCadouri;
};

int main()
{
	/*Produs p1("Pix", 100);
	int x = 10;
	if (!x)
		cout << "\nx este 0";
	else
		cout << "\nx NU este 0";
	cout << endl << x;
	int y = 5;
	y = !x;
	cout << endl << y << " " << x;

	if (!p1)
		cout << "\nProdusul p3 nu are stoc";
	else
		cout << "\nP3 are stoc";
	cin >> p1;
	cout << p1;*/

	Cadou c1;
	Cadou c2("Stilou", 1000);
	cout << c1 << c2;
	Cadou c3 = c2;
	cout << c3;


	return 0;
}