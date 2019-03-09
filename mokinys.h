w#ifndef MOKINYS_H
#define MOKINYS_H

#include <vector>
#include <string>
#include <fstream>

struct mokinys {
	std::string vardas = "";
	std::string pavarde = "";
	std::vector<int> pazym;
	double egz = 0; //egzamino pažymys
	double vidurkis = 0; //namų darbų pažymių vidurkis
	double mediana = 0; //namų darbų pažymių mediana

	void isvestiInfo(std::ofstream& out,int maxVardIlgis, int maxPavardIlgis, int vardPavKrit);

	void spausdintiInfo(int maxVardIlgis, int maxPavardIlgis, int pasirink);

	void skaiciuotiVidurki();

	void skaiciuotiMediana();
};

#endif