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
	explicit operator float() {
		return this->nrPers;
	}
	friend ostream& operator<<(ostream& out, const Eveniment& e) {
		out << "\nNr pers eveniment: " << e.nrPers;
		out << "\nLocatie eveniment: " << e.locatie;
		return out;
	}
};

//clasa Template/sablon
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
				this->nrElemente = 0;
				this->elemente = nullptr;
			}
		}
		return *this;
	}

	~Colectie() {
		delete[] this->elemente;
		this->elemente = nullptr;
	}
	float operator[](int n) {
		if (n > 0 && n <= this->nrElemente) {
			Colectie copie = *this;
			for (int i = 0; i < copie.nrElemente; i++) {
				for (int j = i + 1; j < copie.nrElemente; j++) {
					if (copie.elemente[i] < copie.elemente[j])
						swap(copie.elemente[i], copie.elemente[j]);
				}
			}
			float suma = 0;
			for (int i = 0; i < n; i++)
				suma = suma + (float)copie.elemente[i];
			return suma / n;
		}
	}
	friend ostream& operator<<(ostream& out, const Colectie& c) {
		out << "\nNr elem colectie: " << c.nrElemente;
		out << "\nElementele colectie: ";
		for (int i = 0; i < c.nrElemente; i++)
			out << c.elemente[i] << " ";
		return out;
	}
};

//clasa tip Interfata pentru ca detine doar meth virtuale pure
//Interfata este caz particular din clasa Abstracta
//o clasa Abstracta este o clasa cu cel putin o meth virtuala pura
//Interfata este un contract
class IActiune {
public:
	virtual void spuneLaSuparare() = 0;
	virtual void spuneLaBucurie() = 0;
	virtual void enerveaza() = 0;
	virtual void bucura() = 0;
};

class Persoana :public IActiune {
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
		cout << "\n" + this->nume + " vorbeste tare";
	}
	void bucura() {
		cout << "\n" + this->nume + " canta colinde";
	}
};

class Pisica :public IActiune {
	string nume;
public:
	Pisica(string nume) {
		this->nume = nume;
	}

	void spuneLaSuparare() {
		cout << "\nPisica " + this->nume + " face zzzzzzz";
	}
	void spuneLaBucurie() {
		cout << "\nPisica " + this->nume + " face miau, miau";
	}
	void enerveaza() {
		cout << "\nPisica" + this->nume + " sare pe draperie";
	}
	void bucura() {
		cout << "\nPisica" + this->nume + " toarce";
	}
};

void enervareSiReactie(IActiune* obj1, IActiune* obj2) {
	obj1->enerveaza();
	obj2->spuneLaSuparare();
}

int main()
{
	int vInt[] = { 6,10,43,2,12 };
	Colectie<int> cInt(vInt, 5);
	cout << cInt;

	//colectie de obj de tip Eveniment
	//supraincarcare operator index care returneaza media celor mai
	//"bune" n produse din colectie. n-ul este primit ca param
	//de catre operatorul index
	cout << endl << cInt[2];
	Eveniment vEv[] = { Eveniment(150, "Ev1"), Eveniment(200, "Ev2"), Eveniment(500, "Ev3"), Eveniment(50, "Ev4") };
	Colectie<Eveniment> cEv(vEv, 4);
	cout << cEv;
	cout << endl << cEv[2];

	//sectiune II
	//IActiune actiune;
	Persoana pers("Gigel");
	pers.bucura();
	pers.enerveaza();
	IActiune* pActiune;
	Pisica pisica("Mitza");
	enervareSiReactie(&pisica, &pers);
	enervareSiReactie(&pers, &pisica);
	return 0;
}