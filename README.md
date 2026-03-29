# TDT4102_Prosjekt
Målet med prosjektet er å forsøke å gjøre realistiske simuleringer av systemer av masser. 
For å oppnå det bruker jeg Newtons gravitasjonslov og en fjerde orden runge kutta metode med variabel steglengde. Dette gjør at i tilfeller der det er store krefter mellom noen av massene vil programmet kjøre saktere for å sikre at energi blir bevart.

Koden er strukterert med en simulasjonsklasse som arver fra animationwindow og håndterer alt av tegning og utregninger. Denne klassen har en standard vektor med punktmasser som arver fra en generell masse-klasse med medlemmene masse, posisjon og hastighet samt neste posisjon og hastighet. Hver masse har også et navn for å gjøre det lettere å skille dem ved debugging.

Simulerings klassen oppdateres i 3 steg:
    1. Regn ut neste posisjon og hastighet for hver masse
    2. Sett posisjon og hastighet til å bære de regnet ut i steget forran for alle masser
        - Her skriver programmet ut nåverende kinetisk, potensiel og total energi i systemet samt bevegelsesmengen, til filen *output/energy.txt*
    3. Tegner et nytt bilde av systemet med en periode på *renderPeriod* millisekunder, denne variabelen er definert i deklarason til 20 ms

For å lage en simulering brukes samme argumenter som for å lage det ønskede animationwindow. Masser legges så til ved bruk av addPointMass eller loadFromFile metodene. 
addPointMass(*argumenter til valgfri point mass konstruktør*):
    variadic template metode som lar en legge til punktmasse ved valgfri konstruktør

loadFromFile(*filepath*):
    tar inn en txt fil der hver linje beskriver en masse på formen **massenavn**, **total masse**, **x posisjon**, **y posisjon**, **x hastighet**, **y hastighet**. hver linje sendes så inn i addPointMass


Det er verdt å merke seg at programmet bruker gravitasjonskonstant $G = 1$ for å minimere sjansen for floating point errors. Dette gjør at enhetene for masse og lengde er forskjellige, jeg har ikke per nå regnet ut alternative enheter. Men like forholdstall vil gi lik oppførsel som med vanlig fysisk $G$.
