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
	int rozmiar;
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

	int GraSkonczona(int kolor);

	bool NiebieskiTuraNiebieski1Naiwny();
	bool NiebieskiTuraCzerwony1Naiwny();

	bool CzerwonyTuraNiebieski1Naiwny();
	bool CzerwonyTuraCzerwony1Naiwny();

	bool NiebieskiTuraNiebieski2Naiwny();
	bool NiebieskiTuraCzerwony2Naiwny();

	bool CzerwonyTuraNiebieski2Naiwny();
	bool CzerwonyTuraCzerwony2Naiwny();

	bool CzerwonyWJednymRuchuNaiwny();
	bool NiebieskiWJednymRuchuNaiwny();

	bool CzerwonyWDwochRuchachNaiwny();
	bool NiebieskiWDwochRuchachNaiwny();

	void NaiwnyPrzeciwnik();


	bool NiebieskiTuraNiebieski1Perfekcyjny();
	bool NiebieskiTuraCzerwony1Perfekcyjny();

	bool CzerwonyTuraNiebieski1Perfekcyjny();
	bool CzerwonyTuraCzerwony1Perfekcyjny();

	bool NiebieskiTuraNiebieski2Perfekcyjny();
	bool NiebieskiTuraCzerwony2Perfekcyjny();

	bool CzerwonyTuraNiebieski2Perfekcyjny();
	bool CzerwonyTuraCzerwony2Perfekcyjny();

	bool CzerwonyWJednymRuchuPerfekcyjny();
	bool NiebieskiWJednymRuchuPerfekcyjny();

	bool CzerwonyWDwochRuchachPerfekcyjny();
	bool NiebieskiWDwochRuchachPerfekcyjny();

	void PerfekcyjnyPrzeciwnik();

	~PlanszaHEX();
};