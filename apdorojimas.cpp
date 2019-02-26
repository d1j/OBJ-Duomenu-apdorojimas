#include "apdorojimas.h"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <exception>
#include <stdexcept>

#include "mokinys.h"
#include "funkcijos.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::vector;

//Apsaugota sveikojo skaičiaus įvedimo funkcija.
//Tokia įvestis užtkrina kad į "int" tipo kintamąjį nebus bandoma įrašyti nepalaikomo tipo duomenų

void spausdintiMokinius(vector<mokinys> &mokiniai, int maxVardIlgis, int maxPavardIlgis, int pasirink) {
	if (pasirink == 1) {
		cout << std::left << setw(maxVardIlgis + 2) << "Vardas" << setw(maxPavardIlgis + 2) << "Pavarde";
	} else if (pasirink == 2) {
		cout << std::left << setw(maxPavardIlgis + 2) << "Pavarde" << setw(maxVardIlgis + 2) << "Vardas";
	} else {
		//Nenumatyta klaida
		cout << "Nenumatyta klaida.\n";
	}
	cout << "Galutinis (Vid.)  Galutinis (Med.)\n";
	string linija(maxVardIlgis + maxPavardIlgis + 4, '-');
	cout << linija << "----------------------------------\n";
	for (int i = 0; i < mokiniai.size(); i++) {
		mokiniai[i].spausdintiInfo(maxVardIlgis, maxPavardIlgis, pasirink);
	}
}

void generuotiPazymius(mokinys &esamas, int pazSk) {
	for (int i = 0; i < pazSk; i++) {
		esamas.pazym.push_back(gen_reiksm(1, 10));
	}
	esamas.egz = gen_reiksm(1, 10);
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

//Funkcija atlieka v0.4 užduotį ir sudaro du mokinių sąrašus atskiruose failuose "./rezultatai" aplanke
void isvestiMokinius(vector<mokinys> &mokiniai, int maxVardIlgis, int maxPavardIlgis, int vardPavKrit) {
	bool pavPower = true;
	std::string pavad;
	while (pavPower) {
		cout << "Iveskite tinkama rezultatu failo pavadinima (failo formato vesti nereikia. Programa automatiskai sukuria .txt formato rezultatu failus): ";
		cin >> pavad;
		if (ar_failas_egzistuoja("./rezultatai/" + pavad + "_kiet.txt") ||
		        ar_failas_egzistuoja("./rezultatai/" + pavad + "_varg.txt")) {
			//Failas jau egzistuoja
			int perrPasKrit; //perrašymo pasirinkimo kriterijus. Galimos reikšmės: 1-2
			cout << "Failai nurodytu pavadinimu jau sukurti, ar norite perrasyti siuos failus?\n1.Taip\n2.Ne\n: ";
			perrPasKrit = int_ivestis();
			while (perrPasKrit != 1 && perrPasKrit != 2) {
				cout << "Ivesta negalima reiksme. Iveskite reiksme per naujo: ";
				perrPasKrit = int_ivestis();
			}
			if (perrPasKrit == 1) {
				cout << "Failai pavadinimu " << pavad + "_kiet.txt ir " + pavad + "_varg.txt bus perrasyti.\n";
				pavPower = false;
			} else {
				cout << "Failai pavadinimu " << pavad + "_kiet.txt ir " + pavad + "_varg.txt nebus perrasyti.\n";
			}
		} else {
			//Failas neegzistuoja, galima kurti nauja faila
			pavPower = false;
		}
	}
	cout << "Pagal ka norite skaiciuoti rezultatus?\n1. Vidurki\n2. Mediana\n: ";
	int rezKrit = int_ivestis();
	while (rezKrit != 1 && rezKrit != 2) {
		cout << "Negalima reiksme. Iveskite reiksme is naujo: ";
		rezKrit = int_ivestis();
	}

	std::ofstream kietOut("./rezultatai/" + pavad + "_kiet.txt"),
	    vargOut("./rezultatai/" + pavad + "_varg.txt");
	if (vardPavKrit == 1) {
		kietOut << std::left << setw(maxVardIlgis + 2) << "Vardas" << setw(maxPavardIlgis + 2) << "Pavarde";
		vargOut << std::left << setw(maxVardIlgis + 2) << "Vardas" << setw(maxPavardIlgis + 2) << "Pavarde";
	} else if (vardPavKrit == 2) {
		kietOut << std::left << setw(maxPavardIlgis + 2) << "Pavarde" << setw(maxVardIlgis + 2) << "Vardas";
		vargOut << std::left << setw(maxPavardIlgis + 2) << "Pavarde" << setw(maxVardIlgis + 2) << "Vardas";
	} else {
		//Nenumatyta klaida
		kietOut << "Nenumatyta klaida.\n";
		vargOut << "Nenumatyta klaida.\n";
	}
	kietOut << "Galutinis (Vid.)  Galutinis (Med.)\n";
	vargOut << "Galutinis (Vid.)  Galutinis (Med.)\n";
	string linija(maxVardIlgis + maxPavardIlgis + 4, '-');
	kietOut << linija << "----------------------------------\n";
	vargOut << linija << "----------------------------------\n";
	for (int i = 0; i < mokiniai.size(); ++i) {
		mokinys esamas = mokiniai[i];
		if (rezKrit == 1) {
			//Išvedimas pagal vidurkį
			if ((esamas.vidurkis * 0.4 + esamas.egz * 0.6) >= 5) {
				//mokinys patenka į kietųjų sąrašą
				esamas.isvestiInfo(kietOut, maxVardIlgis, maxPavardIlgis, vardPavKrit);
			} else {
				//mokinys patenka į vargšų sąrašą
				esamas.isvestiInfo(vargOut, maxVardIlgis, maxPavardIlgis, vardPavKrit);
			}
		} else if (rezKrit == 2 ) {
			//Išvedimas pagal medianą
			if ((esamas.mediana * 0.4 + esamas.egz * 0.6) >= 5) {
				//mokinys patenka į kietųjų sąrašą
				esamas.isvestiInfo(kietOut, maxVardIlgis, maxPavardIlgis, vardPavKrit);
			} else {
				//mokinys patenka į vargšų sąrašą
				esamas.isvestiInfo(vargOut, maxVardIlgis, maxPavardIlgis, vardPavKrit);
			}
		}
	}
	kietOut.close();
	vargOut.close();
	cout<<"Rezultatai sekmingai isvesti\n";
}

void skaitytiMokinius(vector<mokinys> &mokiniai, int &maxVardIlgis, int &maxPavardIlgis) {
	string pavadinimas;
	cout << "Iveskite failo pavadinima (PVZ failas.txt): "; cin >> pavadinimas;
	try {
		if (!ar_failas_egzistuoja("./duomenys/" + pavadinimas)) throw std::runtime_error("Nurodytas failas neegzistuoja!");
		std::ifstream input("./duomenys/" + pavadinimas);
		if (input.fail()) throw std::runtime_error("Nurodytas failas neatsidare!");
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
		throw; //Erroras permetamas į funkciją kvietėją. Šiuo atvėju "skaiciuotiRezultatus()" funkciją.
		//Ten bus sugautas tas pats erroras ir nebus vykdoma sekanti dalis kodo, einanti po įvykusios klaidos.
	}
}

//Pagalbinė funkcija, nustatanti mokinio pirmenybę sąraše tarp dviejų mokinių pagal Vardą
bool rikVard(mokinys i, mokinys j) {
	if (i.vardas < j.vardas) {
		return true;
	}
	else if (i.vardas == j.vardas) {
		if (i.pavarde < j.pavarde)
			return true;
		else
			return false;
	} else {
		return false;
	}
}
//Pagalbinė funkcija, nustatanti mokinio pirmenybę sąraše tarp dviejų mokinių pagal pavardę
bool rikPavard(mokinys i, mokinys j) {
	if (i.pavarde < j.pavarde) {
		return true;
	}
	else if (i.pavarde == j.pavarde) {
		if (i.vardas < j.vardas)
			return true;
		else
			return false;
	} else {
		return false;
	}

	return (i.pavarde < j.pavarde);
}
//Mokinių rikiavimo funkcija
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

//Pagrindinė apdorojimo funkcija
void skaiciuotiRezultatus() {
	try {
		vector<mokinys> mokiniai;
		int maxVardIlgis = 6, maxPavardIlgis = 7; //"vardas" - 6 simboliai//"pavarde" - 7 simboliai

		cout << "REZULTATU SKAICIAVIMAS\n";
		cout << "Pasirinkite pazymiu ivesties rezima:\n1. Pazymiu ivedimas ranka\n2. Atsitiktinis pazymiu generavimas\n3. Duomenu skaitymas is failo\n";
		int ivedKrit; //Įvedimo kriterijus//Galimos reikšmės: 1-2
		ivedKrit = int_ivestis();
		while (ivedKrit < 1 && ivedKrit > 4) {
			cout << "Netinkamas pasirinkimas. Galimi pasirinkimai:\n1. Pazymiu ivedimas ranka\n2. Atsitiktinis pazymiu generavimas\n3. Duomenu skaitymas is failo\n4. Atgal\n: ";
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
		case 4:
			break;
		default:
			cout << "Sveikinu, jums pavyko sugadinti programa.";
			break;
		}
		if (ivedKrit != 4) {
			cout << "Pagal ka norite rikiuoti mokinius?\n1. Varda\n2. Pavarde\n";
			int vardPavKrit = int_ivestis(); //Vardo/Pavardės kriterijus. Galimi variantai : 1-2
			while (vardPavKrit != 1 && vardPavKrit != 2) {
				cout << "\nNetinkamas pasirinkimas. Galimi pasirinkimai:\n1. Vidurkis\n2. Mediana\nJusu pasirinkimas: ";
				vardPavKrit = int_ivestis();
			}
			rikiuotiMokinius(mokiniai, vardPavKrit);
			cout << "Pasirinkite rezultatu isvedimo buda:\n1. Isvedimas konsoles lange (v0.2)\n2. Isvedimas i atskirus failus (v0.4)\n: ";
			int isvedKrit = int_ivestis(); //Rezultatų išvedimo kriterijus. Galimi variantai : 1-2
			while (isvedKrit != 1 && isvedKrit != 2) {
				cout << "Negalimas pasirinkimas, pasirinkite is naujo: ";
				isvedKrit = int_ivestis();
			}
			if (isvedKrit == 1) {
				spausdintiMokinius(mokiniai, maxVardIlgis, maxPavardIlgis, vardPavKrit);

			} else if (isvedKrit == 2) {
				isvestiMokinius(mokiniai, maxVardIlgis, maxPavardIlgis, vardPavKrit);
			} else {
				//Nenumatyta klaida
				cout << "Nenumatyta klaida.\n";
			}
		}
	} catch (std::exception& e) {
		//Kodėl šitas catch blokas tuščias, galbūt paaiškės paskaičius komentarus "skaitytiMokinius" funkcijoje
	}
}
