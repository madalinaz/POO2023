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

//utilizare de sabloane
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
		out << "\nElementele colectiei: ";
		for (int i = 0; i < c.nrElemente; i++)
			out << c.elemente[i] << " ";
		return out;
	}
	int operator[](TIP element) {
		Colectie copie = *this;
		for (int i = 0; i < copie.nrElemente; i++) {
			for (int j = i + 1; j < copie.nrElemente; j++) {
				if (copie.elemente[i] < copie.elemente[j])
					swap(copie.elemente[i], copie.elemente[j]);
			}
		}
		int contor = 0;
		for (int i = 1; i < copie.nrElemente; i++) {
			if (copie.elemente[i] != copie.elemente[i - 1]) {
				contor++;
			}
			if (copie.elemente[i] == element) return contor;
		}
		return -1;
	}
};

//clasa abstracta care detine cel putin o meth virtuala pura
class IPersonaj {
public:
	virtual void spuneLaSuparare() = 0;
	virtual void spuneLaBucurie() = 0;
	virtual void enerveazaPeCineva() = 0;
	virtual void bucuraPeCineva() = 0;
};


//depind de abstract, nu de concret
void scenaI(IPersonaj* pers1, IPersonaj* pers2) {
	cout << "\nDECOR SCENA I";
	pers1->enerveazaPeCineva();
	pers2->spuneLaSuparare();
}

void scenaII(IPersonaj* pers1, IPersonaj* pers2) {
	cout << "\nDECOR SCENA II";
	pers1->bucuraPeCineva();
	pers2->spuneLaBucurie();
}

class Persoana :public IPersonaj {
	string nume;
public:
	Persoana(string nume) {
		this->nume = nume;
	}

	void spuneLaSuparare() {
		cout << "\n" + this->nume + " spune offff";
	}
	void spuneLaBucurie() {
		cout << "\n" + this->nume + " spune yuppy";
	}
	void enerveazaPeCineva() {
		cout << "\n" + this->nume + " arunca petarde";
	}
	void bucuraPeCineva() {
		cout << "\n" + this->nume + " canta colinde";
	}
};

class Robot :public IPersonaj {
	string nume;
public:
	Robot(string nume) {
		this->nume = nume;
	}

	void spuneLaSuparare() {
		cout << "\nRobot " + this->nume + " spune offff robotesc";
	}
	void spuneLaBucurie() {
		cout << "\nRobot" + this->nume + " spune yuppy robotesc";
	}
	void enerveazaPeCineva() {
		cout << "\n" + this->nume + " sparge TV";
	}
	void bucuraPeCineva() {
		cout << "\n" + this->nume + " spala vasele";
	}
};

int main()
{
	int vInt[] = { 10,50,50,50,10,45,45,7 };
	Colectie<int> cInt(vInt, 8);
	cout << cInt[673];
	Eveniment e1(50, "Loc1");
	Eveniment e2(30, "Loc2");
	Eveniment e3(50, "Loc3");
	Eveniment e4(60, "Loc4");
	Eveniment e5(50, "Loc5");
	Eveniment vEv[] = { e1, e2, e3, e4, e5 };
	Colectie<Eveniment> eEv(vEv, 5);
	cout << eEv;
	cout << "\n" << eEv[e1];
	//TO DO
	//colectie de evenimente
	//supraincarcare operator index care primeste ca param un elem si returneaza
	//pozitia pe care s-ar afla elementul daca colectia ar fi sortata strict 
	//descrescator

	//sectiune 2
	IPersonaj* personaj1 = new Persoana("Gigel");
	IPersonaj* personaj2 = new Robot("Memo");

	scenaI(personaj1, personaj2);
	scenaI(personaj2, personaj1);
	scenaII(personaj1, personaj2);
	return 0;
}