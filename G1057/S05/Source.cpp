#include<iostream>
using namespace std;

class Firma {
	string denumire = "Anonim";
	const int CUI;
	int nrAngajati = 0;
	float* salarii = nullptr;
	//int nrMinAngajatiDisponibili[12];

	static float salariuMinimEconomie;

public:
	Firma(int CUI) : CUI(CUI) {
		//this->CUI = CUI;
	}

	Firma(string denumire, int CUI) :CUI(CUI) {
		if (denumire.length() >= 5)
			this->denumire = denumire;
	}

	Firma(const Firma& f) :CUI(f.CUI) {
		this->denumire = f.denumire;
		if (f.nrAngajati > 0 && f.salarii != nullptr) {
			this->nrAngajati = f.nrAngajati;
			this->salarii = new float[this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++)
				this->salarii[i] = f.salarii[i];
		}
	}

	void operator=(const Firma& f) {
		delete[] this->salarii;
		this->salarii = nullptr;

		this->denumire = f.denumire;
		if (f.nrAngajati > 0 && f.salarii != nullptr) {
			this->nrAngajati = f.nrAngajati;
			this->salarii = new float[this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++)
				this->salarii[i] = f.salarii[i];
		}
		else {
			this->nrAngajati = 0;
			this->salarii = nullptr;
		}
	}

	static void setSalariuMinimEconomie(float salariuMinimEconomie) {
		if (salariuMinimEconomie > 0) {
			Firma::salariuMinimEconomie = salariuMinimEconomie;
		}
	}

	void afisare() {
		cout << "\n-------------------";
		cout << "\nDenumire: " << this->denumire;
		cout << "\nCUI: " << this->CUI;
		cout << "\nNr angajati: " << this->nrAngajati;
		cout << "\nSalarii: ";
		if (this->salarii != nullptr) {
			for (int i = 0; i < this->nrAngajati; i++)
				cout << this->salarii[i] << " ";
		}
		else cout << "-";
	}

	void addAngajat(float salariu) {
		if (salariu >= Firma::salariuMinimEconomie) {
			float* copie = new float[this->nrAngajati + 1];
			for (int i = 0; i < this->nrAngajati; i++)
				copie[i] = this->salarii[i];
			copie[this->nrAngajati] = salariu;
			delete[] this->salarii;
			this->salarii = nullptr;
			this->nrAngajati++;
			this->salarii = copie;
		}
	}

	~Firma() {
		delete[] this->salarii;
		this->salarii = nullptr;
	}
};

float Firma::salariuMinimEconomie = 600;

int main() {
	Firma::setSalariuMinimEconomie(700);

	Firma f1(12);
	Firma f2("Firma Gigel", 1234);
	f1.afisare();
	f2.afisare();
	f2.addAngajat(1200);
	f2.addAngajat(500);
	f2.addAngajat(700);
	f2.afisare();

	Firma f3 = f2;
	f3.afisare();

	f1 = f2;  f1.operator=(f2);
	//cout << f1;

	return 0;
}