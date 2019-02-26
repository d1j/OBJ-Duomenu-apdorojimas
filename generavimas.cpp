#include "generavimas.h"

#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <stdexcept>

#include "funkcijos.h"

using std::cout;
using std::cin;
using std::endl;

void generuoti(std::string pavad, int mokSk, int pazSk) {
	try {
		std::ofstream out("./duomenys/" + pavad);
		if (out.fail()) throw std::runtime_error("Nepavyko sukurti/atidaryti failo. Patikrinkite, ar gerai ivedete pavadinima");
		out << mokSk << " " << pazSk << endl;
		for (int i = 0; i < mokSk; ++i ) {
			out << "Vardas" << gen_reiksm(min_mok_sk, max_mok_sk)
			    << " Pavarde" << gen_reiksm(min_mok_sk, max_mok_sk) << " ";
			for (int j = 0; j < pazSk; ++j) {
				out << gen_reiksm(1, 10) << " ";
			}
			out << gen_reiksm(1, 10) << endl;
		}
		cout << "Failas sekmingai sugeneruotas.\n";
		out.close();
	} catch (std::exception& e) {
		cout << e.what() << endl;
	}
}

void generuotiDuomenis() {
	cout << "DUOMENU GENERAVIMAS\n";
	cout << "noredami nutraukti generavima, bet kada irasykite \"-1\"\n";
	cout << "Iveskite, kiek mokiniu norite sugeneruoti: ";
	int mokSk = int_ivestis();
	while (mokSk != -1 && mokSk < min_mok_sk && mokSk > max_mok_sk) {
		cout << "Ivesta netinkama reiksme. Galimos reiksmes: -1 arba 1-10 000 000\n:";
		mokSk = int_ivestis();
	}
	if (mokSk != -1) {
		cout << "Iveskite, kiek namu darbu pazymiu turi tureti kiekvienas mokinys: ";
		int pazSk = int_ivestis();
		while (pazSk != -1 && pazSk < min_paz_sk && pazSk > max_paz_sk) {
			cout << "Ivesta netinkama reiksme. Galimos reiksmes: -1 arba 1-1000\n:";
			mokSk = int_ivestis();
		}
		if (pazSk != -1) {
			bool pavPower = true;
			std::string pavad;
			while (pavPower) {
				cout << "Iveskite tinkama failo pavadinima (PVZ.: duomenys.txt arba input.in): ";
				cin >> pavad;
				if (pavad != "-1") {
					if (ar_failas_egzistuoja("./duomenys/" + pavad)) {
						//Failas jau egzistuoja
						int perPasirink;
						cout << "Failas nurodytu pavadinimu jau egzistuoja, ar norite perrasyti si faila?\n1.Taip\n2.Ne\n: ";
						perPasirink = int_ivestis();
						while (perPasirink != 1 && perPasirink != 2) {
							cout << "Ivesta negalima reiksme. Iveskite reiksme per naujo: ";
							perPasirink = int_ivestis();
						}
						if (perPasirink == 1) {
							cout << "Failas pavadinimu " << pavad << " bus perrasytas.\n";
							pavPower = false;
						} else {
							cout << "Failas pavadinimu " << pavad << " nebus perrasytas.\n";
						}
					} else {
						//Failas neegzistuoja, galima kurti nauja faila
						pavPower = false;
					}
				} else {
					pavPower = false;
				}
			}
			if (pavad != "-1")
				generuoti(pavad, mokSk, pazSk);
		}
	}
}