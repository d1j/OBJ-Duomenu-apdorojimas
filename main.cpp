#include <iostream>
#include <exception>

#include "apdorojimas.h"
#include "generavimas.h"
#include "funkcijos.h"

int main()
{
	bool power = true;
	int pasirink = -1;
	while (power)
	{
		std::cout << "\n--Mokiniu rezultatu skaiciavimo programa--" << std::endl
				  << "Pasirinkite ka norite daryti:\n1. Skaiciuoti mokiniu rezultatus\n2. Generuoti duomenis\n3. Iseiti\n: ";
		pasirink = int_ivestis();
		while (pasirink < 1 || pasirink > 3)
		{
			std::cout << "Blogas pasirinkimas, iveskite pasirinkima is naujo: ";
			pasirink = int_ivestis();
		}
		switch (pasirink)
		{
		case 1:
			skaiciuotiRezultatus();
			break;
		case 2:
			generuotiDuomenis();
			break;
		case 3:
			power = false;
			break;
		default:
			std::cout << "Nenumatyta klaida." << std::endl;
			break;
		}
	}
	return 0;
}
