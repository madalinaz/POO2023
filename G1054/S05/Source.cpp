#include<iostream>
using namespace std;

class Firma {
	string denumire = "Anonim";
	const int CUI;
	int nrAngajati = 0;
	string* angajati = nullptr;
	static int dimMinimaNume;

public:
	Firma(int CUI) : CUI(CUI) {
		//this->CUI = CUI;
	}

	Firma(int CUI, string denumire) :CUI(CUI) {
		if (denumire.length() >= 5)
			this->denumire = denumire;
	}

	Firma(const Firma& f) : CUI(f.CUI) {
		this->denumire = f.denumire;
		this->nrAngajati = f.nrAngajati;
		if (f.angajati != nullptr) {
			this->angajati = new string[this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++)
				this->angajati[i] = f.angajati[i];
		}
	}

	void operator=(const Firma& f) {
		delete[] this->angajati;
		this->angajati = nullptr;

		this->denumire = f.denumire;
		this->nrAngajati = f.nrAngajati;
		if (f.angajati != nullptr) {
			this->angajati = new string[this->nrAngajati];
			for (int i = 0; i < this->nrAngajati; i++)
				this->angajati[i] = f.angajati[i];
		}
	}

	void addAngajat(string angajat) {
		if (angajat.length() >= Firma::dimMinimaNume) {
			string* copie = new string[this->nrAngajati + 1];
			for (int i = 0; i < this->nrAngajati; i++)
				copie[i] = this->angajati[i];
			copie[this->nrAngajati] = angajat;
			delete[] this->angajati;
			this->nrAngajati++;
			this->angajati = nullptr;
			this->angajati = copie;
		}
	}

	static void setDimMinimaNume(int dimMinimaNume) {
		if (dimMinimaNume > 0) {
			Firma::dimMinimaNume = dimMinimaNume;
		}
	}

	void afisare() {
		cout << "\n---------------";
		cout << "\nDenumire: " << this->denumire;
		cout << "\nCUI: " << this->CUI;
		cout << "\nNr angajati: " << this->nrAngajati;
		cout << "\nAngajati: ";
		if (this->angajati != nullptr) {
			for (int i = 0; i < this->nrAngajati; i++)
				cout << this->angajati[i] << " ";
		}
		else cout << "-";
	}

	~Firma() {
		delete[] this->angajati;
		this->angajati = nullptr;
	}
};

int Firma::dimMinimaNume = 5;

int main() {
	Firma::setDimMinimaNume(7);

	Firma f1(12);
	Firma f2(123, "Firma lu' Gigel");
	f1.afisare();
	f2.afisare();
	f2.addAngajat("Gigel patron");
	f2.addAngajat("fata lu Gigel");
	f2.afisare();

	Firma f3(f1);
	f3.afisare();

	f1 = f2;  f1.operator=(f2);
	f1.afisare();
	//cout << f1;
	//f1 >> cout;
	return 0;
}