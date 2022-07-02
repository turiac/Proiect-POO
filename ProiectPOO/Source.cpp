#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include<map>
#include<set>
using namespace std;
//Tema aleasa: Componentele unui Calculator
class Abstracta
{
public:
	virtual void detalii() = 0;
	virtual void denumire() = 0;
};

class Procesor
{
private:
	const string socket;
	string tipCPU;
	int nuclee;
	int nrCache;
	float* memorieCache;
	float pretProcesor;
	static float frecventaMaxima;
public:
	Procesor() : socket("0")//constr fara param
	{
		this->tipCPU = "NA";
		this->nuclee = 0;
		this->pretProcesor = 0;
		this->nrCache = 0;
		this->memorieCache = new float[nrCache];
		this->memorieCache[0] = 0;
	}
	Procesor(string socket, string tipCPU, int nuclee, int nrCache, float* memorieCache, float pretProcesor) : socket(socket)//constr cu toti param
	{
		this->tipCPU = tipCPU;
		this->nuclee = nuclee;
		this->pretProcesor = pretProcesor;
		this->nrCache = nrCache;
		this->memorieCache = new float[nrCache];
		if (memorieCache != NULL && nrCache != 0)
			for (int i = 0; i < nrCache; i++)
			{
				this->memorieCache[i] = memorieCache[i];
			}
		else
		{
			this->memorieCache = NULL;
			this->nrCache = 0;
		}
	}
	Procesor(const Procesor& p) : socket(p.socket)//constr de copiere
	{
		this->tipCPU = p.tipCPU;
		this->nuclee = p.nuclee;
		this->pretProcesor = p.pretProcesor;
		this->nrCache = p.nrCache;
		this->memorieCache = new float[p.nrCache];
		if (memorieCache != NULL && nrCache != 0)
			for (int i = 0; i < p.nrCache; i++)
			{
				this->memorieCache[i] = p.memorieCache[i];
			}
		else
		{
			this->memorieCache = NULL;
			this->nrCache = 0;
		}
	}
	Procesor& operator=(Procesor& p)//operator=
	{
		if (this->memorieCache)
		{
			delete[] this->memorieCache;
		}
		this->tipCPU = p.tipCPU;
		this->nuclee = p.nuclee;
		this->pretProcesor = p.pretProcesor;
		this->nrCache = p.nrCache;
		this->memorieCache = new float[p.nrCache];
		if (memorieCache != NULL && nrCache != 0)
			for (int i = 0; i < p.nrCache; i++)
			{
				this->memorieCache[i] = p.memorieCache[i];
			}
		else
		{
			this->memorieCache = NULL;
			this->nrCache = 0;
		}
		return *this;
	}
	~Procesor()//destructor
	{
		/*cout << "\nApel Destructor";
		if (this->memorieCache != NULL)
			delete[] this->memorieCache;*/
	}
	friend ostream& operator<<(ostream& out, Procesor& p)//operator<<
	{
		out << "\nProcesorul costa " << p.pretProcesor << " lei, este marca " << p.tipCPU << " are socketul " << p.socket << ", un numar de " << p.nuclee << " nuclee, un numar de " << p.nrCache << " cache";
		for (int i = 0; i < p.nrCache; i++)
		{
			out << endl << i << ": " << p.memorieCache[i];
		}
		return out;
	}
	friend istream& operator>>(istream& in, Procesor& p)//operator>>
	{
		cout << "\nPret procesor: ";
		in >> p.pretProcesor;
		cout << "Tip CPU : ";
		in >> p.tipCPU;
		cout << "Nuclee: ";
		in >> p.nuclee;
		cout << "Numar Cache: ";
		in >> p.nrCache;
		if (p.memorieCache)
		{
			delete[] p.memorieCache;
		}
		p.memorieCache = new float[p.nrCache];
		for (int i = 0; i < p.nrCache; i++)
		{
			cout << i << ": ";
			in >> p.memorieCache[i];
		}
		return in;
	}
	void afisarePR()
	{
		cout << "\nProcesorul costa " << this->pretProcesor << " lei, este marca " << this->tipCPU << " are socketul " << this->socket << ", un numar de " << this->nuclee << " nuclee, un numar de " << this->nrCache << " cache ";
		if (this->memorieCache != NULL)
			for (int i = 0; i < this->nrCache; i++)
			{
				cout << i << ": " << this->memorieCache[i] << " MB ";
			}
		else cout << "-" << endl;
	}
	float& operator[](int poz)//op pentru indexare
	{
		return this->memorieCache[poz];
	}
	Procesor& operator++() //op ++
	{
		int nr = this->nrCache + 1;
		float* copie = new float[nr];
		for (int i = 0; i < this->nrCache; i++)
		{
			copie[i] = this->memorieCache[i];
		}
		copie[nr - 1] = copie[nr - 2];
		if (this->memorieCache)
		{
			delete[]this->memorieCache;
		}
		this->nrCache = nr;
		this->memorieCache = new float[this->nrCache];
		for (int i = 0; i < this->nrCache; i++)
		{
			this->memorieCache[i] = copie[i];
		}
		return *this;
	}
	bool operator!() //op pentru negatie
	{
		if (this->pretProcesor > 2500)
		{
			return true;
		}
		else return false;
	}
	explicit operator int()//operator cast explicit de la float la int
	{
		return (int)this->pretProcesor;
	}
	Procesor& operator+(float x)//operator +
	{
		this->pretProcesor += x;
		return *this;
	}
	explicit operator float()//operator cast explicit
	{
		return (float)this->nuclee;
	}
	bool operator==(Procesor& p)//operator pentru testarea egalitatii
	{
		if (this->pretProcesor == p.pretProcesor)
		{
			return true;
		}
		else return false;
	}
	bool operator >=(Procesor& p)
	{
		if (this->pretProcesor >= p.pretProcesor)
		{
			return true;
		}
		else return false;
	}
	friend ofstream& operator<<(ofstream& out, Procesor& p)
	{
		out << p.tipCPU << endl;
		out << p.socket << endl;
		out << p.nuclee << endl;
		out << p.nrCache;
		for (int i = 0; i < p.nrCache; i++)
		{
			out << endl << p.memorieCache[i];
		}
		out << endl;
		out << p.pretProcesor << endl;
		return out;
	}
	friend ifstream& operator>>(ifstream& in, Procesor& p)
	{
		in >> p.pretProcesor;
		in >> p.tipCPU;
		in >> p.nuclee;
		in >> p.nrCache;
		if (p.memorieCache)
		{
			delete[] p.memorieCache;
		}
		p.memorieCache = new float[p.nrCache];
		for (int i = 0; i < p.nrCache; i++)
		{
			in >> p.memorieCache[i];
		}
		return in;
	}
};
float Procesor::frecventaMaxima = 5.0;



class PlacaDeBaza : public Procesor
{
private:
	const int tipmemorie;
	string nume;
	int nrfrecvente;
	int* frecventeSuportate;
	int socluProcesor;
	float pretPlacaDeBaza;
	static int MemorieMaximaRAM;
public:
	PlacaDeBaza() : tipmemorie(0)//constr fara param
	{
		this->nume = "NA";
		this->pretPlacaDeBaza = 0;
		this->socluProcesor = 0;
		this->nrfrecvente = 0;
		this->frecventeSuportate = new int[nrfrecvente];
		this->frecventeSuportate[0] = 0;
	}
	PlacaDeBaza(int tipmemorie, string nume, int nrfrecvente, int* frecventeSuportate, int socluProcesor, float pretPlacaDeBaza) : tipmemorie(tipmemorie)//constr cu toti param
	{
		this->nume = nume;
		this->socluProcesor = socluProcesor;
		this->pretPlacaDeBaza = pretPlacaDeBaza;
		this->nrfrecvente = nrfrecvente;
		this->frecventeSuportate = new int[nrfrecvente];
		if (frecventeSuportate != NULL && nrfrecvente != 0)
			for (int i = 0; i < nrfrecvente; i++)
			{
				this->frecventeSuportate[i] = frecventeSuportate[i];
			}
		else
		{
			this->frecventeSuportate = NULL;
			this->nrfrecvente = 0;
		}
	}
	PlacaDeBaza(const PlacaDeBaza& b) : tipmemorie(b.tipmemorie)//constr de copiere
	{
		this->nume = b.nume;
		this->socluProcesor = b.socluProcesor;
		this->pretPlacaDeBaza = b.pretPlacaDeBaza;
		this->nrfrecvente = b.nrfrecvente;
		this->frecventeSuportate = new int[b.nrfrecvente];
		if (frecventeSuportate != NULL && nrfrecvente != 0)
			for (int i = 0; i < b.nrfrecvente; i++)
			{
				this->frecventeSuportate[i] = b.frecventeSuportate[i];
			}
		else
		{
			this->frecventeSuportate = NULL;
			this->nrfrecvente = 0;
		}
	}
	PlacaDeBaza& operator=(PlacaDeBaza& b)//operator=
	{
		if (this->frecventeSuportate)
		{
			delete[] this->frecventeSuportate;
		}
		this->nume = b.nume;
		this->socluProcesor = b.socluProcesor;
		this->pretPlacaDeBaza = b.pretPlacaDeBaza;
		this->nrfrecvente = b.nrfrecvente;
		this->frecventeSuportate = new int[b.nrfrecvente];
		if (frecventeSuportate != NULL && nrfrecvente != 0)
			for (int i = 0; i < b.nrfrecvente; i++)
			{
				this->frecventeSuportate[i] = b.frecventeSuportate[i];
			}
		else
		{
			this->frecventeSuportate = NULL;
			this->nrfrecvente = 0;
		}
		return *this;
	}
	~PlacaDeBaza()//destructor
	{
		/*cout << "\nApel destructor";
		if (frecventeSuportate != NULL)
			delete[] this->frecventeSuportate;*/
	}
	friend ostream& operator<<(ostream& out, PlacaDeBaza& b)//operator<<
	{
		out << "\nPlaca de baza " << b.nume << " costa " << b.pretPlacaDeBaza << " lei, suporta soclul " << b.socluProcesor << " si memoria DDR" << b.tipmemorie << ". Aceasta are un numar de " << b.nrfrecvente << " frecvente suportate ";
		for (int i = 0; i < b.nrfrecvente; i++)
		{
			cout << endl << i << ": " << b.frecventeSuportate[i] << " MHz ";
		}
		return out;
	}
	friend istream& operator>>(istream& in, PlacaDeBaza& b)//operator>>
	{
		cout << "\nPret placa de baza: ";
		cin >> b.pretPlacaDeBaza;
		cout << "Nume placa de baza: ";
		cin >> b.nume;
		cout << "Numar frecvente:";
		cin >> b.nrfrecvente;
		if (b.frecventeSuportate)
		{
			delete[] b.frecventeSuportate;
		}
		b.frecventeSuportate = new int[b.nrfrecvente];
		for (int i = 0; i < b.nrfrecvente; i++)
		{
			cout << i << ": ";
			in >> b.frecventeSuportate[i];
		}
		return in;
	}
	void afisarePB()
	{
		cout << "\nPlaca de baza " << this->nume << " costa " << this->pretPlacaDeBaza << " lei, suporta soclul " << this->socluProcesor << " si memoria DDR" << this->tipmemorie << ". Aceasta are un numar de " << this->nrfrecvente << " frecvente suportate ";
		if (this->frecventeSuportate != NULL)
			for (int i = 0; i < this->nrfrecvente; i++)
			{
				cout << i << ": " << this->frecventeSuportate[i] << " MHz ";
			}
		else cout << "-" << endl;
	}
	int& operator[](int poz)//op pentru indexare
	{
		return this->frecventeSuportate[poz];
	}
	bool operator!() //op pentru negatie
	{
		if (this->pretPlacaDeBaza > 800)
		{
			return true;
		}
		else return false;
	}
	PlacaDeBaza& operator++() //op ++
	{
		int nr = this->nrfrecvente + 1;
		int* copie = new int[nr];
		for (int i = 0; i < this->nrfrecvente; i++)
		{
			copie[i] = this->frecventeSuportate[i];
		}
		copie[nr - 1] = copie[nr - 2];
		if (this->frecventeSuportate)
		{
			delete[]this->frecventeSuportate;
		}
		this->nrfrecvente = nr;
		this->frecventeSuportate = new int[this->nrfrecvente];
		for (int i = 0; i < this->nrfrecvente; i++)
		{
			this->frecventeSuportate[i] = copie[i];
		}
		return *this;
	}
	PlacaDeBaza& operator+(float x)//operator +
	{
		this->pretPlacaDeBaza += x;
		return *this;
	}
	explicit operator float()//operator cast explicit
	{
		return (float)this->socluProcesor;
	}
	bool operator==(PlacaDeBaza& b)//operator pentru testarea egalitatii
	{
		if (this->pretPlacaDeBaza == b.pretPlacaDeBaza)
		{
			return true;
		}
		else return false;
	}
	explicit operator int()//operator cast explicit de la float la int
	{
		return (int)this->pretPlacaDeBaza;
	}
	bool operator >=(PlacaDeBaza& b)
	{
		if (this->pretPlacaDeBaza >= b.pretPlacaDeBaza)
		{
			return true;
		}
		else return false;
	}
	friend ofstream& operator<<(ofstream& out, PlacaDeBaza& b)//scriere in fisier txt
	{
		out << "\n" << b.nume << endl;
		out << b.pretPlacaDeBaza << endl;
		out << b.socluProcesor << endl;
		out << b.tipmemorie << endl;
		out << b.nrfrecvente;
		for (int i = 0; i < b.nrfrecvente; i++)
		{
			out << endl << b.frecventeSuportate[i];
		}
		out << endl;
		return out;
	}
	friend ifstream& operator>>(ifstream& in, PlacaDeBaza& b)
	{
		in >> b.nume;
		in >> b.pretPlacaDeBaza;
		in >> b.socluProcesor;
		if (b.frecventeSuportate)
		{
			delete[] b.frecventeSuportate;
		}
		b.frecventeSuportate = new int[b.nrfrecvente];
		for (int i = 0; i < b.nrfrecvente; i++)
		{
			in >> b.frecventeSuportate[i];
		}
		return in;
	}
};
int PlacaDeBaza::MemorieMaximaRAM = 128;



class RAM
{
private:
	const int frecventaRAM;
	int capacitateRAM;
	float pretRAM;
	char* numeRAM;
	int nrfrecvente;
	int* frecventeSuportate;
public:
	RAM() : frecventaRAM(0)//constr fara param
	{
		this->capacitateRAM = 0;
		this->pretRAM = 0;
		this->numeRAM = new char[strlen("NA") + 1];
		strcpy(this->numeRAM, "NA");
		this->nrfrecvente = 0;
		this->frecventeSuportate = new int[nrfrecvente];
		this->frecventeSuportate[0] = 0;
	}
	RAM(int frecventaRAM, int capacitateRAM, float pretRAM, const char* numeRAM, int nrfrecvente, int* frecventeSuportate) : frecventaRAM(3000)//constr cu toti param
	{
		this->capacitateRAM = capacitateRAM;
		this->pretRAM = pretRAM;
		this->numeRAM = new char[strlen(numeRAM) + 1];
		strcpy(this->numeRAM, numeRAM);
		this->nrfrecvente = nrfrecvente;
		this->frecventeSuportate = new int[nrfrecvente];
		if (frecventeSuportate != NULL && nrfrecvente != 0)
			for (int i = 0; i < nrfrecvente; i++)
			{
				this->frecventeSuportate[i] = frecventeSuportate[i];
			}
		else
		{
			this->frecventeSuportate = NULL;
			this->nrfrecvente = 0;
		}
	}
	RAM(const RAM& r) : frecventaRAM(r.frecventaRAM)//constr de copiere
	{
		this->capacitateRAM = r.capacitateRAM;
		this->pretRAM = r.pretRAM;
		this->numeRAM = new char[strlen(r.numeRAM) + 1];
		strcpy(this->numeRAM, r.numeRAM);
		this->nrfrecvente = r.nrfrecvente;
		this->frecventeSuportate = new int[r.nrfrecvente];
		if (frecventeSuportate != NULL && nrfrecvente != 0)
			for (int i = 0; i < r.nrfrecvente; i++)
			{
				this->frecventeSuportate[i] = r.frecventeSuportate[i];
			}
		else
		{
			this->frecventeSuportate = NULL;
			this->nrfrecvente = 0;
		}
	}
	RAM& operator=(RAM& r)//op=
	{
		if (this->numeRAM)
		{
			delete[] this->numeRAM;
		}
		this->capacitateRAM = r.capacitateRAM;
		this->pretRAM = r.pretRAM;
		this->numeRAM = new char[strlen(r.numeRAM) + 1];
		strcpy(this->numeRAM, r.numeRAM);
		this->nrfrecvente = r.nrfrecvente;
		this->frecventeSuportate = new int[r.nrfrecvente];
		if (frecventeSuportate != NULL && nrfrecvente != 0)
			for (int i = 0; i < r.nrfrecvente; i++)
			{
				this->frecventeSuportate[i] = r.frecventeSuportate[i];
			}
		else
		{
			this->frecventeSuportate = NULL;
			this->nrfrecvente = 0;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, RAM& r)//operator<<
	{
		out << "\nMemoria RAM are capacitatea de " << r.capacitateRAM << " GB, costa " << r.pretRAM << " lei si este marca " << r.numeRAM << ". Are un numar de " << r.nrfrecvente << " frecvente suportate ";
		for (int i = 0; i < r.nrfrecvente; i++)
		{
			cout << endl << i << ": " << r.frecventeSuportate[i] << " MHz ";
		}
		return out;
	}
	friend istream& operator>>(istream& in, RAM& r)//operator>>
	{
		if (r.numeRAM)
		{
			delete[] r.numeRAM;
		}
		cout << "\nCapacitatea RAM: ";
		in >> r.capacitateRAM;
		cout << "Pret RAM: ";
		in >> r.pretRAM;
		char buffer[20];
		cout << "Marca memorie RAM: ";
		in >> buffer;
		r.numeRAM = new char[strlen(buffer) + 1];
		strcpy(r.numeRAM, buffer);
		cout << "Numar frecvente:";
		cin >> r.nrfrecvente;
		if (r.frecventeSuportate)
		{
			delete[] r.frecventeSuportate;
		}
		r.frecventeSuportate = new int[r.nrfrecvente];
		for (int i = 0; i < r.nrfrecvente; i++)
		{
			cout << i << ": ";
			in >> r.frecventeSuportate[i];
		}
		return in;
	}
	void afisareRAM()
	{
		cout << "\nMemoria RAM are capacitatea de " << this->capacitateRAM << " GB, costa " << this->pretRAM << " lei si este marca " << this->numeRAM << ". Aceasta are un numar de " << this->nrfrecvente << " frecvente suportate ";
		if (this->frecventeSuportate != NULL)
			for (int i = 0; i < this->nrfrecvente; i++)
			{
				cout << i << ": " << this->frecventeSuportate[i] << " MHz ";
			}
		else cout << "-" << endl;
	}

	~RAM()//destructor
	{
		//	cout << "\nApel destructor";
		//	if (numeRAM && frecventeSuportate)
		//		delete[] this->numeRAM;
		//	delete[] this->frecventeSuportate;
	}

	int& operator[](int poz)//op pentru indexare
	{
		return this->frecventeSuportate[poz];
	}
	bool operator!() //op pentru negatie
	{
		if (this->pretRAM > 600)
		{
			return true;
		}
		else return false;
	}
	RAM& operator++() //op ++
	{
		int nr = this->nrfrecvente + 1;
		int* copie = new int[nr];
		for (int i = 0; i < this->nrfrecvente; i++)
		{
			copie[i] = this->frecventeSuportate[i];
		}
		copie[nr - 1] = copie[nr - 2];
		if (this->frecventeSuportate)
		{
			delete[]this->frecventeSuportate;
		}
		this->nrfrecvente = nr;
		this->frecventeSuportate = new int[this->nrfrecvente];
		for (int i = 0; i < this->nrfrecvente; i++)
		{
			this->frecventeSuportate[i] = copie[i];
		}
		return *this;
	}
	RAM& operator+(float x)//operator +
	{
		this->pretRAM += x;
		return *this;
	}
	explicit operator string()//operator cast explicit
	{
		return (string)this->numeRAM;
	}
	bool operator==(RAM& r)//operator pentru testarea egalitatii
	{
		if (this->pretRAM == r.pretRAM)
		{
			return true;
		}
		else return false;
	}
	bool operator >=(RAM& r)//op conditional >=
	{
		if (this->pretRAM >= r.pretRAM)
		{
			return true;
		}
		else return false;
	}
	friend ofstream& operator<<(ofstream& out, RAM& r)
	{
		out << "\n" << r.capacitateRAM << endl;
		out << r.pretRAM << endl;
		out << r.numeRAM << endl;
		out << r.nrfrecvente;
		for (int i = 0; i < r.nrfrecvente; i++)
		{
			out << endl << r.frecventeSuportate[i];
		}
		out << endl;
		return out;
	}
	friend ifstream& operator>>(ifstream& in, RAM& r)
	{
		if (r.numeRAM)
		{
			delete[] r.numeRAM;
		}
		in >> r.capacitateRAM;
		in >> r.pretRAM;
		char buffer[20];
		in >> buffer;
		r.numeRAM = new char[strlen(buffer) + 1];
		strcpy(r.numeRAM, buffer);
		in >> r.nrfrecvente;
		if (r.frecventeSuportate)
		{
			delete[] r.frecventeSuportate;
		}
		r.frecventeSuportate = new int[r.nrfrecvente];
		for (int i = 0; i < r.nrfrecvente; i++)
		{
			in >> r.frecventeSuportate[i];
		}
		return in;
	}
	//getteri pentru clasa mostenita
	int getcapacitateRAM()
	{
		return this->capacitateRAM;
	}
	float getpretRAM()
	{
		return this->pretRAM;
	}
	char* getnumeRAM()
	{
		return this->numeRAM;
	}
	int getnrfrecvente()
	{
		return this->nrfrecvente;
	}
	int* getfrecventeSuportate()
	{
		return this->frecventeSuportate;
	}
};



class Sursa
{
private:
	string numeSursa;
	float pretSursa;
	int nrVoltaje;
	int* voltaje;
public:
	Sursa()//constr fara param
	{
		this->numeSursa = "NA";
		this->pretSursa = 0;
		this->nrVoltaje = 0;
		this->voltaje = new int[nrVoltaje];
		this->voltaje[0] = 0;
	}
	Sursa(string numeSursa, float pretSursa, int nrVoltaje, int* voltaje)//constr cu toti param
	{
		this->numeSursa = numeSursa;
		this->pretSursa = pretSursa;
		this->nrVoltaje = nrVoltaje;
		this->voltaje = new int[nrVoltaje];
		if (nrVoltaje != 0 && voltaje != NULL)
			for (int i = 0; i < nrVoltaje; i++)
			{
				this->voltaje[i] = voltaje[i];
			}
		else
		{
			this->nrVoltaje = 0;
			this->voltaje = NULL;
		}
	}
	Sursa(const Sursa& s)//constr de copiere
	{
		this->numeSursa = s.numeSursa;
		this->pretSursa = s.pretSursa;
		this->nrVoltaje = s.nrVoltaje;
		this->voltaje = new int[s.nrVoltaje];
		if (nrVoltaje != 0 && voltaje != NULL)
			for (int i = 0; i < s.nrVoltaje; i++)
			{
				this->voltaje[i] = s.voltaje[i];
			}
		else
		{
			this->nrVoltaje = 0;
			this->voltaje = NULL;
		}
	}
	Sursa& operator=(Sursa& s)//operator=
	{
		if (this->voltaje)
		{
			delete[] this->voltaje;
		}
		this->numeSursa = s.numeSursa;
		this->pretSursa = s.pretSursa;
		this->nrVoltaje = s.nrVoltaje;
		this->voltaje = new int[s.nrVoltaje];
		if (nrVoltaje != 0 && voltaje != NULL)
			for (int i = 0; i < s.nrVoltaje; i++)
			{
				this->voltaje[i] = s.voltaje[i];
			}
		else
		{
			this->nrVoltaje = 0;
			this->voltaje = NULL;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, Sursa& s)//operator <<
	{
		out << "\nSursa " << s.numeSursa << ", costa " << s.pretSursa << ", are un numar de " << s.nrVoltaje << " voltaje ";
		for (int i = 0; i < s.nrVoltaje; i++)
		{
			cout << i << ": " << s.voltaje[i] << "A \n";
		}
		return out;
	}
	friend istream& operator>>(istream& in, Sursa& s)// operator >>
	{
		if (s.voltaje)
		{
			delete[] s.voltaje;
		}
		cout << "\nNumele sursei: ";
		in >> s.numeSursa;
		cout << "Pret sursa: ";
		in >> s.pretSursa;
		cout << "Numar voltaje: ";
		in >> s.nrVoltaje;
		s.voltaje = new int[s.nrVoltaje];
		for (int i = 0; i < s.nrVoltaje; i++)
		{
			cout << i << ": ";
			in >> s.voltaje[i];
		}
		return in;
	}
	void afisareSursa()//afisare
	{
		cout << "\nSursa " << this->numeSursa << ", costa " << this->pretSursa << ", are un numar de " << this->nrVoltaje << " voltaje ";
		for (int i = 0; i < this->nrVoltaje; i++)
		{
			cout << i << ": " << this->voltaje[i] << "A \n";
		}
	}
	~Sursa()
	{
		//	cout << "\nApel destructor";
		//	if (voltaje != NULL)
		//	{
		//		delete[] this->voltaje;
		//	}
	}

	int& operator[](int poz)//op pentru indexare
	{
		return this->voltaje[poz];
	}
	bool operator!()//op pentru negatie
	{
		if (this->pretSursa > 500)
		{
			return true;
		}
		else return false;
	}
	bool operator>=(Sursa& s)//op pentru negatie
	{
		if (this->pretSursa >= 500)
		{
			return true;
		}
		else return false;
	}
	explicit operator int()//operator cast explicit de la float la int
	{
		return (int)this->pretSursa;
	}
	Sursa& operator+(float x)//operator +
	{
		this->pretSursa += x;
		return *this;
	}
	Sursa& operator++() //op ++
	{
		int nr = this->nrVoltaje + 1;
		int* copie = new int[nr];
		for (int i = 0; i < this->nrVoltaje; i++)
		{
			copie[i] = this->voltaje[i];
		}
		copie[nr - 1] = copie[nr - 2];
		if (this->voltaje)
		{
			delete[]this->voltaje;
		}
		this->nrVoltaje = nr;
		this->voltaje = new int[this->nrVoltaje];
		for (int i = 0; i < this->nrVoltaje; i++)
		{
			this->voltaje[i] = copie[i];
		}
		return *this;
	}
	friend ofstream& operator<<(ofstream& out, Sursa& s)
	{
		out << "\n" << s.numeSursa << endl;
		out << s.pretSursa << endl;
		out << s.nrVoltaje;
		for (int i = 0; i < s.nrVoltaje; i++)
		{
			out << endl << s.voltaje[i];
		}
		out << endl;
		return out;
	}
	friend ifstream& operator>>(ifstream& in, Sursa& s)
	{
		if (s.voltaje)
		{
			delete[] s.voltaje;
		}
		in >> s.numeSursa;
		in >> s.pretSursa;
		in >> s.nrVoltaje;
		s.voltaje = new int[s.nrVoltaje];
		for (int i = 0; i < s.nrVoltaje; i++)
		{
			in >> s.voltaje[i];
		}
		return in;
	}
};



class SSD
{
private:
	string numeSSD;
	float pretSSD;
	int nrSSD;
	int* capacitateSSD;
public:
	SSD()//constr fara param
	{
		this->numeSSD = "NA";
		this->pretSSD = 0;
		this->nrSSD = 0;
		this->capacitateSSD = new int[nrSSD];
		this->capacitateSSD[0] = 0;
	}
	SSD(string numeSSD, float pretSSD, int nrSSD, int* capacitateSSD)//constr cu toti param
	{
		this->numeSSD = numeSSD;
		this->pretSSD = pretSSD;
		if (capacitateSSD != NULL && nrSSD != 0)
		{
			this->nrSSD = nrSSD;
			this->capacitateSSD = new int[nrSSD];
			for (int i = 0; i < nrSSD; i++)
			{
				this->capacitateSSD[i] = capacitateSSD[i];
			}
		}
		else
		{
			this->capacitateSSD = NULL;
			this->nrSSD = 0;
		}
	}
	SSD(const SSD& d)//constr de copiere
	{
		this->numeSSD = d.numeSSD;
		this->pretSSD = d.pretSSD;
		if (capacitateSSD != NULL && nrSSD != 0)
		{
			this->nrSSD = d.nrSSD;
			this->capacitateSSD = new int[d.nrSSD];
			for (int i = 0; i < d.nrSSD; i++)
			{
				this->capacitateSSD[i] = d.capacitateSSD[i];
			}
		}
		else
		{
			this->capacitateSSD = NULL;
			this->nrSSD = 0;
		}
	}
	SSD& operator=(const SSD& d)//operator=
	{
		if (this->capacitateSSD)
		{
			delete[] this->capacitateSSD;
		}
		this->numeSSD = d.numeSSD;
		this->pretSSD = d.pretSSD;
		if (capacitateSSD != NULL && nrSSD != 0)
		{
			this->nrSSD = d.nrSSD;
			this->capacitateSSD = new int[d.nrSSD];
			for (int i = 0; i < d.nrSSD; i++)
			{
				this->capacitateSSD[i] = d.capacitateSSD[i];
			}
		}
		else
		{
			this->capacitateSSD = NULL;
			this->nrSSD = 0;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, SSD& d)//operator<<
	{
		out << "\nMarca SSD-ului este " << d.numeSSD << " si are pretul de " << d.pretSSD << " lei." << " Calculatorul are un numar de " << d.nrSSD << " SSD-uri cu capacitatea ";
		for (int i = 0; i < d.nrSSD; i++)
		{
			cout << i << ": " << d.capacitateSSD[i] << " GB " << endl;
		}
		return out;
	}
	friend istream& operator>>(istream& in, SSD& d)//operator>>
	{
		if (d.capacitateSSD)
		{
			delete[] d.capacitateSSD;
		}
		cout << "\nMarca SSD: ";
		in >> d.numeSSD;
		cout << "Pret SSD: ";
		in >> d.pretSSD;
		cout << "Numar de SSD-uri: ";
		in >> d.nrSSD;
		d.capacitateSSD = new int[d.nrSSD];
		for (int i = 0; i < d.nrSSD; i++)
		{
			cout << i << ": ";
			in >> d.capacitateSSD[i];
		}
		return in;
	}
	void afisareSSD()
	{
		cout << "\nMarca SSD-ului este " << this->numeSSD << " si are pretul de " << this->pretSSD << " lei." << " Calculatorul are un numar de " << this->nrSSD << " SSD-uri cu capacitatea";
		if (this->capacitateSSD != NULL)
			for (int i = 0; i < this->nrSSD; i++)
			{
				cout << i << ": " << this->capacitateSSD[i] << " GB ";
			}
		else cout << "-" << endl;
	}
	~SSD()
	{
		//	cout << "\nApel destructor";
		//	if (capacitateSSD != NULL)
		//	{
		//		delete[] this->capacitateSSD;
		//	}
	}

	int& operator[](int poz)//op pentru indexare
	{
		return this->capacitateSSD[poz];
	}
	bool operator!()//op pentru negatie
	{
		if (this->pretSSD > 700)
		{
			return true;
		}
		else return false;
	}
	bool operator>=(SSD& d)//op pentru negatie
	{
		if (this->pretSSD >= 500)
		{
			return true;
		}
		else return false;
	}
	explicit operator int()//operator cast explicit de la float la int
	{
		return (int)this->pretSSD;
	}
	SSD& operator-(float x)//operator -
	{
		this->pretSSD += x;
		return *this;
	}
	SSD& operator++() //op ++
	{
		int nr = this->nrSSD + 1;
		int* copie = new int[nr];
		for (int i = 0; i < this->nrSSD; i++)
		{
			copie[i] = this->capacitateSSD[i];
		}
		copie[nr - 1] = copie[nr - 2];
		if (this->capacitateSSD)
		{
			delete[]this->capacitateSSD;
		}
		this->nrSSD = nr;
		this->capacitateSSD = new int[this->nrSSD];
		for (int i = 0; i < this->nrSSD; i++)
		{
			this->capacitateSSD[i] = copie[i];
		}
		return *this;
	}
	friend ofstream& operator<<(ofstream& out, SSD& d)
	{
		out << "\n" << d.numeSSD << endl;
		out << d.pretSSD << endl;
		out << d.nrSSD;
		for (int i = 0; i < d.nrSSD; i++)
		{
			out << endl << d.capacitateSSD[i];
		}
		return out;
	}
	friend ifstream& operator>>(ifstream& in, SSD& d)
	{
		if (d.capacitateSSD)
		{
			delete[] d.capacitateSSD;
		}
		in >> d.numeSSD;
		in >> d.pretSSD;
		in >> d.nrSSD;
		d.capacitateSSD = new int[d.nrSSD];
		for (int i = 0; i < d.nrSSD; i++)
		{
			in >> d.capacitateSSD[i];
		}
		return in;
	}

};



class NrMemorieRAM : public RAM
{
private:
	int nrRAM;
public:
	NrMemorieRAM() : RAM()//constr default
	{
		this->nrRAM = 2;
	}
	NrMemorieRAM(int frecventaRAM, int capacitateRAM, float pretRAM, const char* numeRAM, int nrfrecvente, int* frecventeSuportate, int nrRAM) : RAM(frecventaRAM, capacitateRAM, pretRAM, numeRAM, nrfrecvente, frecventeSuportate)//constr cu toti param
	{
		this->nrRAM = nrRAM;
	}
	NrMemorieRAM(const NrMemorieRAM& n) : RAM(n)//constr de copiere
	{
		this->nrRAM = n.nrRAM;
	}
	NrMemorieRAM& operator=(NrMemorieRAM& n)//operator=
	{
		RAM::operator=(n);
		this->nrRAM = n.nrRAM;
		return*this;
	}
	friend ostream& operator<<(ostream& out, NrMemorieRAM& n)//operator<<
	{
		out << "\nMemoria RAM are capacitatea de " << n.getcapacitateRAM() << " GB, costa " << n.getpretRAM() << " lei si este marca " << n.getnumeRAM() << ". Are un numar de " << n.getnrfrecvente() << " frecvente suportate, ";
		out << " si un numar de " << n.nrRAM << " placute RAM.";
		return out;
	}
	/*virtual void detalii() override
	{
		cout << "\nAceasta este o memorie Ram";
	}
	virtual void denumire() override
	{
		cout << "\nDenumirea ei este" << getnumeRAM();
	}*/
};



class NumarRAM
{
private:
	int numarRAM;
	RAM** vector;
public:
	NumarRAM()//constr default
	{
		this->numarRAM = 2;
		this->vector = new RAM * [2];
		this->vector[0] = new RAM();
		this->vector[1] = new RAM();
	}
	NumarRAM(int numarRAM, RAM** vector)//constr cu toti param
	{
		this->numarRAM = numarRAM;
		this->vector = new RAM * [numarRAM];
		for (int i = 0; i < this->numarRAM; i++)
		{
			this->vector[i] = vector[i];
		}
	}
	NumarRAM(const NumarRAM& q)//constr cu toti param
	{
		this->numarRAM = q.numarRAM;
		this->vector = new RAM * [q.numarRAM];
		for (int i = 0; i < this->numarRAM; i++)
		{
			this->vector[i] = q.vector[i];
		}
	}
	NumarRAM& operator=(NumarRAM& q)//operator=
	{
		if (this->vector)
		{
			delete[] this->vector;
		}
		this->numarRAM = q.numarRAM;
		this->vector = new RAM * [q.numarRAM];
		for (int i = 0; i < this->numarRAM; i++)
		{
			this->vector[i] = q.vector[i];
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, NumarRAM& q)
	{
		out << "\nCalculatorul are un numar de " << q.numarRAM << " placute RAM ";
		for (int i = 0; i < q.numarRAM; i++)
		{
			q.vector[i]->afisareRAM();//early binding
		}
		return out;
	}
};



void main()
{
	bool repeat = true;
	int choice;
	while (repeat)
	{
		cout << endl
			<< " ======MENIU======\n"
			<< " 1 - Clasa Procesor\n"
			<< " 2 - Clasa Placa de baza\n"
			<< " 3 - Clasa RAM\n"
			<< " 4 - Clasa Sursa \n"
			<< " 5 - Clasa SSD \n"
			<< " 6 - Scrierea componentelor in fisier text \n"
			<< " 7 - Scrierea componentelor in fisier binar \n"
			<< " 8 - Clasa care exemplifica conceptul compunerii \n"
			<< " 9 - Vector de pointeri la clasa de baza \n"
			<< " Introduceti alegerea facuta: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "\n///////////////////////////////////////////CLASA PROCESOR///////////////////////////////////////////////////////////////\n";

			Procesor p;
			Procesor p1("1151", "Intel", 12, 3, new float[3]{ 0.76,6,64 }, 1000);
			Procesor p2("1200", "Intel", 32, 2, new float[2]{ 6,64 }, 1500);
			Procesor p3("1151", "Intel", 20, 3, new float[3]{ 6,6,64 }, 1666);
			p1 = p2;
			cout << p2;
			p2 = p1 + 1500;
			cout << p2;
			p1.afisarePR();
			cin >> p1;
			p1.afisarePR();
			if (p1 == p2)//op testarea egalitatii
			{
				cout << "\nPreturile sunt egale!";
			}
			else cout << "\nPreturile NU sunt egale!";
			cout << (int)p1;//operator cast explicit de la float la int
			if (p2 >= p1)
			{
				cout << "\nPretul 1 este mai MARE decat pretul 2!" << endl;
			}
			else cout << "\nPretul 1 este mai MIC decat pretul 2!" << endl;
			cout << "OPERATOR EXPLICIT: ";
			cout << (float)p1;//operator cast explicit
			p[1] = 62.5;//op indexare
			cout << "\nOPERATOR INDEXARE: " << p[1];
			if (!p2) //op pentru negatie
			{
				cout << "\nOPERATOR NEGATIE: Procesorul costa PESTE 2500 lei.";
			}
			else cout << "\nOPERATOR NEGATIE: Procesorul costa SUB 2500 lei. ";
			cout << p2 << "\n=======================";
			++p2;
			cout << p2 << endl;

			ifstream f("Scriere.txt");
			f >> p3;
			cout << p3;
			f.close();

			vector <Procesor> stl;
			stl.push_back(p);
			stl.push_back(p2);
			cout << "\n Stl vector: \n";
			for (int i = 0; i < stl.size(); i++)
			{
				cout << stl[i];
			}
			break;
		}
		case 2:
		{
			cout << "\n////////////////////////////////////////CLASA PLACA DE BAZA/////////////////////////////////////////////////////////////\n";

			PlacaDeBaza b;
			PlacaDeBaza b1(4, "ASUS", 3, new int[3]{ 2333,3000,3200 }, 1200, 660);
			PlacaDeBaza b2(4, "Gigabyte", 2, new int[2]{ 3000,3200 }, 1200, 700);
			PlacaDeBaza b3(4, "Asus", 2, new int[2]{ 2333,3000 }, 1200, 680);
			b1 = b2;
			cout << b2;
			b2 = b1 + 1500;
			cout << b2;
			b1.afisarePB();
			cin >> b1;
			if (b1 == b2)//op testarea egalitatii
			{
				cout << "\nPreturile sunt egale!";
			}
			else cout << "\nPreturile NU sunt egale!";
			cout << (int)b1;//operator cast explicit de la float la int
			if (b2 >= b1)
			{
				cout << "\nPretul 1 este mai MARE decat pretul 2!" << endl;
			}
			else cout << "\nPretul 1 este mai MIC decat pretul 2!" << endl;
			cout << "OPERATOR EXPLICIT: ";
			cout << (float)b1;//operator cast explicit
			b[1] = 62.5;//op indexare
			cout << "\nOPERATOR INDEXARE: " << b[1];
			if (!b2) //op pentru negatie
			{
				cout << "\nOPERATOR NEGATIE: Placa de baza costa PESTE 800 lei.";
			}
			else cout << "\nOPERATOR NEGATIE: Placa de baza costa SUB 800 lei. ";
			cout << b2 << "\n======================";
			++b2;
			cout << b2 << endl;

			cout << "\nOfera niste valori scrise de mine din fisierul txt, am folosit acelasi fisier pentru toate clasele";
			ifstream f("Scriere.txt");
			f >> b3;
			cout << b3;
			f.close();

			vector <PlacaDeBaza> stl;
			stl.push_back(b);
			stl.push_back(b2);
			cout << "\n Stl vector: \n";
			for (int i = 0; i < stl.size(); i++)
			{
				cout << stl[i];
			}
			break;
		}
		case 3:
		{
			cout << "\n////////////////////////////////////////CLASA MEMORIE RAM///////////////////////////////////////////////////////////////\n";

			RAM r;
			RAM r1(3000, 8, 300, "HyperX", 2, new int[2]{ 3000,3200 });
			RAM r2(3200, 16, 600, "Corsair", 1, new int[1]{ 3200 });
			RAM r3(3200, 12, 450, "HyperX", 2, new int[2]{ 2999,3200 });
			r1 = r2;
			cout << r2;
			r2 = r1 + 500;
			cout << r2;
			r1.afisareRAM();
			cin >> r1;
			if (r1 == r2)//op testarea egalitatii
			{
				cout << "\nPreturile sunt egale!";
			}
			else cout << "\nPreturile NU sunt egale!";
			if (r2 >= r1)
			{
				cout << "\nPretul 1 este mai MARE decat pretul 2!" << endl;
			}
			else cout << "\nPretul 1 este mai MIC decat pretul 2!" << endl;
			cout << "OPERATOR EXPLICIT: ";
			cout << (string)r1;//operator cast explicit de la char la string
			r[1] = 62;//op indexare
			cout << "\nOPERATOR INDEXARE: " << r[1];
			if (!r2) //op pentru negatie
			{
				cout << "\nOPERATOR NEGATIE: Memoria RAM costa PESTE 600 lei.";
			}
			else cout << "\nOPERATOR NEGATIE: Memoria RAM costa SUB 600 lei. ";
			cout << r2 << "\n======================";
			++r2;
			cout << r2 << endl;

			ifstream f("Scriere.txt");
			f >> r3;
			cout << r3;
			f.close();

			vector <RAM> stl;
			stl.push_back(r);
			stl.push_back(r2);
			cout << "\n Stl vector: \n";
			for (int i = 0; i < stl.size(); i++)
			{
				cout << stl[i];
			}
			break;
		}
		case 4:
		{
			cout << "\n///////////////////////////////////////////CLASA SURSA//////////////////////////////////////////////////////////////////\n";

			Sursa s;
			Sursa s1("Sursa", 5000, 2, new int[2]{ 12,20 });
			Sursa s2("Asus", 1000, 3, new int[3]{ 12,24,36 });
			Sursa s3("Corsair", 800, 2, new int[2]{ 24,36 });
			s1 = s2;
			cout << s2;
			s2 = s1 + 500;
			cout << s2;
			s1.afisareSursa();
			cin >> s1;
			if (s1 >= s2)
			{
				cout << "\nPrima sursa este mai SCUMPA decat cea de-a doua." << endl;;
			}
			else cout << "\nPrima sursa este mai IEFTINA decat cea de-a doua" << endl;;
			cout << "OPERATOR EXPLICIT: ";
			cout << (int)s1;//operator cast explicit de la float la int
			s1[1] = 50;//op indexare
			cout << "\nOPERATOR INDEXARE: " << s1[1];
			if (!s2)
			{
				cout << "\nOPERATOR NEGATIE: Sursa costa PESTE 500 lei!";
			}
			else cout << "\nOPERATOR NEGATIE: Sursa costa SUB 500 lei!";
			cout << s2 << "\n======================";
			++s2;
			cout << s2 << endl;

			ifstream f("Scriere.txt");
			f >> s3;
			cout << s3;
			f.close();

			vector <Sursa> stl;
			stl.push_back(s);
			stl.push_back(s2);
			cout << "\n Stl vector: \n";
			for (int i = 0; i < stl.size(); i++)
			{
				cout << stl[i];
			}
			break;
		}

		case 5:
		{
			cout << "\n////////////////////////////////////////////CLASA SSD///////////////////////////////////////////////////////////////////\n";

			SSD d;
			SSD d1("Kingstone", 500, 2, new int[2]{ 256,512 });
			SSD d2("Samsung", 700, 3, new int[3]{ 256,512,1024 });
			SSD d3("Samsung", 350, 1, new int[1]{ 256 });
			d1 = d2;
			cout << d2;
			d2 = d1 - 200;
			cout << d2;
			d1.afisareSSD();
			cin >> d1;
			if (d1 >= d2)
			{
				cout << "\nPrimul SSD este mai SCUMP decat al doilea." << endl;;
			}
			else cout << "\nPrimul SSD este mai IEFTIN decat al doilea." << endl;;
			cout << "OPERATOR EXPLICIT: ";
			cout << (int)d1;//operator cast explicit de la float la int
			d1[1] = 50;//op indexare
			cout << "\nOPERATOR INDEXARE: " << d1[1];
			if (!d2)
			{
				cout << "\nOPERATOR NEGATIE: SSD-ul costa PESTE 500 lei!";
			}
			else cout << "\nOPERATOR NEGATIE: SSD-ul costa SUB 500 lei!";
			cout << d2 << "\n======================";
			++d2;
			cout << d2;

			ifstream f("Scriere.txt");
			f >> d3;
			cout << d3;
			f.close();

			vector <SSD> stl;
			stl.push_back(d);
			stl.push_back(d2);
			cout << "\n Stl vector: \n";
			for (int i = 0; i < stl.size(); i++)
			{
				cout << stl[i];
			}
			break;
		}
		case 6:
		{
			Procesor p4("1151", "Intel", 20, 3, new float[3]{ 6,6,64 }, 1500);
			ofstream g("Calculator.txt");//creare si scriere in fisier txt
			g << p4;
			g.close();

			PlacaDeBaza b4(4, "Asus", 2, new int[2]{ 2999,3200 }, 1151, 650);

			g.open("Calculator.txt", ios::app);
			g << b4;
			g.close();

			RAM r4(3200, 12, 450, "HyperX", 2, new int[2]{ 2999,3200 });

			g.open("Calculator.txt", ios::app);
			g << r4;
			g.close();

			Sursa s4("Corsair", 500, 2, new int[2]{ 24,36 });

			g.open("Calculator.txt", ios::app);
			g << s4;
			g.close();

			SSD d4("Samsung", 399, 2, new int[2]{ 256,512 });

			g.open("Calculator.txt", ios::app);
			if (g.is_open())
			{
				g << d4;
				g.close();
			}
			else cout << "Eroare!\n";
			cout << "\nComponentele au fost scrise in fisierul text!" << endl;
			break;
		}
		case 7:
		{
			Procesor p5("1151", "Intel", 16, 3, new float[3]{ 6,6,64 }, 1639);
			ofstream a;
			a.open("Calculator.dat", ios::out | ios::binary);

			if (a.is_open())
			{
				a.write(reinterpret_cast<char*>(&p5), sizeof(Procesor));
				a.close();
			}
			else cout << "Eroare!\n";
			cout << "\nComponentele au fost scrise in fisierul binar!";
			break;
		}
		case 8:
		{
			cout << "\n/////////////////////////////////////CLASA NUMAR MEMORIE RAM////////////////////////////////////////////////////////////\n";

			NrMemorieRAM n;
			NrMemorieRAM n1(3000, 8, 300, "HyperX", 2, new int[2]{ 3000,3200 }, 2);
			cout << n1;
			NrMemorieRAM n2 = n1;
			cout << n2;
			NrMemorieRAM n3;
			n3 = n2;
			cout << n3;
			break;
		}
		case 9:
		{
			cout << "\n/////////////////////////////////////////CLASA NUMAR RAM////////////////////////////////////////////////////////////////\n";
			RAM r1(3200, 8, 200, "Corsair", 3, new int[3]{ 2600, 2900, 3200 });
			RAM r2(3200, 8, 250, "Corsair", 2, new int[2]{ 2999,3200 });
			NumarRAM q;
			NumarRAM q1(2, new RAM * [2]{ &r1, &r2 });
			cout << q1;
			NumarRAM q2 = q1;
			NumarRAM q3;
			q3 = q2;
			cout << q3;
			break;
		}
		}
		cout << "\n Doriti sa introduceti alt numar?(y/n)" << endl;
		char ch;
		cin >> ch;
		if (ch == 'y' || ch == 'Y')
			continue;
		else
			repeat = false;
	}
}