#include<iostream>
using namespace std;

enum TipCarburant {
	DIESEL, BENZINA, ELECTRIC
};

class Masina {
	//char* marca;
	string marca;
	int anFabricatie;
	int nrTipuriCarburant;
	TipCarburant* tipuriCarburant;

public:
	Masina() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		this->marca = "N/A";
		this->anFabricatie = 0;
		this->nrTipuriCarburant = 0;
		this->tipuriCarburant = nullptr;
	}

	Masina(string marca, int anFabricatie, int nrTipuriCarburant, TipCarburant* tipuriCarburant) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		this->marca = marca;
		this->anFabricatie = anFabricatie;
		if (nrTipuriCarburant > 0 && tipuriCarburant != nullptr) {
			this->nrTipuriCarburant = nrTipuriCarburant;
			this->tipuriCarburant = new TipCarburant[this->nrTipuriCarburant];
			for (int i = 0; i < this->nrTipuriCarburant; i++)
				this->tipuriCarburant[i] = tipuriCarburant[i];
		}
		else {
			this->nrTipuriCarburant = 0;
			this->tipuriCarburant = nullptr;
		}
	}

	Masina(const Masina& m) {
		cout << "\nAPEL CONSTRUCTOR COPY";
		this->marca = m.marca;
		this->anFabricatie = m.anFabricatie;
		if (m.nrTipuriCarburant > 0 && m.tipuriCarburant != nullptr) {
			this->nrTipuriCarburant = m.nrTipuriCarburant;
			this->tipuriCarburant = new TipCarburant[this->nrTipuriCarburant];
			for (int i = 0; i < this->nrTipuriCarburant; i++)
				this->tipuriCarburant[i] = m.tipuriCarburant[i];
		}
		else {
			this->nrTipuriCarburant = 0;
			this->tipuriCarburant = nullptr;
		}
	}

	void afisare() {
		cout << "\n---------------------------------";
		cout << "\nMarca: " << this->marca;
		cout << "\nAn fabricatie: " << this->anFabricatie;
		cout << "\nNr tipuri carburant: " << this->nrTipuriCarburant;
		cout << "\nTipuri carburant: ";
		if (this->tipuriCarburant != nullptr) {
			for (int i = 0; i < this->nrTipuriCarburant; i++)
				cout << this->tipuriCarburant[i] << " ";
		}
		else {
			cout << "-";
		}
	}

	~Masina() {
		cout << "\nAPEL DESTRUCTOR";
		delete[] this->tipuriCarburant;
		this->tipuriCarburant = nullptr;
	}
};

int main() {
	Masina m;
	m.afisare();
	TipCarburant tipuriCarburant[] = { TipCarburant::BENZINA };
	Masina m2("Opel", 1900, 1, tipuriCarburant);
	m2.afisare();
	Masina* pMasina = new Masina();
	delete pMasina;
	Masina m3 = m2;
	Masina m4(m2);
	m3.afisare();
	return 0;
}