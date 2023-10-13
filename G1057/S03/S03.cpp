#include<iostream>
using namespace std;

class Student {
private:
	char nume[30];
	int nrNote;
	int* note;
protected:
	//int varProtected;
public:
	//int varPublic;
	//contructor fara parametri
	Student() {
		strcpy(nume, "Anonim");
		nrNote = 0;
		note = nullptr;
	}

	void afisare() {
		cout << "\n^^^^^^^^^^^^^^^^^^^^^^^^^";
		cout << "\nNume: " << nume;
		cout << "\nNr note: " << nrNote;
		cout << "\nNote: ";
		if (note != nullptr) {
			for (int i = 0; i < nrNote; i++)
				cout << note[i] << " ";
		}
		else {
			cout << "-";
		}
		cout << "\n^^^^^^^^^^^^^^^^^^^^^^^^^";
	}

	//meth accesor(de tip get si set)
	void setNume(const char* numeNou) {
		if (numeNou != nullptr && strlen(numeNou) >= 5) {
			strcpy(nume, numeNou);
		}
	}

	char* getNume() {
		return nume;
	}

	void setNote(int* noteNou, int nrNoteNou) {
		if (noteNou != nullptr && nrNoteNou > 0) {
			delete[] note;
			note = nullptr;
			note = new int[nrNoteNou];
			for (int i = 0; i < nrNoteNou; i++)
				note[i] = noteNou[i];
			nrNote = nrNoteNou;
		}
	}
};

int main() {
	Student s;
	Student* ps = new Student();
	//s.varPublic = 6;
	//(*ps).varPublic
	s.afisare();
	s.setNume(nullptr);
	s.setNume("Gigel");
	s.afisare();
	cout << "\nNume folosind get: " << s.getNume();
	return 0;
}