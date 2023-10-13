#include<iostream>
using namespace std;

class Student {
private:
	char nume[30];
	int anStudiu;
	int nrNote;
	int* note;
public:
	//constructor fara parametri
	Student() {
		strcpy(nume, "Anonim");
		anStudiu = 0;
		nrNote = 0;
		note = NULL;
	}

	//meth accesor( de tip get si set)
	void setNume(const char* numeNou) {
		if (strlen(numeNou) >= 5)
			strcpy(nume, numeNou);
	}

	char* getNume() {
		return nume;
	}

	char* getNume1() {
		char copie[30];
		strcpy(copie, nume);
		return copie;
	}

	char* getNume2() {
		char* copie;
		copie = new char[strlen(nume) + 1];
		strcpy(copie, nume);
		//delete[] copie;
		return copie;
	}

	const char* getNume3() {
		return nume;
	}

	void afisare() {
		cout << "\n****************************";
		cout << "\nNume: " << nume;
		cout << "\nAn studiu: " << anStudiu;
		cout << "\nNr note: " << nrNote;
		cout << "\nNote: ";
		if (note == NULL)
			cout << "-";
		else
			for (int i = 0; i < nrNote; i++)
				cout << note[i] << " ";
		cout << "\n****************************";
	}
};

int main() {
	Student s;
	s.afisare();
	char nume[10];
	strcpy(nume, "Gigel");
	s.setNume("Gigel");
	s.afisare();
	cout << "\nNume student: " << s.getNume3();
	//s.getNume3()[0] = 'F';
	//char* p = s.getNume2();
	//delete[] p;
	s.afisare();
	Student* ps = new Student();//apel constructor fara param
	//ps->afisare();
	return 0;
}