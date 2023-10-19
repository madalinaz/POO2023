#include<iostream>
using namespace std;

class Facultate {
	//char* denumire;
	string denumire;
	int nrStudenti;
	int nrPersConducere;
	string* persConducere; //char**

public:
	Facultate() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		this->denumire = "N/A";
		this->nrStudenti = 0;
		this->nrPersConducere = 0;
		this->persConducere = nullptr;
	}

	Facultate(string denumire, int nrStudenti, int nrPersConducere, string* persConducere) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		this->denumire = denumire;
		this->nrStudenti = nrStudenti;
		if (nrPersConducere > 0 && persConducere != nullptr) {
			this->nrPersConducere = nrPersConducere;
			this->persConducere = new string[this->nrPersConducere];
			for (int i = 0; i < this->nrPersConducere; i++)
				this->persConducere[i] = persConducere[i];
		}
		else {
			this->nrPersConducere = 0;
			this->persConducere = nullptr;
		}
	}

	Facultate(const Facultate& f) {
		cout << "\nAPEL CONSTRUCTOR COPIERE";
		this->denumire = f.denumire;
		this->nrStudenti = f.nrStudenti;
		if (f.nrPersConducere > 0 && f.persConducere != nullptr) {
			this->nrPersConducere = f.nrPersConducere;
			this->persConducere = new string[this->nrPersConducere];
			for (int i = 0; i < this->nrPersConducere; i++)
				this->persConducere[i] = f.persConducere[i];
		}
		else {
			this->nrPersConducere = 0;
			this->persConducere = nullptr;
		}
	}

	void afisare() {
		cout << "\n------------------------";
		cout << "\nDenumire: " << this->denumire;
		cout << "\nNr studenti: " << this->nrStudenti;
		cout << "\nNr persoane conducere: " << this->nrPersConducere;
		cout << "\nPersoane conducere: ";
		if (this->persConducere != nullptr) {
			for (int i = 0; i < this->nrPersConducere; i++)
				cout << this->persConducere[i] << " ";
		}
		else {
			cout << "-";
		}
	}

	~Facultate() {
		cout << "\nAPEL DESTRUCTOR";
		delete[] this->persConducere;
		this->persConducere = nullptr;
	}
};

int main() {
	Facultate f1;
	f1.afisare();
	string persConducere[] = { "Gigel","Costel" };
	Facultate f2("CSIE", 1000, 2, persConducere);
	f2.afisare();
	Facultate* pFacultate;
	pFacultate = new Facultate();
	delete pFacultate;
	Facultate f3 = f2;
	f3.afisare();
	return 0;
}