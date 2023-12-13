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
	friend ostream& operator<<(ostream& out, const Eveniment& e) {
		out << "\nNr pers eveniment: " << e.nrPers;
		out << "\nLocatie eveniment: " << e.locatie;
		return out;
	}

	operator int() {
		return this->nrPers;
	}
};

//clasa sablon/template
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

	~Colectie() {
		delete[] this->elemente;
		this->elemente = nullptr;
	}

	friend ostream& operator<<(ostream& out, const Colectie& c) {
		out << "\nNr elem colectie: " << c.nrElemente;
		out << "\nLista de elem ale colectiei: ";
		for (int i = 0; i < c.nrElemente; i++)
			out << c.elemente[i] << " ";
		return out;
	}

	int operator[](TIP element) {
		Colectie copie = *this;

		for (int i = 0; i < copie.nrElemente - 1; i++)
			for (int j = i + 1; j < copie.nrElemente; j++) {
				if (copie.elemente[i] < copie.elemente[j]) {
					swap(copie.elemente[i], copie.elemente[j]);
				}
			}
		int contor = 1;
		if (copie.elemente[0] == element)return 1;
		for (int i = 1; i < copie.nrElemente; i++) {
			if (copie.elemente[i] != copie.elemente[i - 1]) {
				contor++;
				if (copie.elemente[i] == element)return contor;
			}
		}

		return -1;
	}
};

//clasa abstracta are cel putin o metoda virtuala pura
//caz particular este interfata care contine doar metode virtuale pure
//interfata este un contract
class IPersonaj {
public:
	virtual void spuneLaSuparare() = 0;
	virtual void spuneLaBucurie() = 0;
	virtual void suparaPeCineva() = 0;
	virtual void bucuraPeCineva() = 0;
};

//depind de abstract, nu de concret
void scenaI(IPersonaj* p1, IPersonaj* p2) {
	p1->suparaPeCineva();
	p2->spuneLaSuparare();
}

void scenaII(IPersonaj* p1, IPersonaj* p2) {
	p1->bucuraPeCineva();
	p2->spuneLaBucurie();
}

class Pisica :public IPersonaj {
	void spuneLaSuparare() {
		cout << "\nPisica zice zzzzzz";
	}
	void spuneLaBucurie() {
		cout << "\nPisica zice miau, miau";
	}
	void suparaPeCineva() {
		cout << "\nPisica se urca pe draperie";
	}
	void bucuraPeCineva() {
		cout << "\nPisica toarce de zor";
	}
};

class Persoana :public IPersonaj {
	string nume;
public:
	Persoana(string nume) {
		this->nume = nume;
	}
	void spuneLaSuparare() {
		cout << "\n" + this->nume + " zice offff";
	}
	void spuneLaBucurie() {
		cout << "\n" + this->nume + " zice yuppy";
	}
	void suparaPeCineva() {
		cout << "\n" + this->nume + " arunca cu petarde";
	}
	void bucuraPeCineva() {
		cout << "\n" + this->nume + " canta colinde";
	}
};

int main()
{
	int vInt[] = { 10,30,5,15,45,15,10 };
	Colectie<int> cInt(vInt, 7);
	cout << cInt;

	//in main o colectie de obj de tip Eveniment
	//supraincarcat operator index in clasa Colectie care sa returneze
	//pozitia pe care se afla elem primit ca param intr-o lista
	//sortata descrescator de elemente distincte
	cout << endl << cInt[13];
	Eveniment e1(5, "Loc1");
	Eveniment e2(15, "Loc2");
	Eveniment e3(15, "Loc3");
	Eveniment e4(40, "Loc4");
	Eveniment e5(25, "Loc5");
	Eveniment vEv[] = { e1,e2,e3,e4,e5 };
	Colectie<Eveniment> cEv(vEv, 5);
	cout << endl << cEv;
	cout << endl << cEv[e2];

	Persoana pers1("Gigel");
	Pisica pisica;
	IPersonaj* personaj1 = &pers1;
	IPersonaj* personaj2 = &pisica;

	cout << "\nSCENA I";
	scenaI(personaj1, personaj2);
	scenaI(personaj2, personaj1);

	cout << "\nSCENA II";
	scenaII(personaj1, personaj2);
	return 0;
}