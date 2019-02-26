#include <iostream>
#include <exception>
#include "mokinys.h"
#include "funkcijos.h"

int main() {
	try {
		std::vector<mokinys> mokiniai;
		int maxVardIlgis = 6, maxPavardIlgis = 7; //"vardas" - 6 simboliai//"pavarde" - 7 simboliai

		std::cout << "\n--Mokiniu rezultatu skaiciavimo programa--" << std::endl;
		int ivedKrit; //Įvedimo kriterijus//Galimos reikšmės: 1-2
		std::cout << "  Pasirinkite pazymiu ivesties rezima:\n1. Pazymiu ivedimas ranka\n2. Atsitiktinis pazymiu generavimas\n3. Duomenu skaitymas is failo\n";
		ivedKrit = int_ivestis();
		while (ivedKrit < 1 && ivedKrit > 3) {
			std::cout << "Netinkamas pasirinkimas. Galimi pasirinkimai:\n1. Pazymiu ivedimas ranka\n2. Atsitiktinis pazymiu generavimas\n3. Duomenu skaitymas is failo\n";
			ivedKrit = int_ivestis();
		}
		switch (ivedKrit) {
		case 1:
			ivestiMokinius(mokiniai, 1, maxVardIlgis, maxPavardIlgis);
			break;
		case 2:
			ivestiMokinius(mokiniai, 2, maxVardIlgis, maxPavardIlgis);
			break;
		case 3:
			skaitytiMokinius(mokiniai, maxVardIlgis, maxPavardIlgis);
			break;
		default:
			std::cout << "Sveikinu, jums pavyko sugadinti programa.";
			break;
		}

		std::cout << "Pagal ka norite rikiuoti mokinius?\n1. Varda\n2. Pavarde\n";
		int pasirink = int_ivestis();
		while (pasirink != 1 && pasirink != 2) {
			std::cout << "\nNetinkamas pasirinkimas. Galimi pasirinkimai:\n1. Vidurkis\n2. Mediana\nJusu pasirinkimas: ";
			pasirink = int_ivestis();
		}
		rikiuotiMokinius(mokiniai, pasirink);
		spausdintiMokinius(mokiniai, maxVardIlgis, maxPavardIlgis);
	} catch (std::exception& e) {}
}