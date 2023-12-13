#include<iostream>
using namespace std;


class Eveniment {
private:
	int nrPers = 0;
	string locatie = "Anonim";
public:
	Eveniment() {}
	Eveniment(int nrPers, string locatie) {
		this->nrPers = nrPers;
		this->locatie = locatie;
	}
	Eveniment(const Eveniment& e) {
		this->nrPers = e.nrPers;
		this->locatie = e.locatie;
	}
	Eveniment& operator=(const Eveniment& e) {
		this->nrPers = e.nrPers;
		this->locatie = e.locatie;
		return *this;
	}

	bool operator<(const Eveniment& e) {

		return this->nrPers < e.nrPers;
	}

	friend ostream& operator<<(ostream& out, const Eveniment& e) {
		out << "\nNr pers eveniment: " << e.nrPers;
		out << "\nLocatie eveniment: " << e.locatie;
		return out;
	}
};

//clasa Template(sablon)
template<class TIP>
class Colectie {
	TIP* elemente = nullptr;
	int nrElemente = 0;

public:
	Colectie() { }
	Colectie(TIP* elemente, int nrElemente) {
		if (elemente != nullptr && nrElemente > 0) {
			this->nrElemente = nrElemente;
			this->elemente = new TIP[this->nrElemente];
			for (int i = 0; i < this->nrElemente; i++)
				this->elemente[i] = elemente[i];
		}
	}

	Colectie(const Colectie& c) {
		if (c.elemente != nullptr && c.nrElemente > 0) {
			this->nrElemente = c.nrElemente;
			this->elemente = new TIP[this->nrElemente];
			for (int i = 0; i < this->nrElemente; i++)
				this->elemente[i] = c.elemente[i];
		}
	}

	Colectie& operator=(const Colectie& c) {
		if (this != &c) {
			delete[] this->elemente;
			this->elemente = nullptr;
			if (c.elemente != nullptr && c.nrElemente > 0) {
				this->nrElemente = c.nrElemente;
				this->elemente = new TIP[this->nrElemente];
				for (int i = 0; i < this->nrElemente; i++)
					this->elemente[i] = c.elemente[i];
			}
			else {
				this->elemente = nullptr;
				this->nrElemente = 0;
			}
		}
		return *this;
	}

	static void sort(Colectie<TIP>& colectie) {

		for (int i = 0; i < colectie.nrElemente - 1; i++) {
			for (int j = i + 1; j < colectie.nrElemente; j++) {
				if (colectie.elemente[i] < colectie.elemente[j]) {
					swap(colectie.elemente[i], colectie.elemente[j]);
				}
			}
		}
	}

	TIP operator[](int n) {

		if (n >= 0 && n < this->nrElemente) {

			Colectie<TIP> copie(*this);
			sort(copie);
			return copie.elemente[n];
		}
	}

	~Colectie() {
		delete[] this->elemente;
		this->elemente = nullptr;
	}

	friend ostream& operator<<(ostream& out, const Colectie& c) {
		out << "\nNr elem: " << c.nrElemente;
		out << "\nElemente colectie: ";
		for (int i = 0; i < c.nrElemente; i++)
			out << c.elemente[i] << " ";
		return out;
	}
};

//clasa tip Interfata contine doar metode virtuale pure
//o clasa ce contine cel putin o meth virtuala pura este clasa abstracta
//o interfata este o clasa abstracta
//o interfata este un contract
class IActiune {
public:
	virtual void spuneLaSuparare() = 0;
	virtual void spuneLaBucurie() = 0;
	virtual void enerveaza(IActiune* obj) = 0;
	virtual void bucura(IActiune* obj) = 0;
};

class Persoana :public IActiune {
	string nume;

public:
	Persoana(string nume) { this->nume = nume; }
	void spuneLaSuparare() {
		cout << "\n" + this->nume + " zice offfff";
	}
	void spuneLaBucurie() {
		cout << "\n" + this->nume + " zice yuppy";
	}
	void enerveaza(IActiune* obj) {
		cout << "\n" + this->nume + " tranteste usa";
	}
	void bucura(IActiune* obj) {
		cout << "\n" + this->nume + " canta colinde";
	}
};

class Pisica :public IActiune {
	string denumire;

public:
	Pisica(string denumire) { this->denumire = denumire; }
	void spuneLaSuparare() {
		cout << "\n" + this->denumire + " zice zzzzzzz";
	}
	void spuneLaBucurie() {
		cout << "\n" + this->denumire + " zice miau, miau";
	}
	void enerveaza(IActiune* obj) {
		cout << "\n" + this->denumire + " sare pe draperie";
	}
	void bucura(IActiune* obj) {
		cout << "\n" + this->denumire + " toarce";
	}
};
//depend de abstract, nu de concret
void situatieEnervare(IActiune* obj1, IActiune* obj2) {
	obj1->enerveaza(obj2);
	obj2->spuneLaSuparare();
}

int main()
{
	int vInt[] = { 10,56,4,45,12 };
	Colectie<int> cInt(vInt, 5);
	cout << cInt << "\n";
	cout << cInt[2];

	Eveniment even[] = { Eveniment(21, "locatieMica"), Eveniment(200, "Arena Nationala"), Eveniment(500, "loc mare") };
	Colectie<Eveniment> cEven(even, 3);

	cout << cEven;
	cout << "\nEvenimentul cautat: \n" << cEven[1];


	//supraincarcare op index in clasa colectie care
	//sa returneze al n-lea obiect din colectia sortata descrescator
	//n-ul este primit ca param de catre op index
	//colectie de evenimente
	//apelat op [] pentru ambele colectii

	//sectiune II
	Persoana pers("Gigel");
	Pisica pisica("Arthur");
	IActiune* obj1 = &pers;
	IActiune* obj2 = &pisica;
	situatieEnervare(obj1, obj2);
	situatieEnervare(obj2, obj1);
	return 0;
}