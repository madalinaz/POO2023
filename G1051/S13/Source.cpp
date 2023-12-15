#include<iostream>
#include<vector>
#include<list>
#include<set>
#include<map>
using namespace std;


class Eveniment {
private:
	int nrPers = 0;
	string locatie = "Anonim";
public:
	Eveniment() {}
	Eveniment(int nrPers, string locatie) {
		this->nrPers = nrPers;
		this->locatie = locatie;
	}
	Eveniment(const Eveniment& e) {
		this->nrPers = e.nrPers;
		this->locatie = e.locatie;
	}
	Eveniment& operator=(const Eveniment& e) {
		this->nrPers = e.nrPers;
		this->locatie = e.locatie;
		return *this;
	}

	friend ostream& operator<<(ostream& out,const Eveniment& e) {
		out << "\nNr pers eveniment: " << e.nrPers;
		out << "\nLocatie eveniment: " << e.locatie;
		return out;
	}

	/*bool operator<(const Eveniment& e) {
		return this->nrPers < e.nrPers;
	}*/

	friend bool operator<(const Eveniment& e1, const Eveniment& e2) {
		return e1.nrPers < e2.nrPers;
	}
};

class WishList {
	Eveniment* listaEv;
	int nrEvenimente;

	vector<Eveniment> vEv;
};


int main()
{
	//STL - standard template library
	cout << "\n-------------STL VECTOR----------------------\n";
	vector<int> vInt;
	vInt.push_back(10);
	vInt.push_back(20);
	vInt.push_back(30);
	for (int i = 0; i < vInt.size(); i++)
		cout << vInt[i] << " ";
	vector<int>::iterator it;
	cout << endl;
	for (it = vInt.begin(); it != vInt.end(); it++)
		cout << *it << " ";

	cout << "\n-------------STL LIST----------------------\n";
	list<float> lFloat;
	lFloat.push_back(10.5);
	lFloat.push_front(13.5);
	lFloat.push_front(14.3);
	list<float>::iterator itList;
	for (itList = lFloat.begin(); itList != lFloat.end(); itList++)
		cout << *itList << " ";
	list<float>::reverse_iterator rItList;
	cout << endl;
	for (rItList = lFloat.rbegin(); rItList != lFloat.rend(); rItList++)
		cout << *rItList << " ";

	cout << "\n-------------STL SET----------------------\n";
	set<string> setString;
	setString.insert("Popescu Ioan");
	setString.insert("Coman Irina");
	setString.insert("Popescu Ioan");
	set<string>::iterator itSet;
	for (itSet = setString.begin(); itSet != setString.end(); itSet++)
		cout << *itSet << " ";
	Eveniment e1(100, "loc1");
	Eveniment e2(150, "loc2");
	Eveniment e3(50, "loc3");
	set<Eveniment> setEv;
	setEv.insert(e1);
	setEv.insert(e2);
	setEv.insert(e3);
	set<Eveniment>::iterator itSet2;
	for (itSet2 = setEv.begin(); itSet2 != setEv.end(); itSet2++)
		cout << *itSet2 << " ";

	itSet2 = setEv.find(e2);
	if (itSet2 != setEv.end())
		cout << "\nS-a gasit e2 in set";
	else
		cout << "\nNu s-a gasit e2 in set";

	cout << "\n-------------STL MAP----------------------\n";
	map<int, Eveniment> mapEv;
	mapEv[0] = e1;
	mapEv[10] = e2;
	mapEv[6] = e3;
	mapEv[10] = e3;
	map<int, Eveniment>::iterator itMap;
	for (itMap = mapEv.begin(); itMap != mapEv.end(); itMap++)
		cout << endl<<itMap->first << " " << itMap->second;
	return 0;
}