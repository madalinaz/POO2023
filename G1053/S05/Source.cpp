#include<iostream>
using namespace std;

class Biblioteca {
	string denumire = "Anonim";
	const int codUnic;
	int nrEtaje = 0;
	int* birouriStudiu = nullptr;
	float gradIncarcare[24];
	static float gradMinimIncarcare;

public:
	Biblioteca(int codUnic) : codUnic(codUnic) {
		//this->codUnic = codUnic;
		for (int i = 0; i < 24; i++)
			this->gradIncarcare[i] = 0;
	}

	Biblioteca(int codUnic, string denumire, int nrEtaje, int* birouriStudiu, float gradIncarcare[24]) :codUnic(codUnic) {
		if (denumire.length() >= 5) {
			this->denumire = denumire;
		}

		if (nrEtaje > 0 && birouriStudiu != nullptr) {
			this->nrEtaje = nrEtaje;
			this->birouriStudiu = new int[this->nrEtaje];
			for (int i = 0; i < this->nrEtaje; i++) {
				this->birouriStudiu[i] = birouriStudiu[i];
			}
		}

		for (int i = 0; i < 24; i++) {
			if (gradIncarcare[i] >= 0 && gradIncarcare[i] <= 1)
				this->gradIncarcare[i] = gradIncarcare[i];
			else
				this->gradIncarcare[i] = 1;
		}
	}

	Biblioteca(const Biblioteca& b) :codUnic(b.codUnic) {
		if (b.denumire.length() >= 5) {
			this->denumire = b.denumire;
		}

		if (b.nrEtaje > 0 && b.birouriStudiu != nullptr) {
			this->nrEtaje = b.nrEtaje;
			this->birouriStudiu = new int[this->nrEtaje];
			for (int i = 0; i < this->nrEtaje; i++) {
				this->birouriStudiu[i] = b.birouriStudiu[i];
			}
		}

		for (int i = 0; i < 24; i++) {
			if (b.gradIncarcare[i] >= 0 && b.gradIncarcare[i] <= 1)
				this->gradIncarcare[i] = b.gradIncarcare[i];
			else
				this->gradIncarcare[i] = 1;
		}
	}

	void afisare() {
		cout << "\n---------------------";
		cout << "\nDenumire: " << this->denumire;
		cout << "\nCod unic: " << this->codUnic;
		cout << "\nNr etaje: " << this->nrEtaje;
		cout << "\nBirouri studiu: ";
		if (this->birouriStudiu != nullptr) {
			for (int i = 0; i < this->nrEtaje; i++)
				cout << this->birouriStudiu[i] << " ";
		}
		else {
			cout << "-";
		}
		cout << "\nGrad incarcare pe ora: ";
		for (int i = 0; i < 24; i++)
			cout << this->gradIncarcare[i] << " ";
	}

	bool esteOcupata(int ora) {
		if (ora >= 0 && ora < 23) {
			if (this->gradIncarcare[ora] < Biblioteca::gradMinimIncarcare)
				return true;
			return false;
		}
	}

	static void setGradMinimIncarcare(float gradMinimIncarcare) {
		if (gradMinimIncarcare >= 0 && gradMinimIncarcare <= 1) {
			Biblioteca::gradMinimIncarcare = gradMinimIncarcare;
		}
	}

	~Biblioteca() {
		delete[] this->birouriStudiu;
		this->birouriStudiu = nullptr;
	}
};

float Biblioteca::gradMinimIncarcare = 0.6;

int main() {
	Biblioteca b1(1234);
	int birouriStudiu[] = { 10,40,20 };
	float gradIncarcare[24];
	for (int i = 0; i < 24; i++)
		gradIncarcare[i] = i % 2;
	Biblioteca b2(123, "Biblioteca ASE", 3, birouriStudiu, gradIncarcare);
	b2.afisare();

	Biblioteca b3 = b2;
	b3.afisare();

	if (b3.esteOcupata(10))
		cout << "\nSe poate participa la ora 10";
	else
		cout << "\nNu se poate participa la ora 10";

	Biblioteca::setGradMinimIncarcare(0.9);

	return 0;
}