# Duomenų apdorojimas

### Mokinių rezultatų skaičiavimo programa

---

# v0.1

---

## **_Naudojimosi instrukcijos_**

Kompiliuoti programą galima rankiniu būdu arba naudojant **make** komandas.

`make v1` sukompiliuos programą, kuri veikia panaudojant C-tipo masyvus.
`make v2` sukompiliuos programą, naudojančią `std::vector` konteinerius.

Paleidus programą, atidžiai sekti programos nurodymus.

## **_Pastebėjimai_**

_main_v1.cpp_ faile duomenims saugoti panaudoti C-tipo masyvai. Duomenys apie mokinį saugomi _linked_list'e_, sudarytame iš struktūros `mokinys` (taip, pavadinimas turėtų būti `studentas`, tačiau savo klaidą supratau padaręs v0.3 versiją :D...). Sunkiai paaiškinsiu, kodėl pasirinkau mokinius saugoti _linked_list'e_, tačiau užduotis jau padaryta ir nelabai ką norisi keisti. Struktūra mokinys turi dinaminį pažymių masyvą, kurio reikalauja užduotis.

_main_v2.cpp_ faile duomenims saugoti panaudoti vien tik `std::vector` konteineriai (tiek mokinių masyvas, tiek pažymių masyvai). Pakeitus _linked_list'ą_ ir C masyvus vektoriais, kodas tapo žymiai paprastesnis ir sutrumpėjo 100 eilučių, smagu.

---

# v0.2

---

## **_Naudojimosi instrukcijos_**

Paleisti programą galima sukompiliavus _main_v2.cpp_ ranka arba naudojant `make` (arba `make v2`) komandą.

Šioje versijoje pridėtas duomenų skaitymo iš failo funkcionalumas.

- Skaitomas failas turi būti toje pačioje direktorijoje kaip ir vykdoma programa.
- Duomenų failo pavadinimas privalo būti `duomenys.txt` (tolimesnėse versijose failo pavadinimas galės būti bet koks).
- Duomenys turi būti griežtai struktūrizuoti (pavyzdys `duomenys.txt faile`).

Duomenų failo formatas:

- Pirmas skaičius - mokinių skaičius.
- Antras skaičius - skaičius, nurodantis, kiek namų darbų pažymių turi kiekvienas mokinys.
- Sekančiose eilutėse surašyti duomenys apie mokinius.

> 4 5
> Vardas1 Pavarde1 8 9 10 6 10 9
> Vardas2 Pavarde2 7 10 8 5 5 6
> Vardas3 Pavarde3 8 9 10 6 10 9
> Vardas4 Pavarde4 1 10 8 5 4 6

## **_Pastebėjimai_**

Iš naudojimosi instrukcijų savaime aišku, jog duomenų skaitymas iš failo nėra nei patogus, nei lankstus, tačiau daugelį problemų išsprendžiau ir įvestį patobulinau vėlesnėse projekto versijose.

Šioje versijoje atsiranda galimybė rikiuoti mokinius pagal jų vardus arba pavardes.

---

# v0.3

---

## **_Naudojimosi instrukcijos_**

Nuo šios versijos patogiausia programą kompiliuoti naudojant komandą `make` (arba `make v2`).
