#include "PlanszaHEX.h"
#include "Definicje.h"


#include <string>

PlanszaHEX::PlanszaHEX()
{
	
	this->liczbaCzerwonychPionkow = 0;
	this->liczbaNiebieskichPionkow = 0;
	this->liczbaPol = 0;

	std::string input;
	std::cin >> input; // skip "---"


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
	if (x == plansza.size()-1) {
		return true;
	}

	// Oznaczenie bie¿¹cej komórki jako odwiedzonej
	(*plansza[x])[y]->setOdwiedzony(true);

	// Przegl¹danie s¹siednich komórek
	for (int i = 0; i < 6; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];

		// Sprawdzenie, czy s¹siednia komórka mieœci siê w granicach i czy nie zosta³a odwiedzona
		if (nx >= 0 && nx < plansza.size() && ny >= 0 && ny < (*plansza[0]).size() && !(*plansza[nx])[ny]->getOdwiedzony() && (*plansza[nx])[ny]->getPionek() == 1) {
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
	if (y == plansza.size()-1) {
		return true;
	}

	// Oznaczenie bie¿¹cej komórki jako odwiedzonej
	(*plansza[x])[y]->setOdwiedzony(true);

	// Przegl¹danie s¹siednich komórek
	for (int i = 0; i < 6; ++i) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		// Sprawdzenie, czy s¹siednia komórka mieœci siê w granicach i czy nie zosta³a odwiedzona
		if (nx >= 0 && nx < plansza.size() && ny >= 0 && ny < (*plansza[0]).size() && !(*plansza[nx])[ny]->getOdwiedzony() && (*plansza[nx])[ny]->getPionek() == 2) {
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
		int RC = plansza.size();
		for (int i = 0; i < RC; ++i) {
			if ((*plansza[0])[i]->getPionek() == czerwony && !(*plansza[0])[i]->getOdwiedzony())
			{
				if (CzerwonyDFS(0,i))
				{
					return 1;
				}
			}
		}

		for (int i = 0; i < RC; ++i) {
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
	int RC = plansza.size();
	for (int i = 0; i < RC; ++i) {
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
	int RC = plansza.size();
	for (int i = 0; i < RC; ++i) {
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
	if (CzyPlanszaPoprawna() && (GraSkonczona() == niebieski && Tura() == czerwony || GraSkonczona() == czerwony && Tura() == niebieski || GraSkonczona() == 0))
	{

		int kolor;
		if (GraSkonczona() != 0)
		{
			if (GraSkonczona() == czerwony)
			{
				kolor = czerwony;
			}
			else {
				kolor = niebieski;
			}

			for (int i = 0; i < plansza.size(); i++)
			{
				for (int k = 0; k < plansza.size(); k++)
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
	for (int i = 0; i < plansza.size(); i++)
	{
		for (int k = 0; k < plansza.size(); k++)
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


bool PlanszaHEX::CzerwonyWJednymRuchu() {
	if (CzyPlanszaMozliwa())
	{
		if (liczbaPustePola >=1 && Tura() == czerwony)
		{
			for (int i = 0; i < getRozmiarPlanszy(); i++)
			{
				for (int k = 0; k < getRozmiarPlanszy(); k++)
				{
					if ((*plansza[i])[k]->getPionek() == pusty)
					{
						(*plansza[i])[k]->setPionek(czerwony);
						if (CzerwonyWygral())
						{
							(*plansza[i])[k]->setPionek(pusty);
							return true;
						}
						(*plansza[i])[k]->setPionek(pusty);
					}
				}
			}
		}
		else if (liczbaPustePola >= 2 && Tura() == niebieski)
		{
			for (int i = 0; i < getRozmiarPlanszy(); i++)
			{
				for (int k = 0; k < getRozmiarPlanszy(); k++)
				{
					if ((*plansza[i])[k]->getPionek() == pusty)
					{
						(*plansza[i])[k]->setPionek(czerwony);
						if (CzerwonyWygral())
						{
							(*plansza[i])[k]->setPionek(pusty);
							return true;
						}
						(*plansza[i])[k]->setPionek(pusty);
					}
				}
			}
		}
	}
	return false;
}

bool PlanszaHEX::NiebieskiWJednymRuchu()
{
	if (CzyPlanszaMozliwa())
	{
		if (liczbaPustePola >= 1 && Tura() == niebieski)
		{
			for (int i = 0; i < getRozmiarPlanszy(); i++)
			{
				for (int k = 0; k < getRozmiarPlanszy(); k++)
				{
					if ((*plansza[i])[k]->getPionek() == pusty)
					{
						(*plansza[i])[k]->setPionek(niebieski);
						if (NiebiskiWygral())
						{
							(*plansza[i])[k]->setPionek(pusty);
							return true;
						}
						(*plansza[i])[k]->setPionek(pusty);
					}
				}
			}
		}
		else if (liczbaPustePola >= 2 && Tura() == czerwony)
		{
			for (int i = 0; i < getRozmiarPlanszy(); i++)
			{
				for (int k = 0; k < getRozmiarPlanszy(); k++)
				{
					if ((*plansza[i])[k]->getPionek() == pusty)
					{
						(*plansza[i])[k]->setPionek(niebieski);
						if (NiebiskiWygral())
						{
							(*plansza[i])[k]->setPionek(pusty);
							return true;
						}
						(*plansza[i])[k]->setPionek(pusty);
					}
				}
			}
		}
	}
	return false;
}

bool PlanszaHEX::CzerwonyWDwochRuchach()
{
	if (CzyPlanszaMozliwa())
	{
		if (Tura() == czerwony && liczbaPustePola >= 3)
		{
			for (int i = 0; i < getRozmiarPlanszy(); i++)
			{
				for (int k = 0; k < getRozmiarPlanszy(); k++)
				{
					if ((*plansza[i])[k]->getPionek() == pusty)
					{
						(*plansza[i])[k]->setPionek(czerwony);
						if (CzerwonyWygral())
						{
							(*plansza[i])[k]->setPionek(pusty);
							
						}
						else {
							for (int l = 0; l < getRozmiarPlanszy(); l++)
							{
								for (int o = 0; o < getRozmiarPlanszy(); o++)
								{
									if ((*plansza[l])[o]->getPionek() == pusty) 
									{
										(*plansza[l])[o]->setPionek(czerwony);
										if (CzerwonyWygral())
										{
											(*plansza[i])[k]->setPionek(pusty);
											(*plansza[l])[o]->setPionek(pusty);
											return true;
										}
										(*plansza[l])[o]->setPionek(pusty);
									}
								}
							}
						}
						(*plansza[i])[k]->setPionek(pusty);
					}
				}
			}
		}
		else if (Tura() == niebieski && liczbaPustePola >= 4)
		{
			for (int i = 0; i < getRozmiarPlanszy(); i++)
			{
				for (int k = 0; k < getRozmiarPlanszy(); k++)
				{
					if ((*plansza[i])[k]->getPionek() == pusty)
					{
						(*plansza[i])[k]->setPionek(czerwony);
						if (CzerwonyWygral())
						{
							(*plansza[i])[k]->setPionek(pusty);

						}
						else {
							for (int l = 0; l < getRozmiarPlanszy(); l++)
							{
								for (int o = 0; o < getRozmiarPlanszy(); o++)
								{
									if ((*plansza[l])[o]->getPionek() == pusty)
									{
										(*plansza[l])[o]->setPionek(czerwony);
										if (CzerwonyWygral())
										{
											(*plansza[i])[k]->setPionek(pusty);
											(*plansza[l])[o]->setPionek(pusty);
											return true;
										}
										(*plansza[l])[o]->setPionek(pusty);
									}
								}
							}
						}
						(*plansza[i])[k]->setPionek(pusty);
					}
				}
			}
		}
	}
	return false;
}

bool PlanszaHEX::NiebieskiWDwochRuchach()
{
	if (CzyPlanszaMozliwa())
	{
		if (Tura() == niebieski && liczbaPustePola >= 3)
		{
			for (int i = 0; i < getRozmiarPlanszy(); i++)
			{
				for (int k = 0; k < getRozmiarPlanszy(); k++)
				{
					if ((*plansza[i])[k]->getPionek() == pusty)
					{
						(*plansza[i])[k]->setPionek(niebieski);
						if (NiebiskiWygral())
						{
							(*plansza[i])[k]->setPionek(pusty);

						}
						else {
							for (int l = 0; l < getRozmiarPlanszy(); l++)
							{
								for (int o = 0; o < getRozmiarPlanszy(); o++)
								{
									if ((*plansza[l])[o]->getPionek() == pusty)
									{
										(*plansza[l])[o]->setPionek(niebieski);
										if (NiebiskiWygral())
										{
											(*plansza[i])[k]->setPionek(pusty);
											(*plansza[l])[o]->setPionek(pusty);
											return true;
										}
										(*plansza[l])[o]->setPionek(pusty);
									}
								}
							}
						}
						(*plansza[i])[k]->setPionek(pusty);
					}
				}
			}
		}
		else if (Tura() == czerwony && liczbaPustePola >= 4)
		{
			for (int i = 0; i < getRozmiarPlanszy(); i++)
			{
				for (int k = 0; k < getRozmiarPlanszy(); k++)
				{
					if ((*plansza[i])[k]->getPionek() == pusty)
					{
						(*plansza[i])[k]->setPionek(niebieski);
						if (NiebiskiWygral())
						{
							(*plansza[i])[k]->setPionek(pusty);

						}
						else {
							for (int l = 0; l < getRozmiarPlanszy(); l++)
							{
								for (int o = 0; o < getRozmiarPlanszy(); o++)
								{
									if ((*plansza[l])[o]->getPionek() == pusty)
									{
										(*plansza[l])[o]->setPionek(niebieski);
										if (NiebiskiWygral())
										{
											(*plansza[i])[k]->setPionek(pusty);
											(*plansza[l])[o]->setPionek(pusty);
											return true;
										}
										(*plansza[l])[o]->setPionek(pusty);
									}
								}
							}
						}
						(*plansza[i])[k]->setPionek(pusty);
					}
				}
			}
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

	//std::cout << GraSkonczona();

	if (GraSkonczona() == 0 && CzerwonyWJednymRuchu() )
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	std::cout << "\n";
	if (GraSkonczona() == 0 && NiebieskiWJednymRuchu())
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	std::cout << "\n";
	if (GraSkonczona() == 0 && CzerwonyWDwochRuchach())
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}
	std::cout << "\n";
	if (GraSkonczona() == 0 && NiebieskiWDwochRuchach())
	{
		std::cout << "YES";
	}
	else {
		std::cout << "NO";
	}





}
