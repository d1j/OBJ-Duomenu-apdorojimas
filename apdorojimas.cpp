#include "apdorojimas.h"

#include <deque>
#include <string>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include <exception>
#include <stdexcept>
#include <chrono>
#include <cmath>

#include "mokinys.h"
#include "funkcijos.h"

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;
using std::deque;
using namespace std::chrono;

//Apsaugota sveikojo skaičiaus įvedimo funkcija.
//Tokia įvestis užtkrina kad į "int" tipo kintamąjį nebus bandoma įrašyti nepalaikomo tipo duomenų

void spausdintiMokinius(deque<mokinys> &mokiniai, int maxVardIlgis, int maxPavardIlgis, int pasirink) {
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
	auto it = mokiniai.begin();
	while (it != mokiniai.end()) {
		it->spausdintiInfo(maxVardIlgis, maxPavardIlgis, pasirink);
		it++;
	}
}

void generuotiPazymius(mokinys &esamas, int pazSk) {
	for (int i = 0; i < pazSk; i++) {
		esamas.pazym.push_back(gen_reiksm(1, 10));
	}
	esamas.egz = gen_reiksm(1, 10);
}

//Pagrindinė įvesties ranka funkcija
//rėžimas == 1 - pažymiu įvestis ranka
//rėžimas == 2 - pažymiu generavimas
void ivestiMokinius(deque<mokinys> &mokiniai, int rezimas, int &maxVardIlgis, int &maxPavardIlgis) {
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
void isvestiMokinius(deque<mokinys> &varg, deque<mokinys> &kiet, int maxVardIlgis, int maxPavardIlgis, int vardPavKrit) {
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

	auto start = high_resolution_clock::now();
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
		cout << "Nenumatyta klaida.\n";
		cout << "Nenumatyta klaida.\n";
	}
	kietOut << "Galutinis (Vid.)  Galutinis (Med.)\n";
	vargOut << "Galutinis (Vid.)  Galutinis (Med.)\n";
	string linija(maxVardIlgis + maxPavardIlgis + 4, '-');
	kietOut << linija << "----------------------------------\n";
	vargOut << linija << "----------------------------------\n";
	auto it = varg.begin();
	while (it != varg. end()) {
		it->isvestiInfo(vargOut, maxVardIlgis, maxPavardIlgis, vardPavKrit);
		it++;
	}
	it = kiet.begin();
	while (it != kiet.end()) {
		it->isvestiInfo(kietOut, maxVardIlgis, maxPavardIlgis, vardPavKrit);
		it++;
	}
	kietOut.close();
	vargOut.close();
	auto end = high_resolution_clock::now();
	duration<double> diff = end - start;
	cout << "\nRezultatai isvesti per: \a" << diff.count() << "s.\n";
}

//Duomenų skaitymo iš failo funkcija
void skaitytiMokinius(deque<mokinys> &mokiniai, int &maxVardIlgis, int &maxPavardIlgis) {
	string pavadinimas;
	int eilute = 0;
	cout << "Iveskite failo pavadinima (PVZ failas.txt): "; cin >> pavadinimas;
	try {
		auto start = high_resolution_clock::now();
		if (!ar_failas_egzistuoja("./duomenys/" + pavadinimas)) throw std::runtime_error("Nurodytas failas neegzistuoja!");
		std::ifstream input("./duomenys/" + pavadinimas);
		if (input.fail()) throw std::runtime_error("Nurodytas failas neatsidare!");

		while (!input.eof()) {
			mokinys esamas;
			eilute++;
			int pap;
			input >> esamas.vardas
			      >> esamas.pavarde;
			if (esamas.vardas == "" || esamas.pavarde == "") continue;
			if (esamas.vardas.size() > maxVardIlgis) maxVardIlgis = esamas.vardas.size();
			if (esamas.pavarde.size() > maxPavardIlgis) maxPavardIlgis = esamas.pavarde.size();
			while (input.peek() != '\n' && !input.eof()) {
				input >> pap;
				if (input.fail()) {
					throw std::runtime_error("Nepavyko nuskaityti duomenu, patikrinkite, ar gerai ivedete duomenis. Klaida " + std::to_string(eilute) + "-oje eiluteje.");
				}
				if (pap < 1  || pap > 10) {
					throw std::runtime_error("Nepavyko nuskaityti duomenu, patikrinkite, ar gerai ivedete duomenis. Klaida " + std::to_string(eilute) + "-oje eiluteje.");
				}
				esamas.pazym.push_back(pap);
			}
			if (esamas.pazym.size() < 2) {
				throw std::logic_error("Mokinys turi tik viena pazymi, negalima nustatyti ar tai namu darbo pazymys ar egzamino pazymys. Klaida " + std::to_string(eilute) + "-oje eiluteje.");
			}
			esamas.egz = esamas.egz = esamas.pazym[esamas.pazym.size() - 1];
			esamas.pazym.pop_back();
			try {
				esamas.skaiciuotiVidurki();
				esamas.skaiciuotiMediana();
			} catch (std::exception& e) {
				cout << "Nepavyko apskaiciuoti mokinio vidurkio/medianos: " << e.what() << endl;
			}
			mokiniai.push_back(esamas);
		}
		input.close();
		auto end = high_resolution_clock::now();
		duration<double> diff = end - start;
		cout << "\nFailas nuskaitytas per: \a" << diff.count() << "s.\n";
	} catch (std::exception& e) {
		cout << "Ivyko klaida. " << e.what() << endl;
		throw; //Erroras permetamas į funkciją kvietėją. Šiuo atvėju "skaiciuotiRezultatus()" funkciją.
		//Ten bus sugautas tas pats erroras ir nebus vykdoma sekanti dalis kodo, einanti po įvykusios klaidos.
	}
}

deque<mokinys> atskirtiVarg(deque<mokinys> &mokiniai, int kriterijus) {
	deque<mokinys> varg;
	auto start = high_resolution_clock::now();
	auto it = mokiniai.begin();
	while (it != mokiniai.end()) {
		if (kriterijus == 1 ) {
			if ((it->vidurkis * 0.4 + it->egz * 0.6) < 5.0 ) {
				varg.push_back(*it);
				it = mokiniai.erase(it);
			} else {
				it++;
			}
		} else if (kriterijus == 2 ) {
			if ((it->mediana * 0.4 + it->egz * 0.6) < 5.0 ) {
				varg.push_back(*it);
				it = mokiniai.erase(it);
			} else {
				it++;
			}
		} else {
			break;
		}
	}

	auto end = high_resolution_clock::now();
	duration<double> diff = end - start;
	cout << "\nVargsai atskirti nuo kietu per: \a" << diff.count() << "s.\n";
	return varg;
}

//Pagalbinė funkcija, nustatanti mokinio pirmenybę sąraše tarp dviejų mokinių pagal Vardą
bool rikVard(mokinys& i, mokinys& j) {
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
bool rikPavard(mokinys& i, mokinys& j) {
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
void rikiuotiMokinius(deque<mokinys> &mokiniai, int pasirinkimas) {
	auto start = high_resolution_clock::now();
	if (pasirinkimas == 1) {
		//Rikiavimas pagal vardą
		std::sort(mokiniai.begin(), mokiniai.end(), rikVard);
	}
	else if (pasirinkimas == 2) {
		//Rikiavimas pagal pavardę
		std::sort(mokiniai.begin(), mokiniai.end(), rikPavard);
	}
	else {
		//Klaida
		cout << "Ivyko nenumatyta klaida...";
	}

	auto end = high_resolution_clock::now();
	duration<double> diff = end - start;
	cout << "\nKonteineris surikiuotas per: \a" << diff.count() << "s.\n";
}

//Pagrindinė apdorojimo funkcija
void skaiciuotiRezultatus() {
	try {
		deque<mokinys> mokiniai;
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
			deque<mokinys> vargs = atskirtiVarg(mokiniai, vardPavKrit);
			cout << "Pasirinkite rezultatu isvedimo buda:\n1. Isvedimas konsoles lange (v0.2)\n2. Isvedimas i atskirus failus (v0.4)\n: ";
			int isvedKrit = int_ivestis(); //Rezultatų išvedimo kriterijus. Galimi variantai : 1-2
			while (isvedKrit != 1 && isvedKrit != 2) {
				cout << "Negalimas pasirinkimas, pasirinkite is naujo: ";
				isvedKrit = int_ivestis();
			}
			if (isvedKrit == 1) {
				spausdintiMokinius(mokiniai, maxVardIlgis, maxPavardIlgis, vardPavKrit);

			} else if (isvedKrit == 2) {
				isvestiMokinius(vargs, mokiniai, maxVardIlgis, maxPavardIlgis, vardPavKrit);
			} else {
				//Nenumatyta klaida
				cout << "Nenumatyta klaida.\n";
			}
		}
	} catch (std::exception& e) {
		//Kodėl šitas catch blokas tuščias, galbūt paaiškės paskaičius komentarus "skaitytiMokinius" funkcijoje
	}
}
