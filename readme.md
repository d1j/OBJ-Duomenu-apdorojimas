### Mokinių rezultatų skaičiavimo programa

---

**PERSPĖJIMAS!!!**

Kadangi _readme.md_ ir _makefile_ v0.1 - v0.4 versijoms kūriau tas visas versijas įgyvendinęs, _readme.md_ failuose gali būt "balaganas".

**readme.md** failas daugiausia informacijos apie ankstesnes versijas turės **"master branch'e"**. Readme failuose, pateiktuose su releasais, gali trūkti informacijos arba gali pasitaikyti klaidingos informacijos.

**Nagrinėjant skirtingus releasus, patartina naudotis tik šituo readme failu.**

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
- Duomenų failo pavadinimas privalo būti _duomenys.txt_ (tolimesnėse versijose failo pavadinimas galės būti bet koks).
- Duomenys turi būti griežtai struktūrizuoti (pavyzdys _duomenys.txt_ faile).

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

Duomenų failo formatas išlieka toks pats kaip v0.2 versijoje, tačiau failo pavadinimas gali keistis. Programoje reikia nurodyti failo pavadinimą.

## **_Pastebėjimai_**

_main_v2.cpp_ failo funkcijos ir struktūra buvo išskaidyta į atskirus failus. Nuo šiol _main_v2.cpp_ yra tik main funkcija, kurioje paprastas išorinių funkcijų manipuliavimas; _funkcijos.cpp_ faile laikomos pagrindinės funkcijos, kurių pagalba apdorojami duomenys; Į _mokinys.h_ buvo perkelta struktūra `mokinys`, o struktūros metodai laikomi _mokinys.cpp_ faile.

Panaudoti `try-catch` blokai, kurie nuo šiol gelbėja programą nuo "crashinimo" skaičiuojant vidurkius, medianas bei skaitant duomenų failus.

Patobulintas _makefile_ pagal "tutorialą" [šioje svetainėje](http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/).

---

# v0.4

---

## **_Naudojimosi instrukcijos_**

Programą kompiliuojame komandos `make` (arba `make main`) pagalba. Paleidus programą, sekti instrukcijas.

Programos vykdymui būtini `\duomenys` bei `\rezultatai` folderiai. **Šių folerių netrinti!**

Folderyje `\duomenys` saugomi duomenų failai, tad, testuojant programą, failus kelti čia. Rezultatus rasite folderyje `\rezultatai`. _PASTABA: nurodant rezultatų failo pavadinimą, nurodyti reikia tik failo vardą, programa automatiškai parenka .txt formatą (įvedus pavadinimą "rez" bus segeneruojami failai "rez_kiet.txt" ir "rez_varg.txt")_.

Generuojant duomenų failus pagal `2. Generuoti duomenis` bus sugeneruotas jusų nurodytas skaičius mokinių, su pažymiais, kurių kiekis skiriasi nuo 1 iki 20 (Pavyzdys `\duomenys\100.txt` faile). _PASTABA: norint generuoti daugiau pažymių, reikia keisti programos kodą faile `generavimas.h`_.

**Failas `\duomenys\100.txt` greičiausiai neveiks dėl platformų skirtumo, todėl patariama jo nenaudoti.**

Nuo šios versijos atsiranda galimybė ranka suvestus duomenis išsaugoti rezultatų failuose.

## **_Pastebėjimai_**

- _main_v2.cpp_ pervadintas į _main.cpp_. Pasikeitė _main.cpp_ struktūra;
- nuo šiol `make` kompiliuoja failą pavadinimu _main.exe_;
- _funkcijos.h_ faile aprašomos bendros funkcijos (įvesties, skaičių generavimo, failų egzistavimo tikrinimo ir t.t.), naudojamos visuose failuose.
- _apdorojimas.cpp_ faile randasi didžioji dalis funkcijų, skirtų mokinių rezultatų apdorojimui (Kai kurios skaičiavimo funkcijos yra struktūros `mokinys` metodai, saugomi *mokinys.cpp* faile)
- _generavimas.h_ aprašyta funkcija, kurios pagalba galime sugeneruoti duomenų failus.
- pamiršau padaryt galimybę vartotojui nurodyti, kiek daugiausia pažymių mokinys gali turėti (defaultinės reikšmės: min-1; max-20).

## **_Analizė_**

| Mokinių skaičius | Failo generavimas | Failo skaitymas | Rikiavimas | Išvedimas (į failą) | Viso      |
| ---------------- | ----------------- | --------------- | ---------- | ------------------- | --------- |
| 100              | 0.019736s         | 0.00498s        | 0.003001s  | 0.034002s           | 0.061719s |
| 1000             | 0.041904s         | 0.035984s       | 0.048022s  | 0.079989s           | 0.205899s |
| 10000            | 0.208012s         | 0.29104s        | 0.511567s  | 0.337026s           | 1.347645s |
| 100000           | 2.00921s          | 2.6623s         | 6.64547s   | 3.16874s            | 14.48572s |
| 1000000          | 19.5229s          | 27.1462s        | 79.8309s   | 32.4162s            | 158.9162s |
| 10000000         | std::bad_alloc    | -               | -          | -                   | -         |
Testai atlikti su tokiais parametrais: 
```c++
#define min_paz_sk 1
#define max_paz_sk 20
```

Primityviai mąstant, viso proceso (nuo duomenų generavimo iki duomenų išvedimo) laikas turi kisti tiesiogiai proporcingai didėjant duomenų skaičiui x10, tačiau taip nėra dėl keleto priežasčių:
* kai mokinių skaičius yra nedidelis (100, 1000 ar 10000), viso laiko atžvilgiu duomenų failų ir rezultatų failų sukūrimas užima daugiausia laiko. Todėl ir bendras laikas iš 100 mokinių į 1000 padidėja x3.33 (0.205899s/0.061719s) karto, o iš 1000 į 10000 - x6.54 karto.
* didėjant duomenų skaičiui, laikas, atidarant ir kuriant failus, tampa nereikšmingas, tačiau programos veikimo laikas visgi nedidėja x10 karto; laiko didėjimas tampa ~x11 kartų. Taip greičiausiai yra dėl to, kad naudojamas `std::sort` algoritmas, kurio sudėtingumas yra _O(n log n)_, todėl matome, kad didėjant duomenų skaičiui, rikiavimo trukmė daugmaž didėja x12 kartų. Kadangi rikiavimas užima daugiausia laiko programos veikime, dėl to visos programos veikimo laikas ir keičiasi x11 karto.
* pabandžius sugeneruoti failą su 10 000 000 mokinių, kompiuteris neatlaikė įtampos.