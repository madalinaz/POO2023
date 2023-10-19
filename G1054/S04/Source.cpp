#include<iostream>
using namespace std;

enum TipCarburant {
	BENZINA, DIESEL, ELECTRIC
};

class Masina {
	//char* marca;
	string marca;
	int anFabricatie;
	TipCarburant* tipCarburant;
	int nrTipuriCarburant;
	//bool tipCarburant2[3];

public:
	Masina() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		this->marca = "Anonim";
		this->anFabricatie = 1900;
		this->nrTipuriCarburant = 0;
		this->tipCarburant = nullptr;
	}

	Masina(string marca, int anFabricatie, int nrTipuriCarburant, TipCarburant* tipCarburant) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		this->marca = marca;
		this->anFabricatie = anFabricatie;
		if (nrTipuriCarburant > 0 && tipCarburant != nullptr) {
			this->nrTipuriCarburant = nrTipuriCarburant;
			this->tipCarburant = new TipCarburant[this->nrTipuriCarburant];
			for (int i = 0; i < this->nrTipuriCarburant; i++)
				this->tipCarburant[i] = tipCarburant[i];
		}
		else {
			this->nrTipuriCarburant = 0;
			this->tipCarburant = nullptr;
		}
	}

	Masina(const Masina& m) {
		cout << "\nAPEL CONSTRUCTOR COPIERE";
		this->marca = m.marca;
		this->anFabricatie = m.anFabricatie;
		if (m.nrTipuriCarburant > 0 && m.tipCarburant != nullptr) {
			this->nrTipuriCarburant = m.nrTipuriCarburant;
			this->tipCarburant = new TipCarburant[this->nrTipuriCarburant];
			for (int i = 0; i < this->nrTipuriCarburant; i++)
				this->tipCarburant[i] = m.tipCarburant[i];
		}
		else {
			this->nrTipuriCarburant = 0;
			this->tipCarburant = nullptr;
		}
	}

	TipCarburant getTipCarburant(int index) {
		if (index >= 0 && index < this->nrTipuriCarburant && tipCarburant != nullptr) {
			return this->tipCarburant[index];
		}
		else {
			cout << "\nEroare accesare.";
		}
	}

	void afisare() {
		cout << "\n Masina marca: " << this->marca;
		cout << ", an fabricatie: " << this->anFabricatie;
		cout << " are " << this->nrTipuriCarburant << " tipuri carburant: ";
		if (this->tipCarburant != nullptr) {
			for (int i = 0; i < this->nrTipuriCarburant; i++)
				cout << this->tipCarburant[i] << " ";
		}
		else {
			cout << "-";
		}
	}

	~Masina() {
		cout << "\nAPEL DESTRUCTOR";
		delete[] this->tipCarburant;
		this->tipCarburant = nullptr;
		//this->nrTipuriCarburant = 0;
	}
};

int main() {
	Masina m1;
	m1.afisare();
	TipCarburant carburant[] = { TipCarburant::BENZINA, TipCarburant::ELECTRIC };
	Masina m2("Opel", 2020, 2, carburant);
	m2.afisare();

	Masina* pMasina = new Masina("Opel", 2020, 2, carburant);
	delete pMasina;
	//cout << endl << pMasina->getTipCarburant(0);

	Masina m3 = m2;
	m3.afisare();
	return 0;
}
