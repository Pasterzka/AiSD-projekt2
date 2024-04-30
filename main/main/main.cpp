#include <iostream>
#include <vector>
#include <string>

#include "PlanszaHEX.h"
#include "Definicje.h"
#include "HEX.h"

int main()
{
	std::string input = "";
	PlanszaHEX* plansza = nullptr;
	int testy = 1;

	while(std::cin >> input)
	{
		plansza = new PlanszaHEX();
		//std::cout << plansza->getLiczbaPustychPol() << " " << plansza->getLiczbaCzerownychPionkow() << " " << plansza->getLiczbaNiebieskichPionkow() << " " << plansza->GraSkonczona() << " ";
		std::cin >> input;
		//std::cout << plansza->getLiczbaCzerownychPionkow() << " " << plansza->getLiczbaNiebieskichPionkow();
		if (input == "BOARD_SIZE")
		{
			testy = 517;
			std::cout << plansza->getRozmiarPlanszy();
		}
		else if (input == "PAWNS_NUMBER")
		{
			testy = 517;
			std::cout << plansza->getLiczbaPionkow();
		}
		else if (input == "IS_BOARD_CORRECT")
		{
			testy = 517;
			if (plansza->CzyPlanszaPoprawna())
			{
				std::cout << "YES";
			}
			else {
				std::cout << "NO";
			}
		}
		else if (input == "IS_GAME_OVER")
		{
			testy = 1034;
			switch (plansza->GraSkonczona())
			{
			case 0:
				std::cout << "NO";
				break;
			case 1:
				std::cout << "YES RED";
				break;
			case 2:
				std::cout << "YES BLUE";
				break;
			default:
				break;
			}
		}
		else if (input == "IS_BOARD_POSSIBLE")
		{
			testy = 1017;
			if (plansza->CzyPlanszaMozliwa())
			{
				std::cout << "YES";
			}
			else {
				std::cout << "NO";
			}
		}
		else if (input == "CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT")
		{
			testy = 1206;
			plansza->NaiwnyPrzeciwnik();
		}
		else if (input == "CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT")
		{
			plansza->PerfekcyjnyPrzeciwnik();
		}
		delete plansza;
		std::cout << "\n\n";
	}
	return 0;
}
/*
		  ---
	   --<   >--
	--< b >-< b >--
 --<   >-<   >-< r >--
< b >-< r >-<   >-<   >
 --<   >-< b >-< r >--
	--< b >-< r >--
	   --< r >--
		  ---
CAN_RED_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_1_MOVE_WITH_PERFECT_OPPONENT
CAN_RED_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
CAN_BLUE_WIN_IN_2_MOVES_WITH_PERFECT_OPPONENT
*/