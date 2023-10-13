#include<iostream>
using namespace std;

class Student {
private:
	char* nume;
	char seria;
	int nrNote;
	int note[30];
protected:
	//int varProtected;
public:
	//int varPublic;

	//constructor fara parametri
	Student() {
		//nume = NULL;
		nume = new char[strlen("Anonim") + 1];
		strcpy(nume, "Anonim");
		seria = '-';
		nrNote = 0;
	}

	void afisare() {
		cout << "\n^^^^^^^^^^^^^^^^^^^^^^^^^";
		cout << "\nNume: " << nume;
		cout << "\nSerie: " << seria;
		cout << "\nNr note: " << nrNote;
		cout << "\nNote: ";
		if (nrNote > 0)
			for (int i = 0; i < nrNote; i++)
				cout << note[i] << " ";
		else
			cout << "-";
		cout << "\n^^^^^^^^^^^^^^^^^^^^^^^^^";
	}

	//meth accesor (de tip get si set)
	void setNume(const char* numeNou) {
		if (numeNou != NULL && strlen(numeNou) >= 3) {
			delete[] nume;
			nume = NULL;
			nume = new char[strlen(numeNou) + 1];
			strcpy(nume, numeNou);
		}
	}

	char* getNume() {
		return nume;
	}

	const char* getNume1() {
		return nume;
	}

	char* getNume2() {
		char copie[30];
		strcpy(copie, nume);
		return copie;
	}

	char* getNume3() {
		static char copie[30];
		strcpy(copie, nume);
		return copie;
	}

	char* getNume4() {
		char* copie;
		copie = new char[strlen(nume) + 1];
		strcpy(copie, nume);
		return copie;
	}

	void setNote(int nrNoteNou, int* noteNou) {
		if (nrNoteNou > 0 && noteNou != NULL) {
			nrNote = nrNoteNou;
			for (int i = 0; i < nrNote; i++)
				note[i] = noteNou[i];
		}
	}

	int getNrNote() {
		return nrNote;
	}

	const int* getNote() {
		return note;
	}

	int getNota(int index) {
		return note[index];
	}
};

int main() {
	Student s;
	Student* ps = new Student();
	s.setNume("Gigel");
	s.afisare();
	cout << "\nAfisare nume folosind get: " << s.getNume4();
	s.getNume4()[0] = 'C';
	//delete[] s.getNume4();
	s.afisare();

	int note[] = { 5,8,10 };
	s.setNote(3, note);
	cout << "\nAfisare nrNote folosind get: " << s.getNrNote();
	return 0;
}