#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>
#include <algorithm>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::vector;

struct mokinys {
	string vardas = "";
	string pavarde = "";
	vector<int> pazym;
	int egz = 0; //egzamino pažymys
	double vidurkis = 0; //namų darbų pažymių vidurkis
	double mediana = 0; //namų darbų pažymių mediana

	void spausdintiInfo(int kriterijus, int maxVardIlgis, int maxPavardIlgis) {
		cout << setw(maxVardIlgis + 2) << std::left << vardas << setw(maxPavardIlgis + 2) << pavarde;
		switch (kriterijus) {
		case 1:
			cout << std::setprecision(2) << std::fixed << setw(16) << (0.4 * vidurkis) + (0.6 * egz) << endl;
			break;
		case 2:
			cout << std::setprecision(2) << std::fixed << (0.4 * mediana) + (0.6 * egz) << endl;
			break;
		default:
			cout << "Sveikinu, jums pavyko sugadinti programa.";
			break;
		}
	}

	void skaiciuotiVidurki() {
		int sk = pazym.size();
		//Jei yra bent vienas pažymys
		if (sk > 0) {
			int suma = 0;
			for (int i = 0; i < sk; i++) {
				suma += pazym[i];
			}
			vidurkis = 1.0 * suma / sk;
		}
	}

	void skaiciuotiMediana() {
		int sk = pazym.size();
		//Jei yra bent vienas pažymys
		if (sk > 0) {
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
	}
};

void spausdintiMokinius(vector<mokinys> &mokiniai, int kriterijus, int maxVardIlgis, int maxPavardIlgis) {
	cout << std::left << setw(maxVardIlgis + 2) << "Vardas" << setw(maxPavardIlgis + 2) << "Pavarde";
	switch (kriterijus) {
	case 1:
		cout << "Galutinis (Vid.)\n";
		break;
	case 2:
		cout << "Galutinis (Med.)\n";
		break;
	default:
		cout << "Sveikinu, jums pavyko sugadinti programa.";
		break;
	}
	string linija(maxVardIlgis + maxPavardIlgis + 4, '-');
	cout << linija << "----------------\n";
	for (int i = 0; i < mokiniai.size(); i++) {
		mokiniai[i].spausdintiInfo(kriterijus, maxVardIlgis, maxPavardIlgis);
	}
}

void generuotiPazymius(mokinys &esamas, int pazSk) {
	//Kodo gabaliukas paimtas iš interneto
	std::random_device rd; //atsitiktinis įrenginys
	std::mt19937 mt(rd()); //atsitiktinių skaičių generavimo variklis
	std::uniform_int_distribution<int> dist(1, 10); //intervalas, kuriame generuojame skaičius

	for (int i = 0; i < pazSk; i++) {
		esamas.pazym.push_back(dist(mt));
	}
	esamas.egz = dist(mt);

}

//Apsaugota sveikojo skaičiaus įvedimo funkcija.
//Tokia įvestis užtkrina kad į "int" tipo kintamąjį nebus bandoma įrašyti nepalaikomo tipo duomenų
int int_ivestis() {
	int kint;
	//Šis ciklas paimtas iš forumo
	//https://stackoverflow.com/questions/10349857/how-to-handle-wrong-data-type-input?fbclid=IwAR1QXefXVDUfLMLfKrAKSTaEVU8V7i0oYiCUNbWBezPRGnkpMBsaj2-j-9A
	while (!(std::cin >> kint)) {
		std::cin.clear(); //clear bad input flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		std::cout << "\nIvesta bloga reiksme. Iveskite reiksme is naujo: ";
	}
	//šių dviejų eilučių reikia, kad išvengtume automatinės vardo įvesties. PVZ.:
	//Pasirenku generuoti pažymius atsitiktinai.
	//Kai reikia rinktis, kiek pažymių noriu generuoti, įvedu reikšmę: "1asdasd"
	//Be šių sekančių kodo eilučių, programa nuskaitys "1" kaip pažymių skaičių, o likusi įvesties dalis "asdasd" bus automatiškai įvesta
	//į pirmo mokinio vardo vietą.
	std::cin.clear(); //clear bad input flag
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
	return kint;
	return kint;
}

//Pagrindinė įvesties funkcija
//rėžimas == 1 - pažymiu įvestis ranka
//rėžimas == 2 - pažymiu generavimas
void ivestiMokinius(vector<mokinys> &mokiniai, int rezimas, int &maxVardIlgis, int &maxPavardIlgis) {
	mokinys esamas;
	int genPazSk = 0;
	cout << "---------------------------------------------------------\n";
	switch (rezimas) {
	case 1:
		cout << "Noredami baigti vesti NAMU DARBU PAZYMIUS, irasykite: \"0\"" << endl;
		cout << "Noredami baigti vesti MOKINIUS, irasykite: \"-\"" << endl;
		break;
	case 2:
		cout << "Iveskite, kiek mokinys turi tureti pazymiu: ";
		genPazSk = int_ivestis();
		while (genPazSk < 0 && genPazSk < 10000000) {
			cout << "\nNetinkamas skaicius. Mokiniai pazymiu gali tureti nuo 1 iki 10 000 000. Iveskite skaiciu is naujo: ";
			genPazSk = int_ivestis();
		}
		cout << "Noredami baigti vesti MOKINIUS, irasykite: \"-\"" << endl;
		break;
	default:
		cout << "Sveikinu, jums pavyko sugadinti programa.";
		break;
	}
	int mokSk = 0; //kintamasis, sekantis, kiek mokinių įvesta
	int pazymSk; //kintamasis, sekantis, kiek vieno mokinio pažymiu įvesta esamu laiku
	int pazymys; //pagalbinis kintamasis pažymio įvedimui
	do {
		cout << mokSk + 1 << " mokinio vardas: "; cin >> esamas.vardas;
		if (esamas.vardas != "-") {
			if (esamas.vardas.size() > maxVardIlgis) maxVardIlgis = esamas.vardas.size();
			esamas.egz = 0;
			esamas.pazym.clear();
			esamas.vidurkis = 0;
			esamas.mediana = 0;
			pazymSk = 0;
			cout << mokSk + 1 << " mokinio pavarde: "; cin >> esamas.pavarde;
			if (esamas.pavarde != "-") {
				if (esamas.pavarde.size() > maxPavardIlgis) maxPavardIlgis = esamas.pavarde.size();
				if (rezimas == 1) cout << "Namu darbu pazymiai: \n";
				switch (rezimas) {
				case 1:
					do {
						cout << pazymSk + 1 << ". ";
						pazymys = int_ivestis();
						if (pazymys != 0 && pazymys >= 1 && pazymys <= 10) {
							esamas.pazym.push_back(pazymys);
							pazymSk++;
						}
						else if (pazymys != 0) {
							cout << " Galimi pazymiai: 1-10. Iveskite 0, jei norite baigti ivesti.\n";
						}
					} while (pazymys != 0);
					cout << "Egzamino pazymys: ";
					esamas.egz = int_ivestis();
					while (esamas.egz < 1 || esamas.egz > 10) {
						cout << "Netinkamas pazymys. Galimi pazymiai: 1-10. Iveskite pazymi is naujo: ";
						esamas.egz = int_ivestis();
					}
					break;
				case 2:
					generuotiPazymius(esamas, genPazSk);
					break;
				default:
					cout << "Blogai parinktas pazymiu ivesties rezimas.\nGalimi variantai:\n1. Ivestis ranka\n2. Atsitiktiniu pazymiu generavimas\n";
					break;
				}
				esamas.skaiciuotiVidurki();
				esamas.skaiciuotiMediana();
				mokiniai.push_back(esamas);
				mokSk++;
			}
		}
	} while (esamas.vardas != "-" && esamas.pavarde != "-");
}

int main() {
	vector<mokinys> mokiniai;
	int maxVardIlgis = 6, maxPavardIlgis = 7; //"vardas" - 6 simboliai//"pavarde" - 7 simboliai

	cout << "--Mokiniu rezultatu skaiciavimo programa--" << endl;
	int ivedKrit; //Įvedimo kriterijus//Galimos reikšmės: 1-2
	cout << "Pasirinkite pazymiu ivesties rezima:\n1. Pazymiu ivedimas ranka\n2. Atsitiktinis pazymiu generavimas\n";
	ivedKrit = int_ivestis();
	while (ivedKrit != 1 && ivedKrit != 2) {
		cout << "Netinkamas pasirinkimas. Galimi pasirinkimai:\n1. Pazymiu ivedimas ranka\n2. Atsitiktinis pazymiu generavimas\n";
		ivedKrit = int_ivestis();
	}
	switch (ivedKrit) {
	case 1:
		ivestiMokinius(mokiniai, 1, maxVardIlgis, maxPavardIlgis);
		break;
	case 2:
		ivestiMokinius(mokiniai, 2, maxVardIlgis, maxPavardIlgis);
		break;
	default:
		cout << "Sveikinu, jums pavyko sugadinti programa.";
		break;
	}

	cout << "Pagal ka norite matyti mokininiu vertinimus?\n1. Vidurki\n2. Mediana\n";
	int vertKrit = int_ivestis();
	while (vertKrit != 1 && vertKrit != 2) {
		cout << "\nNetinkamas pasirinkimas. Galimi pasirinkimai:\n1. Vidurkis\n2. Mediana\nJusu pasirinkimas: ";
		vertKrit = int_ivestis();
	}
	spausdintiMokinius(mokiniai, vertKrit, maxVardIlgis, maxPavardIlgis);
}