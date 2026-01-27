# Projekti: ATM-Pankkiautomaatti

Tämä projekti sisältää sovellukseen kirjautumisen, tilitietojen tarkastelun sekä tilitapahtumien katselun. Ratkaisu on jaettu asiakasohjelmaan (frontend), palvelinsovellukseen (backend) ja tietokantaan.

## Ominaisuudet

### Sisältää
- Käyttäjän tunnistautuminen
- Tilitietojen tarkastelu (saldo)
- Tapahtumien seuranta (tilitapahtumat)
- Kortin valinta (esim. käyttäjän/tilin valinta sovelluksessa)

### Ei sisällä (fyysiset laitteet)
Projektissa on oletuksena huomioitu RFID-lätkä ja lukija, mutta monimuotototeutuksen luonteen vuoksi fyysinen RFID-käyttö on jätetty pois.  
Tunnistautuminen tehdään käyttäjätunnuksella ja PIN-koodilla.

## Käyttäjät ja käyttötapaukset

### Käyttäjäryhmät
**Asiakas**
- Käyttää sovellusta omien tilitietojensa tarkasteluun
- Voi nostaa rahaa omilta tileiltään joihin hänellä on oikeudet(Debit/Credit)

### Keskeiset käyttötapaukset
- Kirjautuminen
- Tilin saldon katselu
- Tapahtumien katselu
- Kortin valinta

## Järjestelmäarkkitehtuuri

Järjestelmä koostuu kolmesta osasta:
- **Asiakasohjelma (Qt-sovellus)**  
- **Palvelinsovellus (REST API)**  
- **Relaatiotietokanta (MySQL)**  

Asiakasohjelma kommunikoi palvelimen kanssa **REST-rajapinnan** kautta.

### Pääkomponentit
- Qt-sovellus (frontend)
- REST API (backend)
- Relaatiotietokanta

## Teknologiat ja työkalut

Projektissa käytetään seuraavia teknologioita ja työkaluja:
- **Node.js** ja **Express** (palvelinpuoli)
- **MySQL** (tietokanta)
- **Qt** (käyttöliittymä)
- **GitHub** (versionhallinta)
- **Postman** (rajapintojen testaus)
- **CSC:n virtuaalikone** (tietokanta-alusta)

## Toiminnalliset vaatimukset

- Järjestelmän tulee mahdollistaa käyttäjän kirjautuminen
- Käyttäjä voi tarkastella tilinsä saldoa
- Käyttäjä voi tarkastella tilitapahtumia
- Järjestelmä käsittelee virheelliset syötteet hallitusti

---
