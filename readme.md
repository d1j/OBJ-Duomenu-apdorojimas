# Duomenų apdorojimas

### Mokinių rezultatų skaičiavimo programa

---

# v0.1

---

## **_Naudojimosi instrukcijos_**

Programą kompiliuoti galima rankiniu būdu arba naudojant **make** komandas.

`make v1` paleis programą, kuri veikia panaudojant C-tipo masyvus.
`make v2` paleis programą, naudojančią `std::vector` konteinerius.

Paleidus programą, atidžiai sekti programos nurodymus.

## **_Pastebėjimai_**

_main_v1.cpp_ faile duomenims saugoti panaudoti C-tipo masyvai. Duomenys apie mokinį saugomi _linked_list'e_, sudarytame iš struktūros `mokinys` (taip, pavadinimas turėtų būti `studentas`, tačiau savo klaidą supratau padaręs v0.3 versiją :D...). Sunkiai paaiškinsiu, kodėl pasirinkau mokinius saugoti _linked_list'e_, tačiau užduotis jau padaryta ir nelabai ką norisi keisti. Struktūra mokinys turi dinaminį pažymių masyvą, kurio reikalauja užduotis.

_main_v2.cpp_ faile duomenims saugoti panaudoti vien tik `std::vector` konteineriai (tiek mokinių masyvas, tiek pažymių masyvai). Pakeitus _linked_list'ą_ ir C masyvus vektoriais, kodas tapo žymiai paprastesnis ir sutrumpėjo 100 eilučių, smagu.

---
