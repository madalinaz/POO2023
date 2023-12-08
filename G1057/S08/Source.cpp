#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class AgendaTelefon {
private:
	const int id;
	string detinator = "Anonim";
	int nrContacte = 0;
	string* listaContacte = nullptr;
	int nrContacteFavorite = 0;
	int nrContacteSterse = 0;
	static const int dimensiuneMaximaStocare = 60;
public:
	AgendaTelefon(int id) :id(id) {}

	int getNrContacteFavorite() {
		return this->nrContacteFavorite;
	}

	void setNrContacteFavorite(int numar) {
		if (numar >= 0)
			this->nrContacteFavorite = numar;
	}

	int getNrContacteSterse() {
		return this->nrContacteSterse;
	}

	void setNrContacteSterse(int numar) {
		if (numar >= 0)
			this->nrContacteSterse = numar;
	}

	void adaugaContact(string contact) {
		if (this->nrContacte == 0 && contact.length() <= dimensiuneMaximaStocare) {
			delete[] this->listaContacte;
			this->listaContacte = nullptr;
			this->nrContacte = 1;
			this->listaContacte = new string[1];
			this->listaContacte[0] = contact;
		}
		else if (this->nrContacte > 0 && this->listaContacte != nullptr) {
			int dimensiuneOcupata = 0;
			for (int i = 0; i < this->nrContacte; i++)
				dimensiuneOcupata += this->listaContacte[i].length();
			if (contact.length() <= (dimensiuneMaximaStocare - dimensiuneOcupata)) {
				AgendaTelefon copie = *this;
				delete[] copie.listaContacte;
				copie.listaContacte = nullptr;
				copie.nrContacte++;
				copie.listaContacte = new string[copie.nrContacte];
				for (int i = 0; i < this->nrContacte; i++)
					copie.listaContacte[i] = this->listaContacte[i];
				copie.listaContacte[copie.nrContacte - 1] = contact;
				delete[] this->listaContacte;
				this->listaContacte = nullptr;
				this->nrContacte++;
				this->listaContacte = new string[this->nrContacte];
				for (int i = 0; i < this->nrContacte; i++)
					this->listaContacte[i] = copie.listaContacte[i];
			}
		}
		else throw exception("Nu exista dimensiune disponibila suficient de mare pentru a adauga un contact nou");
	}

	~AgendaTelefon() {
		delete[] this->listaContacte;
		this->listaContacte = nullptr;
	}

	friend ostream& operator<<(ostream& out, const AgendaTelefon& a) {
		out << "\n------AGENDA-------";
		out << "\nID: " << a.id;
		out << "\nDetinator: " << a.detinator;
		out << "\nNr contacte: " << a.nrContacte;
		out << "\nLista contacte: ";
		if (a.nrContacte > 0 && a.listaContacte != nullptr)
			for (int i = 0; i < a.nrContacte; i++)
				out << a.listaContacte[i] << " ";
		else out << "-";
		out << "\nNr contacte favorite: " << a.nrContacteFavorite;
		out << "\nNr contacte sterse: " << a.nrContacteSterse;
		out << "\nDimensiune maxima stocare: " << AgendaTelefon::dimensiuneMaximaStocare;
		out << "\n-------------------";
		return out;
	}

	friend istream& operator>>(istream& in, AgendaTelefon& a) {
		delete[] a.listaContacte;
		a.listaContacte = nullptr;
		cout << "detinator: ";
		in >> a.detinator;
		cout << "nrContacte: ";
		in >> a.nrContacte;
		if (a.nrContacte > 0) {
			a.listaContacte = new string[a.nrContacte];
			for (int i = 0; i < a.nrContacte; i++) {
				cout << "Contact " << i << " : ";
				in >> a.listaContacte[i];
			}
		}
		cout << "nrContacteFavorite: ";
		in >> a.nrContacteFavorite;
		cout << "nrContacteSterse: ";
		in >> a.nrContacteSterse;
		return in;
	}

	AgendaTelefon(const AgendaTelefon& a) :id(a.id) {
		this->detinator = a.detinator;
		this->nrContacte = a.nrContacte;
		if (this->nrContacte > 0) {
			this->listaContacte = new string[this->nrContacte];
			for (int i = 0; i < this->nrContacte; i++)
				this->listaContacte[i] = a.listaContacte[i];
		}
		this->nrContacteFavorite = a.nrContacteFavorite;
		this->nrContacteSterse = a.nrContacteSterse;
	}

	AgendaTelefon& operator=(const AgendaTelefon& a) {
		delete[] this->listaContacte;
		this->listaContacte = nullptr;
		this->detinator = a.detinator;
		this->nrContacte = a.nrContacte;
		if (this->nrContacte > 0) {
			this->listaContacte = new string[this->nrContacte];
			for (int i = 0; i < this->nrContacte; i++)
				this->listaContacte[i] = a.listaContacte[i];
		}
		this->nrContacteFavorite = a.nrContacteFavorite;
		this->nrContacteSterse = a.nrContacteSterse;
		return *this;
	}

	void operator+(string contact) {
		contact + *this;
	}

	friend void operator+(string contact, AgendaTelefon& a) {
		a.adaugaContact(contact);
	}

	int getNrContactiDupaInitiala(char c) {
		if (this->nrContacte > 0 && this->listaContacte != nullptr) {
			int numar = 0;
			for (int i = 0; i < this->nrContacte; i++)
				if (this->listaContacte[i][0] == toupper(c) ||
					this->listaContacte[i][0] == tolower(c))
					numar++;
			return numar;
		}
	}

	bool operator()() {
		if (this->nrContacte > 1 && this->listaContacte != nullptr) {
			int ok = 0;
			for (int i = 0; i < this->nrContacte - 1 && !ok; i++)
				for (int j = i + 1; j < this->nrContacte && !ok; j++)
					if (this->listaContacte[i] == listaContacte[j])
						ok = 1;
			if (ok) return true;
			return false;
		}
		return false;
	}

	string* operator[](char c) {
		string* lista;
		lista = nullptr;
		if (this->nrContacte > 0 && this->listaContacte != nullptr) {
			int dimensiune = this->getNrContactiDupaInitiala(c);
			if (dimensiune > 0) {
				int k = 0;
				lista = new string[dimensiune];
				for (int i = 0; i < this->nrContacte; i++)
					if (this->listaContacte[i][0] == toupper(c) ||
						this->listaContacte[i][0] == tolower(c))
						lista[k++] = this->listaContacte[i];
			}
		}
		return lista;
	}
};

int main() {
	//apel constructor cu 1 param
	AgendaTelefon a1(34);
	cout << a1;
	a1.setNrContacteFavorite(4);
	a1.setNrContacteSterse(5);
	cout << endl << "Nr contacte fav: " << a1.getNrContacteFavorite();
	cout << endl << "Nr contacte sterse: " << a1.getNrContacteSterse();
	cout << a1 << endl;
	cin >> a1;
	cout << a1;
	//apel constructor de copiere
	AgendaTelefon a2(a1);
	cout << a2;
	try {
		a1.adaugaContact("Poroneci");
	}
	catch (exception ex) {
		cout << ex.what();
	}

	cout << a1;

	AgendaTelefon a3(51);
	cout << a3;
	a3 = a1;
	cout << a3;

	"Colo" + a3;
	cout << a3;

	a3 + "Soroneci";
	cout << a3;

	char initiala = 'A';
	cout << endl << "Nr de contacte care incep cu caracterul " << initiala << " este: " << a3.getNrContactiDupaInitiala(initiala);

	if (a3()) cout << endl << "Exista dubluri in a3";
	else cout << endl << "Nu exista dubluri in a3";

	cout << endl << "Lista formata din contacte care incep cu initiala " << initiala << " : ";
	if (a3.getNrContactiDupaInitiala(initiala) == 0) cout << "-";
	else {
		string* lista;
		lista = new string[a3.getNrContactiDupaInitiala(initiala)];
		lista = a3[initiala];
		for (int i = 0; i < a3.getNrContactiDupaInitiala(initiala); i++)
			cout << lista[i] << " ";
	}

	return 0;
}