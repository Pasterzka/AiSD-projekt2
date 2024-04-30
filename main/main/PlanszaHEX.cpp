#include "PlanszaHEX.h"
#include "Definicje.h"


#include <string>

PlanszaHEX::PlanszaHEX()
{
	
	this->liczbaCzerwonychPionkow = 0;
	this->liczbaNiebieskichPionkow = 0;
	this->liczbaPol = 0;

	std::string input;
	//std::cin >> input; // skip "---"


	int i = 0;
	do
	{

		plansza.push_back(new std::vector<HEX*>()); //wczytanie piêtra hexa
		std::cin >> input; // skip "--<"
		do
		{
			std::cin >> input; //wczytanie pionka
			if (input == "r")
			{
				this->plansza[i]->push_back(new HEX(czerwony));
				liczbaCzerwonychPionkow++;
				liczbaPol++;
				std::cin >> input;
			}
			else if (input == "b")
			{
				this->plansza[i]->push_back(new HEX(niebieski));
				liczbaNiebieskichPionkow++;
				liczbaPol++;
				std::cin >> input;
			}
			else
			{
				this->plansza[i]->push_back(new HEX(pusty));
				liczbaPol++;
			}

			i++;
		} while (input != ">--" && input != ">"); //koniec linii

		i = 0;
	} while (input != ">"); //górna czêœæ hexa koniec

	int k = 1;
	i = k;

	do
	{
		std::cin >> input; // skip --<
		if (input != "---") // warunek test 1
		{
			do
			{
				std::cin >> input;
				if (input == "r")
				{
					this->plansza[i]->push_back(new HEX(czerwony));
					liczbaCzerwonychPionkow++;
					liczbaPol++;
					std::cin >> input;
				}
				else if (input == "b")
				{
					this->plansza[i]->push_back(new HEX(niebieski));
					liczbaNiebieskichPionkow++;
					liczbaPol++;
					std::cin >> input;
				}
				else
				{
					this->plansza[i]->push_back(new HEX(pusty));
					liczbaPol++;
				}
				i++;
			} while (input != ">--" && input != "---");
			k++;
			i = k;
		}
	} while (input != "---"); //koniec hexa
	this->liczbaPustePola = plansza.size() * plansza.size() - liczbaNiebieskichPionkow - liczbaCzerwonychPionkow;
	this->rozmiar = plansza.size();
}

int PlanszaHEX::getLiczbaCzerownychPionkow()
{
	return this->liczbaCzerwonychPionkow;
}

int PlanszaHEX::getLiczbaNiebieskichPionkow()
{
	return this->liczbaNiebieskichPionkow;
}

int PlanszaHEX::getLiczbaPol()
{
	return this->liczbaPol;
}

int PlanszaHEX::getLiczbaPionkow()
{
	return this->liczbaCzerwonychPionkow + this->liczbaNiebieskichPionkow;
}

int PlanszaHEX::getRozmiarPlanszy()
{
	return this->plansza.size();
}

bool PlanszaHEX::CzyPlanszaPoprawna()
{
	if (this->liczbaCzerwonychPionkow == this->liczbaNiebieskichPionkow || this->liczbaCzerwonychPionkow == this->liczbaNiebieskichPionkow + 1)
	{
		return true;
	}
	else {
		return false;
	}
}



int dx[] = { -1, -1, 0, 0, 1, 1 };
int dy[] = { 0, -1, -1, 1, 1, 0 };

bool PlanszaHEX::CzerwonyDFS(int x, int y)
{
	// Jeœli dotarliœmy do kolumny max, zwracamy true
	if (x == rozmiar-1) {
		return true;
	}

	// Oznaczenie bie¿¹cej komórki jako odwiedzonej
	(*plansza[x])[y]->setOdwiedzony(true);

	// Przegl¹danie s¹siednich komórek
	for (int i = 0; i < 6; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		// Sprawdzenie, czy s¹siednia komórka mieœci siê w granicach i czy nie zosta³a odwiedzona
		if (nx >= 0 && nx < rozmiar && ny >= 0 && ny < rozmiar && !(*plansza[nx])[ny]->getOdwiedzony() && (*plansza[nx])[ny]->getPionek() == 1) {
			// Rekurencyjne wywo³anie DFS dla s¹siedniej komórki
			if (CzerwonyDFS(nx, ny)) {
				return true;
			}
		}
	}

	// Jeœli nie uda³o siê znaleŸæ œcie¿ki, zwracamy false
	return false;
}

bool PlanszaHEX::NiebieskiDFS(int x, int y)
{
	// Jeœli dotarliœmy do wiersza max, zwracamy true
	if (y == rozmiar-1) {
		return true;
	}

	// Oznaczenie bie¿¹cej komórki jako odwiedzonej
	(*plansza[x])[y]->setOdwiedzony(true);

	// Przegl¹danie s¹siednich komórek
	for (int i = 0; i < 6; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		// Sprawdzenie, czy s¹siednia komórka mieœci siê w granicach i czy nie zosta³a odwiedzona
		if (nx >= 0 && nx < rozmiar && ny >= 0 && ny < rozmiar && !(*plansza[nx])[ny]->getOdwiedzony() && (*plansza[nx])[ny]->getPionek() == 2) {
			// Rekurencyjne wywo³anie DFS dla s¹siedniej komórki
			if (NiebieskiDFS(nx, ny)) {
				return true;
			}
		}
	}

	// Jeœli nie uda³o siê znaleŸæ œcie¿ki, zwracamy false
	return false;
}

int PlanszaHEX::GraSkonczona()
{
	ResetOdwiedziny();
	if (CzyPlanszaPoprawna())
	{
		for (int i = 0; i < rozmiar; ++i) {
			if ((*plansza[0])[i]->getPionek() == czerwony && !(*plansza[0])[i]->getOdwiedzony())
			{
				if (CzerwonyDFS(0,i))
				{
					return 1;
				}
			}
		}

		for (int i = 0; i < rozmiar; ++i) {
			if ((*plansza[i])[0]->getPionek() == niebieski && !(*plansza[i])[0]->getOdwiedzony()) {
				if (NiebieskiDFS( i, 0)) {
					return 2;

				}
			}
		}
	}

	return 0;
}

bool PlanszaHEX::NiebiskiWygral()
{
	ResetOdwiedziny();
	for (int i = 0; i < rozmiar; ++i) {
		if ((*plansza[i])[0]->getPionek() == niebieski && !(*plansza[i])[0]->getOdwiedzony()) {
			if (NiebieskiDFS(i, 0)) {
				return true;
			}
		}
	}
	return false;
}

bool PlanszaHEX::CzerwonyWygral()
{
	ResetOdwiedziny();
	for (int i = 0; i < rozmiar; ++i) {
		if ((*plansza[0])[i]->getPionek() == czerwony && !(*plansza[0])[i]->getOdwiedzony())
		{
			if (CzerwonyDFS(0, i))
			{
				return true;
			}
		}
	}
	return false;
}

bool PlanszaHEX::CzyPlanszaMozliwa()
{
	int gra = GraSkonczona();
	if (CzyPlanszaPoprawna() && (gra == niebieski && Tura() == czerwony || gra == czerwony && Tura() == niebieski || gra == 0))
	{

		int kolor;
		if (gra != 0)
		{
			if (gra == czerwony)
			{
				kolor = czerwony;
			}
			else {
				kolor = niebieski;
			}

			for (int i = 0; i < rozmiar; i++)
			{
				for (int k = 0; k < rozmiar; k++)
				{
					if ((*plansza[i])[k]->getPionek() == kolor)
					{
						(*plansza[i])[k]->setPionek(pusty);
						if (GraSkonczona() != gra)
						{
							(*plansza[i])[k]->setPionek(kolor);
							return true;
						}
						(*plansza[i])[k]->setPionek(kolor);
					}
				}

			}
			return false;
		}
		return true;
	}
	return false;
	
}

void PlanszaHEX::ResetOdwiedziny()
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			(*plansza[i])[k]->setOdwiedzony(false);
		}
	}
}

int PlanszaHEX::Tura()
{
	if (liczbaCzerwonychPionkow == liczbaNiebieskichPionkow)
	{
		return czerwony;
	}
	else {
		return niebieski;
	}
}

int PlanszaHEX::getLiczbaPustychPol()
{
	return liczbaPustePola;
}

int PlanszaHEX::GraSkonczona(int kolor)
{

	ResetOdwiedziny();
	if (CzyPlanszaPoprawna())
	{
		
		for (int i = 0; i < rozmiar; ++i) {
			if (kolor == czerwony && (*plansza[0])[i]->getPionek() == czerwony && !(*plansza[0])[i]->getOdwiedzony())
			{
				if (CzerwonyDFS(0, i))
				{
					return 1;
				}
			}
			if (kolor == niebieski && (*plansza[i])[0]->getPionek() == niebieski && !(*plansza[i])[0]->getOdwiedzony())
			{
				if (NiebieskiDFS(i, 0)) {
					return 2;

				}
			}
		}

		
	}

	return 0;

}




bool PlanszaHEX::NiebieskiTuraNiebieski1Naiwny()
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{
				(*plansza[i])[k]->setPionek(niebieski);
				liczbaNiebieskichPionkow++;
				if (GraSkonczona(niebieski))
				{
					(*plansza[i])[k]->setPionek(pusty);
					liczbaNiebieskichPionkow--;
					return true;
				}
				(*plansza[i])[k]->setPionek(pusty);
				liczbaNiebieskichPionkow--;
			}
		}
	}
	return false;
}

bool PlanszaHEX::NiebieskiTuraCzerwony1Naiwny()
{
	liczbaCzerwonychPionkow++;
	if (liczbaNiebieskichPionkow + liczbaCzerwonychPionkow + 1 <= rozmiar * rozmiar && NiebieskiTuraNiebieski1Naiwny())
	{
		liczbaCzerwonychPionkow--;
		return true;
	}
	liczbaCzerwonychPionkow--;
	return false;
}


bool PlanszaHEX::CzerwonyTuraNiebieski1Naiwny()
{
	liczbaNiebieskichPionkow++;
	if (liczbaNiebieskichPionkow + liczbaCzerwonychPionkow + 1 <= rozmiar * rozmiar && CzerwonyTuraCzerwony1Naiwny())
	{
		liczbaNiebieskichPionkow--;
		return true;
	}
	liczbaNiebieskichPionkow--;
	return false;
}

bool PlanszaHEX::CzerwonyTuraCzerwony1Naiwny()
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{
				(*plansza[i])[k]->setPionek(czerwony);
				liczbaCzerwonychPionkow++;
				if (GraSkonczona() == 1)
				{
					(*plansza[i])[k]->setPionek(pusty);
					liczbaCzerwonychPionkow--;
					return true;
				}
				(*plansza[i])[k]->setPionek(pusty);
				liczbaCzerwonychPionkow--;
			}
		}
	}
	return false;
}

bool PlanszaHEX::NiebieskiTuraNiebieski2Naiwny()
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{
				(*plansza[i])[k]->setPionek(niebieski);
				liczbaNiebieskichPionkow++;
				if (!GraSkonczona() && NiebieskiTuraCzerwony1Naiwny())
				{
					(*plansza[i])[k]->setPionek(pusty);
					liczbaNiebieskichPionkow--;
					return true;
				}
				(*plansza[i])[k]->setPionek(pusty);
				liczbaNiebieskichPionkow--;
			}
		}
	}
	return false;
}

bool PlanszaHEX::NiebieskiTuraCzerwony2Naiwny()
{
	liczbaCzerwonychPionkow++;
	if (liczbaNiebieskichPionkow + liczbaCzerwonychPionkow + 3 <= rozmiar * rozmiar && NiebieskiTuraNiebieski2Naiwny())
	{
		liczbaCzerwonychPionkow--;
		return true;
	}
	liczbaCzerwonychPionkow--;
	return false;
}

bool PlanszaHEX::CzerwonyTuraNiebieski2Naiwny()
{
	liczbaNiebieskichPionkow++;
	if (liczbaNiebieskichPionkow + liczbaCzerwonychPionkow + 3 <= rozmiar * rozmiar && CzerwonyTuraCzerwony2Naiwny())
	{
		liczbaNiebieskichPionkow--;
		return true;
	}
	liczbaNiebieskichPionkow--;
	return false;
}

bool PlanszaHEX::CzerwonyTuraCzerwony2Naiwny()
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{

				(*plansza[i])[k]->setPionek(czerwony);
				liczbaCzerwonychPionkow++;
				if (!GraSkonczona() && CzerwonyTuraNiebieski1Naiwny())
				{
					(*plansza[i])[k]->setPionek(pusty);
					liczbaCzerwonychPionkow--;
					return true;
				}
				(*plansza[i])[k]->setPionek(pusty);
				liczbaCzerwonychPionkow--;
			}
		}
	}
	return false;
}

bool PlanszaHEX::CzerwonyWJednymRuchuNaiwny() {
	int tura = Tura();
		if (tura == czerwony)
		{
			if (CzerwonyTuraCzerwony1Naiwny())
			{
				return true;
			}
		}
		else if (tura == niebieski)
		{
			if (CzerwonyTuraNiebieski1Naiwny())
			{
				return true;
			}
		}
	
	return false;
}

bool PlanszaHEX::NiebieskiWJednymRuchuNaiwny()
{
	int tura = Tura();
		if (tura == niebieski)
		{
			if (NiebieskiTuraNiebieski1Naiwny())
			{
				return true;
			}
		}
		else if (tura == czerwony)
		{
			if (NiebieskiTuraCzerwony1Naiwny())
			{
				return true;
			}
		}
	
	return false;
}

bool PlanszaHEX::CzerwonyWDwochRuchachNaiwny()
{
	int tura = Tura();
		if (tura == czerwony)
		{
			if (CzerwonyTuraCzerwony2Naiwny())
			{
				return true;
			}
		}
		else if (tura == niebieski)
		{
			if (CzerwonyTuraNiebieski2Naiwny())
			{
				return true;
			}
		}
	
	return false;
}

bool PlanszaHEX::NiebieskiWDwochRuchachNaiwny()
{
	int tura = Tura();
		if (tura == niebieski)
		{
			if (NiebieskiTuraNiebieski2Naiwny())
			{
				return true;
			}
		}
		else if (tura == czerwony)
		{
			if (NiebieskiTuraCzerwony2Naiwny())
			{
				return true;
			}
		}
	
	return false;

}


void PlanszaHEX::NaiwnyPrzeciwnik()
{
	std::string input;

	std::cin >> input;
	std::cin >> input;
	std::cin >> input;
	int win = GraSkonczona();
	bool b = CzyPlanszaPoprawna();

	//std::cout << GraSkonczona();

	if (b && win == 0 && CzerwonyWJednymRuchuNaiwny() )
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	std::cout << "\n";
	if (b && win == 0 && NiebieskiWJednymRuchuNaiwny())
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	std::cout << "\n";
	if (b && win == 0 && CzerwonyWDwochRuchachNaiwny())
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	std::cout << "\n";
	if (b && win == 0 && NiebieskiWDwochRuchachNaiwny())
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}

}

void PlanszaHEX::PerfekcyjnyPrzeciwnik()
{

	std::string input;

	std::cin >> input;
	std::cin >> input;
	std::cin >> input;
	int win = GraSkonczona();
	bool b = CzyPlanszaPoprawna();


	//std::cout << GraSkonczona();

	if (b && win == 0 && CzerwonyWJednymRuchuPerfekcyjny())
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	std::cout << "\n";
	if (b && win == 0 && NiebieskiWJednymRuchuPerfekcyjny())
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	std::cout << "\n";
	if (b && win == 0 && CzerwonyWDwochRuchachPerfekcyjny())
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	std::cout << "\n";
	if (b && win == 0 && NiebieskiWDwochRuchachPerfekcyjny())
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
}

PlanszaHEX::~PlanszaHEX()
{
	for (int i = 0; i < plansza.size(); i++)
	{
		for (int k = 0; k < plansza.size(); k++)
		{
			delete (*plansza[i])[k];
		}
		delete plansza[i];
	}
}

bool PlanszaHEX::CzerwonyTuraNiebieski2Perfekcyjny()
{
	if (NiebieskiTuraNiebieski1Perfekcyjny())
	{
		return false;
	}
	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{
				(*plansza[i])[k]->setPionek(czerwony);
				liczbaCzerwonychPionkow++;
				if (GraSkonczona(czerwony) == 0)
				{
					(*plansza[i])[k]->setPionek(niebieski);
					liczbaNiebieskichPionkow++;
					liczbaCzerwonychPionkow--;
					if (!CzerwonyTuraCzerwony2Perfekcyjny())
					{
						(*plansza[i])[k]->setPionek(pusty);
						liczbaNiebieskichPionkow--;
						return false;
					}
					(*plansza[i])[k]->setPionek(pusty);
					liczbaNiebieskichPionkow--;
				}
				else
				{
					(*plansza[i])[k]->setPionek(pusty);
					liczbaCzerwonychPionkow--;
				}
			}
		}
	}

	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{
				(*plansza[i])[k]->setPionek(niebieski);
				liczbaNiebieskichPionkow++;
				if (!CzerwonyTuraCzerwony2Perfekcyjny())
				{
					(*plansza[i])[k]->setPionek(pusty);
					liczbaNiebieskichPionkow--;
					return false;
				}
				(*plansza[i])[k]->setPionek(pusty);
				liczbaNiebieskichPionkow--;
			}
		}
	}
	return true;
}

bool PlanszaHEX::CzerwonyTuraCzerwony2Perfekcyjny()
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek()  == pusty)
			{
				(*plansza[i])[k]->setPionek(czerwony);
				liczbaCzerwonychPionkow++;
				if (GraSkonczona(czerwony) == 0 && CzerwonyTuraNiebieski1Perfekcyjny())
				{
					liczbaCzerwonychPionkow--;
					(*plansza[i])[k]->setPionek(pusty);
					return true;
				}
				(*plansza[i])[k]->setPionek(pusty);
				liczbaCzerwonychPionkow--;
			}
		}
	}
	return false;
}

bool PlanszaHEX::CzerwonyWJednymRuchuPerfekcyjny()
{
	int tura = Tura();
	if (tura == czerwony)
	{
		if (CzerwonyTuraCzerwony1Perfekcyjny())
		{
			return true;
		}
	}
	else if (tura == niebieski)
	{
		if (CzerwonyTuraNiebieski1Perfekcyjny())
		{
			return true;
		}
	}
	return false;
}

bool PlanszaHEX::NiebieskiWJednymRuchuPerfekcyjny()
{
	int tura = Tura();
	if (tura == niebieski)
	{
		if (NiebieskiTuraNiebieski1Perfekcyjny())
		{
			return true;
		}
	}
	else if (tura == czerwony)
	{
		if (NiebieskiTuraCzerwony1Perfekcyjny())
		{
			return true;
		}
	}
	return false;
}

bool PlanszaHEX::CzerwonyWDwochRuchachPerfekcyjny()
{
	int tura = Tura();
	if (tura == czerwony)
	{
		if (CzerwonyTuraCzerwony2Perfekcyjny())
		{
			return true;
		}
	}
	else if (tura == niebieski)
	{
		if (CzerwonyTuraNiebieski2Perfekcyjny())
		{
			return true;
		}
	}
	return false;
}

bool PlanszaHEX::NiebieskiWDwochRuchachPerfekcyjny()
{
	int tura = Tura();
	if (tura == niebieski)
	{
		if (NiebieskiTuraNiebieski2Perfekcyjny())
		{
			return true;
		}
	}
	else if (tura == czerwony)
	{
		if (NiebieskiTuraCzerwony2Perfekcyjny())
		{
			return true;
		}
	}
	return false;
}

bool PlanszaHEX::NiebieskiTuraNiebieski1Perfekcyjny()
{
	if (NiebieskiTuraNiebieski1Naiwny())
	{
		return true;
	}
	return false;
}

bool PlanszaHEX::NiebieskiTuraCzerwony1Perfekcyjny()
{
	if (CzerwonyTuraCzerwony1Naiwny())
	{
		return false;
	}
	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{
				(*plansza[i])[k]->setPionek(niebieski);
				liczbaNiebieskichPionkow++;
				if (GraSkonczona(niebieski))
				{
					(*plansza[i])[k]->setPionek(czerwony);
					liczbaCzerwonychPionkow++;
					liczbaNiebieskichPionkow--;
					if (!NiebieskiTuraNiebieski1Perfekcyjny())
					{
						liczbaCzerwonychPionkow--;
						(*plansza[i])[k]->setPionek(pusty);
						return false;
					}
					liczbaCzerwonychPionkow--;
					(*plansza[i])[k]->setPionek(pusty);
				}
				else {
					liczbaNiebieskichPionkow--;
					(*plansza[i])[k]->setPionek(pusty);
				}
			}
		}
	}

	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{
				(*plansza[i])[k]->setPionek(czerwony);
				liczbaCzerwonychPionkow++;
				if (!NiebieskiTuraNiebieski1Perfekcyjny())
				{
					liczbaCzerwonychPionkow--;
					(*plansza[i])[k]->setPionek(pusty);
					return false;
				}
				liczbaCzerwonychPionkow--;
				(*plansza[i])[k]->setPionek(pusty);
			}
		}
	}
	return true;
}

bool PlanszaHEX::CzerwonyTuraNiebieski1Perfekcyjny()
{
	if (NiebieskiTuraNiebieski1Naiwny())
	{
		return false;
	}
	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{
				(*plansza[i])[k]->setPionek(czerwony); 
				liczbaCzerwonychPionkow++;
				if (GraSkonczona(czerwony))
				{
					(*plansza[i])[k]->setPionek(niebieski);
					liczbaNiebieskichPionkow++;
					liczbaCzerwonychPionkow--;
					if (!CzerwonyTuraCzerwony1Perfekcyjny())
					{
						liczbaNiebieskichPionkow--;
						(*plansza[i])[k]->setPionek(pusty);
						return false;
					}
					liczbaNiebieskichPionkow--;
					(*plansza[i])[k]->setPionek(pusty);
				}
				else {
					liczbaCzerwonychPionkow--;
					(*plansza[i])[k]->setPionek(pusty);
				}
			}
		}
	}

	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty) 
			{
				(*plansza[i])[k]->setPionek(niebieski);
				liczbaNiebieskichPionkow++;
				if (!CzerwonyTuraCzerwony1Perfekcyjny())
				{
					liczbaNiebieskichPionkow--;
					(*plansza[i])[k]->setPionek(pusty);
					return false;
				}
				liczbaNiebieskichPionkow--;
				(*plansza[i])[k]->setPionek(pusty);
			}
		}
	}
	return true;
}

bool PlanszaHEX::CzerwonyTuraCzerwony1Perfekcyjny()
{
	if (CzerwonyTuraCzerwony1Naiwny())
	{
		return true;
	}
	return false;
}

bool PlanszaHEX::NiebieskiTuraNiebieski2Perfekcyjny()
{
	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{
				(*plansza[i])[k]->setPionek(niebieski);
				liczbaNiebieskichPionkow++;
				if (GraSkonczona(niebieski) == 0 && NiebieskiTuraCzerwony1Perfekcyjny())				
				{
					liczbaNiebieskichPionkow--;
					(*plansza[i])[k]->setPionek(pusty);
					return true;
				}
				(*plansza[i])[k]->setPionek(pusty);
				liczbaNiebieskichPionkow--;
			}
		}
	}
	return false;
}

bool PlanszaHEX::NiebieskiTuraCzerwony2Perfekcyjny()
{
	if (CzerwonyTuraCzerwony1Perfekcyjny())
	{
		return false;
	}
	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{
				(*plansza[i])[k]->setPionek(niebieski);
				liczbaNiebieskichPionkow++;
				if (GraSkonczona(niebieski) == 0)
				{
					(*plansza[i])[k]->setPionek(czerwony);
					liczbaCzerwonychPionkow++;
					liczbaNiebieskichPionkow--;
					if (!NiebieskiTuraNiebieski2Perfekcyjny())
					{
						(*plansza[i])[k]->setPionek(pusty);
						liczbaCzerwonychPionkow--;
						return false;
					}
					(*plansza[i])[k]->setPionek(pusty);
					liczbaCzerwonychPionkow--;
				}
				else
				{
					(*plansza[i])[k]->setPionek(pusty);
					liczbaNiebieskichPionkow--;
				}
			}
		}
	}

	for (int i = 0; i < rozmiar; i++)
	{
		for (int k = 0; k < rozmiar; k++)
		{
			if ((*plansza[i])[k]->getPionek() == pusty)
			{
				(*plansza[i])[k]->setPionek(czerwony);
				liczbaCzerwonychPionkow++;
				if (!NiebieskiTuraNiebieski2Perfekcyjny())
				{
					(*plansza[i])[k]->setPionek(pusty);
					liczbaCzerwonychPionkow--;
					return false;
				}
				(*plansza[i])[k]->setPionek(pusty);
				liczbaCzerwonychPionkow--;
			}
		}
	}
	return true;
}
