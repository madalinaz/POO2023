#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//clasa de tip Interfata care descrie un "contract"
//clasa contine metode specifice lucrului cu fisiere binare
class IFile {
	virtual void saveToFile(fstream& file) = 0;//metoda virtuala pura
	virtual void restoreFromFile(fstream& file) = 0;//metoda virtuala pura
};

//Animal este clasa Abstracta (pentru ca nu are implementare concreta pentru meth
//virtuale pure din clasa de baza IFile
class Animal :IFile {
	string denumire;
};

//daca nu exista implementari concrete in clasa Eveniment pentru meth virtuale pure,
//atunci clasa ramane clasa Abstracta
class Eveniment:IFile {
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

	friend ostream& operator<<(ostream& out, const Eveniment& e) {
		out << "\nNr pers: " << e.nrPers;
		out << "\nLocatie ev: " << e.locatie;
		out << "\nPret bilet: " << e.pretBilet;
		return out;
	}

	friend ofstream& operator<<(ofstream& out, const Eveniment& e) {
		out <<  e.nrPers;
		out <<  endl<< e.locatie;
		out <<  endl<< e.pretBilet;
		return out;
	}

	friend istream& operator>>(istream& in, Eveniment& e) {
		cout << "\nIntroduceti nr persoane:";
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

	void saveToFile(fstream& file) {
		//scriere nr persoane(int)
		file.write((char*)&this->nrPers, sizeof(int));
		//sciere sir de caractere(locatie)
		int lg = this->locatie.length() + 1;
		file.write((char*)&lg, sizeof(int));
		file.write(this->locatie.data(), lg);//meth data() extrage char* dintr-un string
		//scriere pret bilet(float)
		file.write((char*)&this->pretBilet, sizeof(float));
	}

	void restoreFromFile(fstream& file) {
		//citire nr persoane(int)
		file.read((char*)&this->nrPers, sizeof(int));
		//citire sir de caractere(locatie)
		int lg;
		file.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		file.read(buffer, lg);
		this->locatie = buffer;
		delete[] buffer;
		//citire pret bilet(float)
		file.read((char*)&this->pretBilet, sizeof(float));
	}
};

int main() {
	ofstream g("evenimente.txt");
	Eveniment ev1(100, "Craiova", 150);
	cout << ev1;
	g << ev1;//ofstream is a ostream
	g.close();
	ifstream f("evenimente.txt");
	Eveniment ev2;
	f >> ev2;//ifstream is a istream
	cout << ev2;

	//IFile file;
	IFile* filePointer;
	//fstream file("colectie.bin", ios::out | ios::binary);
	//ev2.saveToFile(file);
	//file.close();

	fstream file("colectie.bin", ios::in | ios::binary);
	Eveniment ev3;
	ev3.restoreFromFile(file);
	cout << ev3;
	file.close();
}