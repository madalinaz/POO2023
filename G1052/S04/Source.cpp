#include<iostream>
using namespace std;



class Film {
	//char* denumire;
	string denumire;
	int durata;
	int nrActori;
	//char** numeActori;
	string* numeActori;

public:
	Film() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		this->denumire = "N/A";
		this->durata = 0;
		this->nrActori = 0;
		this->numeActori = nullptr;
	}

	Film(string denumire, int durata, int nrActori, string* numeActori) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		this->denumire = denumire;
		this->durata = durata;
		if (nrActori > 0 && numeActori != nullptr) {
			this->nrActori = nrActori;
			this->numeActori = new string[this->nrActori];
			for (int i = 0; i < this->nrActori; i++)
				this->numeActori[i] = numeActori[i];
		}
		else {
			this->nrActori = 0;
			this->numeActori = nullptr;
		}
	}

	Film(const Film& f) {
		cout << "\nAPEL CONSTRUCTOR COPIERE";
		this->denumire = f.denumire;
		this->durata = f.durata;
		if (f.nrActori > 0 && f.numeActori != nullptr) {
			this->nrActori = f.nrActori;
			this->numeActori = new string[this->nrActori];
			for (int i = 0; i < this->nrActori; i++)
				this->numeActori[i] = f.numeActori[i];
		}
		else {
			this->nrActori = 0;
			this->numeActori = nullptr;
		}
	}

	void afisare() {
		cout << "\nDenumire: " << this->denumire;
		cout << "\nDurata: " << this->durata;
		cout << "\nNr actori: " << this->nrActori;
		cout << "\nNume actori: ";
		if (this->numeActori != nullptr) {
			for (int i = 0; i < this->nrActori; i++)
				cout << this->numeActori[i] << " ";
		}
		else {
			cout << "-";
		}
	}

	~Film() {
		cout << "\nAPEL DESTRUCTOR";
		delete[] this->numeActori;
		this->numeActori = nullptr;
	}

	void adaugaActor(string actor) {
		if (actor.length() >= 5) {
			string* copie = new string[this->nrActori + 1];
			for (int i = 0; i < this->nrActori; i++)
				copie[i] = this->numeActori[i];
			copie[this->nrActori] = actor;
			delete[] this->numeActori;
			this->nrActori++;
			this->numeActori = copie;
		}
	}
};

int main() {
	Film f1;
	f1.afisare();
	string actori[] = { "Gigel","Costel" };
	Film f2("Film romanesc", 100, 2, actori);
	f2.afisare();
	f2.adaugaActor("Costelus");
	f2.afisare();
	Film* pFilm = new Film();
	delete pFilm;
	Film f3 = f2;
	Film f4(f2);
	f3.afisare();
	return 0;
}