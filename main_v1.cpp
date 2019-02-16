#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <random>

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::setw;

struct mokinys {
	mokinys *next = nullptr; //rodyklė į sekantį linked listo mazgą
	string vardas = "";
	string pavarde = "";
	//Šitoj versijoj pažymių masyvas, kaip dalis "mokinys" struktūros yra nebūtina,
	//Tačiau tą supratau jau parašęs programą, tad palieku viską taip, kaip yra.
	int *pazym = nullptr; //būsimas dinaminis namų darbų masyvas
	int n = 0; //namų darbų pažymių skaičius
	int masDydis = 0;
	int egz = 0; //egzamino pažymys
	double vidurkis = 0;
	double mediana = 0;

	void spausdintiInfo(int kriterijus, int maxVardIlgis, int maxPavardIlgis) {
		cout << setw(maxVardIlgis + 2) << std::left << vardas << setw(maxPavardIlgis + 2) << pavarde;
		switch (kriterijus) {
		case 1:
			cout << std::setprecision(2) << std::fixed << setw(16) << vidurkis << endl;
			break;
		case 2:
			cout << std::setprecision(2) << std::fixed << mediana << endl;
			break;
		default:
			cout << "Sveikinu, jums pavyko sugadinti programa.";
			break;
		}
	}

	void pridetiPazym(int naujasPaz) {
		if (n != 0) {
			//Nepirmas pažymys
			if (n + 1 <= masDydis) {
				//masyvo dydžio keisti nereikia
				pazym[n] = naujasPaz;
				n++;
			}
			else {
				//reikia keisti masyvo dydį
				masDydis *= 2;
				int *naujasMas = new int[masDydis];
				for (int i = 0; i < n; i++) {
					naujasMas[i] = pazym[i];
				}
				naujasMas[n] = naujasPaz;
				delete[] pazym;
				pazym = naujasMas;
				n++;
			}
		}
		else {
			//Pirmas pažymys
			pazym = new int[1] { naujasPaz };
			n++;
			masDydis++;
		}
		for (int i = 0; i < n; i++) {
			cout << pazym[i] << " ";
		} cout << endl;
	}

	void skaiciuotiVidurki() {
		//Jei yra bent vienas pažymys
		if (n > 0) {
			int suma = 0;
			for (int i = 0; i < n; i++) {
				suma += pazym[i];
			}
			vidurkis = (0.4 * suma / n) + (0.6 * egz);
		}
	}

	void skaiciuotiMediana() {
		//Jei yra bent vienas pažymys
		if (n > 0) {
			//Prieš skaičiavimą išrikiuojame masyvo elementus didėjimo tvarka.
			int pap;
			for (int i = 0; i < n - 1; i++) {
				for (int j = 0; j < n - i - 1; j++) {
					if (pazym[j] > pazym[j + 1]) {
						pap = pazym[j];
						pazym[j] = pazym[j + 1];
						pazym[j + 1] = pap;
					}
				}
			}
			//Nustatome mediana
			if (n % 2 == 1) {
				//Nelyginis skaičius pažymiu
				mediana = pazym[(n - 1) / 2];
			}
			else {
				//Lyginis skaičius pažymiu
				mediana = 1.0 * (pazym[n / 2 - 1] + pazym[n / 2]) / 2;
			}
		}
	}
};

void pridetiMokini(mokinys *&pirm, mokinys *&pask, mokinys naujas) {
	if (pirm) {
		//Nepirmas mokinys sąraše
		pask->next = new mokinys;
		pask = pask->next;
		*pask = naujas;
	}
	else {
		//Pirmas mokinys sąraše
		pirm = new mokinys;
		*pirm = naujas;
		pask = pirm;
	}
}

void spausdintiMokinius(mokinys *pirm, int kriterijus, int maxVardIlgis, int maxPavardIlgis) {
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
	mokinys *t = pirm;
	while (t) {
		t->spausdintiInfo(kriterijus, maxVardIlgis, maxPavardIlgis);
		t = t->next;
	}
}

void generuotiPazymius(mokinys &esamas, int pazSk) {
	//Kodo gabaliukas paimtas iš interneto
	static std::random_device rd; //atsitiktinis įrenginys
	static std::mt19937 mt(rd()); //atsitiktinių skaičių generavimo variklis
	static std::uniform_int_distribution<int> dist(1, 10); //intervalas, kuriame generuojame skaičius

	for (int i = 0; i < pazSk; i++) {
		esamas.pridetiPazym(dist(mt));
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
	return kint;
}

//Pagrindinė įvesties funkcija
//rėžimas == 1 - pažymiu įvestis ranka
//rėžimas == 2 - pažymiu generavimas
void ivestiMokinius(mokinys *&pirm, mokinys *&pask, int rezimas, int &maxVardIlgis, int &maxPavardIlgis) {
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
			esamas.n = 0;
			esamas.masDydis = 0;
			esamas.pazym = nullptr;
			esamas.egz = 0;
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
							esamas.pridetiPazym(pazymys);
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
				pridetiMokini(pirm, pask, esamas);
				mokSk++;
			}
		}
	} while (esamas.vardas != "-" && esamas.pavarde != "-");
}

//Funkcija išvalo linked listą ir kiekvieno mazgo pažymių masyvą
void isvalytiAtminti(mokinys *&pirm) {
	if (pirm) {
		mokinys *esamas = pirm;
		while (esamas) {
			delete[] pirm->pazym;
			pirm = esamas->next;
			delete esamas;
			esamas = pirm;
		}
	}
}

int main() {
	//*pirm - linked listo pirmas narys
	//*pask - linked listo paskutinis narys
	mokinys *pirm = nullptr, *pask = nullptr;
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
		ivestiMokinius(pirm, pask, 1, maxVardIlgis, maxPavardIlgis);
		break;
	case 2:
		ivestiMokinius(pirm, pask, 2, maxVardIlgis, maxPavardIlgis);
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
	spausdintiMokinius(pirm, vertKrit, maxVardIlgis, maxPavardIlgis);
	isvalytiAtminti(pirm);
}