#pragma once


class HEX {
private:
	int pionek;
	bool odwiedzony;
public:
	HEX(int kolor);
	int getPionek();
	bool getOdwiedzony();
	void setOdwiedzony(bool odwiedziny);
	void setPionek(int pionek);
};