#pragma once

#include <iostream>
#include <vector>

#include "HEX.h"

class PlanszaHEX {
private:
	int liczbaCzerwonychPionkow;
	int liczbaNiebieskichPionkow;
	int liczbaPol;
	int liczbaPustePola;
	std::vector<std::vector<HEX*>*> plansza;
public:
	PlanszaHEX();
	int getLiczbaCzerownychPionkow();
	int getLiczbaNiebieskichPionkow();
	int getLiczbaPol();
	int getLiczbaPionkow();
	int getRozmiarPlanszy();
	bool CzyPlanszaPoprawna();
	bool CzerwonyDFS(int x, int y);
	bool NiebieskiDFS(int x, int y);
	int GraSkonczona();
	bool NiebiskiWygral();
	bool CzerwonyWygral();
	bool CzyPlanszaMozliwa();
	void ResetOdwiedziny();
	int Tura();
	int getLiczbaPustychPol();


	bool CzerwonyWJednymRuchu();
	bool NiebieskiWJednymRuchu();

	bool CzerwonyWDwochRuchach();
	bool NiebieskiWDwochRuchach();

	void NaiwnyPrzeciwnik();
};