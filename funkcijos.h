#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include <fstream>
#include "mokinys.h"
#include <exception>
#include <stdexcept>

void spausdintiMokinius(std::vector<mokinys> &mokiniai, int maxVardIlgis, int maxPavardIlgis);

void generuotiPazymius(mokinys &esamas, int pazSk);

//Apsaugota sveikojo skaičiaus įvedimo funkcija.
//Tokia įvestis užtkrina kad į "int" tipo kintamąjį nebus bandoma įrašyti nepalaikomo tipo duomenų
int int_ivestis();

//Pagrindinė įvesties funkcija
//rėžimas == 1 - pažymiu įvestis ranka
//rėžimas == 2 - pažymiu generavimas
void ivestiMokinius(std::vector<mokinys> &mokiniai, int rezimas, int &maxVardIlgis, int &maxPavardIlgis);

void skaitytiMokinius(std::vector<mokinys> &mokiniai, int &maxVardIlgis, int &maxPavardIlgis);

void rikiuotiMokinius(std::vector<mokinys> &mokiniai, int pasirinkimas);

#endif