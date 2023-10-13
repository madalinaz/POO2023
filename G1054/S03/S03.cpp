#include<iostream>
using namespace std;

class Student {
private:
	char nume[30];
	int nrNote;
	int* note;
protected:
	int varProtected;
public:
	int varPublic;
	//constructor fara parametri
	Student() {
		strcpy(nume, "Anonim");
		nrNote = 0;
		note = nullptr;
	}

	void afisare() {
		cout << "\n_________________________";
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
		cout << "\n_________________________";
	}

	//meth accesor(de tip get si set)
	void setNume(const char* numeNou) {
		if (numeNou != nullptr && strlen(numeNou) >= 5) {
			strcpy(nume, numeNou);
		}
	}

	const char* getNume() {
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
		return copie;
	}

	char* getNume3() {
		static char copie[30];
		strcpy(copie, nume);
		return copie;
	}

	void setNote(int* noteNou, int nrNoteNou) {
		if (noteNou != nullptr && nrNoteNou > 0) {
			delete[] note;
			note = nullptr;
			//note = noteNou;
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
	(*ps).varPublic = 13;
	s.afisare();
	s.setNume("Gigel");
	s.afisare();
	cout << "\nNume folosind get: " << s.getNume2();
	s.getNume2()[0] = 'D';
	/*delete[] s.getNume2();
	char* pointer;
	pointer = s.getNume2();
	delete[] pointer;*/
	s.afisare();
	return 0;
}