#include<iostream>
using namespace std;

enum TipProdus {
	PAPETARIE = 10, COSMETICE = 20
};

class Produs {
	//char* denumire;
	string denumire;
	int stoc;
	bool estePerisabil;
	TipProdus tipProdus;
	int nrPreturi;
	float* istoricPreturi;

public:
	Produs() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		this->denumire = "Anonim";
		this->stoc = 0;
		this->estePerisabil = false;
		this->tipProdus = TipProdus::PAPETARIE;
		this->nrPreturi = 0;
		this->istoricPreturi = nullptr;
	}

	Produs(string denumire, int stoc, bool estePerisabil, TipProdus tipProdus, int nrPreturi, float* istoricPreturi) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		this->denumire = denumire;
		this->stoc = stoc;
		this->estePerisabil = estePerisabil;
		this->tipProdus = tipProdus;
		if (nrPreturi >= 0 && istoricPreturi != nullptr) {
			this->nrPreturi = nrPreturi;
			this->istoricPreturi = new float[this->nrPreturi];
			for (int i = 0; i < this->nrPreturi; i++)
				this->istoricPreturi[i] = istoricPreturi[i];
		}
		else {
			this->nrPreturi = 0;
			this->istoricPreturi = nullptr;
		}
	}

	Produs(const Produs& p) {
		cout << "\nAPEL CONSTRUCTOR COPY";
		this->denumire = p.denumire;
		this->stoc = p.stoc;
		this->estePerisabil = p.estePerisabil;
		this->tipProdus = p.tipProdus;
		if (p.nrPreturi >= 0 && p.istoricPreturi != nullptr) {
			this->nrPreturi = p.nrPreturi;
			this->istoricPreturi = new float[this->nrPreturi];
			for (int i = 0; i < this->nrPreturi; i++)
				this->istoricPreturi[i] = p.istoricPreturi[i];
		}
		else {
			this->nrPreturi = 0;
			this->istoricPreturi = nullptr;
		}
	}

	void afisare() {
		cout << "\nDenumire: " << this->denumire;
		cout << "\nStoc: " << this->stoc;
		cout << "\nEste perisabil (1-DA, 0-NU): " << this->estePerisabil;
		cout << "\nTip produs: " << this->tipProdus;
		cout << "\nNr preturi istoric: " << this->nrPreturi;
		cout << "\nIstoric preturi: ";
		if (this->istoricPreturi != nullptr) {
			for (int i = 0; i < this->nrPreturi; i++)
				cout << this->istoricPreturi[i] << " ";
		}
		else {
			cout << "-";
		}
	}

	~Produs() {
		cout << "\nAPEL DESTRUCTOR";
		delete[] this->istoricPreturi;
		this->istoricPreturi = nullptr;
	}
};

int main() {
	Produs p1;
	p1.afisare();
	float istoricPreturi[] = { 12,15,16 };
	Produs p2("Stilou", 10, false, TipProdus::PAPETARIE, 3, istoricPreturi);
	p2.afisare();
	//Produs vProduse[10];
	Produs* pProdus = new Produs();
	delete pProdus;
	Produs p3 = p2;
	Produs p4(p2);
	p3.afisare();
	return 0;
}