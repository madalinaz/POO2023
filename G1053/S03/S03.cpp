#include<iostream>
using namespace std;

class Student {
private:
	char* nume;
	int nrNote;
	int note[20];
protected:
	//int varProtected;
public:
	//int varPublic;
	//constructor fara parametri
	Student() {
		nume = new char[strlen("Anonim") + 1];
		strcpy(nume, "Anonim");
		nrNote = 0;
	}

	void afisare() {
		cout << "\n____________________________";
		cout << "\nNume: " << nume;
		cout << "\nNr note: " << nrNote;
		cout << "\nNote: ";
		if (nrNote > 0) {
			for (int i = 0; i < nrNote; i++)
				cout << note[i] << " ";
		}
		else {
			cout << "-";
		}
		cout << "\n____________________________";
	}

	//meth accesor(de tip get si set)
	void setNume(const char* numeNou) {
		if (numeNou != nullptr && strlen(numeNou) >= 5) {
			delete[] nume;
			nume = nullptr;
			nume = new char[strlen(numeNou) + 1];
			strcpy(nume, numeNou);
		}
	}

	char* getNume() {
		return nume;
	}

};

int main() {
	Student s;
	Student* ps = new Student();
	s.afisare();
	s.setNume("Gigel");
	s.afisare();
	cout << "\nNume folosind get: " << s.getNume();
	return 0;
}