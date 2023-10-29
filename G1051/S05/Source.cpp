#include<iostream>
using namespace std;

class Firma {
	const int CUI;
	string denumire = "Anonim";
	int nrAngajati = 0;
	float* salarii = nullptr;
	static float salariuMinimEconomie;

public:
	Firma(int CUI) : CUI(CUI) {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		//this->CUI = CUI;
	}

	Firma(int CUI, string denumire, int nrAngajati, float* salarii) :CUI(CUI) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		if (denumire.length() >= 5)
			this->denumire = denumire;
		if (nrAngajati > 0 && salarii != nullptr) {
			int ctAngajati = 0;
			for (int i = 0; i < nrAngajati; i++)
				if (salarii[i] >= Firma::salariuMinimEconomie)
					ctAngajati++;
			this->nrAngajati = ctAngajati;
			this->salarii = new float[this->nrAngajati];
			int k = 0;
			for (int i = 0; i < nrAngajati; i++)
				if (salarii[i] >= Firma::salariuMinimEconomie)
					this->salarii[k++] = salarii[i];
		}
	}

	Firma(const Firma& f) :CUI(f.CUI) {
		cout << "\nAPEL CONSTRUCTOR COPIERE";
		if (f.denumire.length() >= 5)
			this->denumire = f.denumire;
		if (f.nrAngajati > 0 && f.salarii != nullptr) {
			this->nrAngajati = f.nrAngajati;
			this->salarii = new float[this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++)
				this->salarii[i] = f.salarii[i];
		}
	}

	void operator =(const Firma& f) {
		cout << "\nAPEL OP=";
		//obj this deja exista
		delete[] this->salarii;
		this->salarii = nullptr;

		if (f.denumire.length() >= 5)
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
		cout << "\n**************************";
		cout << "\nCUI: " << this->CUI;
		cout << "\nDenumire: " << this->denumire;
		cout << "\nNr angajati: " << this->nrAngajati;
		cout << "\nSalarii: ";
		if (this->salarii != nullptr) {
			for (int i = 0; i < this->nrAngajati; i++)
				cout << this->salarii[i] << " ";
		}
		else {
			cout << "-";
		}
	}

	~Firma() {
		cout << "\nAPEL DESTRUCTOR";
		delete[] this->salarii;
		this->salarii = nullptr;
	}
};

float Firma::salariuMinimEconomie = 600;

int main() {
	Firma f1(1234);
	float salarii[] = { 1200,500,700 };
	Firma f2(123, "Firma1", 3, salarii);
	f1.afisare();
	f2.afisare();

	Firma f3(f2);
	f3.afisare();
	Firma::setSalariuMinimEconomie(750);

	f1 = f3;
	f1.afisare();
	//cout << f1;
	return 0;
}