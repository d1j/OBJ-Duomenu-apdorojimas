#include "mokinys.h"

using std::cout;
using std::endl;
using std::setw;


void mokinys::spausdintiInfo(int maxVardIlgis, int maxPavardIlgis) {
	cout << setw(maxVardIlgis + 2) << std::left << vardas << setw(maxPavardIlgis + 2) << pavarde;
	cout << std::setprecision(2) << std::fixed << setw(18) << (0.4 * vidurkis) + (0.6 * egz)
	     << std::setprecision(2) << std::fixed << setw(18) << (0.4 * mediana) + (0.6 * egz) << endl;
}

void mokinys::skaiciuotiVidurki() {
	int sk = pazym.size();
	if (sk == 0) throw std::logic_error("Nera namu darbu pazymiu, apskaiciuoti vidurkio negalima.");
	int suma = 0;
	for (int i = 0; i < sk; i++) {
		suma += pazym[i];
	}
	vidurkis = 1.0 * suma / sk;

}

void mokinys::skaiciuotiMediana() {
	int sk = pazym.size();
	if (sk == 0) throw std::logic_error("Nera namu darbu pazymiu, apskaiciuoti medianos negalima.");
	//Prieš skaičiavimą išrikiuojame masyvo elementus didėjimo tvarka.
	std::sort(pazym.begin(), pazym.end());
	//Nustatome mediana
	if (sk % 2 == 1) {
		//Nelyginis skaičius pažymiu
		mediana = pazym[(sk - 1) / 2];
	}
	else {
		//Lyginis skaičius pažymiu
		mediana = 1.0 * (pazym[sk / 2 - 1] + pazym[sk / 2]) / 2;
	}

}