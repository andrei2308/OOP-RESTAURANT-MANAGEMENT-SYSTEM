#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <sstream>
using namespace std;
enum class Ingredient 
{
	Zahar,
	Faina,
	Oua,
	Ulei,
	Carne,
	Lapte,
	Legume,
	Paste,
	Sos,
	CarneHamburger,
	Paine,
	Rosii
};
unordered_map<Ingredient, string> numeIngredient =
{
	{Ingredient::Zahar, "Zahar"},
	{Ingredient::Faina, "Faina"},
	{Ingredient::Oua, "Oua"},
	{Ingredient::Ulei, "Ulei"},
	{Ingredient::Carne, "Carne"},
	{Ingredient::Lapte, "Lapte"},
	{Ingredient::Legume, "Legume"},
	{Ingredient::Paste, "Paste"},
	{Ingredient::Sos, "Sos"},
	{Ingredient::CarneHamburger, "CarneHamburger"},
	{Ingredient::Paine, "Paine"},
	{Ingredient::Rosii, "Rosii"}
};
class Reteta {
private:
	map<Ingredient, float> ingrediente;
	unordered_map<Ingredient, string> numeIngredient =
	{
		{Ingredient::Zahar, "Zahar"},
		{Ingredient::Faina, "Faina"},
		{Ingredient::Oua, "Oua"},
		{Ingredient::Ulei, "Ulei"},
		{Ingredient::Carne, "Carne"},
		{Ingredient::Lapte, "Lapte"},
		{Ingredient::Legume, "Legume"},
		{Ingredient::Paste, "Paste"},
		{Ingredient::Sos, "Sos"},
		{Ingredient::CarneHamburger, "CarneHamburger"},
		{Ingredient::Paine, "Paine"},
		{Ingredient::Rosii, "Rosii"}
	};

public:
	void adaugaingredient(int id, float cantitate) 
	{
		Ingredient ingredient = static_cast<Ingredient>(id);
		adaugaIngredient(ingredient, cantitate);
	}


	void adaugaIngredient(Ingredient ingredient, float cantitate) 
	{
		ingrediente[ingredient] = cantitate;
	}
	void setProvenientaIngredient(Ingredient ingredient, const string& provenienta) 
	{
		auto it = numeIngredient.find(ingredient);
		if (it != numeIngredient.end()) 
		{
			it->second = provenienta;
		}
		else 
		{
			cout << "Ingredient negasit." << endl;
		}
	}
	void afiseazaReteta(const string& numeReteta) const 
	{
		cout << "Ingrediente " << numeReteta << ":" << endl;
		for (const auto& pair : ingrediente) 
		{
			auto it = numeIngredient.find(pair.first);
			if (it != numeIngredient.end()) 
			{
				cout << "- " << it->second << " : " << pair.second << " unitati" << endl;
			}
			else 
			{
				cout << "Ingredient negasit." << endl;
			}
		}
	}
	string getProvenientaIngredient(Ingredient ingredient) const
	{
		auto it = numeIngredient.find(ingredient);
		if (it != numeIngredient.end()) 
		{
			return it->second;
		}
		else 
		{
			return "Provenienta indisponibila";
		}
	}
	float getCalorii() const 
	{
		float totalCalorii = 0.0f;

		for (const auto& pair : ingrediente) 
		{
			totalCalorii += pair.second;
		}

		return totalCalorii;
	}

	const map<Ingredient, float>& getIngrediente() const
	{
		return ingrediente;
	}
	void populeazaRetetaDinFisier(const string& numeReteta) 
	{
		ifstream fisier(numeReteta + ".txt");

		if (fisier.is_open()) 
		{
			int ingredient;
			float cantitate;

			while (fisier >> ingredient >> cantitate) 
			{
				adaugaIngredient(static_cast<Ingredient>(ingredient), cantitate);
			}

			fisier.close();
		}
		else 
		{
			cout << "Nu s-a putut deschide fisierul pentru " << numeReteta << "." << endl;
		}
	}

};

class materieprima
{
private:
	string provenienta;
	string denumire;
	float cantitate;
	static int totalmaterie;
	float caloriiPerUnitate=1;
public:
	float getcalo() const
	{
		return caloriiPerUnitate;
	}
	materieprima(const string& nume, float cantitate, const string& provenienta, float calorii)
		: cantitate(cantitate), provenienta(provenienta), caloriiPerUnitate(calorii),denumire(nume)
	{
	}
	materieprima(const string& nume, float cantitate, string prov) 
    : cantitate(cantitate), provenienta(prov), denumire(nume)
	{

	}
	void afisare() 
	{
		cout << "Denumire: " << denumire << endl;
		cout << "Cantitate: " << cantitate << endl;
		cout << "Provenienta: " << provenienta << endl; 
		cout << "Numar de calorii per unitate: " << caloriiPerUnitate << endl;
	}
	static int gettotalmat()
	{
		return totalmaterie;
	}
	bool operator==(const materieprima& p) const
	{
		return (denumire == p.denumire && cantitate == p.cantitate);
	}
	bool operator!() const
	{
		return (cantitate == 0);
	}
	materieprima& operator++() 
	{
		++cantitate;
		return *this;
	}
	materieprima operator+(const materieprima& p) const
	{
		materieprima rezultat = *this;
		rezultat.cantitate += p.cantitate;

		return rezultat;
	}
	string getprovenienta() const 
	{
		return provenienta;
	}

	const string getdenumire() const
	{
		return denumire;
	}
	materieprima() :denumire(""), cantitate(0)
	{
		totalmaterie++;
	}
	materieprima(const string& nume, float cantitate) :cantitate(cantitate),denumire(nume)
	{
		
	}
	materieprima(const materieprima& p) : cantitate(p.cantitate), provenienta(p.provenienta),caloriiPerUnitate(p.caloriiPerUnitate),denumire(p.denumire)
	{
	}
	~materieprima()
	{
		totalmaterie--;
	}
	operator int() const
	{
		return static_cast<int>(cantitate);
	}
	materieprima& operator=(const materieprima& p)
	{
		if (this != &p) {

			cantitate = p.cantitate;

			denumire = p.denumire;
		}
		return *this;
	}
	bool operator>=(const materieprima& d) const
	{
		return cantitate >= d.cantitate;
	}

	friend ostream& operator<<(ostream& out, const materieprima& materie) 
	{
		out << "Denumire: " << materie.denumire << endl;
		out << "Cantitate: " << materie.cantitate << endl;
		out << "Provenienta: " << materie.provenienta << endl;
		out << "Numar de calorii per unitate: " << materie.caloriiPerUnitate << endl;
		return out;
	}

	friend istream& operator>>(istream& in, materieprima& materie)
	{
		cout << "Denumire: ";
		in >> materie.denumire;

		cout << endl;
		cout << "Cantitate: ";
		in >> materie.cantitate;
		cout << endl;

		return in;
	}
	void setdenumire(const string den)
	{
		denumire = den;
	}

	void setcantitate(float cant)
	{
		if (cant >= 0)
		{
			cantitate = cant;
		}
		else
		{
			cout << "Cantitate eronata." << endl;
		}
	}

	float getcantitate() const
	{
		return cantitate;
	}
};
int materieprima::totalmaterie = 10000;
vector<materieprima> citesteMateriiPrimeDinCSV(const string& numeFisier) 
{
    vector<materieprima> stoc;
    ifstream file(numeFisier);
    string linie;

    if (!file.is_open()) 
	{
        cerr << "Nu s-a putut deschide fisierul " << numeFisier << endl;
        return stoc;
    }

    while (getline(file, linie)) 
	{
        if (linie.empty()) continue; 

        stringstream ss(linie);
        string nume, provenienta;
        float cantitate, calorii;

        getline(ss, nume, ',');
        if (!ss || ss.peek() == ',') 
		{
            cerr << "Format invalid sau lipsă cantitate la " << nume << endl;
            continue;
        }
        ss >> cantitate;
        ss.ignore(numeric_limits<streamsize>::max(), ',');
        getline(ss, provenienta, ',');
        if (!ss || ss.peek() == ',') 
		{
            cerr << "Format invalid sau lipsă calorii la " << nume << endl;
            continue;
        }
        ss >> calorii;

        materieprima materie(nume, cantitate, provenienta, calorii);
        stoc.push_back(materie);
    }

    return stoc;
}



class reteta
{
private:
	vector<string> proveniente_ingrediente;
	vector<pair<materieprima, float>> ingrediente;

public:

	bool verificareFerma() const 
	{
		for (const auto& IngredientPereche : ingrediente) 
		{
			
			if (IngredientPereche.first.getprovenienta() != "Ferma") 
			{
				return false;
			}
		}
		return true;
	}
	void setProvenientaIngredient(int id, const string& provenienta)
	{
		if (id >= 0 && id < ingrediente.size()) 
		{
			proveniente_ingrediente[id] = provenienta;
		}
		else 
		{
			cout << "Id invalid." << endl;
		}
	}

	string getProvenientaIngredient(int id) const
	{
		if (id >= 0 && id < ingrediente.size()) 
		{
			return proveniente_ingrediente[id];
		}
		else 
		{
			return "Provenienta indisponibila";
		}
	}
	void afiseaza() const
	{
		cout << "Ingrediente: " << endl;
		for (const auto& ingredient : ingrediente) 
		{
			cout << "Nume ingredient: " << ingredient.first.getdenumire() << " Cantitate: " << ingredient.second << endl;
		}
	}
	materieprima& operator[](int id)
	{
		if (id >= 0 && id < ingrediente.size())
		{
			return ingrediente[id].first;
		}
		else {
			throw out_of_range("Id prea mare.");
		}
	}

	void adaugaingredient(const materieprima& ingredient, float cantitate)
	{
		ingrediente.push_back(make_pair(ingredient, cantitate));
	}

	friend ostream& operator<<(ostream& out, const reteta& r)
	{
		out << "Ingrediente: " << endl;
		for (const auto& ingredient : r.ingrediente) 
		{
			out << "Nume ingredient: " << ingredient.first.getdenumire() << " Cantitate: " << ingredient.second << endl;
		}
		return out;
	}

	friend istream& operator>>(istream& in, reteta& r)
	{
		int nring;
		cout << "Numarul de ingrediente: ";
		in >> nring;

		for (int i = 0; i < nring; ++i) 
		{
			materieprima ingredient;
			float cantitate;
			in >> ingredient >> cantitate;
			r.ingrediente.push_back(make_pair(ingredient, cantitate));
		}
		return in;
	}
	void setingredient(int id, float noua_cantitate)
	{
		if (id >= 0 && id < ingrediente.size()) 
		{
			ingrediente[id].second = noua_cantitate;
		}
		else {
			cout << "Id invalid." << endl;
		}
	}
	size_t getnringrediente() 
	{
		return ingrediente.size();
	}

	~reteta()
	{

	}
	const vector<pair<materieprima, float>>& getingrediente() const
	{
		return ingrediente;
	}
	vector<pair<materieprima, float>>& getingredientemod()
	{
		return ingrediente;
	}

};
void salvareStoc(const vector<materieprima>& stoc) 
{
	ofstream file("stoc_materie_prima.bin", ios::out | ios::binary);

	if (!file.is_open()) 
	{
		cout << "Eroare la deschiderea fisierului pentru salvare." << endl;
		return;
	}

	size_t numItems = stoc.size();
	file.write(reinterpret_cast<const char*>(&numItems), sizeof(numItems));

	for (const auto& materie : stoc) 
	{
		const string& denumire = materie.getdenumire();
		size_t lungimeDenumire = denumire.size();
		file.write(reinterpret_cast<const char*>(&lungimeDenumire), sizeof(lungimeDenumire));
		file.write(denumire.c_str(), lungimeDenumire);

		float cantitate = materie.getcantitate();
		file.write(reinterpret_cast<const char*>(&cantitate), sizeof(cantitate));
	}

	file.close();
}
class preparate
{
private:
	string provenienta;
	char* nume;
	reteta retet;
public:
	bool FermaInTotalitate() const 
	{
		return retet.verificareFerma();
	}
	preparate(const char* den, const reteta& reteta, const string& prov) : retet(reteta), provenienta(prov) 
	{
		if (retet.getnringrediente() == 0) 
		{
			cout << "Reteta nu exista." << endl;
		}
		if (den && den[0] != '\0') 
		{
			nume = new char[strlen(den) + 1];
			strcpy_s(nume, strlen(den) + 1, den);
		}
		else 
		{
			nume = new char[1];
			nume[0] = '\0';
		}
	}

	string getprovenienta() const 
	{
		return provenienta;
	}

	const reteta& getreteta() const 
	{
		return retet;
	}

	void setnume(const char* num) 
	{
		if (num) 
		{
			delete[] nume;
			nume = new char[strlen(num) + 1];
			strcpy_s(nume, strlen(num) + 1, num);
		}
	}

	void setreteta(reteta& ret) 
	{
		if (ret.getnringrediente() > 0)
		{
			retet = ret;
		}
		else 
		{
			cout << "Reteta trebuie sa contina cel putin un ingredient.";
		}
	}
	~preparate()
	{
		delete[] nume;
	}

	void afisare() const
	{
		cout << "Nume: " << nume << endl;
	}
	preparate(const char* den, const reteta& reteta) : retet(reteta)
	{
		if (retet.getnringrediente() == 0) 
		{
			cout << "Reteta nu exista." << endl;
		}
		if (den && den[0] != '\0') {
			nume = new char[strlen(den) + 1];
			strcpy_s(nume, strlen(den) + 1, den);
		}
		else 
		{
			nume = new char[1];
			nume[0] = '\0';
		}
	}
	preparate(const preparate& p) : retet(p.retet),provenienta(p.provenienta)
	{
		if (p.nume) 
		{
			nume = new char[strlen(p.nume) + 1];
			strcpy_s(nume, strlen(p.nume) + 1, p.nume);
		}
		else 
		{
			nume = nullptr;
		}
	}
	preparate() :nume() {}
	const char* getnume() const
	{
		return nume ? nume : "";
	}
	preparate& operator=(preparate& p)
	{
		if (this != &p)
		{
			delete[] nume;
			if (p.nume) 
			{
				nume = new char[strlen(p.nume) + 1];
				strcpy_s(nume, strlen(p.nume) + 1, p.nume);
			}
			else 
			{
				nume = nullptr;
			}
			retet = p.retet;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const preparate& p)
	{
		out << "Nume preparat: " << (p.nume ? p.nume : "") << endl;
		out << "Reteta:" << endl << p.retet;
		return out;
	}

	friend istream& operator>>(istream& in, preparate& p)
	{
		char buffer[100];
		cout << "Nume preparat: ";
		in.getline(buffer, sizeof(buffer));
		p.setnume(buffer);
		return in;
	}
};
class Comanda
{
private:
	string numePreparat;
	Reteta retet;
	vector<preparate> prep;
public:
	Comanda () {}
	const vector<preparate>& getPreparate() const 
	{
		return prep;
	}
	const vector<preparate>& getprep() const 
	{
		return prep;
	}
	Comanda(const string& nume) : numePreparat(nume) {}
	string getNumePreparat() const 
	{
		return numePreparat;
	}
	Comanda(const string& nume, const Reteta& ret) : numePreparat(nume), retet(ret) {}
};
void salveazaComenziInFisier(const vector<Comanda>& comenzi, const string& numeFisier) {
	ofstream file(numeFisier, ios::binary);
	if (!file) {
		cerr << "Nu s-a putut deschide fisierul pentru scriere." << endl;
		return;
	}

	size_t numarComenzi = comenzi.size();
	file.write(reinterpret_cast<const char*>(&numarComenzi), sizeof(numarComenzi));

	for (const auto& comanda : comenzi) 
	{
		size_t lungimeNume = comanda.getNumePreparat().size();
		file.write(reinterpret_cast<const char*>(&lungimeNume), sizeof(lungimeNume));
		file.write(comanda.getNumePreparat().c_str(), lungimeNume);
	}
	

	file.close();
}
class comanda
{
private:
	vector<preparate> preparatele;
	string numePreparat;
public:
	comanda(const string& nume) : numePreparat(nume) {}
	void afiseaza() const
	{
		for (const auto& prep : preparatele) 
		{
			cout << prep << endl;
		}
	}
	comanda(const comanda& p) : preparatele(p.preparatele)
	{

	}
	const vector<preparate>& getprep() const
	{
		return preparatele;
	}
	void setprep(const vector<preparate>& preparat)
	{
		if (!preparat.empty()) 
		{
			preparatele = preparat;
		}
		else 
		{
			cout << "Vectorul este gol" << endl;
		}
	}
	void adaugapreparat(const preparate& p)
	{
		preparatele.push_back(p);
	}
	comanda() {}
	comanda(const vector<preparate>& prepar) : preparatele(prepar) {}
	comanda(comanda& p) :preparatele(p.preparatele) {}
	comanda& operator=(comanda& p)
	{
		if (this != &p)
		{
			preparatele = p.preparatele;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const comanda& c)
	{
		for (const auto& prep : c.preparatele)
		{
			out << prep << endl;
		}
		return out;
	}

	friend istream& operator>>(istream& in, comanda& c)
	{
		cout << "Introduceti preparatele din comanda:" << endl;
		preparate prep;
		in >> prep;
		c.adaugapreparat(prep);
		return in;
	}
	string getNumePreparat() const {
		return numePreparat;
	}
};
class restaurant
{
private:
	vector<materieprima> stoc;
	vector<comanda> comenzi;
	vector<preparate> prep;
	static const int maxim = 15;
public:

	void adaugacomanda(const comanda& com)
	{
		if (comenzi.size() < maxim) {
			comenzi.push_back(com);
		}
		else
		{
			cout << "Numarul maxim de comenzi a fost atins." << endl;
			exit(3);
		}
	}

	void afiseaza() const
	{
		cout << "Stocul materiilor prime:" << endl;
		for (const auto& materie : stoc)
		{
			cout << materie.getdenumire() << " " << materie.getcantitate() << endl;
		}

		for (const auto& prep : prep)
		{
			cout << "Nume: " << prep.getnume() << endl;
			prep.getreteta().afiseaza();
		}

		cout << "Lista de comenzi:" << endl;
		for (const auto& comanda : comenzi)
		{
			comanda.afiseaza();
		}
	}

	const vector<preparate>& getprep() const
	{
		return prep;
	}
	const vector<materieprima>& getstoc() const
	{
		return stoc;
	}
	void setstoc(const vector<materieprima>& stooc)
	{
		if (stooc.size() <= maxim) 
		{
			stoc = stooc;
		}
		else 
		{
			cout << "Stoc prea mare" << endl;
		}
	}
	void adaugaMateriePrima(const materieprima& materie)
	{
		if (stoc.size() < materieprima::gettotalmat())
		{
			stoc.push_back(materie);
		}
		else
		{
			cout << "Stocul maxim de materii prime a fost atins." << endl;
		}
	}

	const vector<comanda>& getcomenzi() const 
	{
		return comenzi;
	}
	void setcomenzi(const vector<comanda>& comenz)
	{
		if (comenz.size() <= maxim)
		{
			comenzi = comenz;
		}
		else 
		{
			cout << "Numarul de comenzi este prea mare." << endl;
		}
	}
	restaurant() {}
	restaurant(const vector<materieprima>& stooc, const vector<comanda>& comenz)
		: stoc(stooc), comenzi(comenz)
	{
		if (stooc.size() > maxim || comenz.size() > maxim)
		{
			cout << "Numarul maxim de comenzi sau stocul este prea mare." << endl;
		}
	}
	restaurant(restaurant& p) :stoc(p.stoc), comenzi(p.comenzi) {}
	restaurant& operator=(restaurant& p)
	{
		if (this != &p)
		{
			stoc = p.stoc;
			comenzi = p.comenzi;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const restaurant& rest)
	{
		out << "Stoc: " << endl;
		for (const auto& d : rest.stoc)
		{
			out << d << endl;
		}

		out << "Comenzi: " << endl;
		for (const auto& comanda : rest.comenzi)
		{
			out << comanda << endl;
		}

		return out;
	}
	friend istream& operator>>(istream& in, restaurant& rest)
	{
		cout << "Introduceti detaliile pentru stoc:" << endl;
		int nrstoc;;
		cout << "Numar de ingrediente in stoc: ";
		in >> nrstoc;

		rest.stoc.clear();
		for (int i = 0; i < nrstoc; ++i)
		{
			materieprima mat;
			in >> mat;
			rest.stoc.push_back(mat);
		}
		cout << "Introduceti detaliile pentru comenzi:" << endl;
		int nrcomenzi;
		cout << "Numarul de comenzi: ";
		in >> nrcomenzi;

		rest.comenzi.clear();
		for (int i = 0; i < nrcomenzi; ++i)
		{
			comanda comandaaa;
			in >> comandaaa;
			rest.comenzi.push_back(comandaaa);
		}

		return in;
	}
	~restaurant()
	{
		comenzi.clear();
		stoc.clear();
	}

	bool verificaDisponibilitate(const reteta& retetacomanda)
	{
		const auto& ingrediente = retetacomanda.getingrediente();

		for (const auto& ingredient : ingrediente) 
		{
			bool disponibil = false;

			for (const auto& materie : stoc) 
			{
				if (materie.getdenumire() == ingredient.first.getdenumire()) 
				{
					if (materie.getcantitate() >= ingredient.second) 
					{
						disponibil = true;
						break;
					}
					else 
					{
						cout << "Nu exista suficienta cantitate de " << materie.getdenumire() << " in stoc." << endl;
						return false;
					}
				}
			}

			if (!disponibil)
			{
				cout << "Nu exista " << ingredient.first.getdenumire() << " in stoc." << endl;
				return false;
			}
		}
		for (const auto& ingredient : ingrediente) 
		{
			for (auto& materie : stoc) 
			{
				if (materie.getdenumire() == ingredient.first.getdenumire()) 
				{
					if (materie.getcantitate() >= ingredient.second) 
					{
						materie.setcantitate(materie.getcantitate() - ingredient.second);
					}
					else 
					{
						cout << "Nu există suficientă cantitate de " << materie.getdenumire() << " în stoc." << endl;
					}
					break;
				}
			}
		}

		return true;
	}

	void lanseazaComanda(const comanda& com)
	{
		const vector<preparate>& preparatele = com.getprep();
		for (const auto& preparat : preparatele)
		{
			const reteta& retetacomanda = preparat.getreteta();
			if (verificaDisponibilitate(retetacomanda))
			{
				cout << "Comanda a fost realizata." << endl;
			}
			else
			{
				cout << "Comanda nu poate fi realizata din cauza lipsei de materie prima in stoc." << endl;
			}
		}
	}
	void afiseazaMateriiPrime() const 
	{
		cout << "Stocul materiilor prime:" << endl;
		for (const auto& materie : stoc)
		{
			cout << "Nume: " << materie.getdenumire() << ", Cantitate: " << materie.getcantitate() << endl;
		}
	}
	restaurant(const vector<materieprima>& stoc) : stoc(stoc) {}
	void adaugaPreparat(const preparate& preparedDish)
	{
		prep.push_back(preparedDish);
	}
};
class MateriePrima 
{

public:
	static unordered_map<int, string> numeIngredient;
};

unordered_map<int, string> MateriePrima::numeIngredient = 
{
	{0, "Zahar"},
	{1, "Faina"},
	{2, "Oua"},
	{3, "Ulei"},
	{4, "Carne"},
	{5, "Lapte"},
	{6, "Legume"},
	{7, "Paste"},
	{8, "Sos"},
	{9, "CarneHamburger"},
	{10,"Paine"},
	{11,"Rosii"}
};
void salvarePrepVector(const vector<pair<string, Reteta>>& prepVector) 
{
	ofstream file("prepVector.bin", ios::out | ios::binary);

	if (!file.is_open()) 
	{
		cout << "Eroare la deschiderea fisierului pentru salvare." << endl;
		return;
	}

	size_t numItems = prepVector.size();

	file.write(reinterpret_cast<const char*>(&numItems), sizeof(numItems));

	for (const auto& elem : prepVector) 
	{
		size_t lungimeNume = elem.first.length();
		file.write(reinterpret_cast<const char*>(&lungimeNume), sizeof(lungimeNume));
		file.write(elem.first.c_str(), lungimeNume);
		string reteta = "Reteta preparatului"; 
		size_t lungimeReteta = reteta.length();
		file.write(reinterpret_cast<const char*>(&lungimeReteta), sizeof(lungimeReteta));
		file.write(reteta.c_str(), lungimeReteta);
	}

	file.close();
}
void afiseazaComenziFrumos(const vector<vector<string>>& comenziPreparate, int nrcom) {
	for (int i = 0; i < nrcom; ++i) {
		cout << "Comanda " << i << ": ";
		for (size_t j = 0; j < comenziPreparate[i].size(); ++j) {
			cout << comenziPreparate[i][j];
			if (j < comenziPreparate[i].size() - 1) {
				cout << ", ";
			}
		}
		cout << endl;
	}
}
void afiseazaDetaliiRestaurant(vector<vector<string>>& comenzi,vector<materieprima>& stocmaterie, int nrcom)
{
	cout << "\nStocul de materii prime: " << endl;
	for (const auto& materie : stocmaterie)
	{
		cout << "Nume: " << materie.getdenumire() << ", Cantitate: " << materie.getcantitate() << endl;
			cout<< "Provenienta: " << materie.getprovenienta() << endl; 
	}

	cout << "\nLista de comenzi: " << endl;
	afiseazaComenziFrumos(comenzi,nrcom);
}

bool verificaDisponibilitate(const Reteta& retetacomanda, const vector<materieprima>& stoc) 
{
	const map<Ingredient, float>& ingredienteReteta = retetacomanda.getIngrediente();

	for (const auto& ingredient : ingredienteReteta) 
	{
		bool disponibil = false;

		for (const auto& materie : stoc) 
		{
			if (materie.getdenumire() == MateriePrima::numeIngredient[static_cast<int>(ingredient.first)]) 
			{
				if (materie.getcantitate() >= ingredient.second) 
				{
					disponibil = true;
					break;
				}
				else 
				{
					cout << "Nu exista suficienta cantitate de " << materie.getdenumire() << " in stoc." << endl;
					return false;
				}
			}
		}

		if (!disponibil) 
		{
			cout << "Nu exista " << MateriePrima::numeIngredient[static_cast<int>(ingredient.first)] << " in stoc." << endl;
			return false;
		}
	}

	return true;
}
void adaugaComanda(vector<vector<string>>& comenziPreparate, vector<pair<string, Reteta>>& prepVector, vector<materieprima>& stocmaterie, map<string, float>& datam, int& nrcom) {
	cout << "Adauga o comanda:" << endl;
	for (size_t i = 0; i < prepVector.size(); ++i) {
		cout << i << ". " << prepVector[i].first << endl;
		prepVector[i].second.afiseazaReteta(prepVector[i].first);
		cout << "------------------------" << endl;
	}
	cout << prepVector.size() << ". Terminare comanda" << endl;

	vector<string> comandaCurenta;
	int index;
	do {
		cout << "Introduceti indexul preparatului dorit: ";
		cin >> index;
		if (index >= 0 && index < prepVector.size()) {
			if (verificaDisponibilitate(prepVector[index].second, stocmaterie)) {
				comandaCurenta.push_back(prepVector[index].first);
				const auto& ingredienteReteta = prepVector[index].second.getIngrediente();
				for (const auto& ingredient : ingredienteReteta) {
					string numeIngredienet = numeIngredient[ingredient.first];
					datam[numeIngredienet] += ingredient.second;
				}
				cout << "Comanda a fost adaugata." << endl;
			}
			else {
				cout << "Comanda nu poate fi realizata din cauza lipsei de materie prima in stoc." << endl;
			}
		}
		else if (index == prepVector.size()) {
			comenziPreparate.push_back(comandaCurenta);
			comandaCurenta.clear();
			nrcom++;
		}
		else {
			cout << "Index invalid. Va rugam introduceti un numar intre 0 si " << prepVector.size() << endl;
		}
	} while (index != prepVector.size());

	afiseazaComenziFrumos(comenziPreparate, nrcom);
	salvareStoc(stocmaterie);
}


void generareRaportComplet(const restaurant& restaurantObj, vector<materieprima> stocmaterie, vector<pair<string, Reteta>> prepVector) {
	unordered_map<string, string> provenienteMateriiPrime;
	unordered_map<string, float> caloriiPerUnitate;

	for (const auto& materie : stocmaterie) 
	{
		provenienteMateriiPrime[materie.getdenumire()] = materie.getprovenienta();
		caloriiPerUnitate[materie.getdenumire()] = materie.getcalo();
	}
	ofstream raportFile("raport.txt", ios::app); 

	if (!raportFile.is_open()) 
	{
		cerr << "Nu s-a putut deschide fisierul raport.txt pentru scriere." << endl;
		return;
	}
	bool continua = true;
	while (continua) 
	{
		cout << "\nSelecteaza o optiune:" << endl;
		cout << "1. Care sunt ingredientele de la ferma?" << endl;
		cout << "2. Care sunt preparatele obtinute din ingrediente de la ferma?" << endl;
		cout << "3. Care este numarul de calorii al fiecarui preparat?" << endl;
		cout << "4. Iesire" << endl;
		cout << "Alege o optiune: ";

		int optiune;
		cin >> optiune;

		switch (optiune) 
		{
		case 1:
			raportFile << "Materii prime obtinute de la Ferma:\n";
			cout << "Materii prime obtinute de la Ferma:" << endl;
			for (const auto& materie : stocmaterie) 
			{
				if (materie.getprovenienta() == "Ferma") 
				{
					cout << "Nume materie prima: " << materie.getdenumire()
						<< ", Cantitate: " << materie.getcantitate() << endl;
					raportFile << "Nume materie prima: " << materie.getdenumire() << " , Cantitate: " << materie.getcantitate() << endl;
				}
			}
			raportFile.flush();
			continua = false;
			break;
		case 2:
			raportFile << "\nPreparate cu ingrediente in totalitate de la Ferma:\n";
			cout << "\nPreparate cu ingrediente in totalitate de la Ferma:" << endl;
			for (const auto& preparat : prepVector)
			{
				const Reteta& retetaPreparat = preparat.second;
				bool allIngredientsFromFarm = true;

				for (const auto& IngredientPereche : retetaPreparat.getIngrediente()) 
				{
					string numeIngredient = retetaPreparat.getProvenientaIngredient(IngredientPereche.first);
					auto it = provenienteMateriiPrime.find(numeIngredient);

					if (it != provenienteMateriiPrime.end() && it->second != "Ferma") 
					{
						allIngredientsFromFarm = false;
						break;
					}
				}

				if (allIngredientsFromFarm) 
				{
					cout << "Nume preparat: " << preparat.first << endl;
					raportFile << "Nume preparat: " << preparat.first << endl;
				}
				raportFile.flush();
			}
			continua = false;
			break;
		case 3:
			raportFile << "\nNumarul de calorii al fiecarui preparat:\n";
			cout << "\nNumarul de calorii al fiecarui preparat:" << endl;
			for (const auto& preparat : prepVector)
			{
				const Reteta& retetaPreparat = preparat.second;
				float totalCalorii = 0.0f;

				for (const auto& IngredientPereche : retetaPreparat.getIngrediente())
				{
					string numeIngredient = MateriePrima::numeIngredient[static_cast<int>(IngredientPereche.first)];
					float cantitateIngredient = IngredientPereche.second;
					float caloriiIngredient = caloriiPerUnitate[numeIngredient];

					totalCalorii += caloriiIngredient * cantitateIngredient;
				}

				cout << "Nume preparat: " << preparat.first << ", Calorii totale: " << totalCalorii << " calorii" << endl;
				raportFile << "Nume preparat: " << preparat.first << " , Calorii totale: " << totalCalorii << " calorii" << endl;
			}
			raportFile.flush();
			continua = false;
			break;
		case 4:
			continua = false;
			break;
		default:
			cout << "Optiune invalida! Te rog sa alegi o optiune valida." << endl;
		}
		raportFile.close();
	}
}



void scrieProvenientaMateriiPrime(const restaurant& restaurantObj, const string& numeFisier)
{
	ofstream file(numeFisier);
	if (!file.is_open()) 
	{
		cout << "Nu s-a putut deschide fisierul pentru scriere." << endl;
		return;
	}

	for (const auto& materie : restaurantObj.getstoc()) 
	{
		file << materie.getdenumire() << ", " << materie.getprovenienta() << endl;
	}

	file.close();
}
void raportPopularitatePreparate(vector<vector<string>>& comenzi) {
	unordered_map<string, int> contorPreparate;

	for (const auto& comanda : comenzi) {
		
		for (const auto& preparat : comanda) {
			contorPreparate[preparat]++;
		}
	}

	string preparatPopular;
	int numarMaximComenzi = 0;

	for (const auto& pereche : contorPreparate) {
		if (pereche.second > numarMaximComenzi) {
			numarMaximComenzi = pereche.second;
			preparatPopular = pereche.first;
		}
	}

	cout << "Preparatul cel mai popular: " << preparatPopular
		<< " cu " << numarMaximComenzi << " comenzi." << endl;
}

void raportConsumMateriiPrime(const vector<materieprima>& stocMateriiPrime, const map<string, float>& datam)
{
	cout << "Raport Consum Materii Prime:" << endl;
	for (const auto& materie : stocMateriiPrime) 
	{
		auto it = datam.find(materie.getdenumire());
		float cantitateConsumata = (it != datam.end()) ? it->second : 0;
		cout << "Materie Prima: " << materie.getdenumire() << ", Cantitate Consumata: " << cantitateConsumata << endl;
	}
}
void meniu_datamining(vector<vector<string>>& comenzi, vector <materieprima>& stoc, map<string, float>& datam)
{
	int optiune;
	bool continua = true;
	while (continua) 
	{
		cout << "1. Cel mai des comandat preparat. " << endl;
		cout << "2. Consum de materii prime. " << endl;
		cout << "3. Intoarcere la meniu principal." << endl;
		cout << "Alege o optiune: ";
		cin >> optiune;
		switch (optiune)
		{
		case 1:
			raportPopularitatePreparate(comenzi);
			break;
		case 2:
			raportConsumMateriiPrime(stoc, datam);
			break;
		case 3:
			continua = false; 
			break;
		default:
			cout << "Optiune invalida! Te rog sa alegi o optiune valida." << endl;
		}
	}
}
vector<materieprima> incarcacsv(vector<materieprima> stocmaterie)
{
	string fisiermaterii;
		cout << "Numele fisierului din care vom incarca stocul de materii prime: ";
		cin >> fisiermaterii;
		stocmaterie = citesteMateriiPrimeDinCSV(fisiermaterii);
		return stocmaterie;
}
vector<string> citestePreparateDinCsv(const string& numefisier) 
{
	vector<string> numePreparate;
	ifstream file(numefisier);
	string linie;

	if (!file.is_open()) 
	{
		cerr << "Nu s-a putut deschide fisierul " << numefisier << endl;
		return numePreparate;
	}

	if (getline(file, linie) && !linie.empty()) 
	{
		stringstream ss(linie);
		string numePreparat;

		while (getline(ss, numePreparat, ',')) 
		{
			numePreparate.push_back(numePreparat);
		}
	}

	return numePreparate;
}

Reteta citesteRetetaDinCsv(const string& numefisier) 
{
	Reteta reteta;
	ifstream file(numefisier);
	string linie;

	if (!file.is_open()) 
	{
		cerr << "Nu s-a putut deschide fisierul " << numefisier << endl;
		return reteta;
	}

	while (getline(file, linie)) 
	{
		if (linie.empty()) continue;
		stringstream ss(linie);
		int id;
		float cantitate;

		ss >> id;
		if (ss.fail()) 
		{
			cerr << "Eroare la citirea ID-ului ingredientului din linia: " << linie << endl;
			continue;
		}
		ss.ignore(numeric_limits<streamsize>::max(), ',');

		ss >> cantitate;
		if (ss.fail())
		{
			cerr << "Eroare la citirea cantitatii ingredientului din linia: " << linie << endl;
			continue;
		}

		reteta.adaugaingredient(id, cantitate);
	}

	return reteta;
}
vector<pair<string, Reteta>> csvprep()
{
	string fisierprep;
	cout << "Numele fisierului din care incarcam preparatele: ";
	cin >> fisierprep;

	vector<string> preparate = citestePreparateDinCsv(fisierprep);
	vector<pair<string, Reteta>> prepVector;

	for (const auto& numePreparat : preparate)
	{
		string fisierReteta = numePreparat + ".csv";
		Reteta reteta = citesteRetetaDinCsv(fisierReteta);
		prepVector.push_back(make_pair(numePreparat, reteta));
	}

	return prepVector;
}

int main()
{
	vector<vector<string>> toateComenzile;
	int contor = 0;
	int nrcomenzi = 0;
	map<string, float> datam;
	Reteta insuficienta; Reteta pastele; Reteta cioorba; Reteta reteta1; Reteta reteta2; Reteta burger;
	restaurant rest;
	vector<pair<string, Reteta>> prepVector;
	ifstream preparateFile("preparate.txt");
	if (preparateFile.is_open())
	{
		string numePreparat;
		while (getline(preparateFile, numePreparat)) 
		{
			Reteta reteta;
			reteta.populeazaRetetaDinFisier(numePreparat);
			prepVector.push_back({ numePreparat, reteta });

		}
		preparateFile.close();
	}
	else 
	{
		cout << "Nu s-a putut deschide fisierul cu numele preparatelor." << endl;
	}
	insuficienta.populeazaRetetaDinFisier("oua cu rosii");
	pastele.populeazaRetetaDinFisier("paste");
	cioorba.populeazaRetetaDinFisier("ciorba");
	reteta1.populeazaRetetaDinFisier("prajitura");
	reteta2.populeazaRetetaDinFisier("omleta");
	burger.populeazaRetetaDinFisier("burger");
	int optiune;
	bool continua = true;
	vector<int>nrcome(prepVector.size()+1, 0);
	bool c = true;
	vector<Comanda> comenzi;
	vector<materieprima> stocmaterie;
	ifstream file("materii_prime.txt");
	if (file.is_open()) 
	{
		string nume;
		string provenienta;
		float cantitate;
		float calorii;  

		while (file >> nume >> cantitate >> provenienta >> calorii) 
		{
			materieprima materie(nume.c_str(), cantitate, provenienta, calorii);
			stocmaterie.push_back(materie);
		}

		file.close();
	}
	else 
	{
		cout << "Fisierul nu s-a putut deschide." << endl;
	}
	while (continua) 
	{
		cout << "Meniu:" << endl;
		cout << "1. Afiseaza detalii restaurant" << endl;
		cout << "2. Adauga o comanda" << endl;
		cout << "3. Generare raport" << endl;
		cout << "4. Data mining" << endl;
		cout << "5. Incarca date din fisiere csv." << endl;
		cout << "6. Iesire" << endl;
		cout << "Alege o optiune: ";
		cin >> optiune;

		switch (optiune) 
		{
		case 1:
			afiseazaDetaliiRestaurant(toateComenzile, stocmaterie,nrcomenzi);
			break;
		case 2:
			adaugaComanda(toateComenzile, prepVector, stocmaterie, datam,nrcomenzi);
			break;
		case 3:
			generareRaportComplet(rest, stocmaterie, prepVector);
			break;
		case 4:
			meniu_datamining(toateComenzile, stocmaterie, datam);
			break;
		case 5:
			while (c)
			{
				int otp;
				c = true;
				cout << "1. Populeaza stocul de materii prime din csv." << endl;
				cout << "2. Populeaza meniul cu preparate si retele" << endl;
				cout << "3. Revenire meniu principal. " << endl;
				cout << "Introduceti optiunea: ";
				cin >> otp;
				switch (otp)
				{
				case 1:
					stocmaterie = incarcacsv(stocmaterie);
					break;
				case 2:
					prepVector = csvprep();
				case 3:
					c = false;
					break;
				}
				
			}
			break;
		case 6:
			salveazaComenziInFisier(comenzi, "comenzi.bin");
			continua = false;
			break;
		default:
			cout << "Optiune invalida!" << endl;
			break;
		}
	}

	cout << "La revedere!" << endl;
	return 0;
}
