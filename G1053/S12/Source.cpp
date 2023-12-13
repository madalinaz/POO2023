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

	bool operator>(const Eveniment& e) {
		return this->nrPers > e.nrPers;
	}

	operator float() {
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
		out << "\nLista de obiecte: ";
		for (int i = 0; i < c.nrElemente; i++)
			out << c.elemente[i] << " ";
		return out;
	}

	float operator()(int a, int b) {
		if (a <= b && a >= 0 && b < this->nrElemente) {
			if (this->elemente != nullptr) {
				Colectie copie = *this;

				for (int i = 0; i < copie.nrElemente; i++)
					for (int j = i + 1; j < copie.nrElemente; j++)
						if (copie.elemente[i] > copie.elemente[j])
							swap(copie.elemente[i], copie.elemente[j]);

				float medie = 0;
				for (int i = a; i <= b; i++)
					medie += copie.elemente[i];
				medie /= b - a + 1;
				return medie;
			}
		}
	}
};

//clasa abstracta(are cel putin o meth virtuala pura)
//clasa tip Interfata (contract)
class IPersonaj {
public:
	virtual void spuneLaSuparare() = 0;
	virtual void spuneLaBucurie() = 0;
	virtual void enerveaza() = 0;
	virtual void bucura() = 0;
};

//decuplare implementare de utilizare zona concreta
//depinde de abstract, si nu de concret
void scenetaI(IPersonaj* personaj1, IPersonaj* personaj2) {
	cout << "\nSceneta I";
	personaj1->enerveaza();
	personaj2->spuneLaSuparare();
}

class Persoana : public IPersonaj {
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
	void enerveaza() {
		cout << "\n" + this->nume + " tranteste usa";
	}
	void bucura() {
		cout << "\n" + this->nume + " canta colinde";
	}
};

class Pisica : public IPersonaj {
	string nume;
public:
	Pisica(string nume) {
		this->nume = nume;
	}
	void spuneLaSuparare() {
		cout << "\nPisica " + this->nume + " face zzzzzzzz";
	}
	void spuneLaBucurie() {
		cout << "\nPisica " + this->nume + " zice miau, miau";
	}
	void enerveaza() {
		cout << "\nPisica " + this->nume + " se urca pe draperie";
	}
	void bucura() {
		cout << "\nPisica " + this->nume + " toarce";
	}
};

int main()
{
	//colectie de valori de TIP int
	int vInt[] = { 10,54,23,6,46,78 };//6 10 23 46 54 78
	Colectie<int> cInt(vInt, 6);
	cout << cInt;

	//colectie de valori de TIP Eveniment
	//supraincat operatorul functie care primeste 2 valori intregi (a,b)
	//returneaza media elementelor aflate in intervalul de indexi [a,b] a unei liste
	//ordonate de elemente
	cout << "\nMedie folosind operator functie pe int: " << cInt(1, 3);
	Eveniment vEv[] = { Eveniment(50,"loc1"),Eveniment(100,"loc2"),Eveniment(30,"loc3"),Eveniment(300,"loc4") };
	Colectie<Eveniment>cEv(vEv, 4);
	cout << cEv;
	cout << "\nMedie folosind operator functie pe Eveniment: " << cEv(1, 3);

	//sectiune II ( meth virtuale pure/clase abstracte
	//IPersonaj personaj;
	IPersonaj* pPersonaj1;
	IPersonaj* pPersonaj2;
	pPersonaj1 = new Persoana("Gigel");
	pPersonaj2 = new Pisica("Arthur");
	scenetaI(pPersonaj1, pPersonaj2);
	scenetaI(pPersonaj2, pPersonaj1);
	return 0;
}