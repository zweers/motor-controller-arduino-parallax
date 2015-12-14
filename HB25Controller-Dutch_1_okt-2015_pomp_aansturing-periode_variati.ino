
/*
Arduino code for PWM driven motorcontroller Parallax HB25

version: 7 okt 2015

developer:

Wout Zweers 
www.woutzweers.nl
zweers@dds.nl
tel +(31)623020257

Functie :

Sturen van de juiste signalen naar de motorcontroller (parallax HB25) welke de snelheid van een 12V-gelijkstroommotor regelt.
Een potmeter maakt het mogelijk de motorsnelheid realtime te varieren terwijl de motor draait

Werking:

De parallax motorcontroller vertaalt een pulslengte in een voltage tussen -12V en +12V voor de motor.
Deze puls wordt door een Arduino geleverd.
De pulslengte wordt ingesteld door in de code (de Arduino sketch) de gewenste pulslengtes aan te geven en deze te uploaden naar de Arduino.
De potmeter voltage wordt ingelezen door de Arduino en deze waaarde varieert de wachttijden biunnen de arduino sketch. 
Effectief wordt hiermee de periode van de golf veranderd

Details:

Een puls met een lengte tussen 1000 en 2000 microsec. wordt verwacht door de Parallax driver, 
Deze puls wordt gegenereerd door met de sketch de digitale uitgang (pin digital8) van laag naar hoog (1) te brengen. 
Na de benodigde pulstijd wordt de uitgang weer op laag (0) gezet.
Dit resulteert in een puls naar de Parallax driver van gewenste lengte welke naar de motorcontroller wordt gestuurd.
Tussen de pulsen is een korte tijd nodig om de flanken van de puls goed te kunnen onderscheiden. Minimaal ongeveer 20 microsec. is nodig.
Zie ook de doc van de driver op de Parallax site: https://www.parallax.com/product/29144

Pulslengte:

De pulslengte bepaalt richting en snelheid de snelheid aan:

1000 millisec is maximaal achteruit, 
1500 is neutraal, 
2000 is max. vooruit

(in de code kan iets afwijking nodig zijn ivm vertraging in het circuit, bv tussen 1020 en 1980) 

Golfvorm genereren:

Voor de juiste golf is een wateraanvoer (debiet) nodig wat niet constant is (varierende omhullende = envelope). 
De omhullende (envelope) van de curve wordt in dit programma weergegeven door opeenvolgende snelheidsstappen, met een ingestelde lengte (delay),
de motor houdt de opgegeven snelheid aan tot het volgende commando. Hierdoor kan een getrapt snelheid - tijd profiel worden gemaakt.
Uit experimenten blijkt dat hoog debiet in het begin, dan iets lager debiet, en daarna pomp op neutraal (uit) zetten de beste werking geeft. 
Als de pomp uit staat (pulslengte = 1500) loopt het water door de pomp terug oiv zwaartekracht. 
De pomprichting om te keren (= leegzuigen) heeft bij de hier gebruikte centrifugaal dompelpompjes geen effect 


Periode aanpassen:

De periode van de golf kan op meerdere manieren worden gevarieerd:
-door tussen de afzonderlijke waarden van de curve evenredig korter of langer te pauzeren.
-door de potmeter te verdraaien
-door meer of minder herhalingen van pulscommando's binnen het programma (de sketch)

De cyclustijd van het programma (de periode) wordt voornamelijk bepaald door de pauzetijd en het aantal herhalingen hiervan. 
Met de potmeter verbonden aan ingang A0 kan deze pauzetijd (wachtTijd)worden gevarieerd. 

De rekentijd is gering in vergelijking met de pauzetijd, maar de verhouding is niet constant.  
Calibratie van de periode is hierom noodzakelijk. 

Het circuit:

  board: arduino uno, optioneel: shield, 
  potmeter 10K
  controller: parallax25
  voeding: 12 V= bijv velleman labvoeding 30V5A
  optioneel: een 5V voeding voor de arduino zodat de arduino zonder usb voeding kan werken en geen laptop meer nodig is (nadat het programma geupload is)
  
  Verbinden shield: 
  
  Steek het shield op de arduino
 
  Potmeter aansluiten:
  Verbind met analoog 0 (A0) op het shield met 4-aderige flat cable   
  (of zonder shield: direct op gnd, 5V en signaal naar analoogInput(0))
  
  zie ook: http://www.seeedstudio.com/wiki/GROVE_-_Starter_Kit_v1.1b#Grove_-_Rotary_Angle_Sensor
  
 Verbind de motorcontroller:
  
  gebruik een jumpoer wire (3 of 4 polig)
  pin 8 van de Arduino aan W op de Parallax controller;   
  pin GND aan B
  R, J: not connected (knip kabeltje af)
  
Verbind de pompen: 
  Sluit de dompelpompjes parallel aan aan de M1 en M2 contacten op de Parallax.
 (de driver is geschikt voor alle gelijkstroommotoren tot 12V, 25A)
  
  Verbind de 12V voeding (minimaal 5 Ampere) aan de motorcontroller + en - contacten. 
  Gebruik minimaal 0.5 mm2 kabel ivm stroomsterkte. 
  tape de connectors af om kortsluiting te voorkomen
  
Hardware:

-Pompjes:

Barwich Tauchpumpe. centrifugaal dompelpomp (voor gebruik in campers ed), 
12V=, 12 l/minuut, 0,6 bar. Max opgenomen Amperage ongeveer 2A / pomp
leverancier: diverse, oa camperwebshop,
http://www.camperwebshop.nl/shop/dompelpompen/135/dompelpompje-12v-12-liter.html

-Motorcontroller: 

Parallax HB-25 motor controller
https://www.parallax.com/product/29144
leverancier:
Parallax (goedkoper)of Antratek
https://www.parallax.com/product/29144
https://www.antratek.nl/hb-25-motor-controller?gclid=CL-r7Ojsr8gCFUrpwgodprQA2A

-Arduino:

Arduino Uno
https://www.arduino.cc/en/Main/ArduinoBoardUno
leverancier: leverbaar oa via Conrad en Antratek, maar vele andere leveranciers zijn mogelijk
https://www.antratek.nl/arduino-uno
https://www.conrad.nl/nl/arduino-uno-development-board-092024.html?WT.mc_id=google&insert=8J&gclid=CJXGg9Hwr8gCFScTwwodT_0Edg&WT.srch=1

-Shield: 

Grove-base shield v1.2
http://www.seeedstudio.com/wiki/Grove_-_Base_Shield_v1.2Seeed shield 
leverancier: oa Antratek:
https://www.antratek.nl/grove-base-shield-v2-for-arduino

-Potmeter: 
10K draaipotmeter, geschikt voor gebruik op shield
http://www.seeedstudio.com/wiki/GROVE_-_Starter_Kit_v1.1b#Grove_-_Rotary_Angle_Sensor

Antratek en vele andere leveranciers:

-Jumper wire:(om de potmeter aan te sluiten)
flat cable 4-wire 
http://www.seeedstudio.com/depot/Grove-Universal-4-Pin-20cm-Unbuckled-Cable-5-PCs-Pack-p-749.html

-Jumper wire tussen Parallax driver en Arduino:
https://www.antratek.nl/jumper-wire-0-1-4-pin-12

-Optional 5V power supply for Arduino
https://www.antratek.nl/12v-power-supply

*/

#define SERVO_PIN 8     // bepaal dat pin 8 naam krijgt: SERVO_PIN

int wachtTijd = 500;    // initialisatie
int sensorPin = A0;     // select the input pin for the potentiometer
int sensorValue = 128;  // variable to store the value coming from the sensor, tussen 0 en 255 (afhankelijk van type arduino 255 (mini), 1024 (uno, mega), 8 of 10 bit resolutie)


void setup() 
{
 
  pinMode(SERVO_PIN, OUTPUT); // bepaal dat SERVO_PIN output pin is
 
}


void loop() {

// read the value from the sensor:
  sensorValue = analogRead(sensorPin);
    // waarden sensor tussen 0 en 255
    
  wachtTijd = sensorValue/4 + 40; // eenheid: millisec. 
  
    // Grotere deler (waardes tussen 1 en 10 zijn praktisch) geeft meer gevoeligheid maar inder bereik van potmeter. 
    // eventueel 30 a 40 bij optellen bij wachtTijd om onregelmatig lopende motor te voorkomen bij korte programma doorlooptijden. Bij lange doorlooptijd snelheden mag deze offset 0 worden
    // deelwaarde is ook afhankelijk van aantal trapjes. Bij veel trapjes is een kortere wachttijd en daarvoor hogere deelwaarde zinvol
    // in neutrale stand is het zinvol om een aantal keer te wachten na laatste puls van 1500 ms zodat het water door de motor terug kan stromen. Zelfde aantal keer wachten als aantal stapjes is goed uitgangspunt
  
     rotate();

  delay(1);
}

void rotate() 

// maak een getrapte snelheids envelope van het gewenste pompsnelheid (dit bepaalt het pompdebiet)
// wacht tussen elke afzonderlijke stap (wachtTijd) en varieer dit om de totale periode te varieren

{
   
 
// de pomp gebruikt alleen de positieve voltages, terugstromen gebeurt tijdens stilstand van de pomp oiv zwaartekracht
// motor aansluitingen ompolen of waardes tussen 1500 en 2000 gebruiken indien pomp verkeerd om draait 
  

 // dit is een enkele stap in de snelheids envelope
 
  digitalWrite(SERVO_PIN, HIGH);   // start puls
  delayMicroseconds(1050);         // bepaal pulslengte, pas de waarde van delayMicroseconds aan om pomp sneller of langzamer te laten draaien
  digitalWrite(SERVO_PIN, LOW);    // beeindig puls
  delayMicroseconds(20);           // duur van LOW tussen pulsen moet groter zijn dan ongeveer 20 microsec om een duidelijke flank aan de puls te krijgen
 
  delay(wachtTijd);              
  
  // eventueel meerdere stapjes hieronder invoegen
  
  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(1150); // pas deze waardes evt aan
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(20);  
  
  delay(wachtTijd);

  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(1300); // pas deze waardes evt aan
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(20);     
 
    delay(wachtTijd);

  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(1300); // pas deze waardes evt aan
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(20);     
 delay(wachtTijd);
 
 
  
  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(1500); // de motor wordt nu stopgezet
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(20);  
  
  delay(wachtTijd);
  
   digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(1800); // pas deze waardes evt aan
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(20);  
  
  delay(wachtTijd);

  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(1800); // pas deze waardes evt aan
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(20);     
 
    delay(wachtTijd);

  digitalWrite(SERVO_PIN, HIGH);
  delayMicroseconds(1980); // pas deze waardes evt aan
  digitalWrite(SERVO_PIN, LOW);
  delayMicroseconds(20);     
 delay(wachtTijd);
    
// hieronder een extra delaytijd invoegen om voldoende terugstroomtijd te hebben
// totaal ongeveer zelfde aantal keren delay als trapjes < 1500 is goed uitgangspunt.
// dit is ook afhankelijk van de opvoerhoogte van het water
// uitproberen!
    

// delay(wachtTijd);
// delay(wachtTijd);
  
  
  

}

