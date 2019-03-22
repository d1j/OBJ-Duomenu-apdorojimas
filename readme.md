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
Pastaba: Programa sukurta taip, jog į *failo skaitymo* laiką įeina ir n.d. vidurkio bei medianos skaičiavimas, o *išvedimo į failą* laiką įeina galutinio rezultato skaičiavimas.

| Mokinių skaičius | Failo generavimas | Failo skaitymas | Rikiavimas | Išvedimas (į failus) | Viso      |
| ---------------- | ----------------- | --------------- | ---------- | -------------------- | --------- |
| 100              | 0.019736s         | 0.00498s        | 0.003001s  | 0.034002s            | 0.061719s |
| 1000             | 0.041904s         | 0.035984s       | 0.048022s  | 0.079989s            | 0.205899s |
| 10000            | 0.208012s         | 0.29104s        | 0.511567s  | 0.337026s            | 1.347645s |
| 100000           | 2.00921s          | 2.6623s         | 6.64547s   | 3.16874s             | 14.48572s |
| 1000000          | 19.5229s          | 27.1462s        | 79.8309s   | 32.4162s             | 158.9162s |
| 10000000         | std::bad_alloc    | -               | -          | -                    | -         |
Testai atlikti su tokiais parametrais: 
```c++
#define min_paz_sk 1
#define max_paz_sk 20
```
```
mokinių rikiavimas pagal VARDĄ
rezultatų skaičiavimas pagal VIDURKĮ
```

Primityviai mąstant, viso proceso (nuo duomenų generavimo iki duomenų išvedimo) laikas turi kisti tiesiogiai proporcingai didėjant duomenų skaičiui x10, tačiau taip nėra dėl keleto priežasčių:
* kai mokinių skaičius yra nedidelis (100, 1000 ar 10000), viso laiko atžvilgiu duomenų failų ir rezultatų failų sukūrimas užima daugiausia laiko. Todėl ir bendras laikas iš 100 mokinių į 1000 padidėja x3.33 (0.205899s/0.061719s) karto, o iš 1000 į 10000 - x6.54 karto.
* didėjant duomenų skaičiui, laikas, atidarant ir kuriant failus, tampa nereikšmingas, tačiau programos veikimo laikas visgi nedidėja x10 karto; laiko didėjimas tampa ~x11 kartų. Taip greičiausiai yra dėl to, kad naudojamas `std::sort` algoritmas, kurio sudėtingumas yra _O(n log n)_, todėl matome, kad didėjant duomenų skaičiui, rikiavimo trukmė daugmaž didėja x12 kartų. Kadangi rikiavimas užima daugiausia laiko programos veikime, dėl to visos programos veikimo laikas ir keičiasi x11 karto.
* pabandžius sugeneruoti failą su 10 000 000 mokinių, kompiuteris neatlaikė įtampos.

---

# v0.5

---
## **_Naudojimosi instrukcijos_**
Padaręs v0.4 versiją, iššakojau projektą į 3 papildomas šakas: 
* `v0.5/v1.0vector` šakoje įgyvendinta v0.5 versija su `std::vector` konteineriais,
*  `v0.5/v1.0list` šakoje įgyvendinta su `std::list` konteineriais,
*  `v0.5/v1.0deque` šakoje projektas įgyvenditas su `std::deque` konteineriais

`v0.5/v1.0vector` ir `v0.5/v1.0deque` kodas skiriasi tik tuo, kad visur *vector* buvo pakeista į *deque*, tad projektą releasinsiu tik su `std::vector` ir `std::list` konteineriais.

Iš esmės programos funkcionalumas ir naudojimosi taisyklės nepakito, tad, kaip naudotis, žiūrėti į v0.4 ir ankstesnių versijų naudojimosi aprašus.


## **_Pastebėjimai_**

Programa mažai kuo pakito nuo v0.4 versijos. Šiokie tokie pokyčiai matomi v0.5 įgyvendinime su `std::list` konteineriais, kadangi šis konteineris neuturi `[]` "random access" operatoriaus. Todėl teko panaudoti ir pritaikyti `std::iterator` ir `std::next` funkcionalumus.

## **_Analizė_**
Pastaba: Programa sukurta taip, jog į *failo skaitymo* laiką įeina ir n.d. vidurkio bei medianos skaičiavimas, o *išvedimo į failą* laiką įeina galutinio rezultato skaičiavimas. Todėl negalėjau neįskaičiuoti *išvedimo į failus* laiko, kaip prašo užduotis.

| Konteinerio tipas | Failo skaitymas | Rikiavimas | Išvedimas (į failus) | Viso      |
| ----------------- | --------------- | ---------- | -------------------- | --------- |
| std::vector       | 1.16217s        | 2.76823s   | 1.27052s             | 5.20092s  |
| std::list         | 1.99002s        | 0.218764s  | 1.6116s              | 3.820384s |
| std::deque        | 1.16457s        | 4.92085s   | 1.42958s             | 7.515s    |

Testai atlikti su tokiais parametrais: 
```c++
#define min_paz_sk 1
#define max_paz_sk 20
```
```
mokinių rikiavimas pagal VARDĄ
rezultatų skaičiavimas pagal VIDURKĮ
```

Gauti failo skaitymo (į kurį įeina rezultatų dalinis skaičiavimas) ir rezultatų išvedimo laiko rezultatai nenustebino - matomi vietomis šiek tiek reikšmingi, o kai kur visai nereikšmingi pokyčiai, naudojant skirtingus konteinerius. Tačiau keisti pasirodė rikiavimo laiko pokyčiai, kadangi visiems konteineriams naudojau standartines `std::sort` bei `list::sort` rikiavimo funkcijas ir rezultatai neturėjo taip drastiškai skirtis. Greit supratau, kad problema kode: nuo pat pradžių į pagalbines rikiavimui skirtas funkcijas `rikVard` ir `rikPavard` buvo paduodamos kintamųjų kopijos, o perdarydamas kodą su `std::list` gavau klaidą naudodamas tas funkcijas, todėl jas pertvarkiau, kad kintamieji būtų paduodami pagal adresą. 

Rezultatai po klaidos ištaisymo:

| Konteinerio tipas | Failo skaitymas | Rikiavimas | Išvedimas (į failus) | Viso      |
| ----------------- | --------------- | ---------- | -------------------- | --------- |
| std::vector       | 1.15691s        | 0.622723s  | 1.33029s             | 3.109923s |
| std::deque        | 1.11233ss       | 0.798517s  | 1.39263s             | 3.303477s |
| std::list         | 1.99002s        | 0.218764s  | 1.6116s              | 3.820384s |

Išvados: 
* Mano programos veikimo atžvilgiu naudingiausia naudoti `std::vector` konteinerį, kadangi šis konteineris stipriai pranoksta `std::list`, kuomet duomenys po vieną pridedami į konteinerio galą (failo skaitymas) arba yra vienas po kito pasiekiami (iteruojami) ir naudojami (išvedimas į failus, rezultatų skaičiavimas). Panašius rezultatus šioj srity parodo `std::deque`, tačiau `std::vector` pastarąjį pranoksta rikiavime, kuris trunka mažiau greičiausia dėl konteinerio adresų paskyrimo. Kiek supratau, `std::vector` konteineris paskiria vieną nuoseklų gabalą atminties RAM'e, o `std::deque` paskiria atmintį atskirais gabalais, kurie gali būti išmėtyti po atmintį skirtingose vietose. Todėl rikiuojant greičiau nustatoma `std::vector` elemento vieta atminty, negu `std::deque`
* Nors ir `std::list` vienareikšmiškai greičiausias duomenų rikiavime, jo naudoti neapsimoka, nes duomenys turi kažkaip atsidurt konteineryje, o matyti, jog `std::list` nėra geriausias sprendimas tą padaryti.
* `std::list` pranoksta kitus konteinerius rikiavime, dėl to, kad adresų išdėstymo struktūra kardinaliai skiriasi: `std::list` dažniausiai implementuojamas kaip *doubly-linked list'as*, todėl elementai yra išmėtyti po atmintį ir yra tarpusavy susieti nuorodomis į gretimų elementų adresus. Šis skirtumas leidžia elementus apkeisti pakeičiant adresų sąsajas, o `std::vector` ir `std::deque` reikia perkopijuoti visą elementų informaciją, nes keisti adresų negalime dėl griežtos konteinerių struktūros.

---

# v1.0

---
## **_Naudojimosi instrukcijos_**

Man atrodo, kad kurti ir vėliau peržiūrėti atskirus 6 releasus bus nepatogu ir painu, todėl jų nekursiu.

Pirmos strategijos kodą galima peržiūrėti klonuojant repozitoriją ir nuėjus į "branch'ą" pavadinimu `v1.0_1strat`. Jame nueiti į commitų "log'ą" ir atitinkamai susirasti norimą commitą pagal komentarus. Šiame "branch'e" "commit'inau" tokia eilės tvarka: kodas su std::list -> kodas su std::vector -> kodas su std::deque

Antros strategijos kodą taip pat galima peržiūrėti klonuojant repozitoriją ir nuėjus į "branch'ą" pavadinimu `v1.0_2strat`. Jame nueiti į commitų "log'ą" ir atitinkamai susirasti norimą commitą pagal komentarus. Šiame "branch'e" "commit'inau" tokia eilės tvarka: kodas su std::list -> kodas su std::vector -> kodas su std::deque

## **_Pastebėjimai_**
* Supratau, kad norint atlikti kuo tikslesnį laiko matavimą, reikia pašalinti visus nereikalingus "background'o" procesus ir tuos pačius bandymus atlikti keletą kartų, išvestį rezultatų vidurkį. Tą supratęs perspėju, kad tiek praetų versijų rezultatai tiek tolimesni rezultatai gali būti iškraipyti "muzikos klausymosi naudojantis youtube" ir kitokių pašalinių veiklų. Tolimesnius bandymus stengiausi atlikti neapkraunant kompiuterio pašaliniais procesais.
* v0.5 versijos failo skaitymo laikas tarp `std::list` ir kitų konteinerių drastiškai skiriasi dėl kodo dalies, kur yra pasiekiamas paskutinis pažymių konteinerio narys tam, kad jo reikšmę prilygint egzamino pažymio reikšmei. 
* ```c++
  //kodas, kurį naudojau su std::list konteineriais
  esamas.egz = *--esamas.pazym.end();
  //kodas, kurį naudojau su std::vector konteineriais
  esamas.egz = esamas.pazym[esamas.pazym.size() - 1];
  ```
 * Išbandęs `std::list` kodą su `std::vector` konteineriais, pastebėjau, kad ir su `std::vector` duomenų įrašymas trunka tiek pat, kiek ir su `std::list`. Vadinasi tokiu būdu pasiekti paskutinį listo elementą - neefektyvu. Pagooglinau ir supratau, kad egzistuoja list::back metodas, kurį ir reikįjo naudoti šiuo atvėju
