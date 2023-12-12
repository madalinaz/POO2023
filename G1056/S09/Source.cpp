#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class Eveniment {
private:
	int nrPers = 0;
	string locatie;
	float pretBilet = 0;

public:
	Eveniment() {}
	Eveniment(int nrPers, string locatie, float pretBilet) {
		this->nrPers = nrPers;
		this->locatie = locatie;
		this->pretBilet = pretBilet;
	}

	Eveniment(const Eveniment& e) {
		this->nrPers = e.nrPers;
		this->locatie = e.locatie;
		this->pretBilet = e.pretBilet;
	}

	Eveniment& operator=(const Eveniment& e) {
		this->nrPers = e.nrPers;
		this->locatie = e.locatie;
		this->pretBilet = e.pretBilet;
		return *this;
	}

	//ofstream is a ostream
	friend ostream& operator<<(ostream& out, const Eveniment& e) {
		out << "\nNr pers: " << e.nrPers;
		out << "\nLocatie ev: " << e.locatie;
		out << "\nPret bilet: " << e.pretBilet;
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Eveniment& e) {
		out << e.nrPers << endl;
		out << e.locatie << endl;
		out << e.pretBilet;
		return out;
	}

	friend istream& operator>>(istream& in, Eveniment& e) {
		cout << "\nIntroduceti nr persoane: ";
		in >> e.nrPers;
		cout << "Introduceti locatie: ";
		in >> e.locatie;
		cout << "Introduceti pret bilet: ";
		in >> e.pretBilet;
		return in;
	}

	friend ifstream& operator>>(ifstream& in, Eveniment& e) {
		in >> e.nrPers;
		in >> e.locatie;
		in >> e.pretBilet;
		return in;
	}

	void writeToFile(fstream& f) {
		//scriere nr persoane(int)
		f.write((char*)&this->nrPers, sizeof(int));

		//scriere locatie(string)
		//1.scriere lungime sir
		int lg = this->locatie.size() + 1;
		f.write((char*)&lg, sizeof(int));
		//2.scriere sir de caractere
		f.write(this->locatie.data(), lg);

		//scriere pret bilet
		f.write((char*)&this->pretBilet, sizeof(float));
	}

	void readFromFile(fstream& f) {
		//citire nr persoane(int)
		f.read((char*)&this->nrPers, sizeof(int));
		//citire locatie(string)
		//1.citire lungime sir
		int lg;
		f.read((char*)&lg, sizeof(int));
		//2.citire sir de caractere
		char* buffer;
		buffer = new char[lg];
		f.read(buffer, lg);
		this->locatie = buffer;
		delete[] buffer;
		buffer = nullptr;
		//citire pret bilet(float)
		f.read((char*)&this->pretBilet, sizeof(int));
	}
};

int main() {
	Eveniment ev(100, "Targ de Craciun", 200);
	ofstream g("evenimente.txt");
	g << ev;
	g.close();
	Eveniment ev2;
	ifstream f("evenimente.txt");
	f >> ev2;
	cout<<ev2;
	f.close();

	fstream file("colectie.bin", ios::in | ios::binary);
	//ev.writeToFile(file);
	//Eveniment evRez;
	//evRez.readFromFile(file);
	//cout << evRez;
	//file.close();


}