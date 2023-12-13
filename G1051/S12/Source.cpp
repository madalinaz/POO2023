#include<iostream>
using namespace std;

//clasa Abstracta(clasa care contine cel putin o meth virtuala pura)
//clasa tip Interfata (care contine doar metode virtuale pure)
class IVorbeste {
public:
	virtual void spuneCandTeEnervezi() = 0;
	virtual void spuneCandEstiFericit() = 0;
};

class Caine : public IVorbeste {
	string nume;

public:
	Caine(string nume) {
		this->nume = nume;
	}

	void spuneCandTeEnervezi() {
		cout << "\nCatelul " + this->nume + " maraie!";
	}
	void spuneCandEstiFericit() {
		cout << "\nCatelul " + this->nume + " zice ham,ham!";
	}
};

class Pisica : public IVorbeste {
	string nume;

public:
	Pisica(string nume) {
		this->nume = nume;
	}

	void spuneCandTeEnervezi() {
		cout << "\nPisica " + this->nume + " zzzzzzz!";
	}
	void spuneCandEstiFericit() {
		cout << "\nPisica " + this->nume + " zice miau, miau!";
	}
};

void suparaPeCineva(IVorbeste* pObj) {
	pObj->spuneCandTeEnervezi();
}

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
	bool operator<(Eveniment e) {
		if (this->nrPers < e.nrPers) {
			return true;
		}
		return false;
	}
	friend ostream& operator<<(ostream& out, const Eveniment& e) {
		out << "\nNr pers eveniment: " << e.nrPers;
		out << "\nLocatie eveniment: " << e.locatie;
		return out;
	}
};

template<class TIP>
class Colectie {
	TIP* elemente = nullptr;
	int nrElem = 0;

public:
	Colectie() { }

	Colectie(TIP* elemente, int nrElem) {
		if (elemente != nullptr && nrElem > 0) {
			this->nrElem = nrElem;
			this->elemente = new TIP[this->nrElem];
			for (int i = 0; i < this->nrElem; i++)
				this->elemente[i] = elemente[i];
		}
	}

	Colectie(const Colectie& c) {
		if (c.elemente != nullptr && c.nrElem > 0) {
			this->nrElem = c.nrElem;
			this->elemente = new TIP[this->nrElem];
			for (int i = 0; i < this->nrElem; i++)
				this->elemente[i] = c.elemente[i];
		}
	}

	Colectie& operator=(const Colectie& c) {
		if (this != &c) {
			delete[] this->elemente;
			this->elemente = nullptr;
			if (c.elemente != nullptr && c.nrElem > 0) {
				this->nrElem = c.nrElem;
				this->elemente = new TIP[this->nrElem];
				for (int i = 0; i < this->nrElem; i++)
					this->elemente[i] = c.elemente[i];
			}
			else {
				this->elemente = nullptr;
				this->nrElem = 0;
			}
		}
		return *this;
	}
	void sortare() {
		for (int i = 0; i < this->nrElem - 1; i++) {
			for (int j = i + 1; j < this->nrElem; j++) {
				if (this->elemente[i] < this->elemente[j]) {
					swap(this->elemente[i], this->elemente[j]);
				}
			}
		}
	}

	TIP* operator()(int nrTop) {
		if (nrTop > 0 && this->elemente != nullptr && nrTop <= this->nrElem) {
			TIP* topElem = new TIP[nrTop];
			this->sortare();
			for (int i = 0; i < nrTop; i++) {
				topElem[i] = this->elemente[i];
			}
			return topElem;
		}
		else {
			return nullptr;
		}

	}

	friend ostream& operator<<(ostream& out, const Colectie& c) {
		out << "\nNr elem colectie: " << c.nrElem;
		out << "\nLista elemente colectie: ";
		for (int i = 0; i < c.nrElem; i++)
			out << c.elemente[i] << " ";
		return out;
	}

	~Colectie() {
		delete[] this->elemente;
		this->elemente = nullptr;
	}

	//supraincarcare operator functie care primeste ca param
	//un nr intreg(n) si returneaza un vector format din top n
	//obiecte din vectorul de elemente
};

int main()
{
	int vInt[] = { 10,5,8,9 };
	Colectie<int> cInt(vInt, 4);
	cout << cInt;

	int* topInt = nullptr;
	//topInt = cInt.operator()(2);
	topInt = cInt(2);
	cout << endl << "top inturi : ";
	for (int i = 0; i < 2; i++) {
		cout << topInt[i] << ' ';
	}

	Eveniment e1(10, "loc1");
	Eveniment e2(15, "loc2");
	Eveniment e3(5, "loc3");
	Eveniment vectEvenimente[] = { e1, e2, e3 };
	Colectie <Eveniment> cEv(vectEvenimente, 3);
	cout << cEv;
	Eveniment* topEv = nullptr;
	topEv = cEv(2);
	cout << "\n top evemnimente : ";
	for (int i = 0; i < 2; i++) {
		cout << topEv[i] << ' ';
	}
	delete[] topInt;
	topInt = nullptr;
	delete[] topEv;
	topEv = nullptr;

	//sectiune II
	//IVorbeste obj;
	IVorbeste* pObj;
	Caine caine("Grivei");
	pObj = &caine;
	suparaPeCineva(pObj);
	return 0;
}