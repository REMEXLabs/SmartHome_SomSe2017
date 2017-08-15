# RemactUI
Dieses Projekt enthält das User Interface der **RemAct** Smart Home Application. 

RemAct, **R**emind and **A**ct, ist ein passives und non-invasives System, dass älteren und bedürftigen Menschen bei ihren täglichen Problemen unterstützt. Ziel ist, die Menschen an etwaige Aufgaben zu erinnern und primär das Sicherheitsgefühl zu erhöhen. Ebenfalls soll das System an gezielten und mit Regeln definierten Stellen aktiv eingegriffen.

> Die Implementierung des Basissystems von RemAct auf Basis von openhabian ist unter [remact-openhabianpi](https://github.com/pfecht/remact-openhabianpi/) verfügbar.

> Das Projekt wurde im Rahmen der Smart Home Veranstaltung im Master Computer Science and Media an der Hochschule der Medien in Stuttgart entwickelt.

## Getting Started
1. Klone das Projekt und intalliere die dependencies mittels `npm install`.
2. Starte mit `ng serve` den dev server auf `http://localhost:4200/`.

## Technologien
Die Anwendung basiert auf:

1. [Angular](https://angular.io) und dem [angular-cli](https://github.com/angular/angular-cli) zur Projektverwaltung. 
2. [Angular Material](https://material.angular.io/) als Framework für UI Komponenten.
3. der Rest Schnittstelle von OpenHAB zur Kommunikation mit dem Basissystem. 
4. [OpenAPE](#openape) zur Anpassung der UI an die Bedürfnisse der User. 

## OpenAPE
Die UI nutzt ebenfalls [OpenAPE](https://github.com/REMEXLabs/OpenAPE), um die Usability den Bedürfnissen der Nutzer anzupassen. Eine beispielhafte Konfiguration ist in der [openape.json](https://github.com/pfecht/remact-ui/blob/master/openape-data.json). Ebenfalls interessant an dieser Stelle ist der [openape.service](https://github.com/pfecht/remact-ui/blob/master/src/app/shared/openape.service.ts), der die Konfiguration vom OpenAPE Server abruft und verarbeitet.

> Anmerkung: Leider scheint der [Development-Server](http://dev.openape.gpii.eu:8080/) von OpenAPE nicht mehr erreichbar zu sein (12.07.2017).

## Build und Deployment
Bauen der Anwendung: `npm run build:prod`.

Deployen der Anwendung auf einen openhabian im lokalen Netz mit:  
`rsync -az ./dist/ openhabian@openhabianpi:/etc/openhab2/html`.

## Unit Tests und Ende-zu-Ende Tests
Führe `ng test` für Unit Tests mit [Karma](https://karma-runner.github.io) aus.

Führ `ng e2e` für End-to-end Tests mit [Protractor](http://www.protractortest.org/) aus.

## Contributors

* Maximilian Bischoff ([@MaxBischoff](https://github.com/MaxBischoff))
* Philipp Joseph ([@pjwj](https://github.com/pjwj))
* Pirmin Rehm ([@pirminrehm](https://github.com/pirminrehm))
