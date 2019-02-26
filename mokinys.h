#ifndef MOKINYS_H
#define MOKINYS_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdexcept>

struct mokinys {
	std::string vardas = "";
	std::string pavarde = "";
	std::vector<int> pazym;
	int egz = 0; //egzamino pažymys
	double vidurkis = 0; //namų darbų pažymių vidurkis
	double mediana = 0; //namų darbų pažymių mediana

	void spausdintiInfo(int maxVardIlgis, int maxPavardIlgis);

	void skaiciuotiVidurki();

	void skaiciuotiMediana();
};

#endif