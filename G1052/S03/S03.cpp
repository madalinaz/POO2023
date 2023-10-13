#include<iostream>
using namespace std;

class Student {
private:
	char nume[30];
	bool laBuget;
	int nrNote;
	int* note;
protected:
	//int varProtected;
public:
	//int varPublic;
	//constructor fara parametri
	Student() {
		strcpy(nume, "Anonim");
		laBuget = true;
		nrNote = 0;
		note = NULL;
	}

	void afisare() {
		cout << "\n##################";
		cout << "\nNume: " << nume;
		cout << "\nLa buget? 1-DA 0-NU " << laBuget;
		cout << "\nNr note: " << nrNote;
		cout << "\nNote: ";
		if (note != NULL)
			for (int i = 0; i < nrNote; i++)
				cout << note[i] << " ";
		else
			cout << "-";
		cout << "\n##################";
	}

	//meth accesor(de tip get si set)
	void setNume(const char* numeNou) {
		if (numeNou != NULL && strlen(numeNou) >= 4) {
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
		static char copie[30];
		strcpy(copie, nume);
		return copie;
	}

	char* getNume3() {
		char* copie;
		copie = new char[strlen(nume) + 1];
		strcpy(copie, nume);
		return copie;
	}

	void setNote(int nrNoteNou, int* noteNou) {
		if (noteNou != NULL && nrNoteNou > 0) {
			delete[] note;
			note = NULL;
			//note = noteNou; DO NOT 
			note = new int[nrNoteNou];
			for (int i = 0; i < nrNoteNou; i++)
				note[i] = noteNou[i];
			nrNote = nrNoteNou;
		}
	}

	void setNota(int nota, int index) {
		if (index >= 0 && index < nrNote)
			note[index] = nota;
	}
};

int  main() {
	Student s;
	Student* ps = new Student();
	s.afisare();
	s.setNume("Gigel");
	s.afisare();
	cout << "\nAfis nume folosind get: " << s.getNume3();
	s.getNume3()[2] = '2';
	/*char* p = s.getNume3();
	delete[] p;*/
	//delete[] s.getNume3();
	s.afisare();
	int note[] = { 10,8,7 };
	s.setNote(3, note);
	return 0;
}