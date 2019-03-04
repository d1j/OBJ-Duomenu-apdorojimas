#include "funkcijos.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::vector;

void spausdintiMokinius(vector<mokinys> &mokiniai, int maxVardIlgis, int maxPavardIlgis) {
	cout << std::left << setw(maxVardIlgis + 2) << "Vardas" << setw(maxPavardIlgis + 2) << "Pavarde";
	cout << "Galutinis (Vid.)  Galutinis (Med.)\n";
	string linija(maxVardIlgis + maxPavardIlgis + 4, '-');
	cout << linija << "----------------------------------\n";
	for (int i = 0; i < mokiniai.size(); i++) {
		mokiniai[i].spausdintiInfo(maxVardIlgis, maxPavardIlgis);
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
	//Sekančių dviejų eilučių reikia, kad išvengtume automatinės vardo įvesties. PVZ.:
	//Pasirenku generuoti pažymius atsitiktinai.
	//Kai reikia rinktis, kiek pažymių noriu generuoti, įvedu reikšmę: "1asdasd"
	//Be šių sekančių kodo eilučių, programa nuskaitys "1" kaip pažymių skaičių, o likusi įvesties dalis "asdasd" bus automatiškai įvesta
	//į pirmo mokinio vardo vietą.
	std::cin.clear(); //clear bad input flag
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
	return kint;
}

//Pagrindinė įvesties funkcija
//rėžimas == 1 - pažymiu įvestis ranka
//rėžimas == 2 - pažymiu generavimas
void ivestiMokinius(vector<mokinys> &mokiniai, int rezimas, int &maxVardIlgis, int &maxPavardIlgis) {
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
	mokinys esamas;
	int mokSk = 0; //kintamasis, sekantis, kiek mokinių įvesta
	int pazymSk; //kintamasis, sekantis, kiek vieno mokinio pažymiu įvesta esamu laiku
	int pazymys; //pagalbinis kintamasis pažymio įvedimui
	do {
		esamas.vidurkis = 0;
		esamas.mediana = 0;
		esamas.egz = 0;
		esamas.pazym.clear();
		cout << "\"-\" - baigti vesti mokinius\n" << mokSk + 1 << " mokinio vardas: "; cin >> esamas.vardas;
		if (esamas.vardas != "-") {
			if (esamas.vardas.size() > maxVardIlgis) maxVardIlgis = esamas.vardas.size();
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
				try {
					esamas.skaiciuotiVidurki();
					esamas.skaiciuotiMediana();
				} catch (std::exception& e) {
					cout << "Nepavyko apskaiciuoti mokinio vidurkio/medianos: " << e.what() << endl;
				}
				mokiniai.push_back(esamas);
				mokSk++;
			}
		}
	} while (esamas.vardas != "-" && esamas.pavarde != "-");
}

void skaitytiMokinius(vector<mokinys> &mokiniai, int &maxVardIlgis, int &maxPavardIlgis) {
	string pavadinimas;
	cout << "Iveskite failo pavadinima (PVZ failas.txt): "; cin >> pavadinimas;
	try {
		std::ifstream input(pavadinimas);
		if (input.fail()) throw std::runtime_error("Nurodytas failas neegzistuoja!");
		int mokSk, ndSk;
		input >> mokSk >> ndSk;
		if (input.fail() || mokSk <= 0 || ndSk < 0) throw std::logic_error("Mokiniu skaicius arba namu darbu skaicius ivestas neteisingai!");
		for (int i = 0; i < mokSk; i++) {
			mokinys esamas;
			int pazymys;
			input >> esamas.vardas >> esamas.pavarde;
			if (esamas.vardas.size() > maxVardIlgis) maxVardIlgis = esamas.vardas.size();
			if (esamas.pavarde.size() > maxPavardIlgis) maxPavardIlgis = esamas.pavarde.size();
			for (int j = 0; j < ndSk; j++) {
				input >> pazymys;
				if ( pazymys <= 0 || pazymys > 10)
					throw std::logic_error("Mokiniu duomenys ivesti neteisingu formatu!");
				esamas.pazym.push_back(pazymys);
			}
			input >> esamas.egz;
			try {
				esamas.skaiciuotiVidurki();
				esamas.skaiciuotiMediana();
			} catch (std::exception& e) {
				cout << "Nepavyko apskaiciuoti mokinio vidurkio/medianos: " << e.what() << endl;
			}
			mokiniai.push_back(esamas);
		}
		input.close();
	} catch (std::exception& e) {
		cout << "Ivyko klaida. " << e.what() << endl;
		throw; //Erroras permetamas i funkciją kvietėją. Šiuo atvėju main funkciją.
		//Ten bus sugautas tas pats erroras ir nebus vykdoma sekanti dalis kodo, einanti po įvykusios klaidos.
	}
}


bool rikVard(mokinys i, mokinys j) { return (i.vardas < j.vardas); }
bool rikPavard(mokinys i, mokinys j) { return (i.pavarde < j.pavarde); }
void rikiuotiMokinius(vector<mokinys> &mokiniai, int pasirinkimas) {
	if (pasirinkimas == 1) {
		//Rikiavimas pagal vardą
		sort(mokiniai.begin(), mokiniai.end(), rikVard);
	}
	else if (pasirinkimas == 2) {
		//Rikiavimas pagal pavardę
		sort(mokiniai.begin(), mokiniai.end(), rikPavard);
	}
	else {
		//Klaida
		cout << "Ivyko nenumatyta klaida...";
	}
}
