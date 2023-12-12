#include<iostream>
#include<string>
using namespace std;

//TEMA: De implementat o clasa de baza si 2 derivate. De implementat "must-ul" in clase.
//De adaugat o metoda virtuala si de exemplificat virtualizarea in main pe baza unui vector de pointeri la clasa de baza
//TEMA OPTIONALA: De virtualizat conceptul de cout.

enum Grad
{
	ASIST = 1, LECT = 2, CONF = 3, PROF = 4
};

class Angajat
{
private:
	string nume = "Anonim";
protected:
	int vechime = 0;
	int nrLocuriMunca = 0;
	string* locuriMunca = nullptr;
	float salariu = 0;

public:
	Angajat()
	{
		cout << "\nCONSTRUCTOR FARA PARAM ANGAJAT";
	}

	Angajat(string nume, int vechime, int nrLocuriMunca, string* locuriMunca, float salariu)
	{
		cout << "\nCONSTRUCTOR CU PARAM ANGAJAT";
		this->nume = nume;
		this->vechime = vechime;
		this->salariu = salariu;
		if (locuriMunca != nullptr && nrLocuriMunca != 0)
		{
			this->nrLocuriMunca = nrLocuriMunca;
			this->locuriMunca = new string[this->nrLocuriMunca];
			for (int i = 0; i < this->nrLocuriMunca; i++)
				this->locuriMunca[i] = locuriMunca[i];
		}
	}

	Angajat(const Angajat& a)
	{
		cout << "\nCONSTRUCTOR COPIERE ANGAJAT";
		this->nume = a.nume;
		this->vechime = a.vechime;
		this->salariu = a.salariu;
		if (a.locuriMunca != nullptr && a.nrLocuriMunca > 0)
		{
			this->nrLocuriMunca = a.nrLocuriMunca;
			this->locuriMunca = new string[this->nrLocuriMunca];
			for (int i = 0; i < this->nrLocuriMunca; i++)
				this->locuriMunca[i] = a.locuriMunca[i];
		}
	}

	Angajat& operator=(const Angajat& a)
	{
		cout << "\nOPERATOR = ANGAJAT";
		if (this != &a) {
			this->nume = a.nume;
			this->vechime = a.vechime;
			this->salariu = a.salariu;
			delete[] this->locuriMunca;
			this->locuriMunca = nullptr;
			if (a.locuriMunca != nullptr && a.nrLocuriMunca > 0)
			{
				this->nrLocuriMunca = a.nrLocuriMunca;
				this->locuriMunca = new string[this->nrLocuriMunca];
				for (int i = 0; i < this->nrLocuriMunca; i++)
					this->locuriMunca[i] = a.locuriMunca[i];
			}
			else
			{
				this->nrLocuriMunca = 0;
				this->locuriMunca = nullptr;
			}
		}
		return *this;
	}

	~Angajat()
	{
		cout << "\nDESTRUCTOR ANGAJAT";
		delete[] this->locuriMunca;
		this->locuriMunca = nullptr;
	}


	friend ostream& operator<<(ostream& out, const Angajat& a)
	{
		out << "\nNume: " << a.nume;
		out << "\nVechime: " << a.vechime;
		out << "\nSalariu: " << a.salariu;
		if (a.locuriMunca != nullptr)
		{
			out << "\nLocuri munca: ";
			for (int i = 0; i < a.nrLocuriMunca; i++)
				out << a.locuriMunca[i] << ", ";
		}
		return out;
	}

	//metoda virtuala
	virtual float calculSalariu()
	{
		return this->salariu;
	}
};

//principiul Liskov substitution
//Profesor is a Angajat
class Profesor : public Angajat {
	Grad gradDidactic = Grad::ASIST;
	int nrOreSuplimentare = 0;

public:
	Profesor() {
		cout << "\nCONSTRUCTOR FARA PARAM PROFESOR";
	}

	Profesor(string nume, int vechime, int nrLocuriMunca, string* locuriMunca, float salariu, Grad gradDidactic, int nrOreSuplimentare) :Angajat(nume, vechime, nrLocuriMunca, locuriMunca, salariu) {
		cout << "\nCONSTRUCTOR CU PARAM PROFESOR";
		this->gradDidactic = gradDidactic;
		this->nrOreSuplimentare = nrOreSuplimentare;
	}

	Profesor(Angajat a, Grad gradDidactic, int nrOreSuplimentare) : Angajat(a) {
		cout << "\nCONSTRUCTOR CU PARAM 2 PROFESOR";
		this->gradDidactic = gradDidactic;
		this->nrOreSuplimentare = nrOreSuplimentare;
	}

	Profesor(const Profesor& p) :Angajat(p) {
		cout << "\nCONSTRUCTOR COPY PROFESOR";
		this->gradDidactic = p.gradDidactic;
		this->nrOreSuplimentare = p.nrOreSuplimentare;
	}

	Profesor& operator=(const Profesor& p) {
		cout << "\nOP= PROFESOR";
		if (this != &p) {
			this->Angajat::operator=(p);
			this->gradDidactic = p.gradDidactic;
			this->nrOreSuplimentare = p.nrOreSuplimentare;
		}
		return *this;
	}

	~Profesor() {
		cout << "\nDESTRUCTOR PROFESOR";
	}

	friend ostream& operator<<(ostream& out, const Profesor& p) {
		out << (Angajat&)p;
		out << "\nGrad didactic: " << p.gradDidactic;
		out << "\nNr ore suplimentare: " << p.nrOreSuplimentare;
		return out;
	}

	float calculSalariu() {
		float rez = Angajat::calculSalariu();
		rez += this->nrOreSuplimentare * 100 * (1 + (this->gradDidactic - 1) * 0.1);
		return rez;
	}
};


int main()
{
	string lista[] = { "CNCV","ASE" };
	Angajat a("Costelus", 10, 2, lista, 5000);
	cout << a;
	Profesor p;
	Profesor p2("Marcel", 5, 2, lista, 4000, Grad::CONF, 10);
	Profesor p3(a, Grad::CONF, 10);
	Profesor p4 = p3;
	p4 = p3;
	cout << "\n****************";
	cout << p4;
	cout << "\n****************";

	cout << "\n**********Calcul Salariu***********";
	cout << "\nSalariu calculat angajat: " << a.calculSalariu();
	cout << "\nSalariu calculat profesor: " << p4.calculSalariu();

	//task: de gestionat toti angajatii din Ase intr-o maniera centralizata
	Angajat listaAngajatiAse[10];
	listaAngajatiAse[0] = a;
	listaAngajatiAse[1] = p4;//apel op=din Angajat + upcast
	float totalSalarii = 0;
	for (int i = 0; i < 2; i++)
		totalSalarii += listaAngajatiAse[i].calculSalariu();
	cout << "\nTotal salarii in centralizare obiecte: " << totalSalarii;

	Angajat* listaPointeriAngajatiAse[10];
	listaPointeriAngajatiAse[0] = &a;
	listaPointeriAngajatiAse[1] = &p4;
	float totalSalariiPointeri = 0;
	for (int i = 0; i < 2; i++)
		totalSalariiPointeri += listaPointeriAngajatiAse[i]->calculSalariu();
	cout << "\nTotal salarii in centralizare pointeri: " << totalSalariiPointeri;
	return 0;
}