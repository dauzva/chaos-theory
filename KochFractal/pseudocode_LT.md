# Algoritmas: Kocho kreivė



### Pseudokodas

```pseudo
FUNKCIJA atnaujintiKochTaskus
    // 1 žingsnis: Išvalyti esamus Koch taškus
    IŠVALYTI kochTaskus

    // 2 žingsnis: Gauti drobės geometriją (stačiakampį, kuriame bus piešiama Koch kreivė)
    GAUTI drobės stačiakampį 'rect'
    GAUTI stačiakampio koordinates (ax, ay) ir matmenis (aw, ah) iš 'rect'

    // 3 žingsnis: Inicijuoti pradžios ir pabaigos taškus Koch kreivei
    PRIDĖTI pradžios tašką (ax, 2*(ay+ah)/3) į kochTaskus
    PRIDĖTI pabaigos tašką (ax+aw, 2*(ay+ah)/3) į kochTaskus

    // Išsaugoti dabartinius taškus 'issaugotiKochTaskai' būsimiems iteracijoms
    issaugotiKochTaskai = kochTaskus

    // 4 žingsnis: Jei iteracijų lygis ne 0, pritaikyti Koch skaidymą
    JEI iteracijuLygis ≠ 0 TADA
        KARTOTI j NUO 0 IKI iteracijuLygis - 1
            // Kiekvienai naujai iteracijai išvalyti kochTaskus
            IŠVALYTI kochTaskus
            
            // 5 žingsnis: Iteruoti per kiekvieną linijos segmentą 'issaugotiKochTaskai'
            KARTOTI i NUO 0 IKI dydis(issaugotiKochTaskai) - 2
                p = issaugotiKochTaskai[i]  // pradžios taškas
                PRIDĖTI p į kochTaskus  // pridėti dabartinį tašką

                p1 = issaugotiKochTaskai[i + 1]  // sekantis taškas sekoje
                linija = LINIJA(p, p1)  // sukurti liniją tarp p ir p1

                // 6 žingsnis: Apskaičiuoti taškus, reikalingus linijai padalinti į 4 segmentus
                linija1 = LINIJA(p, taškas ties 1/3 linijos)  // pirmasis trečdalis linijos
                linija21 = LINIJA(taškas ties 1/3, vidurio taškas)  // linija nuo 1/3 iki vidurio taško
                linija22 = normalinė vektoriaus kryptis ties 2/3 linijos  // normalinis vektorius ties 2/3 linijos

                // Sukurti Koch trikampio viršūnę
                virsune = TAŠKAS(linija21.p2.x + linija22.p2.x - linija1.p2.x, linija21.p2.y + linija22.p2.y - linija1.p2.y)
                linija2 = LINIJA(linija1.p2, virsune)  // linija į viršūnę
                linija3 = LINIJA(virsune, taškas ties 2/3 linijos)  // linija nuo viršūnės iki 2/3 linijos
                linija4 = LINIJA(taškas ties 2/3, p1)  // paskutinysis trečdalis linijos

                // 7 žingsnis: Pridėti apskaičiuotus taškus į kochTaskus
                PRIDĖTI linija1.p2 į kochTaskus (du kartus)
                PRIDĖTI linija2.p2 į kochTaskus (du kartus)
                PRIDĖTI linija3.p2 į kochTaskus (du kartus)
                PRIDĖTI linija4.p2 į kochTaskus
            
            // 8 žingsnis: Po visų segmentų apdorojimo, atnaujinti issaugotiKochTaskai su naujais taškais
            PAKEISTI issaugotiKochTaskai dydį iki kochTaskus dydžio
            issaugotiKochTaskai = kochTaskus
        PABAIGTI KARTOTI
    PABAIGTI JEI
PABAIGTI FUNKCIJA
```