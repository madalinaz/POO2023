#include<iostream>
using namespace std;

class Prajitura {
	//char* denumire;
	string denumire;
	int nrCalorii;
	int nrIngrediente;
	string* ingrediente;//char**

public:
	Prajitura() {
		cout << "\nAPEL CONSTRUCTOR FARA PARAM";
		this->denumire = "N\A";
		this->nrCalorii = 0;
		this->nrIngrediente = 0;
		this->ingrediente = nullptr;
	}

	Prajitura(string denumire, int nrCalorii, int nrIngrediente, string* ingrediente) {
		cout << "\nAPEL CONSTRUCTOR CU TOTI PARAM";
		this->denumire = denumire;
		this->nrCalorii = nrCalorii;
		if (nrIngrediente > 0 && ingrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->ingrediente = new string[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->ingrediente[i] = ingrediente[i];
		}
		else {
			this->nrIngrediente = 0;
			this->ingrediente = nullptr;
		}
	}

	Prajitura(const Prajitura& p) {
		cout << "\nAPEL CONSTRUCTOR COPIERE";
		this->denumire = p.denumire;
		this->nrCalorii = p.nrCalorii;
		if (p.nrIngrediente > 0 && p.ingrediente != nullptr) {
			this->nrIngrediente = p.nrIngrediente;
			this->ingrediente = new string[this->nrIngrediente];
			for (int i = 0; i < this->nrIngrediente; i++)
				this->ingrediente[i] = p.ingrediente[i];
		}
		else {
			this->nrIngrediente = 0;
			this->ingrediente = nullptr;
		}
	}

	void afisare() {
		cout << "\n*************************";
		cout << "\nDenumire: " << this->denumire;
		cout << "\nNr calorii: " << this->nrCalorii;
		cout << "\nNr ingrediente: " << this->nrIngrediente;
		cout << "\nIngrediente: ";
		if (this->ingrediente != nullptr) {
			for (int i = 0; i < this->nrIngrediente; i++)
				cout << this->ingrediente[i] << " ";
		}
		else {
			cout << "-";
		}
	}

	~Prajitura() {
		cout << "\nAPEL DESTRUCTOR";
		delete[] this->ingrediente;
		this->ingrediente = nullptr;
	}
};

Prajitura f1(Prajitura* vPrajituri, int nrPrajituri) {
	//to do
	return vPrajituri[0];
}

Prajitura f2() {
	Prajitura p;
	return p;
}

int main() {
	Prajitura p1;
	p1.afisare();

	string ingrediente[] = { "lapte","faina","oua","cacao" };
	Prajitura p2("Negresa", 150, 4, ingrediente);
	p2.afisare();

	Prajitura* pPrajitura = new Prajitura();
	delete pPrajitura;

	Prajitura p3 = p2;
	Prajitura p4(p2);
	p4.afisare();

	cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	Prajitura vPrajitura[] = { p1,p2 };
	cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	Prajitura p5 = f1(vPrajitura, 2);
	cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
	//p5= f1(vPrajitura, 2);
	return 0;
}