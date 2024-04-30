#include "HEX.h"

HEX::HEX(int kolor)
{
	pionek = kolor;
	odwiedzony = false;
}

HEX::HEX()
{
	pionek = 0;
	odwiedzony = false;
}

int HEX::getPionek()
{
	return this->pionek;
}

bool HEX::getOdwiedzony()
{
	return this->odwiedzony;
}

void HEX::setOdwiedzony(bool odwiedziny)
{
	this->odwiedzony = odwiedziny;
}

void HEX::setPionek(int pionek)
{
	this->pionek = pionek;
}
