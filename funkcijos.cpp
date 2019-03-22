#include "funkcijos.h"

#include <iostream>
#include <random>
#include <fstream>

using std::cin;
using std::cout;

bool ar_failas_egzistuoja(std::string pav){
    std::ifstream in(pav);
    bool retVal = in.good();
    in.close();
    return retVal;
}

int int_ivestis() {
	int kint;
	//Šis ciklas paimtas iš forumo
	//https://stackoverflow.com/questions/10349857/how-to-handle-wrong-data-type-input?fbclid=IwAR1QXefXVDUfLMLfKrAKSTaEVU8V7i0oYiCUNbWBezPRGnkpMBsaj2-j-9A
	while (!(cin >> kint)) {
		cin.clear(); //clear bad input flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		cout << "\nIvesta bloga reiksme. Iveskite reiksme is naujo: ";
	}
	//Sekančių dviejų eilučių reikia, kad išvengtume automatinės įvesties. PVZ.:
	//Pasirenku generuoti pažymius atsitiktinai.
	//Kai reikia rinktis, kiek pažymių noriu generuoti, įvedu reikšmę: "1asdasd"
	//Be šių sekančių kodo eilučių, programa nuskaitys "1" kaip pažymių skaičių, o likusi įvesties dalis "asdasd" bus automatiškai įvesta
	//į pirmo mokinio vardo vietą.
	cin.clear(); //clear bad input flag
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
	return kint;
}

int gen_reiksm(int intPrad, int intPab){
	//Kodo gabaliukas paimtas iš interneto
	static std::random_device rd; //atsitiktinis įrenginys
	static std::mt19937 mt(rd()); //atsitiktinių skaičių generavimo variklis
	std::uniform_int_distribution<int> dist(intPrad, intPab); //intervalas, kuriame generuojame skaičius
	return dist(mt);
}

bool arDoubleLygus(double dFirstVal, double dSecondVal)
{
	return std::fabs(dFirstVal - dSecondVal) < 1E-3;
}
